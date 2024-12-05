#include "coreapi.h"    // VeySicKのコア
#include "lexer.h"      // VeySicKのレキサー
#include "parser.h"     // VeySicKのパーサー
#include "random.h"     // 乱数
#include "sound.h"      // 音
#include "renum.h"      // RENUM
#include "draw.h"       // DRAW
#include "turtle.h"     // CMD TURTLE
#include <stack>        // For std::stack
#include <array>        // For std::array
#include <sys/stat.h>   // For std::stat
#include <cfenv>        // 浮動小数点数の例外を扱う

VskLineNo vsk_iLine = 0;            // 字句解析時の行番号
VskColumnNo vsk_target_column = 0;  // ターゲットの桁番号
VskLineNo vsk_target_line = -1;     // ターゲットの行番号
bool vsk_in_data = false;           // DATA文の内部か？

#define VSK_ERROR_AND_RETURN(errcode, ...) do { \
    vsk_machine->do_error(errcode); \
    return __VA_ARGS__; \
} while (0)

#define VSK_SYNTAX_ERROR_AND_RETURN(...) \
    VSK_ERROR_AND_RETURN(VSK_ERR_SYNTAX, ##__VA_ARGS__)

#ifdef _WIN32
    #define VSKAPI __stdcall
#else
    #define VSKAPI
#endif

// 命令を実行する関数の型
typedef VskAstPtr (VSKAPI *VskFn)(VskAstPtr self, const VskAstList& args);

// トラップモード
enum VskTrapMode
{
    VSK_TRAP_MODE_OFF = 0,
    VSK_TRAP_MODE_ON,
    VSK_TRAP_MODE_STOP,
};

// トラップ情報
struct VskTrapInfo
{
    VskTrapMode m_mode = VSK_TRAP_MODE_OFF;
    VskIndexList m_index_list;
    bool m_catching = false;
    bool m_trapping = false;

    bool is_enabled() const
    {
        return m_mode != VSK_TRAP_MODE_OFF;
    }

    bool signal()
    {
        if (!m_trapping)
        {
            m_catching = true;
            return true;
        }
        return false;
    }

    void reset()
    {
        m_mode = VSK_TRAP_MODE_OFF;
        m_index_list.clear();
        m_catching = m_trapping = false;
    }
};

// トラップの種類
enum VskTrapType
{
    VSK_TRAP_STOP,
    VSK_TRAP_HELP,
    VSK_TRAP_COM,
    VSK_TRAP_PEN,
    VSK_TRAP_PLAY,
    VSK_TRAP_TIME,
    VSK_TRAP_F1,
    VSK_TRAP_F2,
    VSK_TRAP_F3,
    VSK_TRAP_F4,
    VSK_TRAP_F5,
    VSK_TRAP_F6,
    VSK_TRAP_F7,
    VSK_TRAP_F8,
    VSK_TRAP_F9,
    VSK_TRAP_F10,
    VSK_TRAP_MOUSE_LEFT_PRESS,
    VSK_TRAP_MOUSE_RIGHT_PRESS,
    VSK_TRAP_MOUSE_LEFT_RELEASE,
    VSK_TRAP_MOUSE_RIGHT_RELEASE,
    VSK_TRAP_MOUSE_MOVE,
    VSK_TRAP_MAX,
};

// インデックスリストを文字列に
VskString vsk_to_string(const VskIndexList& indices)
{
    VskString ret = "{ ";

    bool first = true;
    for (auto& index : indices)
    {
        if (first)
        {
            first = false;
            ret += vsk_to_string(index);
        }
        else
        {
            ret += ", ";
            ret += vsk_to_string(index);
        }
    }

    ret += " }";
    return ret;
}

// ループの種類
enum VSK_LOOP_TYPE
{
    VSK_LOOP_TYPE_WHILE,
    VSK_LOOP_TYPE_WEND,
    VSK_LOOP_TYPE_FOR,
    VSK_LOOP_TYPE_NEXT,
};

// ループ情報
struct VskLoopInfo
{
    VSK_LOOP_TYPE m_type;
    VskAstList m_exprs;
    std::vector<VskIndexList> m_paths;
};

// 時刻文字列を得る
VskString vsk_get_time(void)
{
    std::time_t t = std::time(nullptr);
    std::tm *ptime = std::localtime(&t);
    if (!ptime)
    {
        vsk_machine->bad_call();
        return nullptr;
    }

    assert(0 <= ptime->tm_hour && ptime->tm_hour < 24);
    assert(0 <= ptime->tm_min && ptime->tm_min < 60);
    assert(0 <= ptime->tm_sec && ptime->tm_sec <= 60);

    char buf[256];
    std::sprintf(buf, "%02u:%02u:%02u", ptime->tm_hour, ptime->tm_min, ptime->tm_sec);
    assert(std::strlen(buf) < 256);
    return buf;
}

// インデックスリストの比較
int vsk_index_list_compare(const VskIndexList& x, const VskIndexList& y)
{
    const size_t min_ = std::min(x.size(), y.size());

    for (size_t i = 0; i < min_; ++i)
    {
        if (x[i] < y[i])
            return -1;
        if (x[i] > y[i])
            return +1;
    }

    if (x.size() < y.size())
        return -1;
    if (x.size() > y.size())
        return +1;
    return 0;
}

// ランダムファイルのフィールド
struct VskFieldEntry
{
    int             m_fileno    = 0;
    VskAstPtr       m_lvalue    = nullptr;
    int             m_field_len = 0;
};

struct VskIndexListLess
{
    bool operator()(const VskIndexList& x, const VskIndexList& y) const
    {
        return vsk_index_list_compare(x, y) < 0;
    }
};

// インデックスリストからループ情報への写像
typedef std::map<VskIndexList, VskLoopInfo, VskIndexListLess> VskLoopMap;

// ラベル名からジャンプ先のインデックスリストへの写像
typedef std::map<VskString, VskIndexList> VskLabelMap;

// コードの種類。インデックスリストの先頭に付く
#define I_DIRECT_CODE   0
#define I_PROGRAM_CODE  1

// マウスボタンの種類
enum VskMouseButton
{
    VSK_MOUSE_NONE = 0,
    VSK_MOUSE_LEFT_PRESS,
    VSK_MOUSE_RIGHT_PRESS,
    VSK_MOUSE_LEFT_RELEASE,
    VSK_MOUSE_RIGHT_RELEASE,
    VSK_MOUSE_MAX
};

// machine detailed implementation
struct VskMachineImpl
{
    // コンストラクタ
    VskMachineImpl();
    // デストラクタ
    virtual ~VskMachineImpl();

    // 文の集合
    std::set<INSN_TYPE> m_stmt_set;
    // 直接実行用のデータ
    VskAstPtr m_direct_code;
    // プログラム実行用のデータ
    VskAstPtr m_program_code;
    // 現在のコントロールパス（インデックスリスト）
    VskIndexList m_control_path;
    // 停止中のコントロールパス
    VskIndexList m_stopping_path;
    // 現在のDATAの読み込み位置（インデックスリスト）
    VskIndexList m_data_pointer;
    // コントロールパスのスタック
    std::stack<VskIndexList> m_path_stack;
    // トラップのスタック
    std::stack<VskTrapType> m_trap_type_stack;
    // 命令の種類から関数への写像
    std::unordered_map<INSN_TYPE, VskFn> m_insn_to_fn;
    // ラベルから行番号への写像
    std::unordered_map<VskString, VskLineNo> m_label_to_line_numbers;
    // インデックスリストから行番号への写像
    std::map<VskIndexList, VskLineNo, VskIndexListLess> m_index_list_to_line_number;
    // プログラムリストのテキスト
    VskString m_program_text;
    // インデックスリストからループ情報への写像
    VskLoopMap m_loop_map;
    // ラベル名（または行番号）からジャンプ先のインデックスリストへの写像
    VskLabelMap m_label_map;
    // 直接実行のテキスト
    VskString m_target_line_text;
    // 現在の行
    VskLineNo m_current_line = 0;
    // DEF FNの情報
    std::map<VskString, VskIndexList> m_fn_to_path;
    // トラップ情報
    VskTrapInfo m_traps[VSK_TRAP_MAX];
    // トラップ時刻
    VskString m_trap_time;
    bool m_time_trapped = false;
    // エラートラップ時の移動先
    VskTrapInfo m_error_trap;
    // ライトペン入力
    bool m_pen_pressed = false;
    int m_pen_x = -1;
    int m_pen_y = -1;
    // マウス入力
    bool m_mouse_inited = false;
    std::array<int, VSK_MOUSE_MAX> m_mouse_x = { 0 };
    std::array<int, VSK_MOUSE_MAX> m_mouse_y = { 0 };
    std::array<bool, VSK_MOUSE_MAX> m_mouse_pressed = { 0 };
    // トレース
    bool m_trace_on = false;
    // 出力
    VskFilePtr m_printing_device = nullptr;
    VskAstList m_printing_items = { };
    bool m_printing_is_write = false;
    // BEEP待ち
    bool m_beep_waiting = true;
    // AUTO文情報
    bool m_auto_mode = false;
    VskLineNo m_auto_line_number = 0;
    VskLineNo m_auto_step = 0;
    // DRAW
    VskDrawEngine m_draw_engine;
    std::vector<VskDrawItem> m_draw_items;
    // CMD TURTLE
    VskTurtleEngine m_turtle_engine;
    std::vector<VskTurtleItem> m_turtle_items;
    // PLAY / CMD PLAY
    bool m_play_bgm = true; // CMD BGM (PLAY / CMD PLAY / CMD SINGを並列動作モードにするか？)
    // ランダムファイルのフィールド表
    std::vector<VskFieldEntry> m_field_table;
    // Sleepが終わるまで待つための変数
    VskDword m_sleep_start = 0;
    VskDword m_sleep_amount = 0;
    VskIndexList m_after_sleep_path;
    // 初期化
    void init();
};

// タートルが表示されているか？
bool vsk_turtle_shown(void)
{
    return VSK_IMPL()->m_turtle_engine.m_is_shown;
}

// タートルの位置を返す
VskPointI vsk_turtle_pos_in_view(void)
{
    return VSK_IMPL()->m_turtle_engine.m_last_point_in_view;
}

// タートルの向きを返す
VskSingle vsk_turtle_direction_in_radian(void)
{
    return VSK_IMPL()->m_turtle_engine.get_turtle_direction_in_radian();
}

//////////////////////////////////////////////////////////////////////////////

// フィールドを追加
bool vsk_field_add(VskAstPtr lvalue, int fileno, int field_len)
{
    lvalue = vsk_lvalue_optimize(lvalue, -(VSK_STATE()->m_option_base == 1));

    for (auto& entry : VSK_IMPL()->m_field_table)
    {
        if (entry.m_fileno == fileno && entry.m_lvalue->compare(lvalue.get()) == 0)
        {
            entry.m_field_len = field_len;
            return true;
        }
    }

    VSK_IMPL()->m_field_table.push_back({ fileno, lvalue, field_len });
    return true;
}

// フィールドを探す
VskFieldEntry *vsk_field_find(VskAstPtr lvalue)
{
    lvalue = vsk_lvalue_optimize(lvalue, -(VSK_STATE()->m_option_base == 1));

    for (auto& entry : VSK_IMPL()->m_field_table)
    {
        if (entry.m_lvalue->compare(lvalue.get()) == 0)
        {
            return &entry;
        }
    }

    return nullptr;
}

// フィールドの長さ or レコードの長さを取得
int vsk_field_get_len(int fileno, int field_index = -1)
{
    int index = 0, record_len = 0;
    for (auto& entry : VSK_IMPL()->m_field_table)
    {
        if (entry.m_fileno == fileno)
        {
            if (field_index == -1)
            {
                record_len += entry.m_field_len;
            }
            else if (index == field_index)
            {
                return entry.m_field_len;
            }
            ++index;
        }
    }

    if (VSK_SETTINGS()->m_field_width == 0)
        VSK_SETTINGS()->m_field_width = 256;

    if (VSK_SETTINGS()->m_field_width != -1)
        record_len = VSK_SETTINGS()->m_field_width;

    return record_len;
}

// レコ―ドにフィールド文字列を格納
bool vsk_field_store(int fileno, VskString& bin)
{
    int record_len = vsk_field_get_len(fileno);
    bin.resize(record_len, ' ');

    int index = 0;
    for (auto& entry : VSK_IMPL()->m_field_table)
    {
        if (entry.m_fileno == fileno)
        {
            VskString field_str;
            if (!vsk_str(field_str, entry.m_lvalue))
                return false;
            if (int(field_str.size()) < entry.m_field_len)
                field_str.resize(entry.m_field_len, ' ');
            if (index + entry.m_field_len > record_len)
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, false);
            std::memcpy(&bin[index], field_str.c_str(), entry.m_field_len);
            index += entry.m_field_len;
        }
    }
    return true;
}

// レコ―ドからフィールド文字列を取得
bool vsk_field_fetch(int fileno, const VskString& bin)
{
    int record_len = vsk_field_get_len(fileno);
    assert(record_len == bin.size());
    if (record_len != bin.size())
        return false;

    int index = 0;
    for (auto& entry : VSK_IMPL()->m_field_table)
    {
        if (entry.m_fileno == fileno)
        {
            VskString field_str(entry.m_field_len, ' ');
            std::memcpy(&field_str[0], &bin[index], entry.m_field_len);
            if (!vsk_var_assign(entry.m_lvalue, vsk_ast_str(field_str)))
                return false;
            index += entry.m_field_len;
        }
    }

    return true;
}

// フィールドを閉じる
void vsk_field_close(int fileno)
{
    if (fileno == -1)
    {
        VSK_IMPL()->m_field_table.clear();
        return;
    }

    for (size_t index = VSK_IMPL()->m_field_table.size(); index > 0; )
    {
        --index;
        auto& entry = VSK_IMPL()->m_field_table[index];
        if (entry.m_fileno == fileno)
            VSK_IMPL()->m_field_table.erase(VSK_IMPL()->m_field_table.begin() + index);
    }
}

//////////////////////////////////////////////////////////////////////////////

// トラップをクリアする
void vsk_clear_trap(void)
{
    for (auto& trap : VSK_IMPL()->m_traps)
        trap.reset();

    VSK_IMPL()->m_trap_time.clear();
    VSK_IMPL()->m_time_trapped = false;
    VSK_IMPL()->m_error_trap.reset();
}

// コマンドレベルへ入る
void vsk_enter_command_level(bool show_ok)
{
    if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_COMMAND)
        return;

    vsk_clear_trap();

    VSK_IMPL()->m_printing_device = nullptr;
    VSK_IMPL()->m_printing_items.clear();

    if (VSK_STATE()->m_caret_x != 0)
        vsk_machine->line_feed();

    if (show_ok)
        vsk_machine->print("Ok \n");

    VSK_STATE()->m_wait_for = VSK_WAIT_FOR_COMMAND;
    VSK_STATE()->m_show_text = true;
}

// インデックスリストを解決する
VskAstPtr vsk_resolve_index_list_0(VskAstPtr tree, const VskIndexList& indices)
{
    VskAstPtr node = tree;
    for (size_t idx : indices) {
        if (!node || idx >= node->size()) {
            return nullptr;
        }
        node = (*node)[idx];
    }
    return node;
}

// インデックスリストを解決する
VskAstPtr vsk_resolve_index_list(VskIndexList indices)
{
    if (indices.empty())
        return nullptr;
    auto front = indices.front();
    indices.pop_front();
    if (front == I_DIRECT_CODE)
        return vsk_resolve_index_list_0(VSK_IMPL()->m_direct_code, indices);
    if (front == I_PROGRAM_CODE)
        return vsk_resolve_index_list_0(VSK_IMPL()->m_program_code, indices);
    return nullptr;
}

// 次のコントロールパス。
// 参照: https://github.com/katahiromz/tree_path
VskIndexList vsk_next_control_path_0(VskAstPtr tree, VskIndexList indices)
{
    if (!tree) {
        return {};
    }

    if (indices.empty() && tree->size() > 0 && tree->is_multi()) {
        return {0};
    }

    VskAstPtr node = vsk_resolve_index_list_0(tree, indices);
    if (!node) {
        return {};
    }

    if (node->size() > 0 && node->is_multi()) {
        indices.push_back(0);
        return indices;
    }

    while (!indices.empty()) {
        size_t last_index = indices.back();
        indices.pop_back();

        VskAstPtr parent_node = vsk_resolve_index_list_0(tree, indices);
        if (parent_node->is_multi() && last_index + 1 < parent_node->size()) {
            indices.push_back(last_index + 1);
            return indices;
        }
    }

    return indices;
}

// 次のコントロールパスを計算する
VskIndexList vsk_next_control_path(VskIndexList indices)
{
    // インデックスリストが空なら、次のインデックスリストも空
    if (indices.empty()) {
        return {};
    }

    // 最初のインデックスは特別扱い
    auto front = indices.front();
    indices.pop_front();

    if (front == I_DIRECT_CODE) // 直接コード
    {
        indices = vsk_next_control_path_0(VSK_IMPL()->m_direct_code, indices);
    }
    else if (front == I_PROGRAM_CODE) // プログラムコード
    {
        indices = vsk_next_control_path_0(VSK_IMPL()->m_program_code, indices);
    }
    else // その他はあり得ない
    {
        assert(0);
    }

    // 削った最初のインデックスを元に戻す
    if (indices.size())
        indices.push_front(front);

    return indices;
}

// 一つ次のデータポインタを計算する
VskIndexList vsk_next_data_pointer_0(VskAstPtr tree, VskIndexList indices)
{
    if (!tree) {
        return {};
    }

    if (indices.empty() && tree->size() > 0 && (tree->is_multi() || tree->is_data())) {
        return {0};
    }

    VskAstPtr node = vsk_resolve_index_list_0(tree, indices);
    if (!node) {
        return {};
    }

    if (node->size() > 0 && (node->is_multi() || node->is_data())) {
        indices.push_back(0);
        return indices;
    }

    while (!indices.empty()) {
        size_t last_index = indices.back();
        indices.pop_back();

        VskAstPtr parent_node = vsk_resolve_index_list_0(tree, indices);
        if ((parent_node->is_multi() || parent_node->is_data()) && last_index + 1 < parent_node->size()) {
            indices.push_back(last_index + 1);
            return indices;
        }
    }

    return indices;
}

// 一つ次のデータポインタを計算する
VskIndexList vsk_next_data_pointer(VskIndexList indices)
{
    // インデックスリストが空なら、次のインデックスリストも空
    if (indices.empty()) {
        return {};
    }

    // 最初のインデックスは特別扱い
    auto front = indices.front();
    indices.pop_front();

    if (front == I_DIRECT_CODE) // 直接コード
    {
        indices = std::move(vsk_next_data_pointer_0(VSK_IMPL()->m_direct_code, indices));
    }
    else if (front == I_PROGRAM_CODE) // プログラムコード
    {
        indices = std::move(vsk_next_data_pointer_0(VSK_IMPL()->m_program_code, indices));
    }
    else // その他はあり得ない
    {
        assert(0);
    }

    // 削った最初のインデックスを元に戻す
    if (indices.size())
        indices.push_front(front);

    return indices;
}

// 次の行を取得する
VskIndexList vsk_get_next_line_path(VskIndexList indices)
{
    for (;;)
    {
        indices = vsk_next_control_path(indices);
        if (indices.empty())
            return indices;
        VskAstPtr node = vsk_resolve_index_list(indices);
        if (node->m_program_line != -1)
            return indices;
    }
}

// プログラムデータが必要か？
void vsk_want_program_data(VskAstPtr node, bool& wanted)
{
    if (!node)
        return;

    if (node->is_multi() || node->is_if_then())
    {
        for (size_t index = node->is_if_then(); index < node->size(); ++index)
        {
            vsk_want_program_data(node->at(index), wanted);
            if (wanted)
                return;
        }
        return;
    }

    switch (node->m_insn)
    {
    case INSN_GOTO:
    case INSN_GOSUB:
    case INSN_RUN:
    case INSN_READ:
    case INSN_CONT:
    case INSN_ON_EXPR_GOTO:
    case INSN_ON_EXPR_GOSUB:
        wanted = true; // 必要です！
        break;
    default:
        break;
    }
}

// ラベル情報をスキャンする
VskError vsk_scan_label_info_0(VskAstPtr node, const VskIndexList& indices, VskLabelMap& map)
{
    if (!node)
        return VSK_NO_ERROR;

    // 行番号がもしあれば、セット
    if (node->m_program_line != -1)
    {
        map[vsk_to_string(node->m_program_line)] = indices;
        VSK_IMPL()->m_index_list_to_line_number[indices] = node->m_program_line;
    }

    if (node->is_multi() || node->is_if_then())
    {
        VskIndexList clone = indices;
        for (size_t index = node->is_if_then(); index < node->size(); ++index)
        {
            clone.push_back(index);
            VskError error = vsk_scan_label_info_0(node->at(index), clone, map);
            if (error)
                return error;
            clone.pop_back();
        }
        return VSK_NO_ERROR;
    }

    if (node->m_insn == INSN_LABEL_DEF) // ラベルの定義か？
    {
        map[node->m_str] = indices;
    }

    return VSK_NO_ERROR;
}

// ラベル情報をスキャンする
VskError vsk_scan_label_info(VskAstPtr code, VskLabelMap& label_map)
{
    return vsk_scan_label_info_0(code, { I_PROGRAM_CODE }, label_map);
}

// ループ情報をスキャンする
VskError vsk_scan_loop_info_0(VskAstPtr node, const VskIndexList& indices, VskLoopMap& map)
{
    if (!node)
        return VSK_NO_ERROR;

    if (node->is_multi() || node->is_if_then())
    {
        VskIndexList clone = indices;
        for (size_t index = node->is_if_then(); index < node->size(); ++index)
        {
            clone.push_back(index);
            VskError error = vsk_scan_loop_info_0(node->at(index), clone, map);
            if (error)
                return error;
            clone.pop_back();
        }
        return VSK_NO_ERROR;
    }

    switch (node->m_insn)
    {
    case INSN_WHILE:
        {
            VskLoopInfo loop_info;
            loop_info.m_type = VSK_LOOP_TYPE_WHILE;
            loop_info.m_exprs.push_back(node->at(0));
            loop_info.m_paths.push_back(indices);
            map[indices] = loop_info;
        }
        break;
    case INSN_WEND:
        {
            VskLoopInfo loop_info;
            loop_info.m_type = VSK_LOOP_TYPE_WEND;
            loop_info.m_paths.push_back(indices);
            VskIndexList max_;
            for (auto& pair : map)
            {
                if (pair.second.m_type == VSK_LOOP_TYPE_WHILE && pair.second.m_paths.size() == 1)
                {
                    if (max_ < pair.first)
                        max_ = pair.first;
                }
            }
            if (max_.empty())
                return VSK_ERR_WEND_WITHOUT_WHILE;
            map[max_].m_paths.push_back(indices);
            loop_info.m_paths.push_back(max_);
            loop_info.m_exprs.push_back(map[max_].m_exprs[0]);
            map[indices] = loop_info;
        }
        break;
    case INSN_FOR:
        {
            VskLoopInfo loop_info;
            loop_info.m_type = VSK_LOOP_TYPE_FOR;
            loop_info.m_exprs.push_back(node->at(0));
            loop_info.m_exprs.push_back(node->at(1));
            loop_info.m_exprs.push_back(node->at(2));
            loop_info.m_exprs.push_back(node->at(3));
            loop_info.m_paths.push_back(indices);
            map[indices] = loop_info;
        }
        break;
    case INSN_NEXT:
        {
            VskLoopInfo loop_info;
            loop_info.m_type = VSK_LOOP_TYPE_NEXT;
            loop_info.m_paths.push_back(indices);
            for (size_t iarg = 0; iarg == 0 || iarg < node->size(); ++iarg)
            {
                auto arg0 = (node->size() ? node->at(iarg) : nullptr);
                VskIndexList max_;
                for (auto& pair : map)
                {
                    if (pair.second.m_type == VSK_LOOP_TYPE_FOR && pair.second.m_paths.size() == 1)
                    {
                        if (!arg0 || arg0->compare(pair.second.m_exprs[0].get()) == 0)
                        {
                            if (max_ < pair.first)
                                max_ = pair.first;
                        }
                    }
                }
                if (max_.empty())
                    return VSK_ERR_NEXT_WITHOUT_FOR;
                map[max_].m_paths.push_back(indices);
                loop_info.m_paths.push_back(max_);
                assert(map[max_].m_exprs.size() == 4);
                loop_info.m_exprs.insert(loop_info.m_exprs.end(), map[max_].m_exprs.begin(), map[max_].m_exprs.end());
            }
            map[indices] = loop_info;
        }
        break;
    default:
        break;
    }

    return VSK_NO_ERROR;
}

// ループ情報をスキャンする
VskError vsk_scan_loop_info_1(VskAstPtr node, const VskIndexList& indices, VskLoopMap& map)
{
    if (!node)
        return VSK_NO_ERROR;

    if (node->is_multi() || node->is_if_then())
    {
        VskIndexList clone = indices;
        for (size_t index = node->is_if_then(); index < node->size(); ++index)
        {
            clone.push_back(index);
            VskError error = vsk_scan_loop_info_1(node->at(index), clone, map);
            if (error)
                return error;
            clone.pop_back();
        }
        return VSK_NO_ERROR;
    }

    switch (node->m_insn)
    {
    case INSN_WHILE:
        {
            auto it = map.find(indices);
            assert(it != map.end());
            if (it->second.m_paths.size() != 2)
                return VSK_ERR_WHILE_WITHOUT_WEND;
        }
        break;
    case INSN_FOR:
        {
            auto it = map.find(indices);
            assert(it != map.end());
            if (it->second.m_paths.size() != 2)
                return VSK_ERR_FOR_WITHOUT_NEXT;
        }
        break;
    default:
        break;
    }

    return VSK_NO_ERROR;
}

// ループ情報をスキャンする
VskError vsk_scan_loop_info(VskAstPtr node, const VskIndexList& indices, VskLoopMap& map)
{
    VskError error = vsk_scan_loop_info_0(node, indices, map);
    if (error)
        return error;
    error = vsk_scan_loop_info_1(node, indices, map);
    return error;
}

// プログラムリストをスキャンする
VskError vsk_scan_program_list(void)
{
    VSK_IMPL()->m_label_map.clear();

    VskError error;
    error = vsk_parse_program(VSK_IMPL()->m_program_text, VSK_IMPL()->m_program_code);
    if (error)
    {
        return error;
    }

    error = vsk_scan_label_info(VSK_IMPL()->m_program_code, VSK_IMPL()->m_label_map);
    if (error)
    {
        return error;
    }

    error = vsk_scan_loop_info(VSK_IMPL()->m_program_code, { I_PROGRAM_CODE }, VSK_IMPL()->m_loop_map);
    if (error)
    {
        return error;
    }

    return VSK_NO_ERROR;
}

// ダイレクトモードのデータをスキャンする。必要ならばプログラムデータもスキャンする
VskError vsk_scan_direct_data(VskAstPtr data)
{
    VSK_IMPL()->m_loop_map.clear();

    VskError error;

    bool wanted = false;
    vsk_want_program_data(data, wanted);
    if (wanted)
    {
        error = vsk_scan_program_list();
        if (error)
            return error;
    }

    error = vsk_scan_loop_info(data, { I_DIRECT_CODE }, VSK_IMPL()->m_loop_map);
    if (error)
        return error;

    return VSK_NO_ERROR;
}

// STOP (Ctrl+C)を処理する
void vsk_stop(void)
{
    VSK_IMPL()->m_traps[VSK_TRAP_STOP].signal();
}

// HELPを処理する
void vsk_help(void)
{
    VSK_IMPL()->m_traps[VSK_TRAP_HELP].signal();
}

// ライトペンを処理する
void vsk_pen(int x, int y, bool pressed)
{
    if (VSK_IMPL()->m_traps[VSK_TRAP_PEN].m_trapping)
        return;

    VSK_IMPL()->m_pen_pressed = pressed;
    if (pressed)
    {
        VSK_IMPL()->m_pen_x = x;
        VSK_IMPL()->m_pen_y = y;
        VSK_IMPL()->m_traps[VSK_TRAP_PEN].signal();
    }
}

// マウスを処理する
bool vsk_mouse(int x, int y, int left, int right)
{
    if (VSK_STATE()->m_screen_height == 200)
        y /= 2;

    VSK_IMPL()->m_mouse_x[VSK_MOUSE_NONE] = x;
    VSK_IMPL()->m_mouse_y[VSK_MOUSE_NONE] = y;

    if (left > 0)
    {
        VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_PRESS].signal();
        VSK_IMPL()->m_mouse_x[VSK_MOUSE_LEFT_PRESS] = x;
        VSK_IMPL()->m_mouse_y[VSK_MOUSE_LEFT_PRESS] = y;
        VSK_IMPL()->m_mouse_pressed[VSK_MOUSE_LEFT_PRESS] = true;
    }
    else if (left < 0)
    {
        VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_RELEASE].signal();
        VSK_IMPL()->m_mouse_x[VSK_MOUSE_LEFT_RELEASE] = x;
        VSK_IMPL()->m_mouse_y[VSK_MOUSE_LEFT_RELEASE] = y;
        VSK_IMPL()->m_mouse_pressed[VSK_MOUSE_LEFT_PRESS] = false;
    }
    else if (right > 0)
    {
        VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_PRESS].signal();
        VSK_IMPL()->m_mouse_x[VSK_MOUSE_RIGHT_PRESS] = x;
        VSK_IMPL()->m_mouse_y[VSK_MOUSE_RIGHT_PRESS] = y;
        VSK_IMPL()->m_mouse_pressed[VSK_MOUSE_RIGHT_PRESS] = true;
    }
    else if (right < 0)
    {
        VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_RELEASE].signal();
        VSK_IMPL()->m_mouse_x[VSK_MOUSE_RIGHT_RELEASE] = x;
        VSK_IMPL()->m_mouse_y[VSK_MOUSE_RIGHT_RELEASE] = y;
        VSK_IMPL()->m_mouse_pressed[VSK_MOUSE_RIGHT_PRESS] = false;
    }
    else
    {
        VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_MOVE].signal();
    }

    return VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_MOVE].is_enabled() ||
           VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_PRESS].is_enabled() ||
           VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_PRESS].is_enabled() ||
           VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_RELEASE].is_enabled() ||
           VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_RELEASE].is_enabled();
}

// 行テキストから行番号を取得する
VskLineNo vsk_line_number_from_line_text(const VskString& line, char **endptr)
{
    if (line.empty())
        return 0;

    auto number = std::strtoul(&line[0], endptr, 10);
    if (endptr && **endptr == ' ')
        ++(*endptr);

    return VskLineNo(number);
}

// 行テキストからラベルを取得する
VskString vsk_label_from_line_text(const VskString& line)
{
    char *endptr;
    auto number = vsk_line_number_from_line_text(line, &endptr);
    if (!number)
        return "";

    // 空白を読み捨てる
    while (*endptr == ' ' || *endptr == '\t')
        ++endptr;

    // アスタリスク(*)を確認
    if (*endptr != '*')
        return "";
    ++endptr;

    // 空白を読み捨てる
    while (*endptr == ' ' || *endptr == '\t')
        ++endptr;

    VskString name;
    while (vsk_isalnum(*endptr) || *endptr == '.')
    {
        name += *endptr;
        ++endptr;
    }

    return name;
}

// 指定した行番号の前後の行を取得する
VskString vsk_get_next_line_text(const VskString& text, VskLineNo number, int which)
{
    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, text, "\n");

    // 各行について
    VskString ret;
    for (auto& line : lines)
    {
        // 行テキストから行番号を取得する
        VskLineNo line_number = vsk_line_number_from_line_text(line);
        if (line_number == 0)
            continue;

        if (which < 0)
        {
            if (line_number < number)
                ret = line;
            else
                break;
        }
        else if (which > 0)
        {
            if (line_number > number)
            {
                ret = line;
                break;
            }
        }
        else
        {
            if (line_number == number)
            {
                ret = line;
                break;
            }
        }
    }

    return ret;
}

// 指定した行番号の前後の行を取得する
VskString vsk_get_next_line_text(VskLineNo number, int which)
{
    return vsk_get_next_line_text(VSK_IMPL()->m_program_text, number, which);
}

// ページアップ
void vsk_page_up(void)
{
    if (VSK_STATE()->m_edit_mode)
    {
        vsk_machine->edit_up();
    }
    else
    {
        vsk_machine->scroll_up();
        vsk_machine->move_to_top();
    }
}

// ページダウン
void vsk_page_down(void)
{
    if (VSK_STATE()->m_edit_mode)
    {
        vsk_machine->edit_down();
    }
    else
    {
        vsk_machine->scroll_down();
        vsk_machine->move_to_bottom();
    }
}

// ラベル名から行番号への写像を取得する
void vsk_get_label_to_line_numbers(const VskString& text, std::unordered_map<VskString, VskLineNo>& map)
{
    map.clear();

    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, text, "\n");

    // 各行について
    for (auto& line : lines)
    {
        // 行テキストから行番号を取得する
        VskLineNo line_number = vsk_line_number_from_line_text(line);
        if (line_number == 0)
            continue;
        // 行テキストからラベルを取得する
        VskString label_name = vsk_label_from_line_text(line);
        if (label_name.empty())
            continue;
        // 大文字にする
        vsk_upper(label_name);

        map[label_name] = line_number;
    }
}

// 特定の行番号の行テキストを取得
VskString vsk_get_program_line_text(VskLineNo line_no)
{
    if (line_no > 0)
    {
        // 前後の空白を除去
        mstr_trim(VSK_IMPL()->m_program_text, " \t\r\n");

        // 行に分ける
        std::vector<VskString> lines;
        mstr_split(lines, VSK_IMPL()->m_program_text, "\n");

        // 範囲内の行を出力
        for (auto& line : lines)
        {
            // 行テキストから行番号を取得する
            VskLineNo number = vsk_line_number_from_line_text(line);
            if (!number)
                continue;
            if (number == line_no)
                return line;
        }
    }

    return VSK_IMPL()->m_target_line_text;
}

// BEEP音を鳴らす
void vsk_beep(int number)
{
    vsk_sound_stop();
    vsk_sound_beep(number);
    if (number == -1)
        VSK_IMPL()->m_beep_waiting = true;
}

// エラーを処理する
bool vsk_error(VskError error)
{
    if (vsk_machine->had_error())
        return false;

    if (VSK_IMPL()->m_error_trap.m_mode == VSK_TRAP_MODE_ON &&
        VSK_IMPL()->m_error_trap.signal())
    {
        return true;
    }

    VSK_STATE()->m_error.m_error_code = error;
    VSK_STATE()->m_error.m_error_column = vsk_target_column;
    VSK_STATE()->m_error.m_error_line = vsk_target_line;
    VSK_IMPL()->m_target_line_text = vsk_get_program_line_text(vsk_target_line);

    static const std::unordered_map<VskError, const char *> vsk_error_map =
    {
#define DEFINE_ERROR(error_no, id, str) { id, str },
#include "errors.h"
#undef DEFINE_ERROR
    };

    auto it = vsk_error_map.find(error);
    if (it != vsk_error_map.end())
        vsk_machine->print(it->second);
    else
        vsk_machine->print("Unprintable error");

    if (vsk_target_line != 0 && vsk_target_line != -1)
        vsk_machine->print(" at " + vsk_to_string(vsk_target_line));

    vsk_enter_command_level();
    vsk_beep(-1);
    return true;
}

// ファンクションキーを処理する
void vsk_function_key(int index, bool shift)
{
    if (shift && index < 5)
        index += 5;
    if (index < 0 || 10 < index)
    {
        assert(0);
        return;
    }
    VSK_IMPL()->m_traps[VskTrapType(int(VSK_TRAP_F1) + index)].signal();
}

//////////////////////////////////////////////////////////////////////////////
// floating-point number exception (fe) handling - 浮動小数点数の例外

// 浮動小数点数の例外をチェックする
VskError vsk_had_new_exceptions(VskAstPtr& context)
{
    VskError error = VSK_NO_ERROR;
    if (context == nullptr)
        return error;

    bool overflow = false;
    if (context->m_insn == INSN_DBL_LITERAL) // 倍精度？
    {
        if (context->m_dbl > std::numeric_limits<VskDouble>::max())
        {
            context->m_dbl = std::numeric_limits<VskDouble>::max();
            overflow = true;
        }
        else if (context->m_dbl < std::numeric_limits<VskDouble>::lowest())
        {
            context->m_dbl = std::numeric_limits<VskDouble>::lowest();
            overflow = true;
        }
    }
    else if (context->m_insn == INSN_SNG_LITERAL) // 単精度
    {
        if (context->m_sng > std::numeric_limits<VskSingle>::max())
        {
            context->m_sng = std::numeric_limits<VskSingle>::max();
            overflow = true;
        }
        else if (context->m_sng < std::numeric_limits<VskSingle>::lowest())
        {
            context->m_sng = std::numeric_limits<VskSingle>::lowest();
            overflow = true;
        }
    }

    if (overflow)
    {
        vsk_machine->print("/0\b\n"); // ゼロ除算を表示。"\b"でBEEP音を鳴らす
    }

    return error;
}

