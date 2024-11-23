#include "draw.h"
#include "encoding.h"
#include "coreapi.h"

// 文字列をパースして描画項目にする
bool vsk_get_draw_items_from_string(std::vector<VskDrawItem>& items, const VskString& expr)
{
    items.clear();

    int status = 0;
    VskDrawItem item;
    VskString param;

    for (size_t i = 0; i < expr.size(); ++i) {
        mdbg_traceA("vsk_get_draw_items_from_string: '%s'\n", expr.substr(0, i).c_str());
        char ch = vsk_toupper(expr[i]);
        if (ch == ';') // セミコロン
            continue;
        switch (status) {
        case 0: // 初期状態
            switch (ch) { // 文字に応じて状態とサブコマンドを設定
            case ' ': case '\t':
                // 空白は読み飛ばす
                continue;

            case 'B': // BLANK
                // 修飾子"B"を指定した直後は、描画を行わず、LPのみを更新する
                item.m_B = true;
                break;
            case 'N': // No transition
                // 修飾子"N"を指定した直後は、描画実行後、LPを(0,0)にする
                item.m_N = true;
                break;

            case 'A': case 'C': case 'D': case 'E': case 'F': case 'G': case 'H': case 'L':
            case 'P': case 'R': case 'S': case 'U': case 'X': case 'Y': case 'Z':
                // パラメータ1個のサブコマンド
                item.m_subcommand = ch;
                status = 1;
                break;

            case 'M': case 'Q': case 'T': case 'W':
                // パラメータ2個のサブコマンド
                item.m_subcommand = ch;
                status = 2;
                break;

            default:
                assert(0);
                return false; // 失敗
            }
            break;

        case 1: case 2: // 1個か2個のパラメータがある
            param.clear();

            // 空白をスキップ
            while (i + 1 < expr.size() && vsk_isblank(expr[i]))
                ++i;
            // カンマをスキップ
            if (i + 1 < expr.size() && expr[i] == ',')
                ++i;

            ch = expr[i];
            if (ch == '=' || ch == '&') { // 変数か？n進数か？
                for (;;) {
                    ch = expr[++i];
                    if (ch == ';' || ch == ',' || ch == 0) // 終端？
                        break; 
                    if (!vsk_isblank(ch))
                        param += ch;
                }
                if (ch != 0)
                    --i;
            } else if (vsk_isdigit(ch) || ch == '-' || ch == '+' || ch == '.') { // 数値？
                do {
                    if (!vsk_isblank(ch)) {
                        param.push_back(ch);
                    }
                    ch = expr[++i];
                } while (vsk_isdigit(ch) || ch == '-' || ch == '+' || ch == '.' || vsk_isblank(ch));
                if (ch != ',') {
                    --i;
                }
            } else {
                mdbg_traceA("vsk_get_draw_items_from_string: '%c'\n", ch);
                assert(0);
                return false; // 失敗
            }

            // Xサブコマンド
            if (item.m_subcommand == 'X') {
                mdbg_traceA("vsk_eval_text: '%s'\n", param.c_str());
                auto ast = vsk_eval_text(param);
                if (!ast || !ast->is_str()) {
                    assert(0);
                    return false;
                }
                std::vector<VskDrawItem> children;
                if (!vsk_get_draw_items_from_string(children, ast->m_str)) {
                    assert(0);
                    return false;
                }
                items.insert(items.end(), children.begin(), children.end());
                status = 0;
                continue;
            }

            // パラメータを追加
            mdbg_traceA("vsk_get_draw_items_from_string: '%s'\n", param.c_str());
            item.m_params.emplace_back(param);

            // 初期状態になったら項目を追加
            if (--status == 0) {
                mdbg_traceA("vsk_get_draw_items_from_string: %c: new item\n", item.m_subcommand);
                items.push_back(item);
                item.reset();
            }

            // 空白をスキップ
            while (i + 1 < expr.size() && vsk_isblank(expr[i]))
                ++i;
            break;

        default:
            assert(0);
            return false;
        }
    }

    return true;
} // vsk_get_draw_items_from_string

void VskDrawEngine::reset()
{
    m_draw_items.clear();
    m_draw_coord_system     = 0;
    m_draw_color            = -1;
    m_draw_fill_color       = -1;
    m_draw_scale            = 1;
    m_draw_line_style       = 0xFFFF;
    m_draw_tile             = "";
    m_last_point_in_screen  = { 0, 0 };
}

// 描画位置を移動する
VskPointS VskDrawEngine::map_draw_delta(VskPointS pt, VskPointS delta)
{
    // NOTE: DRAWの座標系は、ワールド座標系とは違って、独立している。
    switch (m_draw_coord_system) {
    case 0:
        pt.m_x += delta.m_x * m_draw_scale;
        pt.m_y += delta.m_y * m_draw_scale;
        break;
    case 1:
        pt.m_x += delta.m_y * m_draw_scale;
        pt.m_y -= delta.m_x * m_draw_scale;
        break;
    case 2:
        pt.m_x -= delta.m_x * m_draw_scale;
        pt.m_y -= delta.m_y * m_draw_scale;
        break;
    case 3:
        pt.m_x -= delta.m_y * m_draw_scale;
        pt.m_y += delta.m_x * m_draw_scale;
        break;
    }
    return pt;
}

VskAstPtr vsk_get_draw_param(const VskDrawItem& item, size_t index)
{
    if (index >= item.m_params.size() || item.m_params[index].empty())
        return nullptr;
    return vsk_eval_text(item.m_params[index]);
} // vsk_get_play_param

#define PT2INTS(pt) vsk_round((pt).m_x), vsk_round((pt).m_y)