//////////////////////////////////////////////////////////////////////////////

// マルチステートメントにする
VskAstPtr vsk_ast_multi(VskAstPtr x)
{
    if (x->is_multi())
        return x;
    return vsk_ast(INSN_MULTI, { x });
}
VskAstPtr vsk_ast_multi(VskAstPtr x, VskAstPtr y)
{
    if (x->is_multi())
    {
        x->push_back(y);
        return x;
    }
    return vsk_ast(INSN_MULTI, { x, y });
}
VskAstPtr vsk_ast_multi(VskAstPtr x, VskAstPtr y, VskAstPtr z)
{
    return vsk_ast_multi(vsk_ast_multi(x, y), z);
}

// ASTの評価を行う関数
VskAstPtr vsk_eval_ast(VskAstPtr arg)
{
    // nullptrなら文法エラー
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    // 評価関数を探す。なければエラー
    auto it = VSK_IMPL()->m_insn_to_fn.find(arg->m_insn);
    if (it == VSK_IMPL()->m_insn_to_fn.end())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    // 評価関数がnullptrの場合は、引数をそのまま返す
    if (!it->second)
        return arg;

    // 位置を覚えておく
    vsk_targeting(arg);

    // 実行し、戻り値を保持する
    auto ret = (*it->second)(arg, arg->children());

    // 浮動小数点数の例外をチェックする
    if (VskError error = vsk_had_new_exceptions(ret))
        VSK_ERROR_AND_RETURN(error, nullptr);

    return ret;
}

// テキストの評価を行う関数
VskAstPtr vsk_eval_text(const VskString& text)
{
    // 構文解析を行う関数
    VskParseResult result;
    auto error = vsk_parse_line("\x01\x02" + text, result);
    if (error)
        return nullptr;

    return vsk_eval_ast(result);
}

// ファイル番号
bool vsk_file_number(VskInt& number, VskAstPtr arg)
{
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(false);
    if (arg->m_insn == INSN_FILE_NUMBER)
        return vsk_int(number, arg->at(0));
    if (!vsk_int(number, arg))
        return false;
    if (number <= 0 || VSK_STATE()->m_how_many_files < number)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_FILE_NO, false);
    return true;
}

// ファイル番号を解釈
VskFilePtr vsk_eval_file_number(VskAstPtr arg, VskError& error)
{
    VskInt v0;
    if (!vsk_file_number(v0, arg))
        return nullptr;

    auto file = vsk_get_file_manager()->assoc(v0);
    if (!file)
    {
        error = VSK_ERR_FILE_NOT_OPEN;
        return nullptr;
    }

    return file;
}

// 左辺値（lvalue）を最適化する
VskAstPtr vsk_lvalue_optimize(VskAstPtr& lvalue, int base)
{
    if (lvalue->is_ident())
    {
        assert(lvalue->size() == 0);
        return lvalue;
    }

    auto& param_list = lvalue->at(1);
    VskAstPtr index_list = vsk_ast(INSN_PARAM_LIST);
    for (auto& param : param_list->children())
    {
        VskInt value;
        if (!vsk_int(value, param))
            return nullptr;
        index_list->push_back(vsk_ast_int(base + value));
    }

    auto new_lvalue = vsk_ast(INSN_LVALUE);
    new_lvalue->copy_node(lvalue.get());
    new_lvalue->push_back(lvalue->at(0));
    new_lvalue->push_back(index_list);
    return new_lvalue;
}

// 左辺値（lvalue）から名前と次元を取得
bool vsk_dimension_from_lvalue(VskString& name, VskIndexList& dimension, const VskAstPtr& lvalue, int base, bool is_array = false)
{
    dimension.clear();

    if (lvalue->is_ident())
    {
        assert(lvalue->size() == 0);
        name = vsk_var_get_typed_name(lvalue->m_str, is_array);
        return true;
    }

    assert(lvalue->m_insn == INSN_LVALUE);
    assert(lvalue->size() == 2);

    auto& ident = lvalue->at(0);
    auto& param_list = lvalue->at(1);

    assert(ident->is_ident());
    name = vsk_var_get_typed_name(ident->m_str, false);

    for (auto& param : param_list->children())
    {
        VskInt value;
        if (!vsk_int(value, param))
            return false;
        dimension.push_back(base + value);
    }

    if (dimension.size() || is_array)
        name += VSK_TYPE_ARRAY;

    return true;
}

// 型キャスト
VskAstPtr vsk_type_cast(VskAstPtr arg, VskType type)
{
    switch (type)
    {
    case VSK_TYPE_SINGLE:
        {
            VskSingle v0;
            if (!vsk_sng(v0, arg))
                return nullptr;
            return vsk_ast_sng(v0);
        }
        break;
    case VSK_TYPE_DOUBLE:
        {
            VskDouble v0;
            if (!vsk_dbl(v0, arg))
                return nullptr;
            return vsk_ast_dbl(v0);
        }
        break;
    case VSK_TYPE_INTEGER:
        {
            VskInt v0;
            if (!vsk_int(v0, arg))
                return nullptr;
            return vsk_ast_int(v0);
        }
        break;
    case VSK_TYPE_STRING:
        {
            VskString v0;
            if (!vsk_str(v0, arg))
                return nullptr;
            return vsk_ast_str(v0);
        }
        break;
    case VSK_TYPE_LONG:
        {
            VskLong v0;
            if (!vsk_lng(v0, arg))
                return nullptr;
            return vsk_ast_lng(v0);
        }
        break;
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);
}

// 変数に代入
bool vsk_var_assign(VskAstPtr arg0, VskAstPtr arg1)
{
    // 左辺値（lvalue）から名前と次元を取得
    VskString name;
    VskIndexList dimension;
    if (!vsk_dimension_from_lvalue(name, dimension, arg0, -(VSK_STATE()->m_option_base == 1)))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, false);

    // 型に合わせて値をセットする
    auto type = vsk_var_get_type(name);
    switch (type)
    {
    case VSK_TYPE_SINGLE:
        {
            VskSingle v1;
            if (!vsk_sng(v1, arg1))
                return false;
            vsk_var_set_value(name, dimension, &v1);
        }
        break;
    case VSK_TYPE_DOUBLE:
        {
            VskDouble v1;
            if (!vsk_dbl(v1, arg1))
                return false;
            vsk_var_set_value(name, dimension, &v1);
        }
        break;
    case VSK_TYPE_INTEGER:
        {
            VskInt v1;
            if (!vsk_int(v1, arg1))
                return false;
            vsk_var_set_value(name, dimension, &v1);
        }
        break;
    case VSK_TYPE_STRING:
        {
            VskString v1;
            if (!vsk_str(v1, arg1))
                return false;
            vsk_var_set_value(name, dimension, &v1);
        }
        break;
    case VSK_TYPE_LONG:
        {
            VskLong v1;
            if (!vsk_lng(v1, arg1))
                return false;
            vsk_var_set_value(name, dimension, &v1);
        }
        break;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////
// VskAst

VskAst::VskAst(INSN_TYPE insn)
    : m_insn(insn)
{
    set_column();
}

VskAst::VskAst(INSN_TYPE insn, VskShort value)
    : m_insn(insn)
    , m_sht(value)
{
#ifndef NDEBUG
    m_str = vsk_to_string(value);
#endif
    set_column();
}

VskAst::VskAst(INSN_TYPE insn, VskLong value)
    : m_insn(insn)
    , m_lng(value)
{
#ifndef NDEBUG
    m_str = vsk_to_string(value);
#endif
    set_column();
}

VskAst::VskAst(INSN_TYPE insn, VskSingle value)
    : m_insn(insn)
    , m_sng(value)
{
#ifndef NDEBUG
    m_str = vsk_to_string(value);
#endif
    set_column();
}

VskAst::VskAst(INSN_TYPE insn, VskDouble value)
    : m_insn(insn)
    , m_dbl(value)
{
#ifndef NDEBUG
    m_str = vsk_to_string(value);
#endif
    set_column();
}

VskAst::VskAst(INSN_TYPE insn, const std::string& str)
    : m_insn(insn)
    , m_str(str)
{
    set_column();
}

VskAst::VskAst(INSN_TYPE insn, std::initializer_list<VskAstPtr> children)
    : m_children(children)
    , m_insn(insn)
{
    set_column();
}

int VskAst::compare(const VskAst *other) const
{
    if (!this && !other)
        return 0;
    if (!this && other)
        return -1;
    if (this && !other)
        return +1;

    if (m_insn < other->m_insn)
        return -1;
    if (m_insn > other->m_insn)
        return +1;

    if (m_str < other->m_str)
        return -1;
    if (m_str > other->m_str)
        return +1;

    const size_t min_ = std::min(size(), other->size());
    for (size_t i = 0; i < min_; ++i)
    {
        auto a0 = at(i), a1 = other->at(i);
        int cmp = a0->compare(a1.get());
        if (cmp != 0)
            return cmp;
    }

    if (size() < other->size())
        return -1;
    if (size() > other->size())
        return +1;

    return 0;
}

bool VskAst::is_stmt() const
{
    return this && VSK_IMPL()->m_stmt_set.count(m_insn) > 0;
}

bool VskAst::is_data_entry() const
{
    return is_data_literal() || is_number() || is_str() || is_ident();
}

VskInt VskAst::to_int() const
{
    if (is_int())
        return m_int;
    if (is_sng())
        return vsk_round(m_sng);
    if (is_dbl())
        return vsk_round(m_dbl);
    if (is_lng())
        return vsk_round(m_lng);
    return 0;
}

VskSingle VskAst::to_sng() const
{
    if (is_int())
        return VskSingle(m_int);
    if (is_sng())
        return m_sng;
    if (is_dbl())
        return VskSingle(m_dbl);
    if (is_lng())
        return VskSingle(m_lng);
    return 0;
}

VskDouble VskAst::to_dbl() const
{
    if (is_int())
        return m_int;
    if (is_sng())
        return m_sng;
    if (is_dbl())
        return m_dbl;
    if (is_lng())
        return VskLong(m_lng);
    return 0;
}

void VskAst::set_column()
{
    m_column = vsk_target_column;
}

void VskAst::copy_node(VskAst *src)
{
    m_insn = src->m_insn;
    m_str = src->m_str;
    m_dbl = src->m_dbl; // TODO: union内で一番大きいメンバーを選んでください
    m_program_line = src->m_program_line;
    m_column = src->m_column;
}

VskAstPtr VskAst::substitute(VskAstPtr var, VskAstPtr value)
{
    auto clone = vsk_ast(m_insn);
    clone->copy_node(this);
    for (auto child : m_children)
    {
        if (child->compare(var.get()) == 0)
            clone->m_children.push_back(value);
        else
            clone->m_children.push_back(child->substitute(var, value));
    }
    return clone;
}

void vsk_targeting(VskAstPtr ast)
{
    if (!ast)
        return;
    vsk_target_column = ast->m_column;
    if (ast->m_program_line != -1)
        vsk_target_line = ast->m_program_line;
}

//////////////////////////////////////////////////////////////////////////////
// 字句解析

// 命令の種類から命令の名前へ
VskString vsk_insn2name(INSN_TYPE insn)
{
#ifdef NDEBUG
    return nullptr;
#else
    static const std::unordered_map<INSN_TYPE, const char *> c_insn_strings =
    {
#define DEFINE_INSN(id, fn, is_stmt) { id, #id },
#include "insn.h"
#undef DEFINE_INSN
    };

    auto it = c_insn_strings.find(insn);
    if (it == c_insn_strings.end())
        return "(invalid)";
    return it->second;
#endif
}

// 文字列から数値を読み取って型付きのASTにする
VskAstPtr vsk_parse_number(const char *ptr, char **endptr, VSK_TYPE& type)
{
    // 文字列をスキャン
    VskString str;
    char *dot, *exp;
    bool minus;
    if (!vsk_scan_number(str, ptr, &minus, &dot, &exp, endptr))
        return nullptr; // 数値は読み取れなかった

    int sign = (minus ? -1 : 1);

    if (!dot && !exp) // 整数っぽい？
    {
        // prefixに応じて進数を読み取る
        VskLong value;
        if (str[0] == '&') {
            type = VSK_TYPE_INTEGER;

            if (str[1] == 'H' || str[1] == 'h') {
                value = std::strtoul(&str[2], nullptr, 16); // 16進数？
            } else if (str[1] == 'O' || str[1] == 'o') {
                value = std::strtoul(&str[2], nullptr, 8); // 8進数？
            } else {
                value = std::strtoul(&str[1], nullptr, 8); // 8進数？
            }

            value = sign * value;

            // VskIntの範囲を超えているか？
            if (value < std::numeric_limits<VskShort>::lowest() || value > std::numeric_limits<VskWord>::max())
                return vsk_ast_dbl(VskDouble(value)); // 倍精度
        } else {
            value = std::strtoul(str.c_str(), nullptr, 10); // 10進数？
            value = sign * value;

            // VskIntの範囲を超えているか？
            if (value < std::numeric_limits<VskShort>::lowest() || value > std::numeric_limits<VskWord>::max())
            {
                type = VSK_TYPE_DOUBLE;
                return vsk_ast_dbl(VskDouble(value)); // 倍精度
            }
        }

        type = VSK_TYPE_INTEGER;
        return vsk_ast_int(sign * VskInt(value)); // 整数
    }

    // 指数表示の"D"はC言語と非互換だから"E"に変える
    mstr_replace_all(str, 'D', 'E');

    // 実数らしい
    VskDouble value = std::strtod(str.c_str(), nullptr);
    if (exp) // 指数あり？
    {
        VskDouble power = std::strtod(exp, nullptr);
        value *= std::pow(10, power); // 指数を適用
        if (*exp == 'E' || *exp == 'e') // 単精度？
        {
            type = VSK_TYPE_SINGLE;
            return vsk_ast_sng(sign * VskSingle(value));
        }
    }
    else
    {
        mstr_replace_all(str, ".", ""); // ドットを取り除く
        mstr_trim(str, "0"); // 前後のゼロを取り除く
        if (str.size() <= 7)
        {
            type = VSK_TYPE_SINGLE;
            return vsk_ast_sng(sign * VskSingle(value)); // 7桁以下なら単精度
        }
    }

    type = VSK_TYPE_DOUBLE;
    return vsk_ast_dbl(sign * value); // 倍精度
}

// 符号付き16-bit整数を取得する
bool vsk_sht(VskShort& value, VskAstPtr arg)
{
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    vsk_targeting(arg);

    auto ret = vsk_eval_ast(arg);
    if (!ret)
        return false;

    switch (ret->m_insn)
    {
    case INSN_SHT_LITERAL:
        value = ret->m_sht;
        break;
    case INSN_LNG_LITERAL:
        {
            VskLong v = ret->m_lng;
            if (v < std::numeric_limits<VskShort>::lowest() || std::numeric_limits<VskWord>::max() < v)
                VSK_ERROR_AND_RETURN(VSK_ERR_OVERFLOW, false);
            if (v < 0)
                value = static_cast<VskShort>(v + 0.5);
            else
                value = static_cast<VskWord>(v + 0.5);
        }
        break;
    case INSN_SNG_LITERAL:
        {
            VskSingle v = ret->m_sng;
            if (v < std::numeric_limits<VskShort>::lowest() || std::numeric_limits<VskWord>::max() < v)
                VSK_ERROR_AND_RETURN(VSK_ERR_OVERFLOW, false);
            if (v < 0)
                value = static_cast<VskShort>(v + 0.5);
            else
                value = static_cast<VskWord>(v + 0.5);
        }
        break;
    case INSN_DBL_LITERAL:
        {
            VskDouble v = ret->m_dbl;
            if (v < std::numeric_limits<VskShort>::lowest() || std::numeric_limits<VskWord>::max() < v)
                VSK_ERROR_AND_RETURN(VSK_ERR_OVERFLOW, false);
            if (v < 0)
                value = static_cast<VskShort>(v + 0.5);
            else
                value = static_cast<VskWord>(v + 0.5);
        }
        break;
    case INSN_STR_LITERAL:
    default:
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, false);
    }

    return true;
}

// 識別子を取得する
bool vsk_ident(VskString& value, VskAstPtr arg)
{
    vsk_targeting(arg);

    if (!arg || (!arg->is_ident() && !arg->is_keyword()))
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    value = arg->m_str;
    return true;
}

// 長い整数を取得する
bool vsk_lng(VskLong& value, VskAstPtr arg)
{
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    vsk_targeting(arg);

    auto ret = vsk_eval_ast(arg);
    if (!ret)
        return false;

    switch (ret->m_insn)
    {
    case INSN_SHT_LITERAL:
        value = ret->m_sht;
        return true;
    case INSN_LNG_LITERAL:
        value = ret->m_lng;
        return true;
    case INSN_SNG_LITERAL:
        {
            VskDouble v = ret->m_sng;
            if (std::numeric_limits<VskDword>::max() < v)
                VSK_ERROR_AND_RETURN(VSK_ERR_OVERFLOW, false);
            value = (VskLong)std::round(v);
        }
        return true;
    case INSN_DBL_LITERAL:
        {
            VskDouble v = ret->m_dbl;
            if (std::numeric_limits<VskDword>::max() < v)
                VSK_ERROR_AND_RETURN(VSK_ERR_OVERFLOW, false);
            value = (VskLong)std::round(v);
        }
        return true;
    case INSN_STR_LITERAL:
    default:
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, false);
    }
}

// 単精度型を取得する
bool vsk_sng(VskSingle& value, VskAstPtr arg)
{
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    vsk_targeting(arg);

    auto ret = vsk_eval_ast(arg);
    if (!ret)
        return false;

    switch (ret->m_insn)
    {
    case INSN_SNG_LITERAL:
        value = ret->m_sng;
        break;
    case INSN_SHT_LITERAL:
        value = ret->m_sht;
        break;
    case INSN_LNG_LITERAL:
        value = VskSingle(ret->m_lng);
        break;
    case INSN_DBL_LITERAL:
        // 範囲をチェック
        if (!(std::numeric_limits<VskSingle>::lowest() <= ret->m_dbl &&
              ret->m_dbl <= std::numeric_limits<VskSingle>::max())) // オーバーフロー？
        {
            vsk_machine->print("OV\b\n"); // Overflow. "\b"でBEEP音を鳴らす
            value = 0; // 自動修正
        }
        else
        {
            value = VskSingle(ret->m_dbl);
        }
        break;
    case INSN_STR_LITERAL:
    default:
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, false);
    }

    return true;
}

// 倍精度型を取得する
bool vsk_dbl(VskDouble& value, VskAstPtr arg)
{
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    vsk_targeting(arg);

    auto ret = vsk_eval_ast(arg);
    if (!ret)
        return false;

    switch (ret->m_insn)
    {
    case INSN_SNG_LITERAL:
        value = ret->m_sng;
        break;
    case INSN_SHT_LITERAL:
        value = ret->m_sht;
        break;
    case INSN_LNG_LITERAL:
        value = ret->m_lng;
        break;
    case INSN_DBL_LITERAL:
        value = ret->m_dbl;
        break;
    case INSN_STR_LITERAL:
    default:
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, false);
    }

    return true;
}

// 文字列型を取得する
bool vsk_str(VskString& value, VskAstPtr arg)
{
    if (!arg)
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    vsk_targeting(arg);

    auto ret = vsk_eval_ast(arg);
    if (!ret)
        return false;

    if (!ret->is_str())
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, false);

    value = ret->to_str();
    return true;
}

// テキストからトークンを得る
int vsk_token_from_text(const char *text)
{
    // キーワードをトークンに変換する変数
    static const std::unordered_map<std::string, int> vsk_keyword_map =
    {
#define DEFINE_KEYWORD(str, id) { str, id },
#include "keywords.h"
#undef DEFINE_KEYWORD
    };

    std::string str = text;
    vsk_upper(str);

    if (str.find("FN") == 0)
        return TK_FN;

    if (str.find("USR") == 0)
        return TK_USR;

    auto it = vsk_keyword_map.find(str);
    return (it != vsk_keyword_map.end()) ? it->second : TK_IDENTIFIER;
}

// テキストを出力
void vsk_print(const VskString& str)
{
    vsk_machine->print(str);
}

//////////////////////////////////////////////////////////////////////////////
// 構文解析

bool VskAst::is_number() const
{
    switch (m_insn)
    {
    case INSN_SHT_LITERAL:
    case INSN_LNG_LITERAL:
    case INSN_SNG_LITERAL:
    case INSN_DBL_LITERAL:
        return true;
    default:
        return false;
    }
}

bool VskAst::is_negative() const
{
    switch (m_insn)
    {
    case INSN_SHT_LITERAL: return m_sht < 0;
    case INSN_LNG_LITERAL: return m_lng < 0;
    case INSN_SNG_LITERAL: return m_sng < 0;
    case INSN_DBL_LITERAL: return m_dbl < 0;
    case INSN_STR_LITERAL:
    default:
        return false;
    }
}

VskString VskAst::to_str() const
{
    switch (m_insn)
    {
    case INSN_SHT_LITERAL: return vsk_to_string(m_sht);
    case INSN_LNG_LITERAL: return vsk_to_string(m_lng);
    case INSN_SNG_LITERAL: return vsk_to_string(m_sng);
    case INSN_DBL_LITERAL: return vsk_to_string(m_dbl);
    case INSN_STR_LITERAL:
    default:
        return m_str;
    }
}

// 抽象構文木をデバッグ用文字列に
VskString VskAst::to_debug_str()
{
#ifdef NDEBUG
    return "";
#else
    if (!this)
        return "nullptr";

    VskString ret = vsk_insn2name(m_insn) + "(";

    bool first = true;
    if (m_str.size())
    {
        ret += '\'';
        ret += m_str;
        ret += '\'';
        first = false;
    }

    for (auto& child : m_children)
    {
        if (first)
            first = false;
        else
            ret += ", ";
        ret += child->to_debug_str();
    }
    ret += ")";

    if (m_column != -1)
    {
        ret += "@";
        ret += vsk_to_string(m_column);
    }

    return ret;
#endif
}

// 構文エラーのときに呼び出される関数
void yyerror(VskParseResult& result, yyscan_t yyscanner, const char *s)
{
    mdbg_traceA("yyerror: %s\n", s);
}

// 実際に構文解析を行う関数
VskError vsk_parse_line(const VskString& text, VskParseResult& result)
{
    vsk_iLine = 0;
    vsk_target_column = 0;
    result = nullptr;
    vsk_in_data = false;

    yyscan_t yyscanner;
    bool parsed = false;
    YY_BUFFER_STATE state = 0;
    if (yylex_init(&yyscanner) == 0)
    {
        state = yy_scan_bytes(text.c_str(), int(text.size()), yyscanner);
        if (state)
        {
            parsed = (yyparse(result, yyscanner) == 0);
            yy_delete_buffer(state, yyscanner);
        }
        yylex_destroy(yyscanner);
    }
    yylval = nullptr; // クリアしないとメモリーリークになる

    if (!state)
        return VSK_ERR_NO_MEMORY;
    if (!parsed)
        return VSK_ERR_SYNTAX;

    return VSK_NO_ERROR;
}

// 実際に構文解析を行う関数
VskError vsk_parse_program(VskString text, VskParseResult& result)
{
    // 前後の空白を除去
    mstr_trim(text, " \t\r\n");

    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, text, "\n");

    VskError error;

    VskAstPtr data = vsk_ast(INSN_MULTI);
    data->m_column = 0;
    for (auto& line : lines)
    {
        // 行番号を取得する
        vsk_target_line = vsk_line_number_from_line_text(line);

        // 1行構文解析
        VskParseResult line_result;
        error = vsk_parse_line(line, line_result);
        if (error)
            return error;

        // dataに連結する
        data = vsk_ast_multi(data, line_result);
    }

    result = data;
    return VSK_NO_ERROR;
}

//////////////////////////////////////////////////////////////////////////////
// 命令関数群

// ラベルから行番号へ変換する。ラベルが先頭にない場合は失敗してゼロを返す
VskLineNo vsk_label_to_line(VskString str)
{
    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, VSK_IMPL()->m_program_text, "\n");

    // 範囲内の行を出力
    for (auto& line : lines)
    {
        char *endptr;
        VskLineNo number = vsk_line_number_from_line_text(line, &endptr);
        if (number == 0)
            continue;

        // 余白を読み捨てる
        while (*endptr == ' ' || *endptr == '\t')
            ++endptr;

        // アスタリスクを確認する
        if (*endptr != '*')
            continue;
        ++endptr;

        // 余白を読み捨てる
        while (*endptr == ' ' || *endptr == '\t')
            ++endptr;

        // ラベルの名前があれば読み込む
        VskString name;
        while (vsk_isalnum(*endptr) || *endptr == '.')
        {
            name += *endptr;
            ++endptr;
        }

        // 大文字にする
        vsk_upper(name);

        // 一致すれば行番号を返す
        if (name == str)
            return number;
    }

    return 0; // 失敗
}

// 行番号やラベルをインデックスリストに変換
VskIndexList vsk_label_to_index_list(const VskString& label_name, const VskLabelMap& label_map)
{
    auto it = label_map.find(label_name);
    if (it == label_map.end()) // ラベルが見つからなかった
        return { };
    return it->second;
}

// 行番号やラベルをインデックスリストに変換
VskIndexList vsk_label_to_index_list(VskAstPtr arg, const VskLabelMap& label_map)
{
    assert(arg->m_insn == INSN_LABEL);

    auto arg0 = arg->at(0);
    if (arg0->m_insn == INSN_PERIOD) // "." は現在の行
        return vsk_label_to_index_list(vsk_to_string(VSK_IMPL()->m_current_line), label_map);

    if (arg0->is_number()) // 数値なら行番号
        return vsk_label_to_index_list(vsk_to_string(arg0->to_dbl()), label_map);

    auto& label_name = arg0->m_str;
    return vsk_label_to_index_list(label_name, label_map);
}

// 行番号やラベルを行番号に直す
bool vsk_label_to_line_number(VskAstPtr arg, VskLineNo& number)
{
    assert(arg->m_insn == INSN_LABEL);
    number = 0;

    auto arg0 = arg->at(0);
    if (arg0->m_insn == INSN_PERIOD) // "." は現在の行
    {
        number = VSK_IMPL()->m_current_line;
        return true;
    }

    if (arg0->is_number()) // 数値なら行番号
    {
        number = arg0->to_dbl();
        return true;
    }

    auto& label_name = arg0->m_str;
    auto it = VSK_IMPL()->m_label_to_line_numbers.find(label_name);
    if (it != VSK_IMPL()->m_label_to_line_numbers.end())
    {
        number = it->second;
        return true;
    }

    return false; // 失敗
}

// プログラムリストを表示
bool vsk_list(bool line_printer, const VskString& program_list_text, VskLineNo min_, VskLineNo max_)
{
    VskAstList printing_items;

    bool found = false;
    if (program_list_text.size())
    {
        // 行に分ける
        std::vector<VskString> lines;
        mstr_split(lines, program_list_text, "\n");

        // 範囲内の行を出力
        for (auto& line : lines)
        {
            VskLineNo number = vsk_line_number_from_line_text(line);
            if (min_ <= number && number <= max_)
            {
                printing_items.push_back(vsk_ast_str(line + "\n"));
                VSK_IMPL()->m_current_line = number;
                found = true;
            }
        }
    }

    if (line_printer)
        VSK_IMPL()->m_printing_device = vsk_get_line_printer();
    else
        VSK_IMPL()->m_printing_device = vsk_get_screen_device();

    assert(VSK_IMPL()->m_printing_device);

    VSK_IMPL()->m_printing_items = printing_items;
    VSK_IMPL()->m_printing_is_write = false;

    return found;
}

// プログラム行を消す
void vsk_delete_lines(VskString& program_list_text, VskDouble min_, VskDouble max_)
{
    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, program_list_text, "\n");

    // 空の行と範囲内の行は要らない
    for (size_t i = lines.size(); i > 0; ) // 削除するので逆順
    {
        --i;
        auto& line = lines[i];
        mstr_trim(line, " \t\r\n");
        if (line.empty())
        {
            lines.erase(lines.begin() + i);
            continue;
        }
        auto number = vsk_line_number_from_line_text(line);
        if (min_ <= number && number <= max_)
        {
            lines.erase(lines.begin() + i);
            continue;
        }
    }

    // 行を連結し、テキストを更新
    program_list_text = mstr_join(lines, "\n");
}

// プログラム行をセットする
void vsk_update_program_line(VskString& program_list_text, VskDouble iProgramLine, const VskString& text)
{
    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, program_list_text, "\n");

    // 空の行は要らない
    for (size_t i = lines.size(); i > 0; ) // 削除するので逆順
    {
        --i;
        mstr_trim(lines[i], " \t\r\n");
        if (lines[i].empty())
        {
            lines.erase(lines.begin() + i);
        }
    }

    // 挿入可能な行の位置を見つけて可能ならばそこに挿入する
    bool found = false;
    for (size_t i = 0; i < lines.size(); ++i)
    {
        auto& line = lines[i];
        auto number = vsk_line_number_from_line_text(line);
        if (number == iProgramLine)
        {
            found = true;
            line = text;
            break;
        }
        if (number > iProgramLine)
        {
            found = true;
            lines.insert(lines.begin() + i, text);
            break;
        }
    }

    // 見つからなかったら、最後に挿入
    if (!found)
        lines.push_back(text);

    // 行を連結し、テキストを更新
    program_list_text = mstr_join(lines, "\n");
}

// 直接実行
void vsk_direct_execute(const VskString& text)
{
    // 空の行は無視する
    auto str = text;
    mstr_trim(str, " \t\r\n");
    if (str.empty())
        return;

    // 行番号を取得する
    auto line_number = vsk_line_number_from_line_text(str);
    if (line_number != 0) // 行番号がある
    {
        // 行番号のみなら、その行を消す
        auto i0 = str.find_first_not_of("0123456789");
        if (i0 == str.npos)
        {
            vsk_delete_lines(VSK_IMPL()->m_program_text, line_number, line_number);
            return;
        }

        // プログラムリストを1行だけ更新する
        vsk_update_program_line(VSK_IMPL()->m_program_text, line_number, str);
        // 現在の行をセット
        VSK_IMPL()->m_current_line = line_number;
        VSK_IMPL()->m_target_line_text = str;
        // 継続(CONT)はできなくなった
        VSK_IMPL()->m_stopping_path.clear();
        return;
    }

    // 実行を開始する
    VSK_STATE()->m_wait_for = VSK_NO_WAIT;

    // いったん無効な行番号にする
    vsk_target_line = -1;

    // 構文解析する
    VskParseResult result;
    VskError error = vsk_parse_line(str, result);
    if (error)
    {
        VSK_IMPL()->m_target_line_text = str;
        VSK_ERROR_AND_RETURN(error);
    }

#if !defined(NDEBUG)
    mdbg_traceA("to_debug_str: %s\n", result->to_debug_str().c_str());
#endif

    // プログラムデータをスキャンする
    error = vsk_scan_direct_data(result);
    if (error)
        VSK_ERROR_AND_RETURN(error);

    VSK_IMPL()->m_control_path = { I_DIRECT_CODE };
    VSK_IMPL()->m_target_line_text = str;
    VSK_IMPL()->m_direct_code = result;

    // トラップをクリア
    vsk_clear_trap();
    // 実行開始
    VSK_STATE()->m_wait_for = VSK_NO_WAIT;
}

// デフォルトのトラップ処理
void vsk_default_trap(VskTrapType type)
{
    switch (type)
    {
    case VSK_TRAP_STOP: // STOPキー（Ctrl+Cキー）を機能させる
        switch (VSK_STATE()->m_wait_for)
        {
        case VSK_NO_WAIT:
        case VSK_WAIT_FOR_INPUT:
        case VSK_WAIT_FOR_DRAW:
        case VSK_WAIT_FOR_SLEEP:
            // 必要ならば停止メッセージを表示
            if (!VSK_IMPL()->m_auto_mode && !VSK_STATE()->m_edit_mode)
            {
                vsk_print("^C\nBreak\b"); // "\b"でBEEP音を鳴らす
                if (vsk_target_line != 0 && vsk_target_line != -1)
                    vsk_print(" at " + vsk_to_string(vsk_target_line));
            }
            // 自動モード、編集モード解除
            VSK_IMPL()->m_auto_mode = VSK_STATE()->m_edit_mode = false;
            // 改行
            vsk_print("\n");
            // 継続（CONT）のために覚えておく
            VSK_IMPL()->m_stopping_path = VSK_IMPL()->m_control_path;
            // IMEをOFFにする
            vsk_ime_on_off(false);
            // コマンドレベルに戻る
            vsk_enter_command_level();
            break;
        case VSK_WAIT_FOR_COMMAND:
            vsk_print("\n");
            VSK_STATE()->m_edit_mode = false;
            break;
        case VSK_WAIT_FOR_INPORT:
            break;
        case VSK_WAIT_FOR_PLAY:
            vsk_sound_stop();
            {
                vsk_print("^C\nBreak\b"); // "\b"でBEEP音を鳴らす
                if (vsk_target_line != 0 && vsk_target_line != -1)
                    vsk_print(" at " + vsk_to_string(vsk_target_line));
            }
            vsk_enter_command_level();
            break;
        }
        break;
    case VSK_TRAP_HELP: // HELPキー（Endキー）を機能させる
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_COMMAND) // 実行中でなければ
        {
            vsk_machine->line_feed();
            vsk_machine->set_line_text(VSK_STATE()->m_caret_y, VSK_IMPL()->m_target_line_text);
            vsk_machine->set_line_column(int(VSK_STATE()->m_error.m_error_column));
        }
        break;
    case VSK_TRAP_F1: case VSK_TRAP_F2: case VSK_TRAP_F3: case VSK_TRAP_F4: case VSK_TRAP_F5:
    case VSK_TRAP_F6: case VSK_TRAP_F7: case VSK_TRAP_F8: case VSK_TRAP_F9: case VSK_TRAP_F10:
        // ファンクションキーを機能させる
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_COMMAND) // 実行中でなければ
        {
            vsk_machine->keyboard_str(VSK_STATE()->m_function_keys[type - VSK_TRAP_F1]);
        }
        break;
    case VSK_TRAP_PEN: // ペン入力
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_COMMAND) // 実行中でなければ
        {
            if (VSK_IMPL()->m_pen_pressed) // ペンが押されているか？
            {
                // 範囲外のときは除外
                int text_x = VSK_IMPL()->m_pen_x, text_y = VSK_IMPL()->m_pen_y;
                if (text_x == -1 && text_y == -1)
                    return;

                // ファンクションキーの上なら、ファンクションキーを機能させる
                int key_no = vsk_machine->hit_test_function_key(text_x, text_y);
                if (key_no >= 1)
                {
                    vsk_function_key(key_no - 1, vsk_is_shift_pressed());
                    return;
                }

                // スクロール範囲内ならキャレットを移動
                if (0 <= text_x && text_x < VSK_STATE()->m_text_width &&
                    0 <= text_y && text_y < VSK_STATE()->m_text_height &&
                    VSK_STATE()->m_console_y0 <= text_y &&
                    text_y < VSK_STATE()->m_console_y0 + VSK_STATE()->m_console_cy0)
                {
                    vsk_caret_move_by_mouse_click(text_x, text_y);
                    return;
                }
            }
        }
        break;
    default:
        break;
    }
}

// トラップをチェックする
bool vsk_check_trap(void)
{
    // 時刻文字列をチェック
    VskString time = vsk_get_time();
    if (VSK_IMPL()->m_trap_time == time)
    {
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_COMMAND)
        {
            ;
        }
        else if (!VSK_IMPL()->m_time_trapped)
        {
            VSK_IMPL()->m_traps[VSK_TRAP_TIME].signal();
            VSK_IMPL()->m_time_trapped = true;
        }
        else
        {
            VSK_IMPL()->m_traps[VSK_TRAP_TIME].m_catching = false;
        }
    }
    else
    {
        VSK_IMPL()->m_time_trapped = false;
    }

    int trap_type = 0;
    for (auto& trap : VSK_IMPL()->m_traps)
    {
        if (trap.m_catching && trap.m_mode != VSK_TRAP_MODE_STOP)
        {
            trap.m_catching = false;
            if (VSK_STATE()->m_wait_for == VSK_NO_WAIT &&
                trap.m_index_list.size() && trap.m_mode == VSK_TRAP_MODE_ON)
            {
                trap.m_trapping = true;

                if (trap_type == VSK_TRAP_PEN)
                    VSK_IMPL()->m_pen_pressed = false;

                VSK_IMPL()->m_path_stack.push(VSK_IMPL()->m_control_path);
                VSK_IMPL()->m_control_path = trap.m_index_list;
                VSK_IMPL()->m_trap_type_stack.push((VskTrapType)trap_type);
            }
            else
            {
                vsk_default_trap((VskTrapType)trap_type);
            }
            return true;
        }

        ++trap_type;
    }

    if (VSK_IMPL()->m_error_trap.m_catching)
    {
        VSK_IMPL()->m_error_trap.m_catching = false;
        if (VSK_IMPL()->m_error_trap.m_index_list.size() &&
            VSK_IMPL()->m_error_trap.m_mode == VSK_TRAP_MODE_ON)
        {
            VSK_IMPL()->m_error_trap.m_trapping = true;
            VSK_IMPL()->m_control_path = VSK_IMPL()->m_error_trap.m_index_list;
        }
        return true;
    }

    // INPUT WAIT / LINE INPUT WAIT
    if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT &&
        VSK_STATE()->m_input_wait_start &&
        vsk_get_tick_count() - VSK_STATE()->m_input_wait_start >= VSK_STATE()->m_input_wait_interval)
    {
        VSK_STATE()->m_input_wait_start = 0;
        VSK_IMPL()->m_control_path = std::move(VSK_STATE()->m_input_wait_default_path);
        VSK_STATE()->m_input_wait_default_path.clear();
        // 実行の再開
        VSK_STATE()->m_wait_for = VSK_NO_WAIT;
        // IMEをOFFにする
        vsk_ime_on_off(false);
        return true;
    }

    return false;
}

void vsk_coreapi_tests(void);

// 装置に印字する
bool vsk_do_printing(void)
{
    // 印字装置の指定がない？
    auto& device = VSK_IMPL()->m_printing_device;
    if (!device)
        return false;

    // 印字すべきものがなくなった？
    if (VSK_IMPL()->m_printing_items.empty())
    {
        // WRITE文のときは最後に改行を出力
        if (VSK_IMPL()->m_printing_is_write)
            device->write_str("\n");
        // 装置の指定をクリアして次に進む
        device = nullptr;
        auto& index_list = VSK_IMPL()->m_control_path;
        index_list = vsk_next_control_path(index_list);
        return true;
    }

    // 先頭から一つ項目を取り出す
    auto item = VSK_IMPL()->m_printing_items.front();
    VSK_IMPL()->m_printing_items.pop_front();

    // カンマか？
    bool is_comma = (item->m_insn == INSN_COMMA);
    if (is_comma)
    {
        if (VSK_IMPL()->m_printing_is_write) // WRITE文か？
        {
            // カンマを出力する
            device->write_str(",");
        }
        else
        {
            // 必要なスペースを出力する
            int x = device->get_x();
            int cx = 14 - (x % 14);
            if (x + cx + 14 >= device->line_width())
                device->write_str("\n");
            else
                device->write_str(std::string(cx, ' '));
        }
        return true;
    }

    // セミコロンか？
    bool is_semicolon = (item->m_insn == INSN_SEMICOLON);
    if (is_semicolon)
    {
        if (VSK_IMPL()->m_printing_is_write) // WRITE文か？
        {
            // カンマを出力する
            device->write_str(",");
        }
        return true;
    }

    // 項目を評価する
    auto column = vsk_target_column;
    auto ret = vsk_eval_ast(item);
    if (!ret)
    {
        vsk_target_column = column;
        return true;
    }

    // 項目を文字列に変換
    VskString str;
    if (VSK_IMPL()->m_printing_is_write)
    {
        if (ret->is_number()) // 数か？
        {
            str += ret->to_str();
        }
        else // 文字列
        {
            str += '"';
            str += ret->to_str();
            str += '"';
        }
    }
    else
    {
        if (ret->is_number()) // 数か？
        {
            if (!ret->is_negative())
                str += ' ';
            str += ret->to_str();
            str += ' ';
        }
        else // 文字列
        {
            str += ret->to_str();
        }
    }

    // 文字列を出力
    device->write_str(str);
    return true;
}

bool vsk_beep_wait(void)
{
    if (!VSK_IMPL()->m_beep_waiting)
        return false; // 待たない

    if (vsk_sound_is_beeping())
        return true; // 待つ

    vsk_sound_wait(50);

    VSK_IMPL()->m_beep_waiting = false;
    return false; // 待たない
}

// 待つ
bool vsk_wait(void)
{
    if (vsk_beep_wait())
        return true; // 待つ

    switch (VSK_STATE()->m_wait_for)
    {
    case VSK_NO_WAIT:
        return false; // 待たない
    case VSK_WAIT_FOR_COMMAND:
        return true; // 待つ
    case VSK_WAIT_FOR_INPUT:
        return true; // 待つ
    case VSK_WAIT_FOR_SLEEP:
        if (vsk_get_tick_count() - VSK_IMPL()->m_sleep_start >= VSK_IMPL()->m_sleep_amount)
        {
            VSK_STATE()->m_wait_for = VSK_NO_WAIT;
            VSK_IMPL()->m_control_path = VSK_IMPL()->m_after_sleep_path;
            return true; // 待たない
        }
        vsk_sleep(0);
        return true; // 待つ
    case VSK_WAIT_FOR_INPORT:
        {
            // 入力ポートの値を取得
            VskInt data;
            if (vsk_machine->is_8801_mode())
                data = vsk_inport_8801(VSK_STATE()->m_wait_inport_port);
            else
                data = vsk_inport_9801(VSK_STATE()->m_wait_inport_port);
            int data1 = VSK_STATE()->m_wait_inport_data1;
            int data2 = VSK_STATE()->m_wait_inport_data2;
            if ((data ^ data2) & data1) // 条件が合えば
            {
                // 次の文へ
                VSK_STATE()->m_wait_for = VSK_NO_WAIT;
                VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
                return false; // 待たない
            }
        }
        return true; // 待つ
    case VSK_WAIT_FOR_DRAW:
        if (VSK_IMPL()->m_draw_items.empty())
        {
            // 次の文へ
            VSK_STATE()->m_wait_for = VSK_NO_WAIT;
            VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
            return false; // 待たない
        }
        else
        {
            auto item = VSK_IMPL()->m_draw_items[0];
            VSK_IMPL()->m_draw_items.erase(VSK_IMPL()->m_draw_items.begin());
            VSK_IMPL()->m_draw_engine.draw_item(item);
        }
        return true; // 待った
    case VSK_WAIT_FOR_TURTLE:
        if (VSK_IMPL()->m_turtle_items.empty())
        {
            // 次の文へ
            VSK_STATE()->m_wait_for = VSK_NO_WAIT;
            VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
            return false; // 待たない
        }
        else
        {
            auto item = VSK_IMPL()->m_turtle_items[0];
            VSK_IMPL()->m_turtle_items.erase(VSK_IMPL()->m_turtle_items.begin());
            VSK_IMPL()->m_turtle_engine.turtle_item(item);
        }
        return true;
    case VSK_WAIT_FOR_PLAY:
        if (vsk_sound_is_playing()) {
            return true; // 待つ
        } else {
            // 次の文へ
            VSK_STATE()->m_wait_for = VSK_NO_WAIT;
            VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
        }
        break;
    }
    return false; // 待たない
}

// ステップ実行
void vsk_step(void)
{
#ifndef NDEBUG
    // 必要なら単体テスト
    static bool s_flag = false;
    if (!s_flag)
    {
        s_flag = true;
        vsk_coreapi_tests();
    }
#endif

    if (!vsk_machine)
        return;

    // トラップをチェックする
    if (vsk_check_trap())
        return;

    // 必要なら待つ
    if (vsk_wait())
        return;

    // コントロールパスを取得する
    auto& index_list = VSK_IMPL()->m_control_path;

    // 印字する項目があれば、印字する
    if (vsk_do_printing())
        return;

    // 実行するものがなければコマンドレベルに入る
    if (index_list.empty())
    {
        vsk_enter_command_level();
        return;
    }

    // コントロールパスを解決する
    auto node = vsk_resolve_index_list(index_list);
    vsk_targeting(node);
    if (!node)
    {
        vsk_enter_command_level();
        return;
    }

    if (node->m_program_line != -1) // 行番号があるか？
    {
        // 現在の行番号をセット
        vsk_target_line = node->m_program_line;

        if (VSK_IMPL()->m_trace_on) // TRACEがONなら行番号トレースを出力。TRON/TROFFを参照
        {
            vsk_print("[" + vsk_to_string(vsk_target_line) + "]");
        }
    }

    // 評価するl
    auto ret = vsk_eval_ast(node);

    // 必要なら次のコントロールパスに移動
    if (!ret || ret->m_insn != INSN_DONT_GO_NEXT)
        index_list = vsk_next_control_path(index_list);
}

// 引数の個数（arity）が範囲内かチェックする
bool vsk_arity_in_range(const VskAstList& args, size_t min_, size_t max_)
{
    if (args.size() < min_)
        VSK_ERROR_AND_RETURN(VSK_ERR_MISSING_OPERAND, false);
    if (args.size() > max_)
        VSK_SYNTAX_ERROR_AND_RETURN(false);
    return true;
}

// 引数にアクセスする
VskAstPtr vsk_arg(const VskAstList& args, size_t index)
{
    if (index < args.size())
        return args[index];
    return nullptr;
}

// プログラムを実行する
VskAstPtr vsk_run(VskIndexList index_list = { I_PROGRAM_CODE }, bool clear_vars = true)
{
    mdbg_traceA("vsk_run\n");
    // オプションベースを初期化
    VSK_STATE()->m_option_base = -1;
    // エラーをクリアする
    VSK_STATE()->error_clear();
    // コントロールパスをセット
    VSK_IMPL()->m_control_path = index_list;
    // DATAの読み込み位置を初期化
    VSK_IMPL()->m_data_pointer = { I_PROGRAM_CODE };
    // 乱数の初期化
    vsk_rand_init(0);
    // DEF FNのデータを消す
    VSK_IMPL()->m_fn_to_path.clear();
    if (clear_vars)
    {
        // 変数を全部消す
        vsk_var_clear_all();
    }
    // プログラムリストをスキャン
    vsk_scan_program_list();

    return vsk_ast(INSN_DONT_GO_NEXT);
}

//////////////////////////////////////////////////////////////////////////////

static VskAstPtr vsk_COLOR_8801(const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 5))
        return nullptr;

    if (args.empty())
    {
        if (!VSK_SETTINGS()->m_unlimited_mode)
            VSK_ERROR_AND_RETURN(VSK_ERR_MISSING_OPERAND, nullptr);

        vsk_machine->reset_palette();
        VSK_STATE()->m_border_color = -1;
        vsk_machine->reset_border_color();
        return nullptr;
    }

    VskInt v0; // 機能コード
    if (VSK_STATE()->m_color_text)
        v0 = VSK_STATE()->m_text_attr.m_palette;
    else
        v0 = VSK_STATE()->m_text_attr.m_effect;

    VskInt v1 = VSK_STATE()->m_back_color; // 背景色
    VskInt v2 = VSK_STATE()->m_border_color; // 境界色
    VskInt v3 = VSK_STATE()->m_fore_color; // 前景色
    auto arg0 = vsk_arg(args, 0);
    auto arg1 = vsk_arg(args, 1);
    auto arg2 = vsk_arg(args, 2);
    auto arg3 = vsk_arg(args, 3);
    if ((!arg0 || vsk_int(v0, arg0)) &&
        (!arg1 || vsk_int(v1, arg1)) &&
        (!arg2 || vsk_int(v2, arg2)) &&
        (!arg3 || vsk_int(v3, arg3)))
    {
        if (!(0 <= v0 && v0 < 8))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (!vsk_machine->is_valid_color(v1) || !vsk_machine->is_valid_color(v3))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        // ボーダーカラーが変更されたか？
        bool border_change = (VSK_STATE()->m_border_color != v2);

        // 引数が全部省略されたら、ボーダーカラーをリセットする
        if (args.empty())
        {
            v2 = -1;
            border_change = true;
        }

        // 格納
        VSK_STATE()->m_text_attr.reset();
        if (VSK_STATE()->m_color_text)
        {
            VSK_STATE()->m_text_color = v0;
            VSK_STATE()->m_text_attr.m_palette = v0;
        }
        else
        {
            VSK_STATE()->m_text_color = (VSK_STATE()->m_green_console ? 4 : 7);
            VSK_STATE()->m_text_attr.m_palette = VSK_STATE()->m_text_color;
            VSK_STATE()->m_text_attr.m_effect = v0;
        }

        VSK_STATE()->m_back_color = v1;
        VSK_STATE()->m_border_color = v2;
        VSK_STATE()->m_fore_color = v3;
        VSK_STATE()->m_palette_mode = VSK_PAL_MODE_8_COLORS_DIGITAL;

        if (border_change)
        {
            // ボーダーカラーのリセット
            vsk_machine->reset_border_color();
        }
    }

    return nullptr;
}

static VskAstPtr vsk_COLOR_9801(const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 5))
        return nullptr;

    if (args.empty())
    {
        vsk_machine->reset_palette();
        VSK_STATE()->m_border_color = -1;
        vsk_machine->reset_border_color();
        return nullptr;
    }

    VskInt v0; // 機能コード
    if (VSK_STATE()->m_color_text)
        v0 = VSK_STATE()->m_text_attr.m_palette;
    else
        v0 = VSK_STATE()->m_text_attr.m_effect;

    VskInt v1 = VSK_STATE()->m_back_color; // 背景色
    VskInt v2 = VSK_STATE()->m_border_color; // 境界色
    VskInt v3 = VSK_STATE()->m_fore_color; // 前景色
    VskInt v4; // パレットモード
    auto arg0 = vsk_arg(args, 0);
    auto arg1 = vsk_arg(args, 1);
    auto arg2 = vsk_arg(args, 2);
    auto arg3 = vsk_arg(args, 3);
    auto arg4 = vsk_arg(args, 4);
    if ((!arg0 || vsk_int(v0, arg0)) &&
        (!arg1 || vsk_int(v1, arg1)) &&
        (!arg2 || vsk_int(v2, arg2)) &&
        (!arg3 || vsk_int(v3, arg3)) &&
        (!arg4 || vsk_int(v4, arg4)))
    {
        if (!arg4)
        {
            switch (VSK_STATE()->m_palette_mode)
            {
            case VSK_PAL_MODE_8_COLORS_DIGITAL: v4 = 0; break;
            case VSK_PAL_MODE_8_COLORS_SUPER:   v4 = 1; break;
            case VSK_PAL_MODE_16_COLORS_SUPER:  v4 = 2; break;
            }
        }
        VskPaletteMode palette_mode = static_cast<VskPaletteMode>(v4);

        if (!(0 <= v0 && v0 < 8))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (!vsk_machine->is_valid_color(v1) ||
            !vsk_machine->is_valid_color(v3) ||
            !(0 <= v4 && v4 <= 2))
        {
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        // ボーダーカラーが変更されたか？
        bool border_change = (VSK_STATE()->m_border_color != v2);

        // 引数が全部省略されたら、ボーダーカラーをリセットする
        if (args.empty())
        {
            v2 = -1;
            border_change = true;
        }

        // 格納
        VSK_STATE()->m_text_attr.reset();
        if (VSK_STATE()->m_color_text)
        {
            VSK_STATE()->m_text_color = v0;
            VSK_STATE()->m_text_attr.m_palette = v0;
        }
        else
        {
            VSK_STATE()->m_text_color = (VSK_STATE()->m_green_console ? 4 : 7);
            VSK_STATE()->m_text_attr.m_palette = VSK_STATE()->m_text_color;
            VSK_STATE()->m_text_attr.m_effect = v0;
        }

        VSK_STATE()->m_back_color = v1;
        VSK_STATE()->m_border_color = v2;
        VSK_STATE()->m_fore_color = v3;
        VSK_STATE()->m_palette_mode = palette_mode;

        // パレットモードがセットされたか、引数が全部省略されたら、パレットをリセットする
        if (arg4 || args.empty())
            vsk_machine->reset_palette();

        if (border_change)
        {
            // ボーダーカラーのリセット
            vsk_machine->reset_border_color();
        }
    }

    return nullptr;
}

// INSN_COLOR (COLOR) @implemented
static VskAstPtr VSKAPI vsk_COLOR(VskAstPtr self, const VskAstList& args)
{
#ifdef ENABLE_VM8801
    if (vsk_machine->is_8801_mode())
        return vsk_COLOR_8801(args);
#endif
#ifdef ENABLE_VM9801
    if (vsk_machine->is_9801_mode())
        return vsk_COLOR_9801(args);
#endif
    return nullptr;
}

// print_using.cpp
VskError vsk_PRINT_USING_helper(VskFilePtr file, const VskString& format_text, const VskAstList& args, bool& is_sep);

// INSN_PRINT_USING (PRINT USING / PRINT# USING) @implemented
static VskAstPtr VSKAPI vsk_PRINT_USING(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    VskString v1;
    if (!vsk_str(v1, args[1]))
        return nullptr;

    // 出力ファイルをセット
    VskFilePtr file;
    VskError error;
    if (args[0])
    {
        file = vsk_eval_file_number(args[0], error);
        if (!file)
            VSK_ERROR_AND_RETURN(error, nullptr);
    }
    else
    {
        file = vsk_get_screen_device();
    }

    bool is_sep;
    error = vsk_PRINT_USING_helper(file, v1, args[2]->children(), is_sep);
    if (error)
        VSK_ERROR_AND_RETURN(error, nullptr);

    if (!is_sep)
        file->write_str("\n");
    return nullptr;
}

// INSN_LPRINT_USING (LPRINT USING) @implemented
static VskAstPtr VSKAPI vsk_LPRINT_USING(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    if (!vsk_str(v0, args[0]))
        return nullptr;

    // 出力ファイルをセット
    VskFilePtr file = vsk_get_line_printer();

    bool is_sep;
    VskError error = vsk_PRINT_USING_helper(file, v0, args[1]->children(), is_sep);
    if (error)
        VSK_ERROR_AND_RETURN(error, nullptr);

    if (!is_sep)
        file->write_str("\n");
    return nullptr;
}

// INSN_PRINT (PRINT / PRINT#) @implemented
static VskAstPtr VSKAPI vsk_PRINT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    // 印字項目
    VskAstList printing_items;
    if (args[1])
        printing_items = args[1]->children();

    // 必要なら "\n" を追加
    if (printing_items.empty() ||
        (printing_items.back()->m_insn != INSN_SEMICOLON &&
         printing_items.back()->m_insn != INSN_SPC))
    {
        printing_items.push_back(vsk_ast_str("\n"));
    }

    // セミコロン(;)を取り除く
    for (size_t i = printing_items.size(); i > 0; )
    {
        --i;
        if (printing_items.at(i)->m_insn == INSN_SEMICOLON)
        {
            printing_items.erase(printing_items.begin() + i);
        }
    }

    // 印字項目をセット
    VSK_IMPL()->m_printing_items = std::move(printing_items);

    // 出力ファイルをセット
    if (args[0])
    {
        VskError error;
        VskFilePtr file = vsk_eval_file_number(args[0], error);
        if (!file)
            VSK_ERROR_AND_RETURN(error, nullptr);

        VSK_IMPL()->m_printing_device = file;
    }
    else
    {
        VSK_IMPL()->m_printing_device = vsk_get_screen_device();
    }

    assert(VSK_IMPL()->m_printing_device);
    VSK_IMPL()->m_printing_is_write = false; // WRITE文ではない

    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_LPRINT (LPRINT) @implemented
static VskAstPtr VSKAPI vsk_LPRINT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    // 印字項目
    VskAstList printing_items;
    if (args[0])
        printing_items = args[0]->children();

    // 最後にセミコロン(;)が付いてなかったら "\n" を追加
    if (printing_items.empty() || printing_items.back()->m_insn != INSN_SEMICOLON)
        printing_items.push_back(vsk_ast_str("\n"));

    // セミコロン(;)を取り除く
    for (size_t i = printing_items.size(); i > 0; )
    {
        --i;
        if (printing_items.at(i)->m_insn == INSN_SEMICOLON)
        {
            printing_items.erase(printing_items.begin() + i);
        }
    }

    // 印字項目をセット
    VSK_IMPL()->m_printing_items = std::move(printing_items);

    // 出力ファイルをセット
    VSK_IMPL()->m_printing_device = vsk_get_line_printer();

    assert(VSK_IMPL()->m_printing_device);
    VSK_IMPL()->m_printing_is_write = false; // WRITE文ではない

    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_WRITE (WRITE) @implemented
static VskAstPtr VSKAPI vsk_WRITE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskAstList printing_items;
    if (args[1])
        printing_items = args[1]->children();

    // 空なら改行を出力
    if (printing_items.empty())
        printing_items.push_back(vsk_ast_str("\n"));

    // 印字項目をセット
    VSK_IMPL()->m_printing_items = std::move(printing_items);

    // 出力ファイルをセット
    if (args[0])
    {
        VskError error;
        VskFilePtr file = vsk_eval_file_number(args[0], error);
        if (!file)
            VSK_ERROR_AND_RETURN(error, nullptr);

        VSK_IMPL()->m_printing_device = file;
    }
    else
    {
        VSK_IMPL()->m_printing_device = vsk_get_screen_device();
    }

    assert(VSK_IMPL()->m_printing_device);
    VSK_IMPL()->m_printing_is_write = true; // WRITE文

    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_REM (コメント) @implemented
static VskAstPtr VSKAPI vsk_REM(VskAstPtr self, const VskAstList& args)
{
    vsk_process_comment(self->m_str);
    return nullptr;
}

// INSN_ERROR (ERROR) @implemented
static VskAstPtr VSKAPI vsk_ERROR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        if (!(1 <= v0 && v0 < 255))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        vsk_machine->do_error(static_cast<VskError>(v0));
    }

    return nullptr;
}

// ファイルを削除する
VskError vsk_delete_file(const char *filename);

// INSN_KILL (KILL) @implemented
static VskAstPtr VSKAPI vsk_KILL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        VskFile::TYPE type;
        VskString device, raw_path;
        if (!vsk_parse_file_descriptor(v0, type, device, raw_path))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_FILE_NAME, nullptr);

        if (type != VskFile::TYPE_HOST_FILE)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_DRIVE_NO, nullptr);

        if (!vsk_is_safe_zone_pathname(raw_path, true))
        {
            vsk_print("Security error!\b\n"); // "\b"でBEEP音を鳴らす
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        if (auto error = vsk_delete_file(raw_path.c_str()))
            VSK_ERROR_AND_RETURN(error, nullptr);
    }

    return nullptr;
}

// INSN_DATE_dollar (DATE$) @implemented
static VskAstPtr VSKAPI vsk_DATE_dollar(VskAstPtr self, const VskAstList& args)
{
    VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
}

// INSN_TIME_dollar (TIME$) @implemented
static VskAstPtr VSKAPI vsk_TIME_dollar(VskAstPtr self, const VskAstList& args)
{
    VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
}

// INSN_DATE_dollar_var (DATE$ 変数みたいな) @implemented
static VskAstPtr VSKAPI vsk_DATE_dollar_var(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    std::time_t t = std::time(nullptr);
    std::tm *ptime = std::localtime(&t);
    if (!ptime)
    {
        vsk_machine->bad_call();
        return nullptr;
    }

    int year = ptime->tm_year + 1900;
    int month = ptime->tm_mon + 1; // make it 1-base
    assert(1900 <= year && year < 10000);
    assert(1 <= month && month <= 12);
    assert(1 <= ptime->tm_mday && ptime->tm_mday <= 31);

    char buf[256];
    std::sprintf(buf, "%02u/%02u/%02u", year % 100, month, ptime->tm_mday);
    assert(std::strlen(buf) < 256);
    return vsk_ast_str(VskString(buf));
}

// INSN_TIME_dollar_var (TIME$ 変数みたいな) @implemented
static VskAstPtr VSKAPI vsk_TIME_dollar_var(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    return vsk_ast_str(vsk_get_time());
}

// INSN_NAME (NAME) @implemented
static VskAstPtr VSKAPI vsk_NAME(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    VskString v0, v1, v2;
    if (vsk_str(v0, args[0]) &&
        vsk_ident(v1, args[1]) &&
        vsk_str(v2, args[2]))
    {
        if (v1 != "AS")
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        // ファイル記述子をパースする
        VskFile::TYPE type0, type1;
        VskString device0, device1;
        VskString raw_path0, raw_path1;
        if (!vsk_parse_file_descriptor(v0, type0, device0, raw_path0) ||
            !vsk_parse_file_descriptor(v2, type1, device1, raw_path1))
        {
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        // 安全圏か？
        if (!vsk_is_safe_zone_pathname(raw_path0, true) ||
            !vsk_is_safe_zone_pathname(raw_path1, true))
        {
            vsk_print("Security error!\b\n"); // "\b"でBEEP音を鳴らす
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        // 変更先を消す
        vsk_delete_file(raw_path1.c_str());

        // 名前を変える
        if (rename(raw_path0.c_str(), raw_path1.c_str()) == 0)
            return nullptr;

        switch (errno)
        {
        case EACCES:
            vsk_machine->do_error(VSK_ERR_FILE_ALREADY_EXIST);
            break;
        case ENOENT:
            vsk_machine->do_error(VSK_ERR_FILE_NOT_FOUND);
            break;
        default:
            vsk_machine->do_error(VSK_ERR_DISK_IO_ERROR);
            break;
        }
    }

    return nullptr;
}

// INSN_DEF_SEG (DEF SEG=) @implemented
static VskAstPtr VSKAPI vsk_DEF_SEG(VskAstPtr self, const VskAstList& args)
{
    if (vsk_machine->is_8801_mode())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskWord v0;
    if (vsk_wrd(v0, args[0]))
        VSK_STATE()->m_segment = v0;

    return nullptr;
}

// INSN_PEEK (PEEK) @implemented
static VskAstPtr VSKAPI vsk_PEEK(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskWord v0;
    if (vsk_wrd(v0, args[0]))
    {
        auto addr = vsk_machine->resolve_addr(v0);
        VskByte byte = 0;
        VSK_STATE()->m_memory->read(&byte, addr, 1);
        return vsk_ast_int(VskInt(byte));
    }

    return nullptr;
}

// INSN_POKE (POKE) @implemented
static VskAstPtr VSKAPI vsk_POKE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskWord v0, v1;
    if (vsk_wrd(v0, args[0]) && vsk_wrd(v1, args[1]))
    {
        if (!(0 <= v1 && v1 < 256))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        auto addr = vsk_machine->resolve_addr(v0);
        auto byte = VskByte(v1);
        VSK_STATE()->m_memory->write(&byte, addr, 1);
    }

    return nullptr;
}

// INSN_CINT (CINT) @implemented
static VskAstPtr VSKAPI vsk_CINT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
        return vsk_ast_int(v0);

    return nullptr;
}

// INSN_CLNG (CLNG) @implemented
static VskAstPtr VSKAPI vsk_CLNG(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskLong v0;
    if (vsk_lng(v0, args[0]))
        return vsk_ast_lng(v0);

    return nullptr;
}

// INSN_CSNG (CSNG) @implemented
static VskAstPtr VSKAPI vsk_CSNG(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskSingle v0;
    if (vsk_sng(v0, args[0]))
        return vsk_ast_sng(v0);
    return nullptr;
}

// INSN_CDBL (CDBL) @implemented
static VskAstPtr VSKAPI vsk_CDBL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskDouble v0;
    if (vsk_dbl(v0, args[0]))
        return vsk_ast_dbl(v0);
    return nullptr;
}

// INSN_CHR_dollar (CHR$) @implemented
static VskAstPtr VSKAPI vsk_CHR_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        VskString str;
        if (!(0 <= v0 && v0 < 256))
        {
            if (!vsk_is_sjis_code(v0))
            {
                vsk_machine->bad_call();
                return nullptr;
            }
            str += vsk_high_byte(v0);
            str += vsk_low_byte(v0);
        }
        else
        {
            str += (char)v0;
        }
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_UMINUS (-; unary minus) @implemented
static VskAstPtr VSKAPI vsk_UMINUS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
    {
        return nullptr;
    }
    else if (arg0->is_str())
    {
        ;
    }
    else if (arg0->is_dbl())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
            return vsk_ast_dbl(-v0);
    }
    else if (arg0->is_sng())
    {
        VskSingle v0;
        if (vsk_sng(v0, arg0))
            return vsk_ast_sng(-v0);
    }
    else if (arg0->is_lng())
    {
        VskLong v0;
        if (vsk_lng(v0, arg0))
            return vsk_ast_lng(-v0);
    }
    else if (arg0->is_int())
    {
        VskInt v0;
        if (vsk_int(v0, arg0))
            return vsk_ast_int(-v0);
    }
    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);
}

// INSN_ABS (ABS) @implemented
static VskAstPtr VSKAPI vsk_ABS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0 || arg0->is_str())
    {
        ;
    }
    else if (arg0->is_sng())
    {
        VskSingle v0;
        if (vsk_sng(v0, arg0))
            return vsk_ast_sng(std::abs(v0));
    }
    else if (arg0->is_dbl())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
            return vsk_ast_dbl(std::abs(v0));
    }
    else if (arg0->is_lng())
    {
        VskLong v0;
        if (vsk_lng(v0, arg0))
            return vsk_ast_lng(std::abs(v0));
    }
    else if (arg0->is_int())
    {
        VskInt v0;
        if (vsk_int(v0, arg0))
        {
#ifndef INT_IS_32BIT
            // EPSONのマニュアルより：
            // 「*数式* が整数でその値が -32768 のときに限り、単精度実数の 32768 を返す」
            if (v0 == -32768)
                return vsk_ast_sng(32768);
#endif
            return vsk_ast_int(std::abs(v0));
        }
    }
    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);
}

// INSN_LT (<) @implemented
static VskAstPtr VSKAPI vsk_LT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;
    if (arg0->is_str() && arg1->is_str())
    {
        VskString v0, v1;
        if (vsk_str(v0, arg0) && vsk_str(v1, arg1))
            return vsk_ast_int((v0 < v1) ? -1 : 0);
    }
    else
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, arg0) && vsk_dbl(v1, arg1))
            return vsk_ast_int((v0 < v1) ? -1 : 0);
    }

    return nullptr;
}

// INSN_LE (<=, =<) @implemented
static VskAstPtr VSKAPI vsk_LE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;
    if (arg0->is_str() && arg1->is_str())
    {
        VskString v0, v1;
        if (vsk_str(v0, arg0) && vsk_str(v1, arg1))
            return vsk_ast_int((v0 <= v1) ? -1 : 0);
    }
    else
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, arg0) && vsk_dbl(v1, arg1))
            return vsk_ast_int((v0 <= v1) ? -1 : 0);
    }

    return nullptr;
}

// INSN_GT (>) @implemented
static VskAstPtr VSKAPI vsk_GT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;
    if (arg0->is_str() || arg1->is_str())
    {
        VskString v0, v1;
        if (vsk_str(v0, arg0) && vsk_str(v1, arg1))
            return vsk_ast_int((v0 > v1) ? -1 : 0);
    }
    else
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, arg0) && vsk_dbl(v1, arg1))
            return vsk_ast_int((v0 > v1) ? -1 : 0);
    }

    return nullptr;
}

// INSN_GE (>=, =>) @implemented
static VskAstPtr VSKAPI vsk_GE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;
    if (arg0->is_str() || arg1->is_str())
    {
        VskString v0, v1;
        if (vsk_str(v0, arg0) && vsk_str(v1, arg1))
            return vsk_ast_int((v0 >= v1) ? -1 : 0);
    }
    else
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, arg0) && vsk_dbl(v1, arg1))
            return vsk_ast_int((v0 >= v1) ? -1 : 0);
    }

    return nullptr;
}

// INSN_EQUAL (=) @implemented
static VskAstPtr VSKAPI vsk_EQUAL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;
    if (arg0->is_str() || arg1->is_str())
    {
        VskString v0, v1;
        if (vsk_str(v0, arg0) && vsk_str(v1, arg1))
            return vsk_ast_int((v0 == v1) ? -1 : 0);
    }
    else
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, arg0) && vsk_dbl(v1, arg1))
            return vsk_ast_int((v0 == v1) ? -1 : 0);
    }

    return nullptr;
}

// INSN_NE (<>, ><) @implemented
static VskAstPtr VSKAPI vsk_NE(VskAstPtr self, const VskAstList& args)
{
    VskAstPtr ret = vsk_EQUAL(self, args);
    if (!ret)
        return nullptr;
    return vsk_ast_int(!ret->m_int ? -1 : 0);
}

// INSN_ADD (+) @implemented
static VskAstPtr VSKAPI vsk_ADD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;

    if (arg0->is_str() || arg1->is_str())
    {
        VskString v0, v1;
        if (vsk_str(v0, arg0) && vsk_str(v1, arg1))
        {
            auto ret = v0 + v1;
            if (!VSK_SETTINGS()->m_unlimited_mode && ret.size() > VSK_MAX_STR_LEN)
                VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
            return vsk_ast_str(ret);
        }
    }
    else if (arg0->is_floating())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
        {
            if (arg1->is_floating())
            {
                VskDouble v1;
                if (vsk_dbl(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 + v1);
                }
            }
            else if (arg1->is_integer())
            {
                VskLong v1;
                if (vsk_lng(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 + v1);
                }
            }
        }
    }
    else if (arg0->is_integer())
    {
        VskLong v0;
        if (vsk_lng(v0, arg0))
        {
            if (arg1->is_floating())
            {
                VskDouble v1;
                if (vsk_dbl(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 + v1);
                }
            }
            else if (arg1->is_integer())
            {
                VskLong v1;
                if (vsk_lng(v1, arg1))
                {
                    vsk_targeting(self);
                    if (arg0->is_lng() || arg1->is_lng())
                        return vsk_ast_lng(v0 + v1);
                    else
                        return vsk_ast_int(v0 + v1);
                }
            }
        }
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);
}

// INSN_SUB (-) @implemented
static VskAstPtr VSKAPI vsk_SUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;

    if (arg0->is_floating())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
        {
            if (arg1->is_floating())
            {
                VskDouble v1;
                if (vsk_dbl(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 - v1);
                }
            }
            else if (arg1->is_integer())
            {
                VskLong v1;
                if (vsk_lng(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 - v1);
                }
            }
        }
    }
    else if (arg0->is_integer())
    {
        VskLong v0;
        if (vsk_lng(v0, arg0))
        {
            if (arg1->is_floating())
            {
                VskDouble v1;
                if (vsk_dbl(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 - v1);
                }
            }
            else if (arg1->is_integer())
            {
                VskLong v1;
                if (vsk_lng(v1, arg1))
                {
                    vsk_targeting(self);
                    if (arg0->is_lng() || arg1->is_lng())
                        return vsk_ast_lng(v0 - v1);
                    else
                        return vsk_ast_int(v0 - v1);
                }
            }
        }
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);
}

// INSN_MUL (*) @implemented
static VskAstPtr VSKAPI vsk_MUL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;

    if (arg0->is_floating())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
        {
            if (arg1->is_floating())
            {
                VskDouble v1;
                if (vsk_dbl(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 * v1);
                }
            }
            else if (arg1->is_integer())
            {
                VskLong v1;
                if (vsk_lng(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 * v1);
                }
            }
        }
    }
    else if (arg0->is_integer())
    {
        VskLong v0;
        if (vsk_lng(v0, arg0))
        {
            if (arg1->is_floating())
            {
                VskDouble v1;
                if (vsk_dbl(v1, arg1))
                {
                    vsk_targeting(self);
                    return vsk_ast_dbl(v0 * v1);
                }
            }
            else if (arg1->is_integer())
            {
                VskLong v1;
                if (vsk_lng(v1, arg1))
                {
                    vsk_targeting(self);
                    if (arg0->is_lng() || arg1->is_lng())
                        return vsk_ast_lng(v0 * v1);
                    else
                        return vsk_ast_int(v0 * v1);
                }
            }
        }
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);
}