bool VskDrawEngine::draw_item(const VskDrawItem& item)
{
    if (item.m_B && item.m_N) {
        m_last_point_in_screen = { 0, 0 };
        return true;
    }

    // 初期状態では、描画に使われる色はCOLORで指定された前景色となる
    int color = (m_draw_color == -1) ? VSK_STATE()->m_fore_color : m_draw_color;
    int fill_color = (m_draw_fill_color == -1) ? VSK_STATE()->m_fore_color : m_draw_fill_color;

    switch (item.m_subcommand) {
    case 'A': // 座標系(Axis)
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto i0 = ast->to_int();
            if (0 <= i0 && i0 < 4) {
                m_draw_coord_system = i0;
                return true;
            }
        }
        break;
    case 'C': // パレット番号を指定
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto i0 = ast->to_int();
            if (vsk_machine->is_valid_color(i0)) {
                m_draw_color = i0;
                return true;
            }
        }
        break;
    case 'D': // 下へ (Down)
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto d0 = ast->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { 0, d0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'E': // 右上へ
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto d0 = ast->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { d0, -d0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'F': // 左上へ
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto d0 = ast->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { -d0, -d0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'G': // 左下へ
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto d0 = ast->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { -d0, d0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'H': // 右下へ
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto d0 = ast->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { d0, d0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'L': // 左へ (Left)
        if (auto ast = vsk_get_draw_param(item, 0)) {
            auto d0 = ast->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { -d0, 0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'M': // ワールド座標(x, y)まで直線を描画 (Move)
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            if (auto ast1 = vsk_get_draw_param(item, 1)) {
                VskPointS pt0 = m_last_point_in_screen;
                VskPointS pt1 = { ast0->to_sng(), ast1->to_sng() };
                auto pt = vsk_machine->world_to_view(pt1);
                if (!item.m_B) {
                    vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt), color, m_draw_line_style);
                }
                update_LP(item, pt1);
                return true;
            }
        }
        break;
    case 'P': // パレット番号またはタイル文字列で塗りつぶし (Paint)
        {
            VskInt i0 = m_draw_color;
            if (auto ast = vsk_get_draw_param(item, 0)) { 
                i0 = ast->to_int();
            }
            if (vsk_machine->is_valid_color(i0)) {
                VskPointS pt0 = m_last_point_in_screen;
                vsk_machine->flood_fill(PT2INTS(pt0), color, i0, m_draw_tile);
                return true;
            }
        }
        break;
    case 'Q': // 長方形
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            if (auto ast1 = vsk_get_draw_param(item, 1)) {
                VskPointS pt0 = m_last_point_in_screen;
                VskPointS pt1 = map_draw_delta(pt0, { ast0->to_sng(), ast1->to_sng() });
                if (!item.m_B) {
                    vsk_machine->draw_box(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
                }
                update_LP(item, pt1);
                return true;
            }
        }
        break;
    case 'R': // 右へ(Right)
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            auto d0 = ast0->to_sng();
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { d0, 0 });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'S': // スケール(Scale)
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            auto d0 = ast0->to_sng();
            if (d0 < 0) {
                assert(0);
                return false; // 負の時はエラー
            }
            m_draw_scale = d0;
            return true;
        }
        break;
    case 'T': // 塗りつぶした長方形
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            if (auto ast1 = vsk_get_draw_param(item, 1)) {
                VskPointS pt0 = m_last_point_in_screen;
                VskPointS pt1 = map_draw_delta(pt0, { ast0->to_sng(), ast1->to_sng() });
                if (!item.m_B) {
                    vsk_machine->fill_box(PT2INTS(pt0), PT2INTS(pt1), fill_color, m_draw_tile);
                }
                update_LP(item, pt1);
                return true;
            }
        }
        break;
    case 'U': // 上へ(UP)
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            VskPointS pt0 = m_last_point_in_screen;
            VskPointS pt1 = map_draw_delta(pt0, { 0, -ast0->to_sng() });
            if (!item.m_B) {
                vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
            }
            update_LP(item, pt1);
            return true;
        }
        break;
    case 'W': // (x * scale, y * scale) まで直線を描画
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            if (auto ast1 = vsk_get_draw_param(item, 1)) {
                VskPointS pt0 = m_last_point_in_screen;
                VskPointS pt1 = map_draw_delta(pt0, { ast0->to_sng(), ast1->to_sng() });
                if (!item.m_B) {
                    vsk_machine->draw_line(PT2INTS(pt0), PT2INTS(pt1), color, m_draw_line_style);
                }
                update_LP(item, pt1);
                return true;
            }
        }
        break;
    case 'X':
        // すでに vsk_get_draw_items_from_string 関数で"X"サブコマンドを処理したはず
        assert(0);
        break;
    case 'Y': // ラインスタイル
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            VskWord w0;
            if (vsk_wrd(w0, ast0)) {
                m_draw_line_style = w0;
                return true;
            }
        }
        break;
    case 'Z': // 塗りつぶしのパレット番号またはタイル文字列
        if (auto ast0 = vsk_get_draw_param(item, 0)) {
            if (ast0->is_number()) {
                auto i0 = ast0->to_int();
                if (vsk_machine->is_valid_color(i0)) {
                    m_draw_fill_color = i0;
                    return true;
                }
            } else if (ast0->is_str()) {
                m_draw_tile = ast0->to_str();
                return true;
            }
        }
        break;
    default:
        assert(0);
        break;
    }

    mdbg_traceA("item.m_subcommand: %c\n", item.m_subcommand);
    assert(0);
    return false;
} // VskDrawEngine::draw_item

void VskDrawEngine::update_LP(const VskDrawItem& item, VskPointS pt1)
{
    if (item.m_N)
        m_last_point_in_screen = { 0, 0 };
    else
        m_last_point_in_screen = pt1;
}