// INSN_DIV (/) @implemented
static VskAstPtr VSKAPI vsk_DIV(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;

    if (arg0->is_dbl() || arg1->is_dbl())
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, args[0]) && vsk_dbl(v1, args[1]))
        {
            vsk_targeting(self);
            return vsk_ast_dbl(v0 / v1);
        }
    }
    else
    {
        VskSingle v0, v1;
        if (vsk_sng(v0, args[0]) && vsk_sng(v1, args[1]))
        {
            vsk_targeting(self);
            return vsk_ast_sng(v0 / v1);
        }
    }

    return nullptr;
}

// INSN_IDIV (\) @implemented
static VskAstPtr VSKAPI vsk_IDIV(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        vsk_targeting(self);
        if (v1 == 0)
        {
            VSK_ERROR_AND_RETURN(VSK_ERR_DIV_BY_ZERO, nullptr);
        }
        return vsk_ast_int(v0 / v1);
    }

    return nullptr;
}

// INSN_MOD (MOD) @implemented
static VskAstPtr VSKAPI vsk_MOD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (v1 == 0)
        {
            vsk_targeting(self);
            VSK_ERROR_AND_RETURN(VSK_ERR_DIV_BY_ZERO, nullptr);
        }
        return vsk_ast_int(v0 % v1);
    }
    return nullptr;
}

// INSN_HAT (^) @implemented
static VskAstPtr VSKAPI vsk_HAT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    auto arg1 = vsk_eval_ast(args[1]);
    if (!arg1)
        return nullptr;

    if (arg0->is_dbl() || arg1->is_dbl())
    {
        VskDouble v0, v1;
        if (vsk_dbl(v0, args[0]) && vsk_dbl(v1, args[1]))
        {
            vsk_targeting(self);
            return vsk_ast_dbl(std::pow(v0, v1));
        }
    }
    else
    {
        VskSingle v0, v1;
        if (vsk_sng(v0, args[0]) && vsk_sng(v1, args[1]))
        {
            vsk_targeting(self);
            return vsk_ast_sng(VskSingle(std::pow(v0, v1)));
        }
    }
    return nullptr;
}

// INSN_AND (AND) @implemented
static VskAstPtr VSKAPI vsk_AND(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        vsk_targeting(self);
        return vsk_ast_int(v0 & v1);
    }
    return nullptr;
}

// INSN_OR (OR) @implemented
static VskAstPtr VSKAPI vsk_OR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        vsk_targeting(self);
        return vsk_ast_int(v0 | v1);
    }
    return nullptr;
}

// INSN_XOR (XOR) @implemented
static VskAstPtr VSKAPI vsk_XOR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        vsk_targeting(self);
        return vsk_ast_int(v0 ^ v1);
    }
    return nullptr;
}

// INSN_IMP (IMP) @implemented
static VskAstPtr VSKAPI vsk_IMP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        vsk_targeting(self);
        return vsk_ast_int((~v0) | v1);
    }
    return nullptr;
}

// INSN_EQV (EQV) @implemented
static VskAstPtr VSKAPI vsk_EQV(VskAstPtr self, const VskAstList& args)
{
    auto ret = vsk_XOR(self, args);
    if (!ret)
        return nullptr;
    ret->m_int = ~ret->m_int;
    return ret;
}

// INSN_SIN (SIN) @implemented
static VskAstPtr VSKAPI vsk_SIN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::sin(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::sin(v0)));
    }
    return nullptr;
}

// INSN_COS (COS) @implemented
static VskAstPtr VSKAPI vsk_COS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::cos(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::cos(v0)));
    }
    return nullptr;
}

// INSN_TAN (TAN) @implemented
static VskAstPtr VSKAPI vsk_TAN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::tan(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::tan(v0)));
    }
    return nullptr;
}

// INSN_EXP (EXP) @implemented
static VskAstPtr VSKAPI vsk_EXP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::exp(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::exp(v0)));
    }
    return nullptr;
}

// INSN_LOG (LOG) @implemented
static VskAstPtr VSKAPI vsk_LOG(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::log(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::log(v0)));
    }
    return nullptr;
}

// INSN_SQR (SQR) @implemented
static VskAstPtr VSKAPI vsk_SQR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::sqrt(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::sqrt(v0)));
    }
    return nullptr;
}

// INSN_ATN (ATN) @implemented
static VskAstPtr VSKAPI vsk_ATN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;
    if (arg0->is_dbl())
    {
        vsk_targeting(self);
        return vsk_ast_dbl(VskDouble(std::atan(arg0->m_dbl)));
    }
    VskSingle v0;
    if (vsk_sng(v0, args[0]))
    {
        vsk_targeting(self);
        return vsk_ast_sng(VskSingle(std::atan(v0)));
    }
    return nullptr;
}

// INSN_SPACE_dollar (SPACE$) @implemented
static VskAstPtr VSKAPI vsk_SPACE_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        if (v0 < 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        if (v0 > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        return vsk_ast_str(VskString(v0, ' '));
    }
    return nullptr;
}

// INSN_SPC (SPC) @implemented
static VskAstPtr VSKAPI vsk_SPC(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    auto device = VSK_IMPL()->m_printing_device;
    if (vsk_int(v0, args[0]) && v0 > 0 && device)
    {
        int line_width = device->line_width();
        if (line_width > 0 && v0 >= line_width)
            v0 %= line_width;
        return vsk_ast_str(VskString(v0, ' '));
    }
    return nullptr;
}

// INSN_TAB (TAB) @implemented
static VskAstPtr VSKAPI vsk_TAB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    auto device = VSK_IMPL()->m_printing_device;
    if (vsk_int(v0, args[0]) && v0 > 0 && device)
    {
        int line_width = device->line_width();
        if (line_width > 0 && v0 >= line_width)
            v0 %= line_width;
        VskInt v1 = device->get_x();
        if (v0 >= v1)
            return vsk_ast_str(VskString(v0 - v1, ' '));
        VskString str = "\n";
        str += VskString(v0, ' ');
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_POS (POS) @implemented
static VskAstPtr VSKAPI vsk_POS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    VskInt ret = VskInt(VSK_STATE()->m_caret_x);
    assert(0 <= ret && ret < 80);
    return vsk_ast_int(VskInt(VSK_STATE()->m_caret_x));
}

// INSN_CSRLIN (CSRLIN) @implemented
static VskAstPtr VSKAPI vsk_CSRLIN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;
    VskInt ret = VskInt(VSK_STATE()->m_caret_y);
    assert(0 <= ret && ret < 25);
    return vsk_ast_int(ret);
}

// INSN_LOCATE (LOCATE) @implemented
static VskAstPtr VSKAPI vsk_LOCATE(VskAstPtr self, const VskAstList& args)
{
    if (args.size() == 0)
        VSK_ERROR_AND_RETURN(VSK_ERR_MISSING_OPERAND, nullptr);

    if (!vsk_arity_in_range(args, 1, 3))
        return nullptr;

    VskInt v0 = 0;
    VskInt v1 = VSK_STATE()->m_caret_y;
    VskInt v2 = VSK_STATE()->m_show_caret;
    auto arg0 = vsk_arg(args, 0);
    auto arg1 = vsk_arg(args, 1);
    auto arg2 = vsk_arg(args, 2);
    if ((!arg0 || vsk_int(v0, args[0])) &&
        (!arg1 || vsk_int(v1, args[1])) &&
        (!arg2 || vsk_int(v2, args[2])))
    {
        if (v0 < 0 || v1 < 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        if (!VSK_SETTINGS()->m_unlimited_mode)
        {
            if (vsk_machine->is_8801_mode() && v2 != 0 && v2 != 1)
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
        if (VSK_STATE()->m_text_width <= v0)
            v0 = VSK_STATE()->m_text_width - 1;
        if (VSK_STATE()->m_text_height <= v1)
            v1 = VSK_STATE()->m_text_height - 1;
        assert(v0 >= 0);
        assert(v1 >= 0);
        VSK_STATE()->m_caret_x = v0;
        VSK_STATE()->m_caret_y = v1;
        VSK_STATE()->m_show_caret = !!v2;
    }
    return nullptr;
}

// INSN_POINT_func (POINT 関数)
static VskAstPtr VSKAPI vsk_POINT_func(VskAstPtr self, const VskAstList& args)
{
    if (args.size() == 1)
    {
        VskInt v0;
        if (vsk_int(v0, args[0]))
        {
            switch (v0)
            {
            case 0:
                return vsk_ast_dbl(VSK_STATE()->m_last_point_in_world.m_x);
            case 1:
                return vsk_ast_dbl(VSK_STATE()->m_last_point_in_world.m_y);
            case 2:
                return vsk_ast_int(vsk_machine->world_to_view(VSK_STATE()->m_last_point_in_world).m_x);
            case 3:
                return vsk_ast_int(vsk_machine->world_to_view(VSK_STATE()->m_last_point_in_world).m_y);
            default:
                vsk_machine->bad_call();
                break;
            }
        }
        return nullptr;
    }

    if (args.size() == 2)
    {
        VskInt v0, v1;
        if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
        {
            int pixel = vsk_machine->get_pixel(v0, v1);
            return vsk_ast_int(VskInt(pixel));
        }
        return nullptr;
    }

    VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
}

// INSN_POINT (POINT文) @implemented
static VskAstPtr VSKAPI vsk_POINT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskSingle v0, v1;
    if (vsk_sng(v0, args[0]) && vsk_sng(v1, args[1]))
    {
        VSK_STATE()->m_last_point_in_world = { v0, v1 };
        return nullptr;
    }
    return nullptr;
}

// INSN_POINT_STEP (POINT STEP文) @implemented
static VskAstPtr VSKAPI vsk_POINT_STEP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskSingle v0, v1;
    if (vsk_sng(v0, args[0]) && vsk_sng(v1, args[1]))
    {
        VSK_STATE()->m_last_point_in_world.m_x += v0;
        VSK_STATE()->m_last_point_in_world.m_y += v1;
        return nullptr;
    }
    return nullptr;
}

enum DIR_OP
{
    DIR_OP_CHDIR, DIR_OP_MKDIR, DIR_OP_RMDIR,
    DIR_OP_CHDIR_PARENT,
};

static VskAstPtr vsk_CHDIR_MKDIR_RMDIR(VskAstPtr self, const VskAstList& args, DIR_OP op)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    auto arg0 = vsk_arg(args, 0);
    if (!arg0) // 引数がない？
    {
        switch (op)
        {
        case DIR_OP_CHDIR:
            {
                auto dir = vsk_getcwd();
                vsk_print(dir + "\n");
                return nullptr;
            }
            break;
        case DIR_OP_MKDIR:
        case DIR_OP_RMDIR:
        case DIR_OP_CHDIR_PARENT:
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
        }
    }

    // 引数を評価する
    arg0 = vsk_eval_ast(arg0);

    // 数字だったらドライブのパス名に変更
    if (arg0->is_number())
        arg0 = vsk_ast_str(vsk_to_string(arg0->to_int()) + ":");

    // 文字列だったらそれをファイル記述子と見なす
    if (arg0->is_str())
    {
        // ファイル記述子を解析する
        VskFile::TYPE type;
        VskString device, raw_path;
        if (!vsk_parse_file_descriptor(arg0->m_str, type, device, raw_path))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_FILE_NAME, nullptr);

        mdbg_traceA("%s -> %s\n", arg0->m_str.c_str(), raw_path.c_str());

        // ホストファイルでなければ失敗
        if (type != VskFile::TYPE_HOST_FILE)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_FILE_NAME, nullptr);

        switch (op)
        {
        case DIR_OP_CHDIR_PARENT:
            raw_path = vsk_path_remove_filename(raw_path);
            // 現在のディレクトリを変更する
            if (auto error = vsk_chdir(raw_path.c_str()))
                VSK_ERROR_AND_RETURN(error, nullptr);
            return nullptr;
        case DIR_OP_CHDIR:
            // 現在のディレクトリを変更する
            if (auto error = vsk_chdir(raw_path.c_str()))
                VSK_ERROR_AND_RETURN(error, nullptr);
            if (op != DIR_OP_CHDIR_PARENT)
                vsk_print("Moved to: " + raw_path + "\n");
            return nullptr;
        case DIR_OP_MKDIR:
            // ディレクトリを作成する
            if (auto error = vsk_mkdir(raw_path.c_str()))
                VSK_ERROR_AND_RETURN(error, nullptr);
            vsk_print("Created: " + raw_path + "\n");
            return nullptr;
        case DIR_OP_RMDIR:
            // ディレクトリを削除する
            if (auto error = vsk_rmdir(raw_path.c_str()))
                VSK_ERROR_AND_RETURN(error, nullptr);
            vsk_print("Deleted: " + raw_path + "\n");
            return nullptr;
        }
    }

    return nullptr;
}

// INSN_CHDIR (CHDIR) @implemented
static VskAstPtr VSKAPI vsk_CHDIR(VskAstPtr self, const VskAstList& args)
{
    return vsk_CHDIR_MKDIR_RMDIR(self, args, DIR_OP_CHDIR);
}

// INSN_MKDIR (MKDIR) @implemented
static VskAstPtr VSKAPI vsk_MKDIR(VskAstPtr self, const VskAstList& args)
{
    return vsk_CHDIR_MKDIR_RMDIR(self, args, DIR_OP_MKDIR);
}

// INSN_RMDIR (RMDIR) @implemented
static VskAstPtr VSKAPI vsk_RMDIR(VskAstPtr self, const VskAstList& args)
{
    return vsk_CHDIR_MKDIR_RMDIR(self, args, DIR_OP_RMDIR);
}

static VskAstPtr vsk_SCREEN_GENERIC(const VskAstList& args, bool is_9801)
{
    if (!vsk_arity_in_range(args, 0, 4))
        return nullptr;

    VskInt v0 = VSK_STATE()->m_screen_mode;
    VskInt v1 = (VSK_STATE()->m_show_graphics ? 1 : 3);
    VskInt v2 = VSK_STATE()->m_active_page;
    VskInt v3 = VSK_STATE()->m_display_pages;
    auto arg0 = vsk_arg(args, 0), arg1 = vsk_arg(args, 1);
    auto arg2 = vsk_arg(args, 2), arg3 = vsk_arg(args, 3);
    if ((!arg0 || vsk_int(v0, arg0)) &&
        (!arg1 || vsk_int(v1, arg1)) &&
        (!arg2 || vsk_int(v2, arg2)) &&
        (!arg3 || vsk_int(v3, arg3)))
    {
        if (!is_9801) // 8801？
        {
            if (v0 == 3 || v0 == 4) // 8801の日本語サポート？
            {
                if (arg1 || arg2 || arg3)
                {
                    assert(0);
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
                }

                // シフトJISモードにする
                VSK_SETTINGS()->m_text_mode = VSK_TEXT_MODE_SJIS;

                v2 = 0;
                v3 = 1;
            }
        }

        bool high_color = (VSK_STATE()->m_palette_mode == VSK_PAL_MODE_16_COLORS_SUPER);
        if (!vsk_machine->is_valid_screen_mode(v0) ||
            !(0 <= v1 && v1 < 4) ||
            !vsk_machine->is_valid_active_page(v0, v2, high_color) ||
            vsk_machine->get_display_pages_flags(v0, v3) == -1)
        {
            assert(0);
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        VSK_STATE()->m_screen_mode = v0;
        VSK_STATE()->m_show_graphics = !(v1 & 2);
        VSK_STATE()->m_active_page = v2;
        VSK_STATE()->m_display_pages = v3;
        vsk_machine->reset_graphics();
        VSK_IMPL()->m_draw_engine.reset();
        VSK_IMPL()->m_turtle_engine.reset();
    }

    return nullptr;
}

// INSN_SCREEN (SCREEN) @implemented
static VskAstPtr VSKAPI vsk_SCREEN(VskAstPtr self, const VskAstList& args)
{
    vsk_targeting(self);
#ifdef ENABLE_VM8801
    if (vsk_machine->is_8801_mode())
        return vsk_SCREEN_GENERIC(args, false);
#endif
#ifdef ENABLE_VM9801
    if (vsk_machine->is_9801_mode())
        return vsk_SCREEN_GENERIC(args, true);
#endif
    assert(0);
    return nullptr;
}

// INSN_CLS (CLS) @implemented
static VskAstPtr VSKAPI vsk_CLS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    VskInt v0 = 1;
    if (args.size() == 0 || vsk_int(v0, args[0]))
    {
        if (!(1 <= v0 && v0 <= 3))
           VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
 
        if (v0 & 1)
        {
            vsk_machine->clear_text();
            VSK_STATE()->m_caret_x = 0;
            VSK_STATE()->m_caret_y = VSK_STATE()->m_console_y0;
        }
        if (v0 & 2)
        {
            vsk_machine->clear_graphic();
            VSK_STATE()->m_last_point_in_world = vsk_machine->client_to_world(VSK_STATE()->m_viewport.m_pt0);
        }

        // 編集モードを解除
        VSK_STATE()->m_edit_mode = false;
    }

    return nullptr;
}

// INSN_CMD_CLS (CMD CLS) @implemented
static VskAstPtr VSKAPI vsk_CMD_CLS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (!vsk_machine->is_9801_mode() || !vsk_machine->has_turtle())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VskInt v0 = 1;
    auto arg0 = vsk_arg(args, 0);
    if ((!arg0 || vsk_int(v0, arg0)))
    {
        if (1 <= v0 && v0 <= 3)
        {
            if (v0 & 1)
            {
                vsk_machine->clear_text();
                VSK_STATE()->m_caret_x = 0;
                VSK_STATE()->m_caret_y = VSK_STATE()->m_console_y0;
            }
            if (v0 & 2)
            {
                VskRectI rect =
                {
                    0, 0,
                    VSK_STATE()->m_screen_width - 1,
                    VSK_STATE()->m_screen_height - 1
                };
                vsk_machine->clear_graphic(&rect);
            }
            return nullptr;
        }

        if (9 <= v0 && v0 <= 15)
        {
            auto flags = v0 - 8;
            vsk_machine->clear_planes(!!(flags & 1), !!(flags & 2), !!(flags & 4), !!(flags & 8));
            return nullptr;
        }
    }

    vsk_machine->bad_call();
    return nullptr;
}

// INSN_BLOAD (BLOAD) @implemented
static VskAstPtr VSKAPI vsk_BLOAD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 3))
        return nullptr;

    VskString v0;
    VskWord v1;
    VskString v2;
    auto arg0 = vsk_arg(args, 0), arg1 = vsk_arg(args, 1), arg2 = vsk_arg(args, 2);
    if (vsk_str(v0, args[0]) &&
        (!arg1 || vsk_wrd(v1, args[1])) &&
        (!arg2 || vsk_ident(v2, args[2])))
    {
        if (v2 != "" && v2 != "R")
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        vsk_upper(v0);
        if (VSK_SETTINGS()->m_unlimited_mode || vsk_machine->is_8801_mode())
        {
            if (v0.find("@EXST*V1") != v0.npos ||
                v0.find("@EXST*V2") != v0.npos ||
                v0.find("1:@EXST*V1") != v0.npos ||
                v0.find("1:@EXST*V2") != v0.npos)
            {
                VSK_STATE()->m_has_turtle = true;
                return nullptr;
            }
            if (v0.find("@EXST") != v0.npos ||
                v0.find("1:@EXST") != v0.npos)
            {
                VSK_STATE()->m_has_turtle = true;
                VSK_STATE()->m_has_cmd_extension = true;
                return nullptr;
            }
        }

        VskAddr addr = arg1 ? v1 : 0xFFFFFFFF;

        VskMemSize size;
        VskAddr call_addr = addr;
        if (vsk_machine->is_8801_mode())
        {
            if (!vsk_machine->binary_load_with_header(v0.c_str(), addr, size, call_addr))
                return nullptr;
        }
        else
        {
            if (!vsk_machine->binary_load(v0.c_str(), addr, size))
                return nullptr;
        }

        if (v2 == "R")
        {
            mdbg_traceA("TODO: Call call_addr\n");
        }
    }

    return nullptr;
}

// INSN_BSAVE (BSAVE) @implemented
static VskAstPtr VSKAPI vsk_BSAVE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    VskString v0;
    VskWord v1, v2;
    if (vsk_str(v0, args[0]) && vsk_wrd(v1, args[1]) && vsk_wrd(v2, args[2]))
    {
        VskAddr addr = v1, size = v2;
        if (vsk_machine->is_8801_mode())
        {
            vsk_machine->binary_save_with_header(v0.c_str(), addr, size);
        }
        else
        {
            vsk_machine->binary_save(v0.c_str(), addr, size);
        }
    }

    return nullptr;
}

// INSN_CONSOLE (CONSOLE) @implemented
static VskAstPtr VSKAPI vsk_CONSOLE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 4))
        return nullptr;

    VskInt v0 = VSK_STATE()->m_console_y0;
    VskInt v1 = VSK_STATE()->m_console_cy0;
    VskInt v2 = VSK_STATE()->m_show_function_keys;
    VskInt v3 = VSK_STATE()->m_color_text;
    auto arg0 = args[0];
    auto arg1 = (args.size() > 1) ? args[1] : nullptr;
    auto arg2 = (args.size() > 2) ? args[2] : nullptr;
    auto arg3 = (args.size() > 3) ? args[3] : nullptr;
    if ((!arg0 || vsk_int(v0, arg0)) &&
        (!arg1 || vsk_int(v1, arg1)) &&
        (!arg2 || vsk_int(v2, arg2)) &&
        (!arg3 || vsk_int(v3, arg3)))
    {
        vsk_targeting(self);

        if (v0 < 0 || v0 >= 25 || v1 <= 0 || v1 > 25 || v0 + v1 > 25)
        {
            vsk_machine->bad_call();
            return nullptr;
        }

        if (arg3 || arg2)
        {
            VSK_STATE()->m_console_y0 = 0;
            VSK_STATE()->m_console_cy0 = VSK_STATE()->m_text_height;
        }

        if (arg2)
        {
            int y = VSK_STATE()->m_console_y0 + VSK_STATE()->m_console_cy0 - 1;
            vsk_machine->clear_text(y, y);
        }

        VSK_STATE()->m_console_y0 = v0;
        VSK_STATE()->m_console_cy0 = v1;
        VSK_STATE()->m_show_function_keys = !!v2;
        VSK_STATE()->m_color_text = !!v3;
        vsk_machine->reset_text();

        if (arg3)
        {
            VSK_STATE()->m_text_attr.reset();
            vsk_machine->clear_text();
            vsk_machine->home();
        }
    }

    return nullptr;
}

// INSN_WIDTH (WIDTH) @implemented
static VskAstPtr VSKAPI vsk_WIDTH(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 2))
        return nullptr;

    if (!args[0])
        VSK_ERROR_AND_RETURN(VSK_ERR_MISSING_OPERAND, nullptr);

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;

    if (arg0->is_str()) // 第一引数が文字列？
    {
        if (!vsk_arity_in_range(args, 2, 2))
            return nullptr;

        auto filename = arg0->m_str;
        VskInt width;
        if (!vsk_int(width, args[1]))
            return nullptr;

        if (!(0 <= width && width <= 255))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (width == 0)
            width = 256;

        VskFilePtr file;
        if (auto error = vsk_get_file_manager()->open(file, filename))
            VSK_ERROR_AND_RETURN(error, nullptr);

        file->line_width(width);
        return nullptr;
    }

    VskInt v0, v1 = VSK_STATE()->m_text_height;
    auto arg1 = (args.size() > 1 ? args[1] : nullptr);
    if (vsk_int(v0, args[0]) &&
        (!arg1 || vsk_int(v1, args[1])))
    {
        if (v0 == 36 || v0 == 72)
        {
            mdbg_traceA("TODO: WIDTH 32 or 72: %d\n", v0);
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
        }
        if (!(v0 == 80 || v0 == 40) || !(v1 == 20 || v1 == 25))
        {
            vsk_machine->bad_call();
            return nullptr;
        }
        VSK_STATE()->m_text_width = v0;
        VSK_STATE()->m_text_height = v1;
        VSK_STATE()->m_console_y0 = 0;
        VSK_STATE()->m_console_cy0 = v1;
        VSK_STATE()->m_show_text = true;
        vsk_machine->reset_text();
        vsk_machine->clear_text();
        vsk_machine->home();
    }

    return nullptr;
}

// INSN_WIDTH_sharp (WIDTH#) @implemented
static VskAstPtr VSKAPI vsk_WIDTH_sharp(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt fileno, buf_size;
    if (vsk_file_number(fileno, args[0]) && vsk_int(buf_size, args[1]))
    {
        auto file = vsk_get_file_manager()->assoc(fileno);
        if (!file)
            VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

        if (!(0 <= buf_size && buf_size <= 255))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (buf_size == 0)
            buf_size = 256;

        if (file->is_line_printer()) // ラインプリンタ？
        {
            file->line_width(buf_size);
            return nullptr;
        }

        if (file->is_com()) // 通信ファイル？
        {
            file->line_width(buf_size);
            return nullptr;
        }
    }

    return nullptr;
}

// INSN_WIDTH_LPRINT (WIDTH LPRINT) @implemented
static VskAstPtr VSKAPI vsk_WIDTH_LPRINT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt width;
    if (vsk_int(width, args[0]))
    {
        if (!(0 <= width && width < 256))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (width == 0)
            width = 256;

        VskFilePtr file;
        if (auto error = vsk_get_file_manager()->open_line_printer(file))
            VSK_ERROR_AND_RETURN(error, nullptr);

        file->line_width(width);
    }

    return nullptr;
}

// INSN_LPOS (LPOS) @implemented
static VskAstPtr VSKAPI vsk_LPOS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;
    VskFilePtr file;
    if (auto error = vsk_get_file_manager()->open_line_printer(file))
        VSK_ERROR_AND_RETURN(error, nullptr);
    return vsk_ast_int(file->get_x());
}

// INSN_ASC (ASC) @implemented
static VskAstPtr VSKAPI vsk_ASC(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (v0.empty())
        {
            vsk_machine->bad_call();
            return nullptr;
        }
        return vsk_ast_int(static_cast<VskByte>(v0[0]));
    }
    return nullptr;
}

// INSN_LEN (LEN) @implemented
static VskAstPtr VSKAPI vsk_LEN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
        return vsk_ast_int(VskInt(v0.size()));
    return nullptr;
}

// INSN_LEFT_dollar (LEFT$) @implemented
static VskAstPtr VSKAPI vsk_LEFT_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    VskInt v1;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (v1 < 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (v1 > int(v0.size()))
            return vsk_ast_str(v0);
        return vsk_ast_str(v0.substr(0, v1));
    }

    return nullptr;
}

// INSN_RIGHT_dollar (RIGHT$) @implemented
static VskAstPtr VSKAPI vsk_RIGHT_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    VskInt v1;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (v1 < 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        if (v1 == 0)
            return vsk_ast_str("");
        if (v1 > int(v0.size()))
            return vsk_ast_str(v0);
        return vsk_ast_str(v0.substr(v0.size() - v1));
    }

    return nullptr;
}

// INSN_STR_dollar (SPC$) @implemented
static VskAstPtr VSKAPI vsk_STR_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskDouble v0;
    if (vsk_dbl(v0, args[0]))
    {
        auto str = vsk_to_string(v0);
        if (str.size() && str[0] != '-')
            str.insert(0, 1, ' ');
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_KEY_LIST (KEY LIST) @implemented
static VskAstPtr VSKAPI vsk_KEY_LIST(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    for (size_t iRow = 0; iRow < 10 / 2; ++iRow)
    {
        for (size_t iCol = 0; iCol < 2; ++iCol)
        {
            assert(iRow + iCol * 5 < 10);
            auto str = VSK_STATE()->m_function_keys[iRow + iCol * 5];
            if (str.size() < 16)
                str.resize(16, ' ');
            else
                str += "  ";
            vsk_machine->print_raw(str);
        }
        vsk_machine->line_feed();
    }

    return nullptr;
}

// INSN_KEY (KEY) @implemented
static VskAstPtr VSKAPI vsk_KEY(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0;
    VskString v1;
    if (vsk_int(v0, args[0]) && vsk_str(v1, args[1]))
    {
        if (!(1 <= v0 && v0 <= 10) || (!VSK_SETTINGS()->m_unlimited_mode && v1.size() > 15))
        {
            vsk_machine->bad_call();
            return nullptr;
        }

        VSK_STATE()->m_function_keys[v0 - 1] = v1;
    }

    return nullptr;
}

// INSN_VAL (VAL) @implemented
static VskAstPtr VSKAPI vsk_VAL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (!vsk_str(v0, args[0]))
        return nullptr;

    VSK_TYPE type;
    auto value = vsk_parse_number(v0.c_str(), nullptr, type);
    if (!value)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    return value;
}

// INSN_STRING_dollar (STRING$) @implemented
static VskAstPtr VSKAPI vsk_STRING_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0;
    auto v1 = vsk_eval_ast(args[1]);
    if (v1 && vsk_int(v0, args[0]))
    {
        if (VSK_SETTINGS()->m_unlimited_mode ? !(0 <= v0) : !(0 <= v0 && v0 <= VSK_MAX_STR_LEN))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        char ch;
        if (v1->is_number())
        {
            int n = std::atoi(v1->c_str());
            if (!(0 <= n && n < 256))
            {
                if (!vsk_is_sjis_code(n))
                {
                    vsk_machine->bad_call();
                    return nullptr;
                }
                VskString str;
                for (VskInt i = 0; i < v0; ++i)
                {
                    str += vsk_high_byte(n);
                    str += vsk_low_byte(n);
                }
                if (!VSK_SETTINGS()->m_unlimited_mode && str.size() > VSK_MAX_STR_LEN)
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
                return vsk_ast_str(str);
            }
            else
            {
                ch = (char)n;
            }
        }
        else if (v1->is_str())
        {
            ch = v1->to_str()[0];
        }
        else
        {
            vsk_machine->do_error(VSK_ERR_BAD_TYPE);
            return nullptr;
        }

        return vsk_ast_str(VskString(v0, ch));
    }

    return nullptr;
}

// INSN_HEX_dollar (HEX$) @implemented
static VskAstPtr VSKAPI vsk_HEX_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskWord v0;
    if (vsk_wrd(v0, args[0]))
    {
        char buf[64];
        std::sprintf(buf, "%X", v0);
        return vsk_ast_str(VskString(buf));
    }

    return nullptr;
}

// INSN_OCT_dollar (OCT$) @implemented
static VskAstPtr VSKAPI vsk_OCT_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskWord v0;
    if (vsk_wrd(v0, args[0]))
    {
        char buf[64];
        std::sprintf(buf, "%o", v0);
        return vsk_ast_str(VskString(buf));
    }

    return nullptr;
}

// INSN_INT (INT) @implemented
static VskAstPtr VSKAPI vsk_INT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;

    if (arg0->is_int())
    {
        return arg0;
    }
    else if (arg0->is_sng())
    {
        VskSingle v0;
        if (vsk_sng(v0, arg0))
            return vsk_ast_sng(VskSingle(std::floor(v0)));
    }
    else if (arg0->is_dbl())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
            return vsk_ast_dbl(VskDouble(std::floor(v0)));
    }
    else if (arg0->is_lng())
    {
        return arg0;
    }

    vsk_machine->do_error(VSK_ERR_BAD_TYPE);
    return nullptr;
}

// INSN_FIX (FIX) @implemented
static VskAstPtr VSKAPI vsk_FIX(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = vsk_eval_ast(args[0]);
    if (!arg0)
        return nullptr;

    if (arg0->is_int())
    {
        return arg0;
    }
    else if (arg0->is_sng())
    {
        VskSingle v0;
        if (vsk_sng(v0, arg0))
            return vsk_ast_sng(VskSingle(std::trunc(v0)));
    }
    else if (arg0->is_dbl())
    {
        VskDouble v0;
        if (vsk_dbl(v0, arg0))
            return vsk_ast_dbl(VskDouble(std::trunc(v0)));
    }
    else if (arg0->is_lng())
    {
        return arg0;
    }

    vsk_machine->do_error(VSK_ERR_BAD_TYPE);
    return nullptr;
}

// 直線や長方形を描くヘルパー関数、その１
void vsk_LINE_helper_1(VskSingle v0, VskSingle v1, VskSingle v2, VskSingle v3, VskInt v4, VskString v5, VskInt v6 = -1, VskString v7 = "")
{
    // ワールド座標をスクリーン座標に
    auto pt0 = vsk_machine->world_to_view({ v0, v1 });
    auto pt1 = vsk_machine->world_to_view({ v2, v3 });

    if (v5 == "BF")
        vsk_machine->fill_box(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, v4, v7);
    else if (v5 == "B")
        vsk_machine->draw_box(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, v4, v6);
    else
        vsk_machine->draw_line(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, v4, v6);

    VSK_STATE()->m_last_point_in_world = { v2, v3 };
}

// 直線や長方形を描くヘルパー関数、その２
VskAstPtr vsk_LINE_helper_2(const VskAstList& args, bool step0, bool step1)
{
    if (!vsk_arity_in_range(args, 4, 7))
        return nullptr;

    auto arg4 = vsk_arg(args, 4);
    auto arg5 = vsk_arg(args, 5);
    auto arg6 = vsk_arg(args, 6);

    VskSingle v0 = VSK_STATE()->m_last_point_in_world.m_x;
    VskSingle v1 = VSK_STATE()->m_last_point_in_world.m_y;
    VskSingle v2, v3;
    VskInt v4 = VSK_STATE()->m_fore_color;
    VskString v5;
    VskInt v6 = -1;

    if (arg6)
        arg6 = vsk_eval_ast(arg6);

    if ((!args[0] || vsk_sng(v0, args[0])) &&
        (!args[1] || vsk_sng(v1, args[1])) &&
        vsk_sng(v2, args[2]) &&
        vsk_sng(v3, args[3]) &&
        (!arg4 || vsk_int(v4, arg4)) &&
        (!arg5 || vsk_ident(v5, arg5)))
    {
        if (!vsk_machine->is_valid_color(v4))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (!(v5.empty() || v5 == "B" || v5 == "BF"))
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        if (step0)
        {
            v0 += VSK_STATE()->m_last_point_in_world.m_x;
            v1 += VSK_STATE()->m_last_point_in_world.m_y;
        }

        if (step1)
        {
            v2 += v0;
            v3 += v1;
        }

        if (v5 == "BF")
        {
            if (arg6 && arg6->is_number()) // パレット番号2
            {
                if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
                    VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
                if (!vsk_int(v6, arg6))
                    return nullptr;
                if (!vsk_machine->is_valid_color(v6))
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
                vsk_LINE_helper_1(v0, v1, v2, v3, v6, "BF");
                vsk_LINE_helper_1(v0, v1, v2, v3, v4, "B");
            }
            else if (arg6 && arg6->is_str()) // タイル文字列
            {
                if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
                    VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
                if (!vsk_machine->is_valid_tile(arg6->m_str))
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
                vsk_LINE_helper_1(v0, v1, v2, v3, v4, v5, -1, arg6->m_str);
                vsk_LINE_helper_1(v0, v1, v2, v3, v4, "B");
            }
            else if (!arg6) // その他のBoxFill
            {
                vsk_LINE_helper_1(v0, v1, v2, v3, v4, v5);
            }
            else
            {
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
            }
        }
        else // Box or Line
        {
            if (arg6) // ラインスタイル
            {
                if (!vsk_wrd((VskWord&)v6, arg6))
                    return nullptr;
            }
            vsk_LINE_helper_1(v0, v1, v2, v3, v4, v5, v6);
        }
    }

    return nullptr;
}

// INSN_LINE0 @implemented
// LINE(0,0)-(100,100) likely
static VskAstPtr VSKAPI vsk_LINE0(VskAstPtr self, const VskAstList& args)
{
    return vsk_LINE_helper_2(args, false, false);
}

// INSN_LINE1 @implemented
// LINE(0,0)-STEP(100,100) likely
static VskAstPtr VSKAPI vsk_LINE1(VskAstPtr self, const VskAstList& args)
{
    return vsk_LINE_helper_2(args, false, true);
}

// INSN_LINE2 @implemented
// LINE STEP(0,0)-(100,100) likely
static VskAstPtr VSKAPI vsk_LINE2(VskAstPtr self, const VskAstList& args)
{
    return vsk_LINE_helper_2(args, true, false);
}

// INSN_LINE3 @implemented
// LINE STEP(0,0)-STEP(100,100) likely
static VskAstPtr VSKAPI vsk_LINE3(VskAstPtr self, const VskAstList& args)
{
    return vsk_LINE_helper_2(args, true, true);
}

// 円の弧または楕円の弧を描くヘルパー関数
void vsk_circle_helper_2(VskSingle x0, VskSingle y0, VskSingle radius, int palette, VskSingle start_angle, VskSingle end_angle, VskSingle aspect, bool fill = false, VskString tile = "")
{
    // 真の楕円か？
    const bool full_moon_likely = (start_angle == 0) && (end_angle == VskSingle(2 * M_PI));

    auto& view = VSK_STATE()->m_viewport;
    auto& window = VSK_STATE()->m_window;

    auto pt = vsk_machine->world_to_view(VskPointS{ x0 , y0 });
    VskInt cx, cy;
    if (aspect <= 1)
    {
        cx = vsk_round(radius * view.width() / window.width());
        cy = vsk_round(cx * aspect);
    }
    else
    {
        cy = vsk_round(radius * view.height() / window.height());
        cx = vsk_round(cy / aspect);
    }
    VskPointI pt0 = { pt.m_x - cx, pt.m_y - cy }, pt1 = { pt.m_x + cx, pt.m_y + cy };

    if (full_moon_likely) // 真の楕円か？
    {
        if (fill) // 楕円の内部を塗りつぶす
            vsk_machine->fill_ellipse(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, palette, tile);
        else // 楕円を描画する
            vsk_machine->draw_ellipse(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, palette);
    }
    else
    {
        if (fill) // 円の弧または楕円の弧を塗りつぶす
            vsk_machine->fill_arc(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, start_angle, end_angle, palette, tile);
        else // 円の弧または楕円の弧を描画する
            vsk_machine->draw_arc(pt0.m_x, pt0.m_y, pt1.m_x, pt1.m_y, start_angle, end_angle, palette);
    }

    // LPを覚えておく
    VSK_STATE()->m_last_point_in_world = { x0, y0 };
}

// "CIRCLE", "CIRCLE STEP"
static VskAstPtr vsk_CIRCLE_helper_1(const VskAstList& args, bool step)
{
    if (!vsk_arity_in_range(args, 3, 9))
        return nullptr;

    VskSingle v0, v1, v2;
    VskInt v3 = VSK_STATE()->m_fore_color;
    VskSingle v4 = 0;
    VskSingle v5 = float(2 * M_PI);
    VskSingle v6 = (VSK_STATE()->m_screen_height == 400 ? 1 : 0.5f);
    VskString v7;
    VskInt v8;
    VskString str8;
    VskAstPtr arg8;

    if (!(args.size() <= 8))
        arg8 = vsk_eval_ast(args[8]);

    auto arg3 = vsk_arg(args, 3);
    auto arg4 = vsk_arg(args, 4);
    auto arg5 = vsk_arg(args, 5);
    auto arg6 = vsk_arg(args, 6);
    auto arg7 = vsk_arg(args, 7);
    if (vsk_sng(v0, args[0]) && // WX
        vsk_sng(v1, args[1]) && // WY
        vsk_sng(v2, args[2]) && // R
        (!arg3 || vsk_int(v3, args[3])) && // PALETTE #1
        (!arg4 || vsk_sng(v4, args[4])) && // start_angle
        (!arg5 || vsk_sng(v5, args[5])) && // end_angle
        (!arg6 || vsk_sng(v6, args[6])) && // aspect
        (!arg7 || vsk_ident(v7, args[7]))) // F
    {
        if (!vsk_machine->is_valid_color(v3))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        v8 = v3;
        if (arg8)
        {
            if (arg8->is_number()) // PALETTE #2
            {
                if (!vsk_int(v8, arg8))
                    return nullptr;
                if (!vsk_machine->is_valid_color(v8))
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
            }
            else if (arg8->is_str()) // TILE
            {
                str8 = arg8->m_str;
                if (!vsk_machine->is_valid_tile(str8))
                {
                    vsk_machine->bad_call();
                    return nullptr;
                }
            }
            else
            {
                vsk_machine->bad_call();
                return nullptr;
            }
        }

        if (!((VskSingle(-2 * M_PI) <= v4 && v4 <= VskSingle(2 * M_PI)) &&
              (VskSingle(-2 * M_PI) <= v5 && v5 <= VskSingle(2 * M_PI))) ||
            (v7.size() && v7 != "F"))
        {
            vsk_machine->bad_call();
            return nullptr;
        }

        if (step)
        {
            v0 += VSK_STATE()->m_last_point_in_world.m_x;
            v1 += VSK_STATE()->m_last_point_in_world.m_y;
        }

        if (v7 == "F")
        {
            // 塗りつぶす
            vsk_circle_helper_2(v0, v1, v2, v8, v4, v5, v6, true, str8);

            // この場合は角度を負にして、常に弧の両側の半径を描画する
            v4 = -std::abs(v4);
            v5 = -std::abs(v5);
            if (v4 == 0) v4 = -0.00001f;
            if (v5 == 0) v5 = -0.00001f;
        }

        // 円または楕円を描画。ついでに必要ならば弧の両側の半径を描画する
        vsk_circle_helper_2(v0, v1, v2, v3, v4, v5, v6, false);
    }

    return nullptr;
}

// INSN_CIRCLE (CIRCLE) @implemented
static VskAstPtr VSKAPI vsk_CIRCLE(VskAstPtr self, const VskAstList& args)
{
    return vsk_CIRCLE_helper_1(args, false);
}

// INSN_CIRCLE_STEP (CIRCLE STEP) @implemented
static VskAstPtr VSKAPI vsk_CIRCLE_STEP(VskAstPtr self, const VskAstList& args)
{
    return vsk_CIRCLE_helper_1(args, true);
}

// 点を描画するヘルパー関数
void vsk_do_PSET_PRESET_helper_1(VskPointS pt, VskInt palette)
{
    auto newpt = vsk_machine->world_to_view(pt);
    vsk_machine->set_pixel(newpt.m_x, newpt.m_y, palette);
    VSK_STATE()->m_last_point_in_world = pt;
}

// 点を描画するヘルパー関数
void vsk_do_PSET_PRESET_helper_2(VskAstPtr& self, const VskAstList& args, bool step, bool reset)
{
    if (!vsk_arity_in_range(args, 2, 3))
        return;

    VskSingle v0, v1;
    VskInt v2 = (reset ? VSK_STATE()->m_back_color : VSK_STATE()->m_fore_color);
    if (vsk_sng(v0, args[0]) &&
        vsk_sng(v1, args[1]) &&
        (args.size() <= 2 || !args[2] || vsk_int(v2, args[2])))
    {
        vsk_targeting(self);
        if (!vsk_machine->is_valid_color(v2))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL);

        if (step)
        {
            v0 += VSK_STATE()->m_last_point_in_world.m_x;
            v1 += VSK_STATE()->m_last_point_in_world.m_y;
        }

        vsk_do_PSET_PRESET_helper_1({ v0, v1 }, v2);
    }
}

// INSN_PSET (PSET) @implemented
static VskAstPtr VSKAPI vsk_PSET(VskAstPtr self, const VskAstList& args)
{
    vsk_do_PSET_PRESET_helper_2(self, args, false, false);
    return nullptr;
}

// INSN_PSET_STEP (PSET STEP) @implemented
static VskAstPtr VSKAPI vsk_PSET_STEP(VskAstPtr self, const VskAstList& args)
{
    vsk_do_PSET_PRESET_helper_2(self, args, true, false);
    return nullptr;
}

// INSN_PRESET (PRESET) @implemented
static VskAstPtr VSKAPI vsk_PRESET(VskAstPtr self, const VskAstList& args)
{
    vsk_do_PSET_PRESET_helper_2(self, args, false, true);
    return nullptr;
}

// INSN_PRESET_STEP (PRESET STEP) @implemented
static VskAstPtr VSKAPI vsk_PRESET_STEP(VskAstPtr self, const VskAstList& args)
{
    vsk_do_PSET_PRESET_helper_2(self, args, true, true);
    return nullptr;
}

// 塗りつぶす
static void vsk_PAINT_helper(VskSingle v0, VskSingle v1, VskInt v2, VskInt v3, VskString v4)
{
    auto pt = vsk_machine->world_to_client(VskPointS { v0, v1 });
    vsk_machine->flood_fill(vsk_round(pt.m_x), vsk_round(pt.m_y), v2, v3, v4);
    VSK_STATE()->m_last_point_in_world = { v0, v1 };
}

static VskAstPtr vsk_PAINT_helper(VskAstPtr& self, const VskAstList& args, bool step)
{
    if (!vsk_arity_in_range(args, 2, 4))
        return nullptr;

    VskSingle v0, v1;
    VskInt v2 = VSK_STATE()->m_fore_color, v3 = VSK_STATE()->m_fore_color;
    VskString tile;
    if (vsk_sng(v0, args[0]) && vsk_sng(v1, args[1])) // WX, WY
    {
        vsk_targeting(self);
        if (step)
        {
            v0 += VSK_STATE()->m_last_point_in_world.m_x;
            v1 += VSK_STATE()->m_last_point_in_world.m_y;
        }

        if (!(args.size() <= 2) && args[2])
        {
            auto arg2 = vsk_eval_ast(args[2]);
            if (!arg2)
                return nullptr;
            if (arg2->is_str()) // タイル文字列？
                tile = arg2->m_str;
            else if (!arg2->is_number())
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
            else if (!vsk_int(v2, arg2)) // 領域色？
                return nullptr;

            v3 = v2;
        }

        if (!(args.size() <= 3) && args[3] && !vsk_int(v3, args[3])) // 境界色
            return nullptr;

        if (!vsk_machine->is_valid_color(v2) ||
            !vsk_machine->is_valid_color(v3) ||
            (tile.size() && !vsk_machine->is_valid_tile(tile)))
        {
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        vsk_PAINT_helper(v0, v1, v2, v3, tile);
    }

    return nullptr;
}

// INSN_PAINT (PAINT) @implemented
static VskAstPtr VSKAPI vsk_PAINT(VskAstPtr self, const VskAstList& args)
{
    return vsk_PAINT_helper(self, args, false);
}

// INSN_PAINT_STEP (PAINT STEP) @implemented
static VskAstPtr VSKAPI vsk_PAINT_STEP(VskAstPtr self, const VskAstList& args)
{
    return vsk_PAINT_helper(self, args, true);
}

// INSN_VIEW_func (VIEW 関数) @implemented
static VskAstPtr VSKAPI vsk_VIEW_func(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        switch (v0)
        {
        case 0: return vsk_ast_dbl(VSK_STATE()->m_viewport.m_x0);
        case 1: return vsk_ast_dbl(VSK_STATE()->m_viewport.m_y0);
        case 2: return vsk_ast_dbl(VSK_STATE()->m_viewport.m_x1);
        case 3: return vsk_ast_dbl(VSK_STATE()->m_viewport.m_y1);
        default:
            vsk_machine->bad_call();
            break;
        }
    }

    return nullptr;
}

// INSN_WINDOW_func (WINDOW 関数) @implemented
static VskAstPtr VSKAPI vsk_WINDOW_func(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        switch (v0)
        {
        case 0: return vsk_ast_dbl(VSK_STATE()->m_window.m_x0);
        case 1: return vsk_ast_dbl(VSK_STATE()->m_window.m_y0);
        case 2: return vsk_ast_dbl(VSK_STATE()->m_window.m_x1);
        case 3: return vsk_ast_dbl(VSK_STATE()->m_window.m_y1);
        default:
            vsk_machine->bad_call();
            break;
        }
    }

    return nullptr;
}

// INSN_WINDOW_stmt @implemented
static VskAstPtr VSKAPI vsk_WINDOW_stmt(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 4, 4))
        return nullptr;

    VskSingle v0, v1, v2, v3;
    if (vsk_sng(v0, args[0]) &&
        vsk_sng(v1, args[1]) &&
        vsk_sng(v2, args[2]) &&
        vsk_sng(v3, args[3]))
    {
        if (v0 >= v2 || v1 >= v3)
        {
            vsk_machine->bad_call();
            return nullptr;
        }
        VSK_STATE()->m_window.m_x0 = v0;
        VSK_STATE()->m_window.m_y0 = v1;
        VSK_STATE()->m_window.m_x1 = v2;
        VSK_STATE()->m_window.m_y1 = v3;
    }

    return nullptr;
}

// INSN_VIEW_stmt (VIEW文) @implemented
static VskAstPtr VSKAPI vsk_VIEW_stmt(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 4, 6))
        return nullptr;

    VskInt x0, y0, x1, y1, v4 = 0, v5 = 7;
    auto arg4 = vsk_arg(args, 4), arg5 = vsk_arg(args, 5);
    if (vsk_int(x0, args[0]) && vsk_int(y0, args[1]) &&
        vsk_int(x1, args[2]) && vsk_int(y1, args[3]) &&
        (!arg4 || vsk_int(v4, arg4)) && (!arg5 || vsk_int(v5, arg5)))
    {
        if (x0 < 0 || y0 < 0 || x0 >= x1 || y0 >= y1 ||
            !vsk_machine->is_valid_color(v4) ||
            !vsk_machine->is_valid_color(v5) ||
            x1 >= VSK_STATE()->m_screen_width || y1 >= VSK_STATE()->m_screen_height)
        {
            vsk_machine->bad_call();
            return nullptr;
        }
        VSK_STATE()->m_viewport.m_x0 = x0; VSK_STATE()->m_viewport.m_y0 = y0;
        VSK_STATE()->m_viewport.m_x1 = x1; VSK_STATE()->m_viewport.m_y1 = y1;
        if (arg4)
        {
            vsk_machine->clear_graphic(v4);
        }
        if (arg5)
        {
            VskRectI clipping = { 0, 0, VSK_STATE()->m_screen_width - 1, VSK_STATE()->m_screen_height - 1 };
            vsk_machine->draw_box(x0 - 1, y0 - 1, x1 + 1, y1 + 1, v5, 0xFFFF, &clipping);
        }
    }

    return nullptr;
}

// INSN_SGN (SGN) @implemented
static VskAstPtr VSKAPI vsk_SGN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskDouble v0;
    if (vsk_dbl(v0, args[0]))
    {
        if (v0 > 0)
            return vsk_ast_int(1);
        if (v0 < 0)
            return vsk_ast_int(-1);
        return vsk_ast_int(0);
    }

    return nullptr;
}

// プログラムリストに行番号を追加する
void vsk_add_line_numbers(VskString& text, VskLineNo start = 100, VskLineNo step = 10)
{
    // 前後の空白を削除
    mstr_trim_right(text, " \t\r\n");

    // 行に分ける
    std::vector<VskString> lines;
    mstr_split(lines, text, "\n");

    // 行番号を各行に追加
    VskLineNo line_no = start;
    for (auto& line : lines)
    {
        mstr_trim_right(line, " \t\r\n");
        if (line.empty())
            line = "'";

        line = vsk_to_string(line_no) + " " + line;
        line_no += step;
    }

    // 行を結合
    text = std::move(mstr_join(lines, "\n"));
}

// ファイルを読み込む
bool vsk_load_file(const VskString& filename, VskString& text, bool change_dir)
{
    // ファイルから読み込む
    VskString new_filename = filename;
    auto error = vsk_machine->load(new_filename, text);
    if (error)
    {
        new_filename = filename + ".BAS";
        error = vsk_machine->load(new_filename, text);
    }
    if (error)
    {
        new_filename = filename + ".N88";
        error = vsk_machine->load(new_filename, text);
    }
    if (error)
    {
        vsk_error(error);
        return false;
    }

    // 必要ならディレクトリを変更する
    if (change_dir)
    {
        vsk_CHDIR_MKDIR_RMDIR(nullptr, { vsk_ast_str(new_filename) }, DIR_OP_CHDIR_PARENT);
    }

    // '\x1A' 以降を削除する
    auto i0 = text.find('\x1A');
    if (i0 != text.npos)
        text.erase(i0);

    // 後ろの空白を取り除く
    mstr_trim_right(text, " \t\r\n");

    // 行番号がなければ追加
    VskLineNo number = vsk_line_number_from_line_text(text);
    if (!number)
        vsk_add_line_numbers(text);

    // 行番号でソートする
    RENUM_sort_by_line_numbers(text);

    // 実行トレースモードを解除する
    VSK_IMPL()->m_trace_on = false;

    return true;
}

// INSN_LOAD (LOAD) @implemented
static VskAstPtr VSKAPI vsk_LOAD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v1;
    if (args[1] && !vsk_ident(v1, args[1]))
        return nullptr;
    if (v1 != "" && v1 != "R")
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VskString v0;
    if (!vsk_str(v0, args[0]))
        return nullptr;

    if (!vsk_load_file(v0, VSK_IMPL()->m_program_text, true))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    // Rが付いていたら実行する。Rが付いてなければファイルをすべて閉じる
    if (v1 == "R")
        return vsk_run();

    vsk_file_close_all();
    return nullptr;
}

// INSN_SAVE
static VskAstPtr VSKAPI vsk_SAVE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 2))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (auto error = vsk_machine->save(v0, VSK_IMPL()->m_program_text + "\n"))
        {
            vsk_error(error);
            return nullptr;
        }
    }

    return nullptr;
}

// INSN_MERGE (MERGE) @implemented
static VskAstPtr VSKAPI vsk_MERGE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        // 読み込む
        VskString text;
        if (!vsk_load_file(v0, text, false))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        // 行に分ける
        std::vector<VskString> lines;
        mstr_split(lines, text, "\n");

        // 統合する
        for (auto& line : lines)
        {
            mstr_trim(line, " \t\r\n");
            if (line.empty())
                continue; // 空行は無視

            // 行番号を取得
            auto number = vsk_line_number_from_line_text(line);
            if (!number)
                continue;

            // 行を上書きする
            vsk_update_program_line(VSK_IMPL()->m_program_text, number, line);
        }

        // コマンドレベルに戻る
        vsk_enter_command_level();
    }

    return nullptr;
}

// INSN_RUN @implemented
static VskAstPtr VSKAPI vsk_RUN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    auto arg0 = args[0], arg1 = args[1], arg2 = args[2];
    if (!arg0 && !arg1 && !arg2) // No arguments
        return vsk_run();

    if (arg0) // line number
    {
        auto index_list = vsk_label_to_index_list(arg0, VSK_IMPL()->m_label_map);
        if (index_list.empty())
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_LINE_NO, nullptr);

        return vsk_run(index_list);
    }

    // Otherwise, load from file
    VskString v1, v2;
    if (!vsk_str(v1, arg1))
        return nullptr;

    if (arg2 && (!arg2->is_ident() || arg2->m_str != "R"))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    if (arg2)
        v2 = arg2->m_str;

    if (!vsk_load_file(v1, VSK_IMPL()->m_program_text, true))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    return vsk_run();
}

// 行番号の範囲を取得する
static bool vsk_get_line_range(VskAstPtr& self, std::pair<VskLineNo, VskLineNo>& pair)
{
    // ラベル名から行番号への写像を取得する
    vsk_get_label_to_line_numbers(VSK_IMPL()->m_program_text, VSK_IMPL()->m_label_to_line_numbers);

    VskLineNo v0 = 0, v1 = std::numeric_limits<VskLineNo>::max();
    if (self)
    {
        assert(self->m_insn == INSN_LINE_RANGE);

        auto arg0 = (*self)[0], arg1 = (*self)[1];
        if (arg0)
        {
            if (!vsk_label_to_line_number(arg0, v0))
            {
                return false;
            }
        }
        if (arg1)
        {
            if (!vsk_label_to_line_number(arg1, v1))
            {
                return false;
            }
        }
    }

    pair = { v0, v1 };
    return true;
}

// INSN_LIST (LIST) @implemented
static VskAstPtr VSKAPI vsk_LIST(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    std::pair<VskLineNo, VskLineNo> line_range;
    auto arg0 = ((args.size() > 0) ? args[0] : nullptr);
    if (!vsk_get_line_range(arg0, line_range))
        return nullptr;

    vsk_list(false, VSK_IMPL()->m_program_text, line_range.first, line_range.second);
    return nullptr;
}

// INSN_LLIST (LLIST) @implemented
static VskAstPtr VSKAPI vsk_LLIST(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    std::pair<VskLineNo, VskLineNo> line_range;
    auto arg0 = ((args.size() > 0) ? args[0] : nullptr);
    if (!vsk_get_line_range(arg0, line_range))
        return nullptr;

    vsk_list(true, VSK_IMPL()->m_program_text, line_range.first, line_range.second);
    return nullptr;
}

// INSN_PEN_OFF (PEN OFF) @implemented
static VskAstPtr VSKAPI vsk_PEN_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_PEN].m_mode = VSK_TRAP_MODE_OFF;
    return nullptr;
}

// INSN_PEN_ON (PEN ON) @implemented
static VskAstPtr VSKAPI vsk_PEN_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_PEN].m_mode = VSK_TRAP_MODE_ON;
    return nullptr;
}

// INSN_PEN_STOP (PEN STOP) @implemented
static VskAstPtr VSKAPI vsk_PEN_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_PEN].m_mode = VSK_TRAP_MODE_STOP;
    return nullptr;
}

// INSN_PLAY_OFF (PLAY OFF) @implemented
static VskAstPtr VSKAPI vsk_PLAY_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_PLAY].m_mode = VSK_TRAP_MODE_OFF;
    return nullptr;
}

// INSN_PLAY_ON (PLAY ON) @implemented
static VskAstPtr VSKAPI vsk_PLAY_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_PLAY].m_mode = VSK_TRAP_MODE_ON;
    return nullptr;
}

// INSN_PLAY_STOP (PLAY STOP) @implemented
static VskAstPtr VSKAPI vsk_PLAY_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_PLAY].m_mode = VSK_TRAP_MODE_STOP;
    return nullptr;
}

// INSN_EDIT (EDIT) @implemented
static VskAstPtr VSKAPI vsk_EDIT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    // ラベル名から行番号への写像を取得する
    vsk_get_label_to_line_numbers(VSK_IMPL()->m_program_text, VSK_IMPL()->m_label_to_line_numbers);

    // 行番号を取得する
    VskLineNo number = 0;
    if (!vsk_label_to_line_number(args[0], number))
        return nullptr;
    if (!number)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_LINE_NO, nullptr);

    // 画面をクリア
    vsk_machine->clear_text();
    vsk_machine->home();
    vsk_machine->line_feed();

    // 行テキストをセット、改行
    auto line = vsk_get_next_line_text(number, 0);
    if (line.empty())
        line = vsk_get_next_line_text(number, +1);
    vsk_machine->set_line_text(VSK_STATE()->m_caret_y, line);

    // 現在の行をセット、編集モードを有効に
    VSK_IMPL()->m_current_line = number;
    VSK_STATE()->m_edit_mode = true;

    // コマンドレベルに戻る（Okは表示しない）
    vsk_enter_command_level(false);
    return nullptr;
}

// INSN_JIS_dollar (JIS$) @implemented
static VskAstPtr VSKAPI vsk_JIS_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (v0.size() <= 1)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        VskWord ret = vsk_make_word(v0[1], v0[0]);
        char buf[32];
        std::sprintf(buf, "%04X", ret);
        return vsk_ast_str(buf);
    }

    return nullptr;
}

// INSN_LOAD_question
static VskAstPtr VSKAPI vsk_LOAD_question(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_CONT (CONT) @implemented
static VskAstPtr VSKAPI vsk_CONT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    if (VSK_IMPL()->m_stopping_path.empty())
        VSK_ERROR_AND_RETURN(VSK_ERR_CANT_CONTINUE, nullptr);

    VSK_IMPL()->m_control_path = VSK_IMPL()->m_stopping_path;
    VSK_STATE()->m_wait_for = VSK_NO_WAIT;
    return nullptr;
}

// INSN_NEW_CMD (NEW CMD) @implemented
static VskAstPtr VSKAPI vsk_NEW_CMD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_9801_mode())
        return nullptr;

    VSK_STATE()->m_has_cmd_extension = true;
    return nullptr;
}

// INSN_FRE (FRE)
static VskAstPtr VSKAPI vsk_FRE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        switch (v0)
        {
        case 0:
        case 2:
            // TODO: ガーベジコレクション
            return vsk_ast_dbl(vsk_machine->get_free_size());
        case 1:
            return vsk_ast_dbl(99999); // ダミー
        case 3:
            if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
                VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
            return vsk_ast_dbl(99999);
        default:
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
    }
    return nullptr;
}

static bool vsk_KEY_OFF_ON_STOP_helper(VskAstPtr arg0, VskTrapMode mode)
{
    if (!arg0)
    {
        for (int trap_type = VSK_TRAP_F1; trap_type <= VSK_TRAP_F10; ++trap_type)
        {
            VSK_IMPL()->m_traps[trap_type].m_mode = mode;
        }
        return true;
    }

    VskInt v0;
    if (!vsk_int(v0, arg0))
        return false;
    if (!(1 <= v0 && v0 <= 10))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, false);
    VSK_IMPL()->m_traps[VSK_TRAP_F1 + v0 - 1].m_mode = mode;
    return true;
}

// INSN_KEY_OFF @implemented
static VskAstPtr VSKAPI vsk_KEY_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    auto arg0 = args.empty() ? nullptr : args[0];
    vsk_KEY_OFF_ON_STOP_helper(arg0, VSK_TRAP_MODE_OFF);
    return nullptr;
}

// INSN_KEY_ON @implemented
static VskAstPtr VSKAPI vsk_KEY_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    auto arg0 = args.empty() ? nullptr : args[0];
    vsk_KEY_OFF_ON_STOP_helper(arg0, VSK_TRAP_MODE_ON);
    return nullptr;
}

// INSN_KEY_STOP @implemented
static VskAstPtr VSKAPI vsk_KEY_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    auto arg0 = args.empty() ? nullptr : args[0];
    vsk_KEY_OFF_ON_STOP_helper(arg0, VSK_TRAP_MODE_STOP);
    return nullptr;
}

// INSN_CMD_SING (CMD SING) @implemented
static VskAstPtr VSKAPI vsk_CMD_SING(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_turtle())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (!vsk_sound_sing(v0))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        if (!VSK_IMPL()->m_play_bgm)
        {
            VSK_STATE()->m_wait_for = VSK_WAIT_FOR_PLAY;
            return vsk_ast(INSN_DONT_GO_NEXT);
        }
    }

    return nullptr;
}

// INSN_CMD_TURTLE (CMD TURTLE) @implemented
static VskAstPtr VSKAPI vsk_CMD_TURTLE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_turtle())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (!vsk_get_turtle_items_from_string(VSK_IMPL()->m_turtle_items, v0))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_TURTLE;
        return vsk_ast(INSN_DONT_GO_NEXT);
    }
    return nullptr;
}

// INSN_CMD_BGM (CMD BGM) @implemented
static VskAstPtr VSKAPI vsk_CMD_BGM(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_cmd_extension())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0 != 0 && v0 != 1)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        VSK_IMPL()->m_play_bgm = !!v0;
    }

    return nullptr;
}

// INSN_CMD_STOPM (CMD STOPM) @implemented
static VskAstPtr VSKAPI vsk_CMD_STOPM(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_cmd_extension())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    vsk_sound_stop();
    return nullptr;
}

// INSN_CMD_UNLINK (CMD UNLINK) @implemented
static VskAstPtr VSKAPI vsk_CMD_UNLINK(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_cmd_extension())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    vsk_sound_stop(); // 音を止める
    VSK_STATE()->m_has_cmd_extension = false; // 拡張命令を破棄する
    VSK_STATE()->m_has_turtle = false; // タートルグラフィック拡張命令を破棄する
    return nullptr;
}

// INSN_CMD_VOICE (CMD VOICE)
static VskAstPtr VSKAPI vsk_CMD_VOICE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 3))
        return nullptr;

    assert(0);
    return nullptr;
}

// INSN_CMD_CUT (CMD CUT) @implemented
static VskAstPtr VSKAPI vsk_CMD_CUT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_turtle())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VSK_STATE()->m_has_turtle = false;
    return nullptr;
}

// INSN_CMD_PAL (CMD PAL) @implemented
static VskAstPtr VSKAPI vsk_CMD_PAL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 2))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_cmd_extension())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    if (args.size() == 0)
    {
        vsk_machine->reset_palette();
        return nullptr;
    }

    VskInt v0;
    if (!vsk_int(v0, args[0]))
        return nullptr;
    if (!vsk_machine->is_valid_color(v0))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    VskInt v1 = vsk_get_default_digital_color_8(v0);
    if (args.size() <= 1 || vsk_int(v1, args[1]))
    {
        VskWebColor web_color;
        if (!vsk_web_color_from_analog_8_color_code(web_color, v1))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        VSK_STATE()->m_palette[v0] = web_color;
    }

    return nullptr;
}

// INSN_STOP_OFF (STOP OFF) @implemented
static VskAstPtr VSKAPI vsk_STOP_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_STOP].m_mode = VSK_TRAP_MODE_OFF;
    return nullptr;
}

// INSN_STOP_ON (STOP ON) @implemented
static VskAstPtr VSKAPI vsk_STOP_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_STOP].m_mode = VSK_TRAP_MODE_ON;
    return nullptr;
}

// INSN_STOP_STOP (STOP STOP) @implemented
static VskAstPtr VSKAPI vsk_STOP_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_STOP].m_mode = VSK_TRAP_MODE_STOP;
    return nullptr;
}

// INSN_AKCNV_dollar (AKCNV$) @implemented
static VskAstPtr VSKAPI vsk_AKCNV_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        VskString str = vsk_ank_to_kanji(v0);
        if (!VSK_SETTINGS()->m_unlimited_mode && str.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_KACNV_dollar (KACNV$) @implemented
static VskAstPtr VSKAPI vsk_KACNV_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        VskString str = vsk_kanji_to_ank(v0);
        if (!VSK_SETTINGS()->m_unlimited_mode && str.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        return vsk_ast_str(str);
    }

    return nullptr;
}

// DEFINT, DEFSNG, DEFDBL, DEFSTR
void vsk_def_vars(const VskAstList& args, VskType type)
{
    for (auto& arg : args)
    {
        if (arg->is_ident())
        {
            if (arg->m_str.size() != 1)
                VSK_SYNTAX_ERROR_AND_RETURN();
            vsk_set_def_type(arg->m_str[0], type);
            continue;
        }
        // A-Z likely
        if (arg->m_insn == INSN_SUB && arg->size() == 2)
        {
            auto arg0 = arg->at(0), arg1 = arg->at(1);
            if (arg0->is_ident() && arg1->is_ident() &&
                arg0->m_str.size() == 1 && arg1->m_str.size() == 1)
            {
                auto ch0 = arg0->m_str[0], ch1 = arg1->m_str[0];
                if (ch0 <= ch1)
                {
                    for (auto ch = ch0; ch <= ch1; ++ch)
                        vsk_set_def_type(ch, type);
                    continue;
                }
            }
        }
        VSK_SYNTAX_ERROR_AND_RETURN();
    }
}

// INSN_DEFINT (DEFINT) @implemented
static VskAstPtr VSKAPI vsk_DEFINT(VskAstPtr self, const VskAstList& args)
{
    vsk_def_vars(args, VSK_TYPE_INTEGER);
    return nullptr;
}

// INSN_DEFSNG (DEFSNG) @implemented
static VskAstPtr VSKAPI vsk_DEFSNG(VskAstPtr self, const VskAstList& args)
{
    vsk_def_vars(args, VSK_TYPE_SINGLE);
    return nullptr;
}

// INSN_DEFDBL (DEFDBL) @implemented
static VskAstPtr VSKAPI vsk_DEFDBL(VskAstPtr self, const VskAstList& args)
{
    vsk_def_vars(args, VSK_TYPE_DOUBLE);
    return nullptr;
}

// INSN_DEFSTR (DEFSTR) @implemented
static VskAstPtr VSKAPI vsk_DEFSTR(VskAstPtr self, const VskAstList& args)
{
    vsk_def_vars(args, VSK_TYPE_STRING);
    return nullptr;
}

static VskAstPtr vsk_GET_at_helper(const VskAstList& args, bool step)
{
    if (!vsk_arity_in_range(args, 5, 5))
        return nullptr;

    VskInt v0, v1, v2, v3;
    if (vsk_int(v0, args[0]) &&
        vsk_int(v1, args[1]) &&
        vsk_int(v2, args[2]) &&
        vsk_int(v3, args[3]))
    {
        if (step)
        {
            v2 += v0;
            v3 += v1;
        }

        // プレーンの数
        int M = 1;
        if (VSK_STATE()->m_color_graphics)
        {
            switch (VSK_STATE()->m_palette_mode)
            {
            case VSK_PAL_MODE_8_COLORS_DIGITAL:
            case VSK_PAL_MODE_8_COLORS_SUPER:
                M = 3;
                break;
            case VSK_PAL_MODE_16_COLORS_SUPER:
                M = 4;
                break;
            }
        }

        // 必要なバイト数を計算する
        int cx = v2 - v0 + 1, cy = v3 - v1 + 1;
        VskMemSize required_bytes = (cx + 7) / 8 * cy * M + 4;

        // 左辺値（lvalue）から名前と次元を取得
        VskString name;
        VskIndexList dimension;
        if (!vsk_dimension_from_lvalue(name, dimension, args[4], -VSK_STATE()->m_option_base == 1, true))
            return nullptr;

        // 配列変数を探す
        auto var_desc = vsk_var_find(name);
        if (!var_desc || !vsk_var_is_array(name))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 見つからない
        auto type = vsk_var_get_type(name);
        if (type == VSK_TYPE_STRING)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr); // 文字列は使えない

        // 添え字を解決する
        VskIndex total_index = 0;
        vsk_get_total_index(total_index, *var_desc, dimension);

        // サイズをチェック
        auto type_size = vsk_get_type_size(type);
        VskMemSize remainder = (var_desc->get_total_count() - total_index) * type_size;
        if (remainder < required_bytes)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 領域が足りない

        // 変数へのポインタを取得する
        void *ptr = vsk_var_get_ptr(name, dimension);
        if (!ptr)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 見つからない

        // 画像を取得
        if (!vsk_machine->get_image(v0, v1, cx, cy, ptr, required_bytes, M))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 見つからない
    }

    return nullptr;
}

// INSN_GET_at (GET@)
static VskAstPtr VSKAPI vsk_GET_at(VskAstPtr self, const VskAstList& args)
{
    return vsk_GET_at_helper(args, false);
}

// INSN_GET_at_STEP (GET@ STEP)
static VskAstPtr VSKAPI vsk_GET_at_STEP(VskAstPtr self, const VskAstList& args)
{
    return vsk_GET_at_helper(args, true);
}

// INSN_PUT_at (PUT@)
static VskAstPtr VSKAPI vsk_PUT_at(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 6))
        return nullptr;

    VskInt v0, v1;
    VskString v3;
    VskInt v4, v5;
    auto arg4 = vsk_arg(args, 4);
    auto arg5 = vsk_arg(args, 5);
    if (vsk_int(v0, args[0]) &&
        vsk_int(v1, args[1]) &&
        (args.size() <= 3 || vsk_str(v3, args[3])) &&
        (!arg4 || vsk_int(v4, arg4)) &&
        (!arg5 || vsk_int(v5, arg5)))
    {
        // 前景色と背景色を指定するなら、同時に指定しないといけない
        if (!arg4 != !arg5)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        // プレーンの数
        int M = 1;
        if (VSK_STATE()->m_color_graphics)
        {
            switch (VSK_STATE()->m_palette_mode)
            {
            case VSK_PAL_MODE_8_COLORS_DIGITAL:
            case VSK_PAL_MODE_8_COLORS_SUPER:
                M = 3;
                break;
            case VSK_PAL_MODE_16_COLORS_SUPER:
                M = 4;
                break;
            }
        }

        // 左辺値（lvalue）から名前と次元を取得
        VskString name;
        VskIndexList dimension;
        if (!vsk_dimension_from_lvalue(name, dimension, args[2], -VSK_STATE()->m_option_base == 1, true))
            return nullptr;

        // 配列変数を探す
        auto var_desc = vsk_var_find(name);
        if (!var_desc || !vsk_var_is_array(name))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 見つからない
        auto type = vsk_var_get_type(name);
        if (type == VSK_TYPE_STRING)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr); // 文字列は使えない

        // 添え字を解決する
        VskIndex total_index = 0;
        vsk_get_total_index(total_index, *var_desc, dimension);

        // サイズをチェック
        auto type_size = vsk_get_type_size(type);
        VskMemSize remainder = (var_desc->get_total_count() - total_index) * type_size;

        // 変数へのポインタを取得する
        void *ptr = vsk_var_get_ptr(name, dimension);
        if (!ptr)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 見つからない

        if (arg4)
        {
            // カラーが正しいか？
            if (!vsk_machine->is_valid_color(v4) || !vsk_machine->is_valid_color(v5))
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr); // 不正な色

            // 画像をセット
            if (!vsk_machine->put_image(v0, v1, ptr, remainder, M, v3, v4, v5))
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
        else
        {
            // 画像をセット
            if (!vsk_machine->put_image(v0, v1, ptr, remainder, M, v3))
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
    }

    return nullptr;
}

// INSN_PUT_at_KANJI (PUT@ KANJI)
static VskAstPtr VSKAPI vsk_PUT_at_KANJI(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 6))
        return nullptr;

    VskInt v0, v1, v4 = 7, v5 = 0;
    VskWord v2;
    VskString v3 = "XOR";
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]) && vsk_wrd(v2, args[2]))
    {
        if (args.size() > 3 && args[3] && !vsk_str(v3, args[3]))
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
        if (!(v3 == "PSET" || v3 == "PRESET" || v3 == "OR" || v3 == "AND" || v3 == "XOR"))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (vsk_is_sjis_code(v2))
            v2 = vsk_sjis2jis(v2);

        VskAstPtr arg4 = nullptr, arg5 = nullptr;
        if (args.size() > 4 && args[4]) arg4 = args[4];
        if (args.size() > 5 && args[5]) arg5 = args[5];
        if (!!arg4 != !!arg5)
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
        if (arg4 && !vsk_int(v4, arg4))
            return nullptr;
        if (arg5 && !vsk_int(v5, arg5))
            return nullptr;

        vsk_machine->draw_kanji(v0, v1, v2, v3, v4, v5, !vsk_machine->is_8801_mode());
    }

    return nullptr;
}

static bool vsk_DIM_helper(VskAstPtr& lvalue)
{
    // 左辺値（lvalue）から名前と次元を取得
    VskString name;
    VskIndexList dimension;
    if (!vsk_dimension_from_lvalue(name, dimension, lvalue, +(VSK_STATE()->m_option_base != 1, true)))
        return false;

    // 変数を宣言
    return vsk_var_declare(name, dimension);
}

// INSN_DIM (DIM) @implemented
static VskAstPtr VSKAPI vsk_DIM(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    assert(args[0]->m_insn == INSN_DIM_LIST);

    for (auto& lvalue : args[0]->children())
    {
        if (!vsk_DIM_helper(lvalue))
            return nullptr;
    }

    return nullptr;
}

// INSN_VARPTR
static VskAstPtr VSKAPI vsk_VARPTR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 2))
        return nullptr;

    // 左辺値（lvalue）から名前と次元を取得
    VskString name;
    VskIndexList dimension;
    if (!vsk_dimension_from_lvalue(name, dimension, args[0], +(VSK_STATE()->m_option_base == 1)))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VskInt v1 = 0;
    if (args.size() <= 1 || vsk_int(v1, args[1]))
    {
        // 変数名から変数ポインタを取得
        VskAddr varptr = vsk_var_get_varptr(name, dimension);
        if (!varptr)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        // アドレスを解決する
        VskAddr segment;
        VskAddr offset = vsk_machine->unresolve_addr(&segment, varptr);

        return vsk_ast_int(VskInt(v1 == 0 ? offset : segment));
    }

    return nullptr;
}

// INSN_ERASE (ERASE) @implemented
static VskAstPtr VSKAPI vsk_ERASE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    for (auto& ident : args[0]->children())
    {
        if (!vsk_var_is_array(ident->m_str) || !vsk_var_delete(ident->m_str, true))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    }

    return nullptr;
}

// INSN_CLEAR (CLEAR) @implemented
static VskAstPtr VSKAPI vsk_CLEAR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 3))
        return nullptr;

    VskLong v1;
    if (args.size() > 1 && args[1])
    {
        if (!vsk_lng(v1, args[1]))
            return nullptr;
        if (!vsk_machine->clear_memory(v1))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    }

    // 変数を全部消す
    vsk_var_clear_all();
    // 乱数の初期化
    vsk_rand_init(0);
    // DEF FNのデータを消す
    VSK_IMPL()->m_fn_to_path.clear();
    // 継続(CONT)はできなくなった
    VSK_IMPL()->m_stopping_path.clear();
    return nullptr;
}

// INSN_SWAP (SWAP) @implemented
static VskAstPtr VSKAPI vsk_SWAP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    // 左辺値（lvalue）から名前と次元を取得
    VskString name0, name1;
    VskIndexList dimension0, dimension1;
    if (!vsk_dimension_from_lvalue(name0, dimension0, args[0], +(VSK_STATE()->m_option_base == 1)))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
    if (!vsk_dimension_from_lvalue(name1, dimension1, args[1], +(VSK_STATE()->m_option_base == 1)))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    // 型を取得
    auto type0 = vsk_var_get_type(name0);
    auto type1 = vsk_var_get_type(name1);
    if (type0 != type1)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);

    // 変数記述子を取得
    auto var_desc0 = vsk_var_find(name0), var_desc1 = vsk_var_find(name1);
    if (!var_desc1)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    // 変数の値を取得する
    void *ptr0, *ptr1;
    bool flag0 = vsk_var_get_value(name0, &ptr0, dimension0);
    bool flag1 = vsk_var_get_value(name1, &ptr1, dimension1);

    // 配列の場合は配列ごと交換する
    if (!flag0 && !flag1 && vsk_var_is_array(name1) && dimension0.empty() && dimension1.empty())
    {
        (*vsk_vars_map)[name0] = var_desc1;
        if (var_desc0)
            (*vsk_vars_map)[name1] = var_desc0;
        else
            (*vsk_vars_map).erase(name1);
        return nullptr;
    }

    if (type0 == VSK_TYPE_STRING) // 文字列の場合
    {
        VskString str0, str1;
        if (ptr0) str0 = *(VskString*)ptr0;
        if (ptr1) str1 = *(VskString*)ptr1;

        // 値を交換する
        if (flag1)
            vsk_var_set_value(name0, dimension0, &str1);
        else if (dimension0.empty())
            vsk_var_delete(name0);
        if (flag0)
            vsk_var_set_value(name1, dimension1, &str0);
        else if (dimension1.empty())
            vsk_var_delete(name1);

        // 後始末
        delete (VskString*)ptr0;
        delete (VskString*)ptr1;
    }
    else
    {
        // 値を保存する
        size_t type_size = vsk_get_type_size(type0);
        std::string value0(type_size, '\0'), value1(type_size, '\0');
        if (flag0)
            std::memcpy(&value0[0], ptr0, type_size);
        if (flag1)
            std::memcpy(&value1[0], ptr1, type_size);

        // 値を交換する
        if (flag1)
            vsk_var_set_value(name0, dimension0, value1.data());
        else if (dimension0.empty())
            vsk_var_delete(name0);
        if (flag0)
            vsk_var_set_value(name1, dimension1, value0.data());
        else if (dimension1.empty())
            vsk_var_delete(name1);
    }

    return nullptr;
}

// INSN_EOF (EOF) @implemented
static VskAstPtr VSKAPI vsk_EOF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskError error;
    VskFilePtr file = vsk_eval_file_number(args[0], error);
    if (!file)
        VSK_ERROR_AND_RETURN(error, nullptr);

    if (!(file->is_sequential() || file->is_com()))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    return vsk_ast_int(file->eof() ? -1 : 0);
}

// INSN_ATTR_dollar (ATTR$)
static VskAstPtr VSKAPI vsk_ATTR_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto v0 = vsk_eval_ast(args[0]);
    if (v0->is_str())
    {
        auto filename = v0->c_str();

        struct stat sbuf;
        if (stat(filename, &sbuf) != 0)
        {
            switch (errno)
            {
            case ENOENT:
                vsk_machine->do_error(VSK_ERR_FILE_NOT_FOUND);
                return nullptr;
            default:
                vsk_machine->do_error(VSK_ERR_DISK_IO_ERROR);
                return nullptr;
            }
        }

        VskString ret = "   ";
        if (!(sbuf.st_mode & S_IWRITE))
            ret[2] = 'P';

        mdbg_traceA("TODO: R or E\n");
        //ret[0] = 'R';
        //ret[1] = 'E';
        return vsk_ast_str(ret);
    }

    assert(0);
    return nullptr;
}

// INSN_AUTO (AUTO) @implemented
static VskAstPtr VSKAPI vsk_AUTO(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    // ラベル名から行番号への写像を取得する
    vsk_get_label_to_line_numbers(VSK_IMPL()->m_program_text, VSK_IMPL()->m_label_to_line_numbers);

    // 行番号を取得
    VskLineNo number = 10;
    if (args[0] && !vsk_label_to_line_number(args[0], number))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    if (number <= 0)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    // 増分を取得
    VskDouble v1 = 10;
    if (args[1] && !vsk_dbl(v1, args[1]))
        return nullptr;

    VSK_IMPL()->m_auto_mode = true;
    VSK_IMPL()->m_auto_line_number = number;
    VSK_IMPL()->m_auto_step = v1;

    if (vsk_get_next_line_text(number, 0).size())
        VSK_STATE()->m_input_prompt = vsk_to_string(number) + "*";
    else
        VSK_STATE()->m_input_prompt = vsk_to_string(number) + " ";
    VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;
    vsk_show_input_prompt();

    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_BEEP @implemented
static VskAstPtr VSKAPI vsk_BEEP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    VskInt v0 = -1;
    if (args.size() != 0 && !vsk_int(v0, args[0]))
        return nullptr;
    if (args.size())
        v0 = !!v0;
    vsk_beep(v0);
    return nullptr;
}

// INSN_CALL
static VskAstPtr VSKAPI vsk_CALL(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_SYSTEM (SYSTEM) @implemented
static VskAstPtr VSKAPI vsk_SYSTEM(VskAstPtr self, const VskAstList& args)
{
    vsk_app_quit();
    return nullptr;
}

// INSN_CHAIN (CHAIN)
static VskAstPtr VSKAPI vsk_CHAIN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 3))
        return nullptr;

    VskString v2;
    auto arg2 = vsk_arg(args, 2);
    if (arg2 && (!vsk_ident(v2, arg2) || v2 != "ALL"))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
    bool all = !!arg2;

    // 文字列を取得する
    VskString v0;
    if (!vsk_str(v0, args[0]))
        return nullptr;

    // ファイルを読み込む
    if (!vsk_load_file(v0, VSK_IMPL()->m_program_text, true))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    if (auto error = vsk_scan_program_list())
        VSK_ERROR_AND_RETURN(error, nullptr);

    // 行番号を取得
    VskLineNo number = 0;
    auto arg1 = vsk_arg(args, 1);
    VskIndexList index_list = { I_PROGRAM_CODE };
    if (arg1)
    {
        index_list = vsk_label_to_index_list(arg1, VSK_IMPL()->m_label_map);
        if (index_list.empty())
            VSK_ERROR_AND_RETURN(VSK_ERR_UNDEFINED_LABEL, nullptr);
    }

    if (!all)
        mdbg_traceA("CHAIN: TODO: COMMON を指定した変数だけをつなげてください。");

    // 実行
    vsk_run(index_list, false);

    return nullptr;
}

// INSN_CHAIN_MERGE
static VskAstPtr VSKAPI vsk_CHAIN_MERGE(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_CHAIN_MERGE_ALL
static VskAstPtr VSKAPI vsk_CHAIN_MERGE_ALL(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_CHAIN_MERGE_ALL_DELETE
static VskAstPtr VSKAPI vsk_CHAIN_MERGE_ALL_DELETE(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_CHAIN_MERGE_DELETE
static VskAstPtr VSKAPI vsk_CHAIN_MERGE_DELETE(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_CLOSE (CLOSE) @implemented
static VskAstPtr VSKAPI vsk_CLOSE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = args[0];
    if (!arg0)
    {
        vsk_file_close_all();
        return nullptr;
    }

    assert(arg0->m_insn == INSN_FILE_NUMBERS);

    for (auto& arg : arg0->children())
    {
        VskInt fileno;
        if (!vsk_file_number(fileno, arg))
            return nullptr;

        vsk_get_file_manager()->close(fileno);
    }

    return nullptr;
}

// CMD VOICE COPY
static bool vsk_CMD_VOICE_COPY(VskInt v1, VskAstPtr arg2)
{
    // 左辺値（lvalue）から名前と次元を取得
    VskString name;
    VskIndexList dimension;
    if (!vsk_dimension_from_lvalue(name, dimension, arg2, -VSK_STATE()->m_option_base == 1, true))
        return false;

    if (!(dimension.size() == 2 && dimension[0] == 5 && dimension[1] == 10))
        return false;

    // 配列変数を探す
    auto var_desc = vsk_var_find(name);
    if (!var_desc || !vsk_var_is_array(name))
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, false); // 見つからない

    auto type = vsk_var_get_type(name);
    if (type != VSK_TYPE_INTEGER)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, false); // 型が違う

    // 変数へのポインタを取得する
    void *ptr = vsk_var_get_ptr(name, {});
    if (!ptr)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, false); // 見つからない

    return vsk_sound_voice_copy(ptr, v1);
}

// INSN_CMD_TEXT_ON_OFF (CMD TEXT ON/OFF) @implemented
static VskAstPtr VSKAPI vsk_CMD_TEXT_ON_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_turtle())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VskString v0;
    if (vsk_ident(v0, args[0]))
    {
        if (v0 == "ON") // CMD TEXT ON
        {
            VSK_STATE()->m_show_text = true;
            return nullptr;
        }
        if (v0 == "OFF") // CMD TEXT OFF
        {
            VSK_STATE()->m_show_text = false;
            return nullptr;
        }
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    return nullptr;
}

// INSN_CMD_PLAY (CMD PLAY) @implemented
static VskAstPtr VSKAPI vsk_CMD_PLAY(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 7))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode)
    {
        if (vsk_machine->is_9801_mode() || !vsk_machine->has_cmd_extension())
            VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VskInt sharp = 2;
    size_t i = 0;
    if (args[0]->m_insn == INSN_FILE_NUMBER)
    {
        if (!vsk_file_number(sharp, args[0]))
            return nullptr;
        i = 1;
    }
    else
    {
        if (!vsk_arity_in_range(args, 1, 6))
            return nullptr;
    }

    std::vector<VskString> strs;
    for (; i < args.size(); ++i)
    {
        auto arg = args.at(i);
        if (!arg)
        {
            strs.push_back("");
            continue;
        }

        VskString str;
        if (!vsk_str(str, arg))
            return nullptr;

        if (!VSK_SETTINGS()->m_unlimited_mode && str.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);

        strs.push_back(str);
    }

    switch (sharp)
    {
    case 0:
        if (!vsk_sound_play_ssg(strs))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        break;
    case 2:
        if (!vsk_sound_play_fm_and_ssg(strs))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        break;
    default:
        vsk_machine->bad_call();
        return nullptr;
    }

    if (!VSK_IMPL()->m_play_bgm)
    {
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_PLAY;
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_CMD (CMD ...)
static VskAstPtr VSKAPI vsk_CMD(VskAstPtr self, const VskAstList& args)
{
    auto params = args;
    auto cmd_name = params[0]->m_str;
    params.erase(params.begin());

    if (cmd_name == "CLS")
        return vsk_CMD_CLS(self, params);
    if (cmd_name == "BGM")
        return vsk_CMD_BGM(self, params);
    if (cmd_name == "CUT")
        return vsk_CMD_CUT(self, params);
    if (cmd_name == "PAL")
        return vsk_CMD_PAL(self, params);
    if (cmd_name == "PLAY")
        return vsk_CMD_PLAY(self, params);
    if (cmd_name == "SING")
        return vsk_CMD_SING(self, params);
    if (cmd_name == "TURTLE")
        return vsk_CMD_TURTLE(self, params);
    if (cmd_name == "STOPM")
        return vsk_CMD_STOPM(self, params);
    if (cmd_name == "UNLINK")
        return vsk_CMD_UNLINK(self, params);
    if (cmd_name == "VOICE")
        return vsk_CMD_VOICE(self, params);
    if (cmd_name == "TEXT")
        return vsk_CMD_TEXT_ON_OFF(self, params);

    VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
}

// INSN_COLOR_equal (COLOR=)
static VskAstPtr VSKAPI vsk_COLOR_equal(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (!vsk_machine->is_valid_color(v0))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        switch (VSK_STATE()->m_palette_mode)
        {
        case VSK_PAL_MODE_8_COLORS_DIGITAL:
            {
                VskWebColor web_color;
                if (!vsk_web_color_from_digital_8_color_code(web_color, v1))
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
                VSK_STATE()->m_palette[v0] = web_color;
            }
            break;
        case VSK_PAL_MODE_8_COLORS_SUPER:
        case VSK_PAL_MODE_16_COLORS_SUPER:
            {
                VskWebColor web_color;
                if (!vsk_web_color_from_super_16_color_code(web_color, v1))
                    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
                VSK_STATE()->m_palette[v0] = web_color;
            }
            break;
        }
    }

    // ボーダーカラーのリセット
    vsk_machine->reset_border_color();

    return nullptr;
}

// INSN_COLOR_at (COLOR@) @implemented
static VskAstPtr VSKAPI vsk_COLOR_at(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 4, 5))
        return nullptr;

    VskInt v0, v1, v2, v3, v4 = 7;
    if (vsk_int(v0, args[0]) &&
        vsk_int(v1, args[1]) &&
        vsk_int(v2, args[2]) &&
        vsk_int(v3, args[3]) &&
        (args.size() <= 4 || vsk_int(v4, args[4])))
    {
        VskLogAttr new_attr;
        new_attr.reset();
        if (VSK_STATE()->m_color_text)
            new_attr.m_palette = v4;
        else
            new_attr.m_effect = v4;

        if (v0 > v2) std::swap(v0, v2);
        if (v1 > v3) std::swap(v1, v3);

        for (int y = v1; y <= v3; ++y)
        {
            for (int x = v0; x <= v2; ++x)
            {
                vsk_machine->set_attr(x, y, new_attr);
            }
        }
    }

    return nullptr;
}

// INSN_COMMON
static VskAstPtr VSKAPI vsk_COMMON(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_COM_OFF (COM OFF) @implemented
static VskAstPtr VSKAPI vsk_COM_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_COM].m_mode = VSK_TRAP_MODE_OFF;
    return nullptr;
}

// INSN_COM_ON (COM ON) @implemented
static VskAstPtr VSKAPI vsk_COM_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_COM].m_mode = VSK_TRAP_MODE_ON;
    return nullptr;
}

// INSN_COM_STOP (COM STOP) @implemented
static VskAstPtr VSKAPI vsk_COM_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_COM].m_mode = VSK_TRAP_MODE_STOP;
    return nullptr;
}

// INSN_COPY (COPY) @implemented
static VskAstPtr VSKAPI vsk_COPY(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    VskInt v0 = 3;
    if (args.empty() || vsk_int(v0, args[0]))
    {
        if (!(1 <= v0 && v0 <= 5))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        // 表示・非表示の状態を保存する。
        bool show_graphics = VSK_STATE()->m_show_graphics;
        bool show_text = VSK_STATE()->m_show_text;
        bool half = false;
        switch (v0)
        {
        case 1:
            show_graphics = false;
            break;
        case 2:
            show_text = false;
            break;
        case 3:
            break;
        case 4:
            show_text = false;
            half = (VSK_STATE()->m_screen_height == 200);
            break;
        case 5:
            half = (VSK_STATE()->m_screen_height == 200);
            break;
        }

        // 指定された表示・非表示の状態でスクリーンショットを保存する
        vsk_save_screenshot(show_text, show_graphics, half);
    }

    return nullptr;
}

// INSN_DEF_USR
static VskAstPtr VSKAPI vsk_DEF_USR(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_DELETE (DELETE) @implemented
static VskAstPtr VSKAPI vsk_DELETE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    std::pair<VskLineNo, VskLineNo> line_range;
    auto arg0 = ((args.size() > 0) ? args[0] : nullptr);
    if (!vsk_get_line_range(arg0, line_range))
        return nullptr;

    vsk_delete_lines(VSK_IMPL()->m_program_text, line_range.first, line_range.second);
    VSK_IMPL()->m_current_line = 0;
    return nullptr;
}

// INSN_DRAW
static VskAstPtr VSKAPI vsk_DRAW(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (!vsk_get_draw_items_from_string(VSK_IMPL()->m_draw_items, v0))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_DRAW;
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_DSKF
static VskAstPtr VSKAPI vsk_DSKF(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_DSKI_dollar (DSKI$)
static VskAstPtr VSKAPI vsk_DSKI_dollar(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_DSKO_dollar (DSKO$)
static VskAstPtr VSKAPI vsk_DSKO_dollar(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_DSKO_dollar_func (DDSKO$ 関数)
static VskAstPtr VSKAPI vsk_DSKO_dollar_func(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_END @implemented
static VskAstPtr VSKAPI vsk_END(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;
    // ファイルを全部閉じる
    vsk_file_close_all();
    // DATAの読み込み位置を初期化
    VSK_IMPL()->m_data_pointer = { I_PROGRAM_CODE };
    // CONT可能にする
    VSK_IMPL()->m_stopping_path = VSK_IMPL()->m_control_path;
    // コマンドレベルに戻る
    vsk_enter_command_level();

    return nullptr;
}

// INSN_ERL (ERL) @implemented
static VskAstPtr VSKAPI vsk_ERL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;
    return vsk_ast_int(VskInt(VSK_STATE()->error_line()));
}

// INSN_ERR (ERR) @implemented
static VskAstPtr VSKAPI vsk_ERR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;
    return vsk_ast_int(VskInt(VSK_STATE()->error_code()));
}

// INSN_FIELD (FIELD) @implemented
static VskAstPtr VSKAPI vsk_FIELD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    assert(args[1]->m_insn == INSN_FIELD_ITEMS);
    auto& items = args[1];

    // ファイル番号を取得
    VskInt fileno;
    if (vsk_file_number(fileno, args[0]))
    {
        // フィールドを削除
        vsk_field_close(fileno);

        // 各フィールド項目について
        for (auto& item : items->children())
        {
            assert(item->m_insn == INSN_FIELD_ITEM);
            if (item->at(1)->m_str != "AS")
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

            // フィールド長を取得
            auto expr = item->at(0);
            VskInt field_len;
            if (!vsk_int(field_len, expr))
                return nullptr;

            // 左辺値を最適化
            auto lvalue = vsk_lvalue_optimize(item->at(2), -(VSK_STATE()->m_option_base == 1));
            if (!lvalue)
                return nullptr;

            // フィールドを追加
            vsk_field_add(lvalue, fileno, field_len);
            // フィールド変数に空白を代入する
            VskString str(field_len, ' ');
            if (!vsk_var_assign(lvalue, vsk_ast_str(str)))
                return nullptr;
        }
    }

    return nullptr;
}

// LSET / RSET helper
static VskAstPtr VSKAPI vsk_LSET_RSET(VskAstPtr& self, const VskAstList& args, bool right)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    // 左辺値を最適化
    VskAstPtr arg0 = args[0];
    auto lvalue = vsk_lvalue_optimize(arg0, -(VSK_STATE()->m_option_base == 1));
    if (!lvalue)
        return nullptr;

    // 文字列を取得
    VskString str;
    if (!vsk_str(str, args[1]))
        return nullptr;

    // フィールドを探す
    auto *entry = vsk_field_find(lvalue);
    if (!entry)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    // 文字列を更新(左そろえまたは右そろえ)
    auto field_len = entry->m_field_len;
    if (int(str.size()) < field_len)
    {
        auto diff = field_len - str.size();
        if (right)
            str = VskString(diff, ' ') + str;
        else
            str += VskString(diff, ' ');
    }
    else
    {
        if (right)
            str.erase(0, str.size() - field_len);
        else
            str.resize(field_len);
    }

    // 文字列を代入
    vsk_var_assign(lvalue, vsk_ast_str(str));
    return nullptr;
}

// INSN_LSET (LSET) @implemented
static VskAstPtr VSKAPI vsk_LSET(VskAstPtr self, const VskAstList& args)
{
    return vsk_LSET_RSET(self, args, false);
}

// INSN_RSET (RSET) @implemented
static VskAstPtr VSKAPI vsk_RSET(VskAstPtr self, const VskAstList& args)
{
    return vsk_LSET_RSET(self, args, true);
}

// INSN_PUT_sharp (PUT#) @implemented
static VskAstPtr VSKAPI vsk_PUT_sharp(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt fileno;
    if (!vsk_file_number(fileno, args[0]))
        return nullptr;

    auto file = vsk_get_file_manager()->assoc(fileno);
    if (!file)
        VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

    VskLong v1 = 0;
    if (!args[1] || vsk_lng(v1, args[1]))
    {
        if (!(0 <= v1 && v1 <= 65000))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        VskString bin;
        if (!vsk_field_store(fileno, bin))
            return nullptr;

        if (file->is_sequential())
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (file->is_random())
        {
            if (v1 == 0)
            {
                if (auto error = file->write_bin(bin.c_str(), bin.size()))
                    VSK_ERROR_AND_RETURN(error, nullptr);
            }
            else
            {
                if (!file->set_pos((v1 - 1) * bin.size()))
                    VSK_ERROR_AND_RETURN(VSK_ERR_DISK_IO_ERROR, nullptr);
                if (auto error = file->write_bin(bin.c_str(), bin.size()))
                    VSK_ERROR_AND_RETURN(error, nullptr);
            }
            return nullptr;
        }

        if (file->is_screen())
        {
            if (v1 == 0)
            {
                if (VSK_SETTINGS()->m_field_width == -1)
                    bin.resize(256, ' ');
                else
                    bin.resize(VSK_SETTINGS()->m_field_width, ' ');
                if (auto error = file->write_bin(bin.c_str(), 256))
                    VSK_ERROR_AND_RETURN(error, nullptr);
            }
            else
            {
                if (v1 >= int(bin.size()))
                    v1 = bin.size();
                if (auto error = file->write_bin(bin.c_str(), v1))
                    VSK_ERROR_AND_RETURN(error, nullptr);
            }
            return nullptr;
        }

        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    return nullptr;
}

// INSN_GET_sharp (GET#)
static VskAstPtr VSKAPI vsk_GET_sharp(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt fileno;
    if (!vsk_file_number(fileno, args[0]))
        return nullptr;

    auto file = vsk_get_file_manager()->assoc(fileno);
    if (!file)
        VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

    VskLong v1 = 0;
    if (!args[1] || vsk_lng(v1, args[1]))
    {
        int record_len = vsk_field_get_len(fileno);
        if (!(0 <= v1 && v1 <= 65000) || record_len <= 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        VskString bin(record_len, ' ');

        if (file->is_sequential())
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (file->is_random())
        {
            if (v1 == 0)
            {
                if (auto error = file->read_bin(&bin[0], bin.size()))
                    VSK_ERROR_AND_RETURN(error, nullptr);
            }
            else
            {
                if (!file->set_pos((v1 - 1) * bin.size()))
                    VSK_ERROR_AND_RETURN(VSK_ERR_DISK_IO_ERROR, nullptr);
                if (auto error = file->read_bin(&bin[0], bin.size()))
                    VSK_ERROR_AND_RETURN(error, nullptr);
            }
            vsk_field_fetch(fileno, bin);
            return nullptr;
        }

        if (file->is_keyboard())
        {
            mdbg_traceA("TODO:\n");
        }

        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    return nullptr;
}

static VskAstPtr vsk_FILES_LFILES_helper(const VskAstList& args, bool is_line_printer)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    std::vector<VskString> files;

    VskError error;
    VskString device = "1";
    if (args.size() > 0)
    {
        auto arg0 = vsk_eval_ast(args[0]);
        if (arg0->is_number())
            error = vsk_files_helper(files, device, arg0->to_int());
        else if (arg0->is_str())
            error = vsk_files_helper(files, device, arg0->m_str);
        else
            error = VSK_ERR_SYNTAX;
    }
    else
    {
        error = vsk_files_helper(files, device, 1);
    }

    // ソートする
    std::sort(files.begin(), files.end());

    if (error)
        VSK_ERROR_AND_RETURN(error, nullptr);

    // 印字項目
    VskAstList printing_items;
    if (device.size())
        printing_items.push_back(vsk_ast_str(VskString("In ") + device + ":\n"));

    // 印字項目をさらに追加
    bool first = true;
    for (auto& file : files)
    {
        if (first)
            first = false;
        else
            printing_items.push_back(vsk_ast(INSN_COMMA));

        printing_items.push_back(vsk_ast_str(file));
    }
    printing_items.push_back(vsk_ast_str("\n"));

    // 印字項目をセット
    VSK_IMPL()->m_printing_items = std::move(printing_items);

    if (is_line_printer)
        VSK_IMPL()->m_printing_device = vsk_get_line_printer();
    else
        VSK_IMPL()->m_printing_device = vsk_get_screen_device();

    assert(VSK_IMPL()->m_printing_device);

    VSK_IMPL()->m_printing_is_write = false; // WRITE文ではない

    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_FILES (FILES) @implemented
static VskAstPtr VSKAPI vsk_FILES(VskAstPtr self, const VskAstList& args)
{
    return vsk_FILES_LFILES_helper(args, false);
}

// INSN_LFILES (LFILES) @implemented
static VskAstPtr VSKAPI vsk_LFILES(VskAstPtr self, const VskAstList& args)
{
    return vsk_FILES_LFILES_helper(args, true);
}

// INSN_DEF_FN (DEF FN)
static VskAstPtr VSKAPI vsk_DEF_FN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    // ダイレクトモードなら失敗
    if (VSK_IMPL()->m_control_path.size() && VSK_IMPL()->m_control_path[0] == I_DIRECT_CODE)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_DIRECT, nullptr);

    // m_fn_to_pathにDEF FNのあるコントロールパスを保存する
    auto fn = args[0];
    assert(fn->m_insn == INSN_FN);
    assert(fn->m_str.size());
    VSK_IMPL()->m_fn_to_path[fn->to_str()] = VSK_IMPL()->m_control_path;

    return nullptr;
}

// INSN_FN (ユーザー定義関数)
static VskAstPtr VSKAPI vsk_FN(VskAstPtr self, const VskAstList& args)
{
    // m_fn_to_pathからDEF FNのあるコントロールパスを取得する
    auto name = self->to_str();
    auto it = VSK_IMPL()->m_fn_to_path.find(name);
    if (it == VSK_IMPL()->m_fn_to_path.end())
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_DIRECT, nullptr);
    auto& path = it->second;

    // コントロールパスを解決し、関数名などを確認する
    auto node = vsk_resolve_index_list(path);
    if (!node || name != node->at(0)->m_str || node->m_insn != INSN_DEF_FN)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_DIRECT, nullptr);

    // 引数の数が不一致なら失敗
    auto lvalue_list = node->at(1); // 仮引数リスト
    if (lvalue_list)
    {
        if (args.size() < lvalue_list->size())
            VSK_ERROR_AND_RETURN(VSK_ERR_MISSING_OPERAND, nullptr);
        if (args.size() > lvalue_list->size())
            VSK_ERROR_AND_RETURN(VSK_ERR_SYNTAX, nullptr);
    }
    else if (args.size())
    {
        VSK_ERROR_AND_RETURN(VSK_ERR_SYNTAX, nullptr);
    }

    // 実引数を評価して値リストを作成
    VskAstList value_list;
    for (size_t iarg = 0; iarg < args.size(); ++iarg)
    {
        auto value = vsk_eval_ast(args[iarg]);
        if (!value)
            return nullptr;
        value_list.push_back(value);
    }

    // 値を式に代入
    auto expr = node->at(2);
    for (size_t iarg = 0; iarg < args.size(); ++iarg)
        expr = expr->substitute(lvalue_list->at(iarg), value_list[iarg]);
    // 評価
    auto ret = vsk_eval_ast(expr);
    if (!ret)
        return nullptr;
    // 関数の型を取得
    auto type = vsk_var_get_type_0(name);
    if (!type)
        type = VSK_TYPE_SINGLE;
    // 型キャスト
    return vsk_type_cast(ret, type);
}

// INSN_FPOS (FPOS) @implemented
static VskAstPtr VSKAPI vsk_FPOS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt fileno;
    if (!vsk_file_number(fileno, args[0]))
        return nullptr;

    auto file = vsk_get_file_manager()->assoc(fileno);
    if (!file)
        VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

    if (file->is_line_printer()) // ラインプリンタ？
    {
        return vsk_ast_int(file->get_x());
    }

    if (file->is_sequential() || file->is_random()) // ディスクファイル？
    {
        VskDword offset;
        if (!file->get_pos(&offset))
            VSK_ERROR_AND_RETURN(VSK_ERR_DISK_IO_ERROR, nullptr);
        mdbg_traceA("TODO:\n"); // ディスク上の位置がわからないんだからしょうがない。。。
        return vsk_ast_dbl(offset / VSK_SECTOR_SIZE);
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
}

// INSN_GOTO (GOTO) @implemented
static VskAstPtr VSKAPI vsk_GOTO(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_ERROR_AND_RETURN(VSK_ERR_UNDEFINED_LABEL, nullptr);

    VSK_IMPL()->m_control_path = index_list;
    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_ON_EXPR_GOTO (ON ... GOTO) @implemented
static VskAstPtr VSKAPI vsk_ON_EXPR_GOTO(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        auto arg1 = args[1];
        assert(arg1->m_insn == INSN_LINE_NUMBERS);

        if (!(0 <= v0 && v0 < 256))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (v0 == 0 || v0 - 1 >= int(arg1->size()))
            return nullptr; // simply go to next statement

        auto label = arg1->at(v0 - 1);
        if (!label)
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        auto index_list = vsk_label_to_index_list(label, VSK_IMPL()->m_label_map);
        if (index_list.empty())
            VSK_ERROR_AND_RETURN(VSK_ERR_UNDEFINED_LABEL, nullptr);

        VSK_IMPL()->m_control_path = index_list;
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_GOSUB (GOSUB) @implemented
static VskAstPtr VSKAPI vsk_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_ERROR_AND_RETURN(VSK_ERR_UNDEFINED_LABEL, nullptr);

    auto next = vsk_next_control_path(VSK_IMPL()->m_control_path);
    VSK_IMPL()->m_path_stack.push(next);
    VSK_IMPL()->m_control_path = index_list;
    VSK_IMPL()->m_trap_type_stack.push(VSK_TRAP_MAX);
    return vsk_ast(INSN_DONT_GO_NEXT);
}

// INSN_ON_EXPR_GOSUB (ON ... GOSUB) @implemented
static VskAstPtr VSKAPI vsk_ON_EXPR_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        auto arg1 = args[1];
        assert(arg1->m_insn == INSN_LINE_NUMBERS);

        if (!(0 <= v0 && v0 < 256))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (v0 == 0 || v0 - 1 >= int(arg1->size()))
            return nullptr; // simply go to next statement

        auto label = arg1->at(v0 - 1);
        if (!label)
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        auto index_list = vsk_label_to_index_list(label, VSK_IMPL()->m_label_map);
        if (index_list.empty())
            VSK_ERROR_AND_RETURN(VSK_ERR_UNDEFINED_LABEL, nullptr);

        auto next = vsk_next_control_path(VSK_IMPL()->m_control_path);
        VSK_IMPL()->m_path_stack.push(next);
        VSK_IMPL()->m_control_path = index_list;
        VSK_IMPL()->m_trap_type_stack.push(VSK_TRAP_MAX);
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_RETURN (RETURN) @implemented
static VskAstPtr VSKAPI vsk_RETURN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    if (VSK_IMPL()->m_path_stack.empty())
        VSK_ERROR_AND_RETURN(VSK_ERR_RETURN_WITHOUT_GOSUB, nullptr);

    if (args.size() == 0)
    {
        VSK_IMPL()->m_control_path = VSK_IMPL()->m_path_stack.top();
        VSK_IMPL()->m_path_stack.pop();

        auto trap_type = VSK_IMPL()->m_trap_type_stack.top();
        VSK_IMPL()->m_trap_type_stack.pop();
        if (trap_type != VSK_TRAP_MAX)
            VSK_IMPL()->m_traps[trap_type].m_trapping = false;

        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    if (args.size() == 1)
    {
        auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
        VSK_IMPL()->m_control_path = index_list;
        VSK_IMPL()->m_path_stack.pop();

        auto trap_type = VSK_IMPL()->m_trap_type_stack.top();
        VSK_IMPL()->m_trap_type_stack.pop();
        if (trap_type != VSK_TRAP_MAX)
            VSK_IMPL()->m_traps[trap_type].m_trapping = false;

        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_HELP_OFF (HELP OFF) @implemented
static VskAstPtr VSKAPI vsk_HELP_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_HELP].m_mode = VSK_TRAP_MODE_OFF;
    return nullptr;
}

// INSN_HELP_ON (HELP ON) @implemented
static VskAstPtr VSKAPI vsk_HELP_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_HELP].m_mode = VSK_TRAP_MODE_ON;
    return nullptr;
}

// INSN_HELP_STOP (HELP STOP) @implemented
static VskAstPtr VSKAPI vsk_HELP_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_HELP].m_mode = VSK_TRAP_MODE_STOP;
    return nullptr;
}

static VskTrapInfo *vsk_get_mouse_trap(VskInt v0)
{
    switch (v0)
    {
    case 1: return &VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_MOVE];
    case 2: return &VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_PRESS];
    case 3: return &VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_PRESS];
    case 4: return &VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_RELEASE];
    case 5: return &VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_RELEASE];
    default: return nullptr;
    }
}

static void vsk_MOUSE_ON_OFF_STOP_helper(const VskAstList& args, VskTrapMode mode)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return;

    if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
        VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED);

    VskInt v0 = 1;
    if (args.size() <= 0 || !args[0] || vsk_int(v0, args[0]))
    {
        auto info = vsk_get_mouse_trap(v0);
        if (info)
        {
            info->m_mode = mode;
        }
    }
}

// INSN_MOUSE_OFF (MOUSE OFF) @implemented
static VskAstPtr VSKAPI vsk_MOUSE_OFF(VskAstPtr self, const VskAstList& args)
{
    vsk_MOUSE_ON_OFF_STOP_helper(args, VSK_TRAP_MODE_OFF);
    return nullptr;
}

// INSN_MOUSE_ON (MOUSE ON) @implemented
static VskAstPtr VSKAPI vsk_MOUSE_ON(VskAstPtr self, const VskAstList& args)
{
    vsk_MOUSE_ON_OFF_STOP_helper(args, VSK_TRAP_MODE_ON);
    return nullptr;
}

// INSN_MOUSE_STOP (MOUSE STOP) @implemented
static VskAstPtr VSKAPI vsk_MOUSE_STOP(VskAstPtr self, const VskAstList& args)
{
    vsk_MOUSE_ON_OFF_STOP_helper(args, VSK_TRAP_MODE_STOP);
    return nullptr;
}

static VskAstPtr vsk_LVALUE_helper(const VskString& name, VskIndexList index_list)
{
    // 型付き変数名と変数名の型を取得する
    auto typed_name = vsk_var_get_typed_name(name, index_list.size());
    assert(typed_name.size());
    auto type = vsk_var_get_type(typed_name);

    // 変数を探す
    VskVarDescPtr var_desc = vsk_var_find(typed_name);
    if (!var_desc && (index_list.empty() || (index_list.size() == 1 && index_list[0] <= 10)))
    {
        if (type == VSK_TYPE_STRING)
            return vsk_ast_str(VskString(""));
        return vsk_ast_sng(VskSingle(0));
    }

    // 型に合わせて値を取得する
    void *ptr;
    if (!vsk_var_get_value(typed_name, &ptr, index_list))
    {
        vsk_error(VSK_ERR_BAD_INDEX);
        return nullptr;
    }

    switch (type)
    {
    case VSK_TYPE_SINGLE:
        return vsk_ast_sng(*(VskSingle*)ptr);
    case VSK_TYPE_DOUBLE:
        return vsk_ast_dbl(*(VskDouble*)ptr);
    case VSK_TYPE_INTEGER:
        return vsk_ast_int(*(VskInt*)ptr);
    case VSK_TYPE_STRING:
        {
            auto ret = vsk_ast_str(*(VskString*)ptr);
            delete (VskString*)ptr;
            return ret;
        }
    case VSK_TYPE_LONG:
        return vsk_ast_lng(*(VskLong*)ptr);
    }

    return nullptr;
}

// INSN_IDENTIFIER (識別子) @implemented
static VskAstPtr VSKAPI vsk_IDENTIFIER(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    return vsk_LVALUE_helper(self->m_str, { });
}

// INSN_LVALUE (左辺値; lvalue) @implemented
static VskAstPtr VSKAPI vsk_LVALUE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    assert(args[0]->is_ident());
    assert(args[1]->m_insn == INSN_PARAM_LIST);

    VskIndexList index_list;
    for (auto& param : args[1]->children())
    {
        VskInt value;
        if (!vsk_int(value, param))
            return nullptr;
        if (VSK_STATE()->m_option_base == 1)
            --value;
        if (value < 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_INDEX, nullptr);
        index_list.push_back(value);
    }

    return vsk_LVALUE_helper(args[0]->m_str, index_list);
}

// INSN_IF (IF-THEN-ELSE) @implemented
static VskAstPtr VSKAPI vsk_IF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    VskDouble v0;
    if (vsk_dbl(v0, args[0]))
    {
        auto& index_list = VSK_IMPL()->m_control_path;

        if (v0 != 0)
            index_list.push_back(1); // then
        else if (args[2])
            index_list.push_back(2); // else
        else
            index_list = vsk_next_control_path(index_list);

        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_INKEY_dollar (INKEY$) @implemented
static VskAstPtr VSKAPI vsk_INKEY_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VskString ret;
    if (vsk_inkey)
        ret += (char)vsk_inkey;

    return vsk_ast_str(ret);
}

// INSN_INP (INP) @implemented
static VskAstPtr VSKAPI vsk_INP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        if (!(0 <= v0 && v0 < 256))
        {
            vsk_machine->bad_call();
            return nullptr;
        }
        if (vsk_machine->is_8801_mode())
            return vsk_ast_int(vsk_inport_8801(v0));
        else
            return vsk_ast_int(vsk_inport_9801(v0));
    }

    return nullptr;
}

// INSN_INPUT_dollar (INPUT$) @implemented
static VskAstPtr VSKAPI vsk_INPUT_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 2))
        return nullptr;

    VskInt v0, v1;
    auto arg1 = vsk_arg(args, 1);
    if (vsk_int(v0, args[0]) &&
        (!arg1 || vsk_file_number(v1, arg1)))
    {
        // 256文字以上は失敗
        if (v0 >= 256)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (arg1) // ファイル番号の指定があれば
        {
            // ファイル番号からファイルを取得
            auto file = vsk_get_file_manager()->assoc(v1);
            if (!file)
                VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

            // ファイルから読み込む
            char buf[256];
            if (auto error = file->read_bin(buf, v0))
                VSK_ERROR_AND_RETURN(error, nullptr);

            // 文字列を返す
            return vsk_ast_str(buf);
        }
        else // ファイル番号の指定がなければ
        {
            // キーボードから読み込む準備をする
            VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT_dollar;
            VSK_STATE()->m_input_dollar_length = v0;
            VSK_STATE()->m_input_dollar_string.clear();

            // ロックを解除
            vsk_unlock();
            while (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT_dollar) // INPUT$が解除されるまで待つ
            {
                // 少し待つ
                vsk_sleep(80);
            }
            // ロックする
            vsk_lock();

            // 指定文字数の文字列が入力されていれば
            if (int(VSK_STATE()->m_input_dollar_string.size()) >= v0)
            {
                // 文字列を返す
                auto str = VSK_STATE()->m_input_dollar_string;
                VSK_STATE()->m_input_dollar_string.clear();
                return vsk_ast_str(str);
            }
        }
    }

    return nullptr;
}

// INSN_INSTR (INSTR) @implemented
static VskAstPtr VSKAPI vsk_INSTR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 3))
        return nullptr;

    VskInt pos = 0;
    VskString str0, str1;
    if (args.size() == 2)
    {
        if (!(vsk_str(str0, args[0]) && vsk_str(str1, args[1])))
            return nullptr;
    }
    else if (args.size() == 3)
    {
        if (!(vsk_int(pos, args[0]) && vsk_str(str0, args[1]) && vsk_str(str1, args[2])))
            return nullptr;

        if (pos < 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    }

    if (str1.empty() || pos >= int(str0.size() + 1))
        return vsk_ast_int(0);

    auto ich = str0.find(str1, pos);
    if (ich == str0.npos)
        return vsk_ast_int(0);

    return vsk_ast_int(VskInt(ich + 1));
}

// INSN_KEXT_dollar (KEXT$) @implemented
static VskAstPtr VSKAPI vsk_KEXT_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0, ret;
    VskInt v1;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (v1 != 0 && v1 != 1)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

#ifdef JAPAN
        if (vsk_machine->is_jis_mode())
            v0 = vsk_jis2sjis(v0);

        bool is_zenkaku = (v1 == 1);
        ret = vsk_sjis_kanji_extract(v0, is_zenkaku);

        if (vsk_machine->is_jis_mode())
            ret = vsk_remove_ki_ko(vsk_sjis2jis(ret));
#else
        ret = v0;
#endif
        return vsk_ast_str(ret);
    }

    return nullptr;
}

// INSN_KINSTR (KINSTR) @implemented
static VskAstPtr VSKAPI vsk_KINSTR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 3))
        return nullptr;

    VskInt v0 = 0;
    VskString str0, str1;
    if (args.size() == 2)
    {
        if (!(vsk_str(str0, args[0]) && vsk_str(str1, args[1])))
            return nullptr;
    }
    else if (args.size() == 3)
    {
        if (!(vsk_int(v0, args[0]) && vsk_str(str0, args[1]) && vsk_str(str1, args[2])))
            return nullptr;
    }

    if (str1.empty())
        return vsk_ast_int(0);

    if (vsk_machine->is_jis_mode())
    {
        str0 = vsk_jis2sjis(str0);
        str1 = vsk_jis2sjis(str1);
    }

    size_t ib0 = (v0 != 0) ? vsk_sjis_kpos2ib(str0, v0) : 0;
    size_t ib1 = str0.find(str1, ib0);
    if (ib1 == str0.npos)
        return vsk_ast_int(VskInt(0));

    auto ret = vsk_sjis_ib2kpos(str0, ib1);
    return vsk_ast_int(VskInt(ret));
}

// INSN_KLEN (KLEN) @implemented
static VskAstPtr VSKAPI vsk_KLEN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 2))
        return nullptr;

    VskString v0;
    VskInt v1 = 0;
    if (vsk_str(v0, args[0]) &&
        (args.size() <= 1 || vsk_int(v1, args[1])))
    {
        if (vsk_machine->is_jis_mode())
        {
            int ret = vsk_jis_kanji_len(v0, v1);
            return vsk_ast_int(VskInt(ret));
        }
        else
        {
            int ret = vsk_sjis_kanji_len(v0, v1);
            return vsk_ast_int(VskInt(ret));
        }
    }

    return nullptr;
}

// INSN_KMID_dollar (KMID$) @implemented
static VskAstPtr VSKAPI vsk_KMID_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 3))
        return nullptr;

    VskString v0;
    VskInt v1, v2;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (v1 <= 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (args.size() > 2)
        {
            if (!vsk_int(v2, args[2]))
                return nullptr;
            if (v2 < 0)
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
        else
        {
            v2 = VskInt(v0.size());
        }

        if (int(v0.size()) < v1)
            return vsk_ast_str("");

        if (vsk_machine->is_jis_mode())
        {
            size_t ib0 = vsk_jis_kpos2ib(v0, v1);
            size_t ib1 = vsk_jis_kpos2ib(v0, v1 + v2);
            auto substr = v0.substr(ib0, ib1 - ib0);
            if (!VSK_SETTINGS()->m_unlimited_mode && substr.size() >= 256)
                VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
            return vsk_ast_str(substr);
        }
        else
        {
            size_t ib0 = vsk_sjis_kpos2ib(v0, v1);
            size_t ib1 = vsk_sjis_kpos2ib(v0, v1 + v2);
            auto substr = v0.substr(ib0, ib1 - ib0);
            if (!VSK_SETTINGS()->m_unlimited_mode && substr.size() >= 256)
                VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
            return vsk_ast_str(substr);
        }
    }

    return nullptr;
}

// INSN_KNJ_dollar (KNJ$) @implemented
static VskAstPtr VSKAPI vsk_KNJ_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        if (v0.size() < 4)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        if (!(vsk_isxdigit(v0[0]) && vsk_isxdigit(v0[1]) && vsk_isxdigit(v0[2]) && vsk_isxdigit(v0[3])))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        v0.resize(4);

        VskWord w = (VskWord)std::strtoul(v0.c_str(), nullptr, 16);
        if (!vsk_is_jis_code(w) && !vsk_is_ki_code(w) && !vsk_is_ko_code(w))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        v0.clear();
        v0 += vsk_high_byte(w);
        v0 += vsk_low_byte(w);
        return vsk_ast_str(v0);
    }

    return nullptr;
}

// INSN_KPLOAD
static VskAstPtr VSKAPI vsk_KPLOAD(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_KPOS (KPOS) @implemented
static VskAstPtr VSKAPI vsk_KPOS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    if (!vsk_machine->is_8801_mode() && !VSK_SETTINGS()->m_unlimited_mode)
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    VskString v0;
    VskInt v1;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (v1 < 0 || (!VSK_SETTINGS()->m_unlimited_mode && v1 >= 256))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (vsk_machine->is_jis_mode()) // JISモード
        {
            int klen = vsk_jis_kanji_len(v0, 0);
            if (klen < v1)
                return vsk_ast_int(VskInt(0));

            size_t ib = vsk_jis_kpos2ib(v0, v1);
            return vsk_ast_int(VskInt(ib + 1));
        }
        else // SJISモード
        {
            int klen = vsk_sjis_kanji_len(v0, 0);
            if (klen < v1)
                return vsk_ast_int(VskInt(0));

            size_t ib = vsk_sjis_kpos2ib(v0, v1);
            return vsk_ast_int(VskInt(ib + 1));
        }
    }

    return nullptr;
}

// INSN_KTYPE (KTYPE) @implemented
static VskAstPtr VSKAPI vsk_KTYPE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    VskInt v1;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (v0.empty())
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (vsk_machine->is_jis_mode()) // JISモード
        {
            int klen = vsk_jis_kanji_len(v0, 0);
            if (!(0 < v1 && v1 <= klen))
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

            size_t ib = vsk_jis_kpos2ib(v0, v1);
            if (ib == v0.size())
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

            auto ret = vsk_jis_ktype(&v0[ib]);
            return vsk_ast_int(VskInt(ret));
        }
        else // SJISモード
        {
            int klen = vsk_sjis_kanji_len(v0, 0);
            if (!(0 < v1 && v1 <= klen))
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

            size_t ib = vsk_sjis_kpos2ib(v0, v1);
            if (ib == v0.size())
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

            auto ret = vsk_sjis_ktype(&v0[ib]);
            return vsk_ast_int(VskInt(ret));
        }
    }

    return nullptr;
}

// INSN_LET (LET) @implemented
static VskAstPtr VSKAPI vsk_LET(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    vsk_var_assign(args[0], args[1]);
    return nullptr;
}

// INSN_LINE_INPUT (LINE INPUT) @implemented
static VskAstPtr VSKAPI vsk_LINE_INPUT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    if (!args[0] || vsk_str(v0, args[0]))
    {
        // 左辺値（lvalue）から名前と次元を取得
        VskString name;
        VskIndexList dimension;
        if (!vsk_dimension_from_lvalue(name, dimension, args[1], +(VSK_STATE()->m_option_base == 1)))
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        if (vsk_var_get_type(name) != VSK_TYPE_STRING)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        VSK_STATE()->m_input_prompt = v0;
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;

        vsk_show_input_prompt();
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_LINE_INPUT_WAIT (LINE INPUT WAIT) @implemented
static VskAstPtr VSKAPI vsk_LINE_INPUT_WAIT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    VskInt v0;
    VskString v1;
    if (vsk_int(v0, args[0]) &&
        (!args[1] || vsk_str(v1, args[1])))
    {
        // 左辺値（lvalue）から名前と次元を取得
        VskString name;
        VskIndexList dimension;
        if (!vsk_dimension_from_lvalue(name, dimension, args[2], +(VSK_STATE()->m_option_base == 1)))
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        if (vsk_var_get_type(name) != VSK_TYPE_STRING)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        auto prompt = vsk_machine->get_line_text(VSK_STATE()->m_caret_y);
        mstr_trim_right(prompt, " \t\r\n");
        prompt.resize(vsk_machine->get_line_column(), ' ');

        VSK_STATE()->m_input_prompt = prompt + v1;
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;
        VSK_STATE()->m_input_wait_start = vsk_get_tick_count();
        VSK_STATE()->m_input_wait_interval = v0 * 100;
        VSK_STATE()->m_input_wait_default_path = vsk_get_next_line_path(VSK_IMPL()->m_control_path);

        vsk_show_input_prompt();
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_KINPUT (KINPUT) @implemented
static VskAstPtr VSKAPI vsk_KINPUT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    // 左辺値（lvalue）から変数名と次元を取得
    VskString name;
    VskIndexList dimension;
    if (!vsk_dimension_from_lvalue(name, dimension, args[0], +(VSK_STATE()->m_option_base == 1)))
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    // この変数は文字列でなければならない
    if (vsk_var_get_type(name) != VSK_TYPE_STRING)
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);

    // 行入力の準備
    auto prompt = vsk_machine->get_line_text(VSK_STATE()->m_caret_y);
    mstr_trim_right(prompt, " \t\r\n");
    prompt.resize(vsk_machine->get_line_column(), ' ');
    VSK_SETTINGS()->m_text_mode = VSK_TEXT_MODE_SJIS;
    VSK_STATE()->m_input_prompt = prompt + "\x81\x48 "; // 全角の疑問符を付ける
    VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;
    vsk_show_input_prompt();

    // IMEをONにする
    vsk_ime_on_off(true);

    return vsk_ast(INSN_DONT_GO_NEXT);
}

static VskAstPtr vsk_INPUT_WAIT_helper(const VskAstList& args, bool semicolon)
{
    if (!vsk_arity_in_range(args, 3, 3))
        return nullptr;

    VskInt v0;
    VskString v1;
    if (vsk_int(v0, args[0]) &&
        (!args[1] || vsk_str(v1, args[1])))
    {
        auto v2 = args[2];
        assert(v2->m_insn == INSN_LVALUE_LIST);

        for (auto arg : v2->children())
        {
            // 左辺値（lvalue）から名前と次元を取得
            VskString name;
            VskIndexList dimension;
            if (!vsk_dimension_from_lvalue(name, dimension, arg, +(VSK_STATE()->m_option_base == 1)))
            {
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
            }
        }

        if (!args[1] || semicolon)
            v1 += "? ";

        auto prompt = vsk_machine->get_line_text(VSK_STATE()->m_caret_y);
        mstr_trim_right(prompt, " \t\r\n");
        prompt.resize(vsk_machine->get_line_column(), ' ');
        VSK_STATE()->m_input_prompt = prompt + v1;
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;

        VSK_STATE()->m_input_wait_start = vsk_get_tick_count();
        VSK_STATE()->m_input_wait_interval = v0 * 100;
        VSK_STATE()->m_input_wait_default_path = vsk_get_next_line_path(VSK_IMPL()->m_control_path);
        vsk_show_input_prompt();
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_INPUT_WAIT (INPUT WAIT) @implemented
static VskAstPtr VSKAPI vsk_INPUT_WAIT(VskAstPtr self, const VskAstList& args)
{
    return vsk_INPUT_WAIT_helper(args, false);
}

// INSN_INPUT_WAIT_semicolon (INPUT WAIT;) @implemented
static VskAstPtr VSKAPI vsk_INPUT_WAIT_semicolon(VskAstPtr self, const VskAstList& args)
{
    return vsk_INPUT_WAIT_helper(args, true);
}

static VskAstPtr vsk_INPUT_helper(const VskAstList& args, bool semicolon)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    if (!args[0] || vsk_str(v0, args[0]))
    {
        auto v1 = args[1];
        assert(v1->m_insn == INSN_LVALUE_LIST);

        for (auto arg : v1->children())
        {
            // 左辺値（lvalue）から名前と次元を取得
            VskString name;
            VskIndexList dimension;
            if (!vsk_dimension_from_lvalue(name, dimension, arg, +(VSK_STATE()->m_option_base == 1)))
            {
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
            }
        }

        if (!args[0] || semicolon)
            v0 += "? ";

        auto prompt = vsk_machine->get_line_text(VSK_STATE()->m_caret_y);
        mstr_trim_right(prompt, " \t\r\n");
        prompt.resize(vsk_machine->get_line_column(), ' ');

        VSK_STATE()->m_input_prompt = prompt + v0;
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;
        vsk_show_input_prompt();
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_INPUT (INPUT) @implemented
static VskAstPtr VSKAPI vsk_INPUT(VskAstPtr self, const VskAstList& args)
{
    return vsk_INPUT_helper(args, false);
}

// INSN_INPUT_semicolon (INPUT;) @implemented
static VskAstPtr VSKAPI vsk_INPUT_semicolon(VskAstPtr self, const VskAstList& args)
{
    return vsk_INPUT_helper(args, true);
}

// INSN_INPUT_sharp (INPUT#) @implemented
static VskAstPtr VSKAPI vsk_INPUT_sharp(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 64))
        return nullptr;

    VskError error;
    auto file = vsk_eval_file_number(args[0], error);
    if (!file)
        VSK_ERROR_AND_RETURN(error, nullptr);

    VskString line;
    error = file->read_line(line);
    if (!file)
        VSK_ERROR_AND_RETURN(error, nullptr);

    // 入力テキストを分割
    std::vector<VskString> data;
    vsk_split_input_text(data, line);

    // 左辺値への入力
    for (size_t iarg = 1; iarg < args.size() && iarg - 1 < data.size(); ++iarg)
    {
        vsk_complete_lvalue_input(args[iarg], data[iarg - 1], false);
    }

    return nullptr;
}

// INSN_LOC (LOC) @implemented
static VskAstPtr VSKAPI vsk_LOC(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt fileno;
    if (!vsk_file_number(fileno, args[0]))
        return nullptr;

    auto file = vsk_get_file_manager()->assoc(fileno);
    if (!file)
        VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

    if (file->is_random()) // ランダムファイル？
    {
        VskDword offset;
        if (!file->get_pos(&offset))
            VSK_ERROR_AND_RETURN(VSK_ERR_DISK_IO_ERROR, nullptr);
        VskInt record_len = vsk_field_get_len(fileno);
        if (record_len == 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        return vsk_ast_dbl(offset / record_len + 1); // レコード番号
    }

    if (file->is_sequential()) // シーケンシャルファイル？
    {
        VskDword offset;
        if (!file->get_pos(&offset))
            VSK_ERROR_AND_RETURN(VSK_ERR_DISK_IO_ERROR, nullptr);
        return vsk_ast_dbl(offset / VSK_SECTOR_SIZE); // セクタ数
    }

    if (file->is_keyboard() || file->is_com()) // キーボードか通信ファイル？
    {
        mdbg_traceA("TODO:\n");
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
}

// INSN_LOF (LOF) @implemented
static VskAstPtr VSKAPI vsk_LOF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt fileno;
    if (!vsk_file_number(fileno, args[0]))
        return nullptr;

    auto file = vsk_get_file_manager()->assoc(fileno);
    if (!file)
        VSK_ERROR_AND_RETURN(VSK_ERR_FILE_NOT_OPEN, nullptr);

    if (file->is_sequential()) // シーケンシャルファイル？
    {
        VskDword size;
        if (!file->get_size(&size))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        return vsk_ast_dbl(size / VSK_SECTOR_SIZE); // セクタ数
    }

    if (file->is_random()) // ランダムファイル？
    {
        VskDword size;
        if (!file->get_size(&size))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        VskInt record_len = vsk_field_get_len(fileno);
        if (record_len == 0)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        return vsk_ast_dbl(size / record_len); // レコード番号
    }

    if (file->is_com()) // 通信ファイル？
    {
        mdbg_traceA("TODO:\n");
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    }

    VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
}

// INSN_MAP (MAP) @implemented
static VskAstPtr VSKAPI vsk_MAP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskSingle v0;
    VskInt v1;
    if (vsk_sng(v0, args[0]) && vsk_int(v1, args[1]))
    {
        switch (v1)
        {
        case 0: return vsk_ast_int(vsk_machine->world_to_view({ v0, 0 }).m_x);
        case 1: return vsk_ast_int(vsk_machine->world_to_view({ 0, v0 }).m_y);
        case 2: return vsk_ast_sng(vsk_machine->view_to_world({ vsk_round(v0), 0 }).m_x);
        case 3: return vsk_ast_sng(vsk_machine->view_to_world({ 0, vsk_round(v0) }).m_y);
        default:
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
    }

    return nullptr;
}

// INSN_MID_dollar_func (MID$ 関数) @implemented
static VskAstPtr VSKAPI vsk_MID_dollar_func(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 3))
        return nullptr;

    VskString v0;
    VskInt v1, v2 = -1;
    if (vsk_str(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (!VSK_SETTINGS()->m_unlimited_mode && v0.size() > VSK_MAX_STR_LEN)
            VSK_ERROR_AND_RETURN(VSK_ERR_STRING_TOO_LONG, nullptr);
        if (v0 == "" || v1 <= 0 || v1 > int(v0.size()))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (args.size() == 2)
        {
            return vsk_ast_str(v0.substr(v1 - 1));
        }
        else if (args.size() == 3 && vsk_int(v2, args[2]))
        {
            if (v2 < 0)
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
            if (v1 + v2 - 1 > int(v0.size()))
                v2 = VskInt(v0.size() - v1 + 1);
            return vsk_ast_str(v0.substr(v1 - 1, v2));
        }
    }

    return nullptr;
}

// INSN_MID_dollar_stmt (MID$ 文) @implemented
static VskAstPtr VSKAPI vsk_MID_dollar_stmt(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 4, 4))
        return nullptr;

    VskString v0, v3;
    VskInt v1, v2;
    if (vsk_str(v0, args[0]) &&
        vsk_int(v1, args[1]) &&
        (!args[2] || vsk_int(v2, args[2])) &&
        vsk_str(v3, args[3]))
    {
        if (v0 == "" || v1 <= 0 || v1 > int(v0.size()))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        --v1;
        if (!args[2] || v2 > VskInt(v3.size()))
            v2 = VskInt(v3.size());
        VskString ret = v0;
        for (VskInt i = v1; i < int(v0.size()) && (i - v1) < v2; ++i)
            ret[i] = v3[i - v1];
        vsk_var_assign(args[0], vsk_ast_str(ret));
    }
    return nullptr;
}

// INSN_MKI_dollar (MKI$) @implemented
static VskAstPtr VSKAPI vsk_MKI_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskShort v0;
    static_assert(sizeof(v0) == 2, "");
    if (vsk_sht(v0, args[0]))
    {
        VskString str;
        str.resize(sizeof(v0));

        std::memcpy(&str[0], &v0, sizeof(v0));
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_MKS_dollar (MKS$) @implemented
// NOTE: 浮動小数点数の形式が実機とは異なっている
static VskAstPtr VSKAPI vsk_MKS_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskSingle v0;
    static_assert(sizeof(v0) == 4, "");
    if (vsk_sng(v0, args[0]))
    {
        VskString str;
        str.resize(sizeof(v0));

        std::memcpy(&str[0], &v0, sizeof(v0));
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_MKD_dollar (MKD$) @implemented
// NOTE: 浮動小数点数の形式が実機とは異なっている
static VskAstPtr VSKAPI vsk_MKD_dollar(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskDouble v0;
    static_assert(sizeof(v0) == 8, "");
    if (vsk_dbl(v0, args[0]))
    {
        VskString str;
        str.resize(sizeof(v0));

        std::memcpy(&str[0], &v0, sizeof(v0));
        return vsk_ast_str(str);
    }

    return nullptr;
}

// INSN_CVI (CVI) @implemented
static VskAstPtr VSKAPI vsk_CVI(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        VskShort ret;
        static_assert(sizeof(ret) == 2, "");
        if (v0.size() != sizeof(ret))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        std::memcpy(&ret, &v0[0], sizeof(ret));
        return vsk_ast(INSN_SHT_LITERAL, ret);
    }

    return nullptr;
}

// INSN_CVS (CVS) @implemented
// NOTE: 浮動小数点数の形式が実機とは異なっている
static VskAstPtr VSKAPI vsk_CVS(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        VskSingle ret;
        static_assert(sizeof(ret) == 4, "");
        if (v0.size() != sizeof(ret))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        std::memcpy(&ret, &v0[0], sizeof(ret));
        return vsk_ast_sng(ret);
    }

    return nullptr;
}

// INSN_CVD (CVD) @implemented
// NOTE: 浮動小数点数の形式が実機とは異なっている
static VskAstPtr VSKAPI vsk_CVD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskString v0;
    if (vsk_str(v0, args[0]))
    {
        VskDouble ret;
        static_assert(sizeof(ret) == 8, "");
        if (v0.size() != sizeof(ret))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        std::memcpy(&ret, &v0[0], sizeof(ret));
        return vsk_ast_dbl(ret);
    }

    return nullptr;
}

// INSN_MON (MON)
static VskAstPtr VSKAPI vsk_MON(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_MOTOR (MOTOR)
static VskAstPtr VSKAPI vsk_MOTOR(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_NEW (NEW) @implemented
static VskAstPtr VSKAPI vsk_NEW(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    // プログラムリストをクリアする
    VSK_IMPL()->m_program_text.clear();
    // コントロールパスをクリアする
    VSK_IMPL()->m_control_path.clear();
    // ループ情報を消す
    VSK_IMPL()->m_loop_map.clear();
    // ターゲット行をクリアする
    VSK_IMPL()->m_target_line_text.clear();
    // ダイレクトコードをクリアする
    VSK_IMPL()->m_direct_code = nullptr;
    // DATAの読み込み位置を初期化
    VSK_IMPL()->m_data_pointer = { I_PROGRAM_CODE };
    // トレースをOFFにする
    VSK_IMPL()->m_trace_on = false;
    // エラーをクリア
    VSK_STATE()->error_clear();
    // 変数を全部消す
    vsk_var_clear_all();
    // ファイルを全部閉じる
    vsk_file_close_all();
    // 乱数の初期化
    vsk_rand_init(0);
    // DEF FNのデータを消す
    VSK_IMPL()->m_fn_to_path.clear();
    // コマンドレベルに戻る
    vsk_enter_command_level();

    return nullptr;
}

// INSN_NEW_ON
static VskAstPtr VSKAPI vsk_NEW_ON(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_NOT (NOT) @implemented
static VskAstPtr VSKAPI vsk_NOT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
        return vsk_ast_int(~v0);

    return nullptr;
}

// INSN_ON_ERROR_GOTO (ON ERROR GOTO)
static VskAstPtr VSKAPI vsk_ON_ERROR_GOTO(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = args[0];
    assert(arg0->m_insn == INSN_LABEL);
    auto arg = arg0->at(0);
    if (arg->is_number() && arg->to_dbl() == 0)
    {
        VSK_IMPL()->m_error_trap.reset();
        return nullptr;
    }

    auto index_list = vsk_label_to_index_list(arg0, VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_error_trap.m_mode = VSK_TRAP_MODE_ON;
    VSK_IMPL()->m_error_trap.m_index_list = index_list;

    return nullptr;
}

// INSN_ON_KEY_GOSUB (ON KEY GOSUB) @implemented
static VskAstPtr VSKAPI vsk_ON_KEY_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto arg0 = args[0];
    for (size_t key = 0; key < 10; ++key)
    {
        if (key < arg0->size() && arg0->at(key))
        {
            auto index_list = vsk_label_to_index_list(arg0->at(key), VSK_IMPL()->m_label_map);
            if (index_list.empty())
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

            VSK_IMPL()->m_traps[VSK_TRAP_F1 + key].m_index_list = index_list;
        }
        else
        {
            VSK_IMPL()->m_traps[VSK_TRAP_F1 + key].m_index_list.clear();
        }
    }

    return nullptr;
}

// INSN_ON_MOUSE_GOSUB (ON MOUSE GOSUB) @implemented
static VskAstPtr VSKAPI vsk_ON_MOUSE_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    auto index_list = vsk_label_to_index_list(args[1], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VskInt v0 = 1;
    if (!args[0] || vsk_int(v0, args[0]))
    {
        auto info = vsk_get_mouse_trap(v0);
        if (info)
            info->m_index_list = index_list;
    }

    return nullptr;
}

// INSN_ON_PEN_GOSUB (ON PEN GOSUB) @implemented
static VskAstPtr VSKAPI vsk_ON_PEN_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_traps[VSK_TRAP_PEN].m_index_list = index_list;
    return nullptr;
}

// INSN_ON_STOP_GOSUB (ON STOP GOSUB) @implemented
static VskAstPtr VSKAPI vsk_ON_STOP_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_traps[VSK_TRAP_STOP].m_index_list = index_list;
    return nullptr;
}

// INSN_ON_TIME_dollar_GOSUB (ON TIME$ GOSUB) @implemented
static VskAstPtr VSKAPI vsk_ON_TIME_dollar_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    if (!vsk_str(v0, args[0]))
        return nullptr;

    if (v0.size() != 8 ||
        !vsk_isdigit(v0[0]) ||
        !vsk_isdigit(v0[1]) ||
        (v0[2] != ':') ||
        !vsk_isdigit(v0[3]) ||
        !vsk_isdigit(v0[4]) ||
        (v0[5] != ':') ||
        !vsk_isdigit(v0[6]) ||
        !vsk_isdigit(v0[7]))
    {
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    }

    auto index_list = vsk_label_to_index_list(args[1], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_trap_time = v0;
    VSK_IMPL()->m_traps[VSK_TRAP_TIME].m_index_list = index_list;
    return nullptr;
}

// INSN_ON_COM_GOSUB
static VskAstPtr VSKAPI vsk_ON_COM_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_traps[VSK_TRAP_COM].m_index_list = index_list;
    return nullptr;
}

// INSN_ON_PLAY_GOSUB
static VskAstPtr VSKAPI vsk_ON_PLAY_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_traps[VSK_TRAP_PLAY].m_index_list = index_list;
    return nullptr;
}

// INSN_ON_HELP_GOSUB
static VskAstPtr VSKAPI vsk_ON_HELP_GOSUB(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto index_list = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    if (index_list.empty())
        VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

    VSK_IMPL()->m_traps[VSK_TRAP_HELP].m_index_list = index_list;
    return nullptr;
}

// INSN_OPEN (OPEN) @implemented
static VskAstPtr VSKAPI vsk_OPEN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 4, 4))
        return nullptr;

    VskString v0, v1, v2;
    VskInt v3;
    if (vsk_str(v0, args[0]) &&
        (!args[1] || vsk_ident(v1, args[1])) &&
        vsk_ident(v2, args[2]) &&
        vsk_file_number(v3, args[3]))
    {
        auto& descriptor = v0;
        auto& mode = v1;
        auto& as = v2;
        auto& file_number = v3;
        if (as != "AS")
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
        if (mode != "INPUT" && mode != "OUTPUT" && mode != "APPEND" && mode != "")
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        auto file_manager = vsk_get_file_manager();
        if (file_manager->assoc(file_number))
            VSK_ERROR_AND_RETURN(VSK_ERR_FILE_ALREADY_OPEN, nullptr);
        if (file_number > VSK_STATE()->m_how_many_files)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_FILE_NO, nullptr);

        VskFilePtr file;
        VskFile::MODE file_mode;
        if (mode == "INPUT")
            file_mode = VskFile::MODE_INPUT;
        else if (mode == "OUTPUT")
            file_mode = VskFile::MODE_OUTPUT;
        else if (mode == "APPEND")
            file_mode = VskFile::MODE_APPEND;
        else
            file_mode = VskFile::MODE_DEFAULT;

        auto error = file_manager->open(file, descriptor, file_mode);
        if (error)
            VSK_ERROR_AND_RETURN(error, nullptr);
        file_manager->assoc(file_number, file);
    }

    return nullptr;
}

// INSN_OPTION_IDENT (OPTION ...) @implemented
static VskAstPtr VSKAPI vsk_OPTION_IDENT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskString v0;
    if (!vsk_ident(v0, args[0]))
        return nullptr;

    if (v0 == "BASE") // OPTION BASE
    {
        if (!args[1]->is_int() || !(args[1]->m_int == 0 || args[1]->m_int == 1))
        {
            vsk_machine->syntax_error();
            return nullptr;
        }

        if (VSK_STATE()->m_option_base != -1)
        {
            vsk_machine->do_error(VSK_ERR_DUPLICATE_DEFINE);
            return nullptr;
        }

        VSK_STATE()->m_option_base = !!args[1]->m_int;
    }
    else
    {
        vsk_machine->syntax_error();
    }

    return nullptr;
}

// INSN_OUT (OUT)
static VskAstPtr VSKAPI vsk_OUT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    VskInt v0, v1;
    if (vsk_int(v0, args[0]) && vsk_int(v1, args[1]))
    {
        if (vsk_machine->is_8801_mode())
        {
            switch (v0)
            {
            case 0x40:
                // BEEP音のオン／オフ
                if (v1 == 0x20)
                    vsk_BEEP(self, { vsk_ast_int(1) });
                else if (v1 == 0)
                    vsk_BEEP(self, { vsk_ast_int(0) });
                break;
            case 0x51:
                switch (v1)
                {
                case 0:
                    // テキスト画面非表示
                    VSK_STATE()->m_show_text = false;
                    break;
                case 0x20:
                    // テキスト画面表示
                    VSK_STATE()->m_show_text = true;
                    break;
                }
                break;
            }
        }
        else
        {
            switch (v0)
            {
            case 0x37:
                // BEEP音のオン／オフ
                if (v1 == 0x06)
                    vsk_BEEP(self, { vsk_ast_int(1) });
                else if (v1 == 0x07)
                    vsk_BEEP(self, { vsk_ast_int(0) });
                break;
            case 0x68:
                switch (v1)
                {
                case 0x06:
                    mdbg_traceA("TODO: 8801 font\n");
                    break;
                case 0x07:
                    mdbg_traceA("TODO: 9801 font\n");
                    break;
                case 0x08:
                    // 奇数ラスタの表示
                    VSK_STATE()->m_odd_line = true;
                    break;
                case 0x09:
                    // 奇数ラスタの非表示
                    VSK_STATE()->m_odd_line = false;
                    break;
                case 0x0E:
                    // 画面の非表示
                    VSK_STATE()->m_show_text = false;
                    VSK_STATE()->m_show_graphics = false;
                    break;
                case 0x0F:
                    // 画面の表示
                    VSK_STATE()->m_show_text = true;
                    VSK_STATE()->m_show_graphics = true;
                    break;
                }
                break;
            case 0x6A:
                // TODO: パレットモード
                break;
            case 0xA4:
                // TODO: 表示画面の切り替え
                break;
            case 0xA6:
                // TODO: アクティブ画面の切り替え
                break;
            }
        }
    }
    return nullptr;
}

// INSN_PEN (PEN) @implemented
static VskAstPtr VSKAPI vsk_PEN(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    VskInt v0;
    if (vsk_int(v0, args[0]))
    {
        switch (v0)
        {
        case 0:
            if (VSK_IMPL()->m_pen_pressed)
                return vsk_ast_int(-1);
            return vsk_ast_int(0);
        case 1:
            return vsk_ast_int(VskInt(VSK_IMPL()->m_pen_x));
        case 2:
            return vsk_ast_int(VskInt(VSK_IMPL()->m_pen_y));
        default:
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
    }

    return nullptr;
}

// INSN_MOUSE_func (MOUSE関数) @implemented
static VskAstPtr VSKAPI vsk_MOUSE_func(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 2))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);
    if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
        VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);

    VskInt v0, v1 = 0;
    if (vsk_int(v0, args[0]) &&
        (args.size() <= 1 || vsk_int(v1, args[1])))
    {
        switch (v0)
        {
        case 0: // マウスのX座標
            return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_x[VSK_MOUSE_NONE])); 
        case 1: // マウスのY座標
            return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_y[VSK_MOUSE_NONE]));
        case 2: // マウスボタンの状態
            switch (v1)
            {
            case 1:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_pressed[VSK_MOUSE_LEFT_PRESS]));
            case 2:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_pressed[VSK_MOUSE_RIGHT_PRESS]));
            }
            break;
        case 3: // 最後にこの関数が実行されてから現在までの間に、指定されたボタンが押された回数
            // TODO:
            break;
        case 4: // マウスボタンが押されたときのX座標
            switch (v1)
            {
            case 1:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_x[VSK_MOUSE_LEFT_PRESS]));
            case 2:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_x[VSK_MOUSE_RIGHT_PRESS]));
            }
            break;
        case 5: // マウスボタンが押されたときのY座標
            switch (v1)
            {
            case 1:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_y[VSK_MOUSE_LEFT_PRESS]));
            case 2:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_y[VSK_MOUSE_RIGHT_PRESS]));
            }
            break;
        case 6: // 最後にこの関数が実行されてから現在までの間に、指定されたボタンが離された回数
            // TODO:
            break;
        case 7: // マウスボタンが離されたときのX座標
            switch (v1)
            {
            case 1:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_x[VSK_MOUSE_LEFT_RELEASE]));
            case 2:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_x[VSK_MOUSE_RIGHT_RELEASE]));
            }
            break;
        case 8: // マウスボタンが離されたときのY座標
            switch (v1)
            {
            case 1:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_y[VSK_MOUSE_LEFT_RELEASE]));
            case 2:
                return vsk_ast_int(VskInt(VSK_IMPL()->m_mouse_y[VSK_MOUSE_RIGHT_RELEASE]));
            }
            break;
        case 9: // 最後にこの関数が実行されてから現在までに移動したX方向の距離
            // TODO:
            break;
        case 10: // 最後にこの関数が実行されてから現在までに移動したY方向の距離
            // TODO:
            break;
        default:
            break;
        }
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    }

    return nullptr;
}

// vsk_MOUSE_stmt (MOUSE文) @implemented
static VskAstPtr VSKAPI vsk_MOUSE_stmt(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 5))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    VskInt v0, v1, v2, v3, v4;
    if (vsk_int(v0, args[0]))
    {
        switch (v0)
        {
        case 0:
            VSK_IMPL()->m_mouse_inited = true;
            // ...FALL THROUGH...
        case 6:
            // マウスの初期化・破棄
            if (v0 == 6 && !VSK_IMPL()->m_mouse_inited)
                VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);
            if (args.size() > 1)
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
            vsk_mouse_clip(-1, -1, -1, -1);
            VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_MOVE].reset();
            VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_PRESS].reset();
            VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_PRESS].reset();
            VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_LEFT_RELEASE].reset();
            VSK_IMPL()->m_traps[VSK_TRAP_MOUSE_RIGHT_RELEASE].reset();
            VSK_IMPL()->m_mouse_x = { 0 };
            VSK_IMPL()->m_mouse_y = { 0 };
            VSK_IMPL()->m_mouse_pressed = { 0 };
            if (v0 == 0)
                vsk_set_mouse_pos(VSK_STATE()->m_screen_width / 2, VSK_STATE()->m_screen_height / 2, true);
            if (v0 == 6)
                VSK_IMPL()->m_mouse_inited = false;
            break;
        case 1: // マウスの移動、表示・非表示
            if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
                VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);
            if (args.size() > 4)
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
            v1 = v2 = -1;
            v3 = 1;
            if ((args.size() <= 1 || !args[1] || vsk_int(v1, args[1])) &&
                (args.size() <= 2 || !args[2] || vsk_int(v2, args[2])) &&
                (args.size() <= 3 || !args[3] || vsk_int(v3, args[3])))
            {
                vsk_set_mouse_pos(v1, v2, !!v3);
            }
            break;
        case 2: // マウスポインタの形状
            if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
                VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);
            mdbg_traceA("TODO: mouse cursor shape\n");
            break;
        case 3: // マウスポインタの移動比率
            if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
                VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);
            mdbg_traceA("TODO: mouse move ratio\n");
            break;
        case 4: // マウスのクリッピング
            if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
                VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);
            if (args.size() > 5)
                VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
            v1 = v2 = v3 = v4 = -1;
            if ((args.size() <= 1 || !args[1] || vsk_int(v1, args[1])) &&
                (args.size() <= 2 || !args[2] || vsk_int(v2, args[2])) &&
                (args.size() <= 3 || !args[3] || vsk_int(v3, args[3])) &&
                (args.size() <= 4 || !args[4] || vsk_int(v4, args[4])))
            {
                vsk_mouse_clip(v1, v2, v3, v4);
            }
            break;
        case 5: // マウスの色
            if (!VSK_SETTINGS()->m_unlimited_mode && !VSK_IMPL()->m_mouse_inited)
                VSK_ERROR_AND_RETURN(VSK_ERR_MOUSE_NOT_INITED, nullptr);
            mdbg_traceA("TODO: mouse cursor color\n");
            break;
        default:
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }
    }

    return nullptr;
}

// INSN_PLAY (PLAY) @implemented
static VskAstPtr VSKAPI vsk_PLAY(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 2))
        return nullptr;

    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
        VSK_ERROR_AND_RETURN(VSK_ERR_NO_FEATURE, nullptr);

    VskInt v0 = 2;
    if (args[0] && !vsk_file_number(v0, args[0]))
        return nullptr;

    auto arg1 = args[1];

    std::vector<VskString> strs;
    for (size_t i = 0; i < arg1->size(); ++i)
    {
        auto arg = arg1->at(i);
        if (!arg)
        {
            strs.push_back("");
            continue;
        }

        VskString str;
        if (!vsk_str(str, arg))
            return nullptr;
        strs.push_back(str);
    }

    switch (v0)
    {
    case 0:
    case 1:
        if (!vsk_sound_play_fm(strs))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        break;
    case 2:
        if (!vsk_sound_play_ssg(strs))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        break;
    default:
        vsk_machine->bad_call();
        return nullptr;
    }

    if (!VSK_IMPL()->m_play_bgm)
    {
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_PLAY;
        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_PLAY_ALLOC
static VskAstPtr VSKAPI vsk_PLAY_ALLOC(VskAstPtr self, const VskAstList& args)
{
    return nullptr;
}

// INSN_RND (RND) @implemented
static VskAstPtr VSKAPI vsk_RND(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    VskInt v0 = 1;
    if (args.size() <= 0 || vsk_int(v0, args[0]))
        return vsk_ast_sng(VskSingle(vsk_rand_get_next(v0)));

    return nullptr;
}

// INSN_RANDOMIZE (RANDOMIZE) @implemented
static VskAstPtr VSKAPI vsk_RANDOMIZE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    if (args.size() == 0)
    {
        VSK_STATE()->m_input_prompt = "Random number seed (-32768 to 32767)? ";
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPUT;
        vsk_show_input_prompt();
        return vsk_ast(INSN_DONT_GO_NEXT);
    }
    else
    {
        VskInt v0;
        if (vsk_int(v0, args[0]))
        {
            vsk_rand_init(v0);
        }
    }

    return nullptr;
}

// INSN_READ (READ) @implemented
static VskAstPtr VSKAPI vsk_READ(VskAstPtr self, const VskAstList& args)
{
    auto& data_pointer = VSK_IMPL()->m_data_pointer;

    // 各引数について
    for (auto& arg : args)
    {
        if (!arg->is_ident())
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        VskType type = vsk_var_get_type(arg->m_str);

        VskAstPtr data;
        do
        {
            // データポインタが空なら"Out of DATA"エラー
            if (data_pointer.empty())
                VSK_ERROR_AND_RETURN(VSK_ERR_OUT_OF_DATA, nullptr);

            // データポインタを解決。データ項目ならループ終了
            data = vsk_resolve_index_list(data_pointer);
            if (data->is_data_entry())
                break;

            // 次のデータポインタへ
            data_pointer = vsk_next_data_pointer(data_pointer);
        } while (true);

        // 変数の型が文字列でなく、データが文字列なら文法エラー
        if (type != VSK_TYPE_STRING && data->is_str())
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);

        // データがデータリテラルであれば、適切な型に修正
        if (data->is_data_literal())
        {
            if (type == VSK_TYPE_STRING)
            {
                data = vsk_ast_str(data->m_str);
            }
            else
            {
                VSK_TYPE type2;
                data = vsk_parse_number(data->m_str.c_str(), nullptr, type2);
            }
        }

        // 変数に代入
        if (!vsk_var_assign(arg, data))
            break;

         // 次のデータポインタへ
        data_pointer = vsk_next_data_pointer(data_pointer);
    }

    return nullptr;
}

// INSN_RESTORE (RESTORE) @implemented
static VskAstPtr VSKAPI vsk_RESTORE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    if (args.size() >= 1)
    {
        VSK_IMPL()->m_data_pointer = vsk_label_to_index_list(args[0], VSK_IMPL()->m_label_map);
    }
    else
    {
        VSK_IMPL()->m_data_pointer = { I_PROGRAM_CODE };
    }

    return nullptr;
}

// INSN_RENUM (RENUM) @implemented
static VskAstPtr VSKAPI vsk_RENUM(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 3))
        return nullptr;

    VskDouble v0, v1 = 0, v2 = 10;
    if (vsk_dbl(v0, args[0]) &&
        (args.size() <= 1 || !args[1] || vsk_dbl(v1, args[1])) &&
        (args.size() <= 2 || !args[2] || vsk_dbl(v2, args[2])))
    {
        auto& text = VSK_IMPL()->m_program_text;

        auto first_lineno = (renum_lineno_t)vsk_line_number_from_line_text(text, nullptr);
        if (first_lineno == 0)
        {
            RENUM_add_line_numbers(text, (renum_lineno_t)v0, (renum_lineno_t)v2);
        }
        else
        {
            RENUM_renumber_lines(text, (renum_lineno_t)v0, (renum_lineno_t)v1, (renum_lineno_t)v2, true);
        }
    }

    return nullptr;
}

// INSN_RESUME
static VskAstPtr VSKAPI vsk_RESUME(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_ROLL (ROLL) @implemented
static VskAstPtr VSKAPI vsk_ROLL(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 3))
        return nullptr;

    VskInt v0 = 0, v1 = 0;
    VskString v2 = "N";
    if (!VSK_SETTINGS()->m_unlimited_mode && vsk_machine->is_8801_mode())
    {
        if (args.size() >= 2)
            VSK_SYNTAX_ERROR_AND_RETURN(nullptr);
        if (vsk_int(v0, args[0]))
        {
            if (v0 < -197) v0 = -197;
            if (v0 > +197) v0 = +197;
            vsk_machine->draw_scroll(0, -v0, 0);
        }
    }
    else
    {
        if (args[0] && !vsk_int(v0, args[0]))
            return nullptr;
        if (args.size() > 1 && args[1] && !vsk_int(v1, args[1]))
            return nullptr;
        if (args.size() > 2 && args[2] && args[2]->is_ident())
        {
            v2 = args[2]->m_str;
            if (v2 != "Y" && v2 != "N")
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
        }

        if (!VSK_SETTINGS()->m_unlimited_mode)
        {
            if (VSK_STATE()->m_screen_height == 400)
            {
                if (v0 < -399) v0 = -399;
                if (v0 > +399) v0 = +399;
            }
            else
            {
                if (v0 < -199) v0 = -199;
                if (v0 > +199) v0 = +199;
            }

            if (v1 < -639) v1 = -639;
            if (v1 > +639) v1 = +639;

            if (v1 < 0)
                v1 = -((-v1 / 8) * 8);
            else
                v1 = +((+v1 / 8) * 8);
        }

        if (v2 == "Y")
            vsk_machine->draw_scroll(-v1, -v0, VSK_STATE()->m_fore_color);
        else
            vsk_machine->draw_scroll(-v1, -v0, 0);
    }
    return nullptr;
}

// INSN_SEARCH (SEARCH) @implemented
static VskAstPtr VSKAPI vsk_SEARCH(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 4))
        return nullptr;

    VskString v0;
    VskInt v1, v2 = 1, v3 = 1;
    if (vsk_ident(v0, args[0]) && vsk_int(v1, args[1]))
    {
        VskIndexList dimension = vsk_var_get_dimension(v0);

        if (vsk_var_get_type(v0) != VSK_TYPE_INTEGER || dimension.size() != 1)
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

        if (args.size() > 2 && !vsk_int(v2, args[2]))
            return nullptr;
        if (args.size() > 3 && !vsk_int(v3, args[3]))
            return nullptr;

        for (VskInt i = v2; i < VskInt(dimension[0]); i += v3)
        {
            void *ptr;
            if (!vsk_var_get_value(v0, &ptr, { size_t(i) }))
                VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

            if (*(VskInt*)ptr == v1) // 見つかった
                return vsk_ast_int(i);
        }

        return vsk_ast_int(-1); // 見つからなかった
    }

    return nullptr;
}

// INSN_SET
static VskAstPtr VSKAPI vsk_SET(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_STOP (STOP) @implemented
static VskAstPtr VSKAPI vsk_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    vsk_stop();
    return nullptr;
}

// INSN_TERM
static VskAstPtr VSKAPI vsk_TERM(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_TIME_dollar_OFF (TIME$ OFF) @implemented
static VskAstPtr VSKAPI vsk_TIME_dollar_OFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_TIME].m_mode = VSK_TRAP_MODE_OFF;
    return nullptr;
}

// INSN_TIME_dollar_ON (TIME$ ON) @implemented
static VskAstPtr VSKAPI vsk_TIME_dollar_ON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_TIME].m_mode = VSK_TRAP_MODE_ON;
    return nullptr;
}

// INSN_TIME_dollar_STOP (TIME$ STOP) @implemented
static VskAstPtr VSKAPI vsk_TIME_dollar_STOP(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_traps[VSK_TRAP_TIME].m_mode = VSK_TRAP_MODE_STOP;
    return nullptr;
}

// INSN_TROFF (TROFF) @implemented
static VskAstPtr VSKAPI vsk_TROFF(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_trace_on = false;
    return nullptr;
}

// INSN_TRON (TRON) @implemented
static VskAstPtr VSKAPI vsk_TRON(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    VSK_IMPL()->m_trace_on = true;
    return nullptr;
}

// INSN_USR
static VskAstPtr VSKAPI vsk_USR(VskAstPtr self, const VskAstList& args)
{
    assert(0);
    return nullptr;
}

// INSN_WAIT (WAIT) @implemented
static VskAstPtr VSKAPI vsk_WAIT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 2, 3))
        return nullptr;

    VskInt v0, v1, v2 = 0;
    if (vsk_int(v0, args[0]) &&
        vsk_int(v1, args[1]) &&
        (args.size() <= 2 || vsk_int(v2, args[2])))
    {
        VSK_STATE()->m_wait_inport_port = v0;
        VSK_STATE()->m_wait_inport_data1 = v1;
        VSK_STATE()->m_wait_inport_data2 = v2;
        VSK_STATE()->m_wait_for = VSK_WAIT_FOR_INPORT;

        return vsk_ast(INSN_DONT_GO_NEXT);
    }

    return nullptr;
}

// INSN_FOR (FOR) @implemented
static VskAstPtr VSKAPI vsk_FOR(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 4, 4))
        return nullptr;

    auto it = VSK_IMPL()->m_loop_map.find(VSK_IMPL()->m_control_path);
    if (it == VSK_IMPL()->m_loop_map.end())
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    auto& loop_info = it->second;
    assert(loop_info.m_type == VSK_LOOP_TYPE_FOR);
    assert(loop_info.m_paths.size() == 2);

    if (!vsk_var_assign(args[0], args[1]))
        return nullptr;

    VskDouble v1, v2, v3 = 1;
    if (vsk_dbl(v1, args[1]) &&
        vsk_dbl(v2, args[2]) &&
        (!args[3] || vsk_dbl(v3, args[3])))
    {
        VskDouble steps = 0;
        if (v3 > 0)
        {
            if (v1 > v2)
            {
                VSK_IMPL()->m_control_path = loop_info.m_paths[1];
                return nullptr;
            }
            steps = (v2 - v1) / v3;
        }
        else if (v3 < 0)
        {
            if (v1 < v2)
            {
                VSK_IMPL()->m_control_path = loop_info.m_paths[1];
                return nullptr;
            }
            steps = (v1 - v2) / v3;
        }
        else
        {
            if (v1 == v2)
            {
                VSK_IMPL()->m_control_path = loop_info.m_paths[1];
                return nullptr;
            }
            steps = 0;
        }

        if (steps > 0)
        {
            auto next_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
            if (loop_info.m_paths[1] == next_path)
            {
                VSK_IMPL()->m_sleep_start = vsk_get_tick_count();
                VSK_IMPL()->m_sleep_amount = VskLong(steps / 2);
                VSK_IMPL()->m_after_sleep_path = vsk_next_control_path(next_path);
                VSK_STATE()->m_wait_for = VSK_WAIT_FOR_SLEEP;
                return vsk_ast(INSN_DONT_GO_NEXT);
            }
        }
    }

    return nullptr;
}

// INSN_NEXT (NEXT) @implemented
static VskAstPtr VSKAPI vsk_NEXT(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 64))
        return nullptr;

    auto it = VSK_IMPL()->m_loop_map.find(VSK_IMPL()->m_control_path);
    if (it == VSK_IMPL()->m_loop_map.end())
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    auto& loop_info = it->second;
    assert(loop_info.m_type == VSK_LOOP_TYPE_NEXT);
    assert(loop_info.m_paths.size() >= 2);

    for (size_t i = 0; i < loop_info.m_paths.size() - 1; ++i)
    {
        auto& expr0 = loop_info.m_exprs[4*i + 0];
        auto& expr2 = loop_info.m_exprs[4*i + 2];
        auto& expr3 = loop_info.m_exprs[4*i + 3];

        VskDouble v3 = 1;
        if (expr3 && !vsk_dbl(v3, expr3))
            return nullptr;

        if (!vsk_var_assign(expr0, vsk_ast(INSN_ADD, { expr0, vsk_ast_dbl(v3) })))
            return nullptr;

        VskDouble v0, v2;
        if (vsk_dbl(v0, expr0) && vsk_dbl(v2, expr2))
        {
            if (v3 > 0)
            {
                if (v0 <= v2)
                {
                    VSK_IMPL()->m_control_path = loop_info.m_paths[1 + i];
                    return nullptr;
                }
            }
            else if (v3 < 0)
            {
                if (v0 >= v2)
                {
                    VSK_IMPL()->m_control_path = loop_info.m_paths[1 + i];
                    return nullptr;
                }
            }
        }
    }

    return nullptr;
}

// INSN_WHILE (WHILE) @implemented
static VskAstPtr VSKAPI vsk_WHILE(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 1, 1))
        return nullptr;

    auto it = VSK_IMPL()->m_loop_map.find(VSK_IMPL()->m_control_path);
    if (it == VSK_IMPL()->m_loop_map.end())
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);

    auto& loop_info = it->second;
    assert(loop_info.m_type == VSK_LOOP_TYPE_WHILE);
    assert(loop_info.m_paths.size() == 2);

    VskDouble v0;
    if (vsk_dbl(v0, args[0]))
    {
        if (v0 == 0)
        {
            VSK_IMPL()->m_control_path = loop_info.m_paths[1];
        }
    }

    return nullptr;
}

bool vsk_child(const char *str);

// INSN_CHILD (CHILD)
static VskAstPtr VSKAPI vsk_CHILD(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 1))
        return nullptr;

    VskString v0;
    if (!vsk_arg(args, 0) || vsk_str(v0, args[0]))
    {
        if (!vsk_child(v0.c_str()))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, nullptr);
    }

    return nullptr;
}

// INSN_WEND (WEND) @implemented
static VskAstPtr VSKAPI vsk_WEND(VskAstPtr self, const VskAstList& args)
{
    if (!vsk_arity_in_range(args, 0, 0))
        return nullptr;

    auto it = VSK_IMPL()->m_loop_map.find(VSK_IMPL()->m_control_path);
    if (it == VSK_IMPL()->m_loop_map.end())
        VSK_ERROR_AND_RETURN(VSK_ERR_BAD_TYPE, nullptr);

    auto& loop_info = it->second;
    assert(loop_info.m_type == VSK_LOOP_TYPE_WEND);
    assert(loop_info.m_paths.size() == 2);

    VskDouble v0;
    if (vsk_dbl(v0, loop_info.m_exprs[0]))
    {
        if (v0 != 0)
        {
            VSK_IMPL()->m_control_path = loop_info.m_paths[1];
        }
    }

    return nullptr;
}

//////////////////////////////////////////////////////////////////////////////

VskMachineImpl::VskMachineImpl()
{
    init();
}

void VskMachineImpl::init()
{
    m_insn_to_fn.clear();
    m_stmt_set.clear();

#define DEFINE_INSN(id, fn, is_stmt) do { \
    m_insn_to_fn[id] = fn; \
    if (is_stmt) m_stmt_set.insert(id); \
} while (0);
#include "insn.h"
#undef DEFINE_INSN
}

VskMachineImpl::~VskMachineImpl()
{
}

std::shared_ptr<VskMachineImpl> vsk_create_machine_impl(void)
{
    return std::make_shared<VskMachineImpl>();
}

//////////////////////////////////////////////////////////////////////////////

void vsk_screen_tests_color(void)
{
    int screen_mode = 0; // カラーモード

    // 描画ページのテスト
    for (int i = 0; i <= 3; ++i)
    {
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(i), vsk_ast_int(1) });
        assert(VSK_STATE()->m_active_page == i);
    }

    // 表示ページのテスト
    vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(0) });
    assert(VSK_STATE()->m_active_page == 0);
    assert(VSK_STATE()->m_display_pages_flags == 0);
    vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(1) });
    assert(VSK_STATE()->m_active_page == 0);
    assert(VSK_STATE()->m_display_pages_flags == (1 << 0));
    vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(2) });
    assert(VSK_STATE()->m_active_page == 0);
    assert(VSK_STATE()->m_display_pages_flags == (1 << 1));
    if (vsk_machine->is_9801_mode() && VSK_STATE()->m_palette_mode == VSK_PAL_MODE_16_COLORS_SUPER)
    {
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(17) });
        assert(VSK_STATE()->m_active_page == 0);
        assert(VSK_STATE()->m_display_pages_flags == (1 << 2));
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(18) });
        assert(VSK_STATE()->m_active_page == 0);
        assert(VSK_STATE()->m_display_pages_flags == (1 << 3));
    }

    if (vsk_machine->is_9801_mode())
    {
        screen_mode = 3; // 高解像カラーモード

        // 描画ページのテスト
        for (int i = 0; i <= 1; ++i)
        {
            vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(i), vsk_ast_int(1) });
            assert(VSK_STATE()->m_active_page == i);
            assert(VSK_STATE()->m_display_pages_flags == 1);
        }

        // 表示ページのテスト
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(0) });
        assert(VSK_STATE()->m_active_page == 0);
        assert(VSK_STATE()->m_display_pages_flags == 0);
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(1) });
        assert(VSK_STATE()->m_active_page == 0);
        assert(VSK_STATE()->m_display_pages_flags == 1);
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(17) });
        assert(VSK_STATE()->m_active_page == 0);
        assert(VSK_STATE()->m_display_pages_flags == 2);
    }
}

void vsk_screen_tests_mono(void)
{
    int screen_mode = 1; // 白黒モード

    // 描画ページのテスト
    for (int i = 0; i <= 11; ++i)
    {
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(i), vsk_ast_int(1) });
        assert(VSK_STATE()->m_active_page == i);
        assert(VSK_STATE()->m_display_pages_flags == 1);
    }

    // 表示ページのテスト
    vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(0) });
    assert(VSK_STATE()->m_active_page == 0);
    assert(VSK_STATE()->m_display_pages_flags == 0);
    if (vsk_machine->is_8801_mode())
    {
        for (int i = 1; i <= 7; ++i)
        {
            vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(i) });
            assert(VSK_STATE()->m_active_page == 0);
            assert(VSK_STATE()->m_display_pages_flags == i);
        }
    }
    if (vsk_machine->is_9801_mode())
    {
        for (int i = 1; i <= 7; ++i)
        {
            vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(i) });
            assert(VSK_STATE()->m_active_page == 0);
            assert(VSK_STATE()->m_display_pages_flags == i);
        }
        for (int i = 9; i <= 15; ++i)
        {
            vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(i) });
            assert(VSK_STATE()->m_active_page == 0);
            assert(VSK_STATE()->m_display_pages_flags == (i - 8) << 3);
        }
        for (int i = 17; i <= 23; ++i)
        {
            vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(i) });
            assert(VSK_STATE()->m_active_page == 0);
            assert(VSK_STATE()->m_display_pages_flags == (i - 16) << 6);
        }
        for (int i = 25; i <= 31; ++i)
        {
            vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(0), vsk_ast_int(i) });
            assert(VSK_STATE()->m_active_page == 0);
            assert(VSK_STATE()->m_display_pages_flags == (i - 24) << 9);
        }
    }

    screen_mode = 2; // 高解像白黒モード

    // 描画ページのテスト
    for (int i = 0; i < 6; ++i)
    {
        vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(i), vsk_ast_int(1) });
        assert(VSK_STATE()->m_active_page == i);
        assert(VSK_STATE()->m_display_pages_flags == 1);
    }
}

// SCREENのテスト
void vsk_screen_tests(void)
{
#ifndef NDEBUG
    // SCREENのテスト
    auto screen_mode = VSK_STATE()->m_screen_mode;
    auto active_page = VSK_STATE()->m_active_page;
    auto display_page = VSK_STATE()->m_display_pages;
    auto text_mode = VSK_SETTINGS()->m_text_mode;
    vsk_screen_tests_color();
    vsk_screen_tests_mono();
    // 元に戻す
    vsk_SCREEN(nullptr, { vsk_ast_int(screen_mode), vsk_ast_int(1), vsk_ast_int(active_page), vsk_ast_int(display_page) });
    VSK_SETTINGS()->m_text_mode = text_mode;
#endif
}

// 単体テスト
void vsk_coreapi_tests(void)
{
#ifndef NDEBUG
    vsk_screen_tests();
#endif
}

// 入力テキストを分割する
void vsk_split_input_text(std::vector<VskString>& data, const VskString& text)
{
    bool in_quote = false;
    VskString str;
    for (auto ch : text)
    {
        if (ch == ',' && !in_quote)
        {
            data.push_back(str);
            str.clear();
            continue;
        }
        if (ch == '"')
        {
            in_quote = !in_quote;
            continue;
        }
        str += ch;
    }

    if (str.size())
    {
        data.push_back(str);
    }
}

// 左辺値への入力
bool vsk_complete_lvalue_input(VskAstPtr lvalue, const VskString& data, bool prompt)
{
    // 左辺値（lvalue）から名前と次元を取得
    VskString name;
    VskIndexList dimension;
    if (!vsk_dimension_from_lvalue(name, dimension, lvalue, +(VSK_STATE()->m_option_base == 1)))
        VSK_SYNTAX_ERROR_AND_RETURN(false);

    // 変数に代入する
    auto type = vsk_var_get_type(name);
    if (type == VSK_TYPE_STRING)
    {
        if (!vsk_var_assign(lvalue, vsk_ast_str(data)))
        {
            if (prompt)
            {
                vsk_print("?Redo from start\n");
                vsk_show_input_prompt();
            }
            else
            {
                vsk_var_assign(lvalue, vsk_ast_str(""));
            }
            return false;
        }
    }
    else
    {
        VSK_TYPE type;
        auto value = vsk_parse_number(data.c_str(), nullptr, type);
        if (!value || !value->is_number())
        {
            if (prompt)
            {
                vsk_print("?Redo from start\n");
                vsk_show_input_prompt();
            }
            else
            {
                vsk_var_assign(lvalue, vsk_ast_int(0));
            }
            return false;
        }
        vsk_var_assign(lvalue, value);
    }

    return true;
}

static bool vsk_enter_input_text_2(VskAstList& args, const VskString& text)
{
    VskString str = text;
    mstr_trim(str, " \t\r\n");

    if (str.empty() && args.size() == 1)
    {
        // 左辺値（lvalue）から名前と次元を取得
        VskString name;
        VskIndexList dimension;
        if (!vsk_dimension_from_lvalue(name, dimension, args[0], +(VSK_STATE()->m_option_base == 1)))
            VSK_ERROR_AND_RETURN(VSK_ERR_BAD_CALL, false);

        // 変数に代入する
        auto type = vsk_var_get_type(name);
        if (type == VSK_TYPE_STRING)
            vsk_var_assign(args[0], vsk_ast_str(""));
        else
            vsk_var_assign(args[0], vsk_ast_int(0));
        return true;
    }

    // 入力テキストを分割
    std::vector<VskString> data;
    vsk_split_input_text(data, str);

    // 個数が一致しない？
    if (data.size() != args.size())
    {
        vsk_print("?Redo from start\n");
        vsk_show_input_prompt();
        return false;
    }

    for (size_t iarg = 0; iarg < args.size(); ++iarg)
    {
        vsk_complete_lvalue_input(args[iarg], data[iarg], true);
    }

    return true;
}

// 入力テキストを入れる
void vsk_enter_input_text(const VskString& text)
{
    // コントロールパスを解決する
    auto node = vsk_resolve_index_list(VSK_IMPL()->m_control_path);

    // LINE INPUT文か？
    if (node->m_insn == INSN_LINE_INPUT)
    {
        // 変数に代入する
        vsk_var_assign(node->at(1), vsk_ast_str(text));
        // 次の文へ
        VSK_STATE()->m_wait_for = VSK_NO_WAIT;
        VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
        // IMEをOFFにする
        vsk_ime_on_off(false);
        return;
    }

    // LINE INPUT WAIT文か？
    if (node->m_insn == INSN_LINE_INPUT_WAIT)
    {
        // クリア
        VSK_STATE()->m_input_wait_start = 0;
        VSK_STATE()->m_input_wait_default_path.clear();

        // 変数に代入する
        vsk_var_assign(node->at(2), vsk_ast_str(text));

        // 次の文へ
        VSK_STATE()->m_wait_for = VSK_NO_WAIT;
        VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
        // IMEをOFFにする
        vsk_ime_on_off(false);
        return;
    }

    // RANDOMIZE文か？
    if (node->m_insn == INSN_RANDOMIZE)
    {
        VSK_TYPE type;
        auto value = vsk_parse_number(text.c_str(), nullptr, type);
        if (value && value->is_number())
        {
            auto number = value->to_int();
            if (!(-32768 <= number && number <= 32767))
            {
                vsk_error(VSK_ERR_OVERFLOW);
                return;
            }
            vsk_rand_init(number);
        }
        // 次の文へ
        VSK_STATE()->m_wait_for = VSK_NO_WAIT;
        VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
        // IMEをOFFにする
        vsk_ime_on_off(false);
        return;
    }

    // KINPUT文か？
    if (node->m_insn == INSN_KINPUT)
    {
        // 変数に代入する
        vsk_var_assign(node->at(0), vsk_ast_str(text));

        // 次の文へ
        VSK_STATE()->m_wait_for = VSK_NO_WAIT;
        VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
        // IMEをOFFにする
        vsk_ime_on_off(false);
        return;
    }

    // INPUT文か？
    if (node->m_insn == INSN_INPUT ||
        node->m_insn == INSN_INPUT_semicolon)
    {
        auto& args = node->at(1)->children();
        if (vsk_enter_input_text_2(args, text))
        {
            // 次の文へ
            VSK_STATE()->m_wait_for = VSK_NO_WAIT;
            VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
            // IMEをOFFにする
            vsk_ime_on_off(false);
            return;
        }
    }

    // INPUT WAIT文か？
    if (node->m_insn == INSN_INPUT_WAIT ||
        node->m_insn == INSN_INPUT_WAIT_semicolon)
    {
        auto& args = node->at(2)->children();
        if (vsk_enter_input_text_2(args, text))
        {
            // クリア
            VSK_STATE()->m_input_wait_start = 0;
            VSK_STATE()->m_input_wait_default_path.clear();
            // 次の文へ
            VSK_STATE()->m_wait_for = VSK_NO_WAIT;
            VSK_IMPL()->m_control_path = vsk_next_control_path(VSK_IMPL()->m_control_path);
            // IMEをOFFにする
            vsk_ime_on_off(false);
            return;
        }
    }

    // AUTO文か？
    if (node->m_insn == INSN_AUTO)
    {
        // 行を取得して行を格納
        VskString line;
        line = vsk_to_string(VSK_IMPL()->m_auto_line_number) + " " + text;
        vsk_direct_execute(line);
        // 増分だけ行番号を加算
        VSK_IMPL()->m_auto_line_number += VSK_IMPL()->m_auto_step;
        // すでに存在する行番号のときは行番号プロンプトにアスタリスク(*)を出力
        auto number = VSK_IMPL()->m_auto_line_number;
        if (vsk_get_next_line_text(number, 0).size())
            VSK_STATE()->m_input_prompt = vsk_to_string(number) + "*";
        else
            VSK_STATE()->m_input_prompt = vsk_to_string(number) + " ";
        // プロンプトを表示
        vsk_show_input_prompt();
        // IMEをOFFにする
        vsk_ime_on_off(false);
        return;
    }
}

// 入力プロンプトを表示する
void vsk_show_input_prompt(void)
{
    vsk_machine->set_line_text(VSK_STATE()->m_caret_y, VSK_STATE()->m_input_prompt);
    vsk_machine->set_line_column(VSK_STATE()->m_input_prompt.size());
}
