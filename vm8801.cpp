// 8801 Virtual Machine
#ifdef ENABLE_PC8801

#include "VeySicK.h"            // VeySicK
#include "draw_algorithm.h"     // 描画アルゴリズム
#include "turtle.h"             // タートル
#include <array>                // std::array
#include <iterator>             // std::begin, std::end

////////////////////////////////////////////////////////////////////////////////////
// 8801 machine

// NOTE: VeySicKの8801のVRAMはSJISに拡張している。SJISモードの場合はVeySicKの8801の場合でも漢字が表示できる
// TODO: まだVRAMが8801と非互換じゃないか！ 直せよ！

// VRAM基本情報
#define VSK_8801_VRAM_START_ADDR        0xC000
#define VSK_8801_VRAM_END_ADDR          0xFFFF
#define VSK_8801_VRAM_SIZE              (VSK_8801_VRAM_END_ADDR - VSK_8801_VRAM_START_ADDR + 1)
#define VSK_8801_TEXT_VRAM_ADDR         0xF3C8
#define VSK_8801_TEXT_VRAM_OFFSET       (VSK_8801_TEXT_VRAM_ADDR - VSK_8801_VRAM_START_ADDR)
#define VSK_8801_TEXT_VRAM_TEXT_WIDTH   80
#define VSK_8801_TEXT_VRAM_ATTR_WIDTH   40
#define VSK_8801_TEXT_VRAM_PITCH        (VSK_8801_TEXT_VRAM_TEXT_WIDTH + VSK_8801_TEXT_VRAM_ATTR_WIDTH)
#define VSK_8801_TEXT_VRAM_MAX_HEIGHT   25
#define VSK_8801_GRAPH_VRAM_PLANE_PITCH (640 / CHAR_BIT)
#define VSK_8801_VRAM_BANK_0            0 // Main memory (with text)
#define VSK_8801_VRAM_BANK_1            1 // Plane 1 (Blue)
#define VSK_8801_VRAM_BANK_2            2 // Plane 2 (Red)
#define VSK_8801_VRAM_BANK_3            3 // Plane 3 (Green)
#define VSK_8801_VRAM_BANK_MAX          4

////////////////////////////////////////////////////////////////////////////////////
// 8801 テキスト VRAM の文字属性について

// 参考資料：『テキストおよびグラフィック VRAM についての覚え書き』
// http://mydocuments.g2.xrea.com/html/p8/vraminfo.html

// 文字属性値は、「白黒モードの装飾指定」「カラーモードの色指定」「カラーモードの装飾指定」の3種類ある。

// 「白黒モードの装飾指定」と「カラーモードの装飾指定」で共通
#define VSK_8801_ATTR_SECRET            (uint8_t)(1 << 0)        // シークレット文字属性(装飾指定)
#define VSK_8801_ATTR_BLINK             (uint8_t)(1 << 1)        // ブリンク文字属性(装飾指定)
#define VSK_8801_ATTR_REVERSE           (uint8_t)(1 << 2)        // リバース文字属性(装飾指定)
#define VSK_8801_ATTR_GET_EFFECT(attr)  (uint8_t)((attr) & 0x07) // 上記３ビットの組み合わせ(装飾指定)
#define VSK_8801_ATTR_UPPERLINE         (uint8_t)(1 << 4)        // 上線文字属性(白黒モード ／ カラーモードの装飾指定)
#define VSK_8801_ATTR_UNDERLINE         (uint8_t)(1 << 5)        // 下線文字属性(白黒モード ／ カラーモードの装飾指定)

// カラーモード専用。カラーモードでこれがONなら色指定、OFFなら装飾指定
#define VSK_8801_ATTR_COLOR             (uint8_t)(1 << 3)   // カラー指定文字属性

// 「カラーモードの色指定」専用
#define VSK_8801_ATTR_COLOR_BLUE        (uint8_t)(1 << 5)   // ブルー文字属性(カラーモードの色指定)
#define VSK_8801_ATTR_COLOR_RED         (uint8_t)(1 << 6)   // レッド文字属性(カラーモードの色指定)
#define VSK_8801_ATTR_COLOR_GREEN       (uint8_t)(1 << 7)   // グリーン文字属性(カラーモードの色指定)

// セミグラのビットは白黒とカラーで異なる
#define VSK_8801_ATTR_COLOR_SEMIGRA     (uint8_t)(1 << 4)   // セミグラ文字属性(カラーモードの色指定)
#define VSK_8801_ATTR_MONO_SEMIGRA      (uint8_t)(1 << 7)   // セミグラ文字属性(「白黒モード」専用)

// 色の取得または設定
#define VSK_8801_ATTR_GET_COLOR(attr)   (uint8_t)(((attr) >> 5) & 0x07)
#define VSK_8801_ATTR_SET_COLOR(color)  (uint8_t)(VSK_8801_ATTR_COLOR | (((color) & 0x07) << 5))

#define VSK_8801_INVALID_X                  0x80    // 無効な桁位置指定
#define VSK_8801_TEXT_MAX_X                 80      // テキスト画面の最大幅
#define VSK_8801_ATTR_PAIR_MAX              20

// 桁位置と文字属性値のペア
struct alignas(1) VSK_8801_ATTR_PAIR
{
    uint8_t m_x;              // 桁位置、ゼロベース。無効なとき VSK_8801_INVALID_X になる
    uint8_t m_attr_value;     // 属性値

    void reset(bool color_mode)
    {
        m_x = VSK_8801_INVALID_X;
        if (color_mode)
        {
            m_attr_value = VSK_8801_ATTR_SET_COLOR(7);
            assert(m_attr_value == 0xE8);
        }
        else
        {
            m_attr_value = 0;
        }
    }
};

// 属性展開のヘルパー関数
void vsk_8801_expand_attr_0(VskLogAttr& log_attr, uint8_t attr_value, bool color_mode)
{
    if (color_mode) // カラーモード？
    {
        if (attr_value & VSK_8801_ATTR_COLOR) // 色指定？
        {
            log_attr.m_palette = VSK_8801_ATTR_GET_COLOR(attr_value);
            log_attr.m_semigra = !!(attr_value & VSK_8801_ATTR_COLOR_SEMIGRA);
        }
        else // 修飾指定？
        {
            log_attr.m_effect = VSK_8801_ATTR_GET_EFFECT(attr_value);
            log_attr.m_upperline = !!(attr_value & VSK_8801_ATTR_UPPERLINE);
            log_attr.m_underline = !!(attr_value & VSK_8801_ATTR_UNDERLINE);
        }
    }
    else // 白黒モード？
    {
        log_attr.m_palette = 7;
        log_attr.m_effect = VSK_8801_ATTR_GET_EFFECT(attr_value);
        log_attr.m_upperline = !!(attr_value & VSK_8801_ATTR_UPPERLINE);
        log_attr.m_underline = !!(attr_value & VSK_8801_ATTR_UNDERLINE);
    }
}

void vsk_reset_attr_area(VskByte *attr_area)
{
    for (int x = 0; x < VSK_8801_ATTR_PAIR_MAX / 2; x += 2)
    {
        attr_area[x + 0] = 0x80;
        attr_area[x + 1] = 0xE8;
    }
}

// 属性データを展開： log_attrs <-- attr_area
void
vsk_8801_expand_attrs_of_width_40(
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X>& log_attrs, // 論理属性値の配列
    VskByte *attr_area,                                     // 属性ペアの配列
    bool color_mode)                                        // カラーモードか？
{
    auto *pairs = reinterpret_cast<VSK_8801_ATTR_PAIR *>(attr_area);

    // X座標でソート
    std::sort(&pairs[0], &pairs[VSK_8801_ATTR_PAIR_MAX], [&](const VSK_8801_ATTR_PAIR& x, const VSK_8801_ATTR_PAIR& y) {
        return x.m_x < y.m_x;
    });

    // 論理属性を初期化
    VskLogAttr old_attr;
    old_attr.reset();
    vsk_8801_expand_attr_0(old_attr, pairs[0].m_attr_value, color_mode);

    // ペアをlog_attrsに展開する
    int old_x = 0;
    for (size_t i = 0;; )
    {
        auto& pair = pairs[i];

        if (pair.m_x >= 40)
            break;

        int next_x = (pair.m_x + 1) / 2;
        for (int x0 = old_x; x0 < next_x; ++x0)
        {
            log_attrs.at(x0) = old_attr;
        }

        ++i;
        if (i >= VSK_8801_ATTR_PAIR_MAX)
            break;

        vsk_8801_expand_attr_0(old_attr, pairs[i].m_attr_value, color_mode);
        old_x = next_x;
    }

    // 残りを埋める
    for (int x0 = old_x; x0 < 40; ++x0)
    {
        log_attrs.at(x0) = old_attr;
    }
}

// 属性データを展開： log_attrs <-- attr_area
void
vsk_8801_expand_attrs_of_width_80(
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X>& log_attrs, // 論理属性値の配列
    VskByte *attr_area,                                     // 属性ペアの配列
    bool color_mode)                                        // カラーモードか？
{
    auto *pairs = reinterpret_cast<VSK_8801_ATTR_PAIR *>(attr_area);

    // 最初はゼロ固定
    pairs[0].m_x = 0;

    // X座標でソート
    std::sort(&pairs[0], &pairs[VSK_8801_ATTR_PAIR_MAX], [&](const VSK_8801_ATTR_PAIR& x, const VSK_8801_ATTR_PAIR& y) {
        return x.m_x < y.m_x;
    });

    // 論理属性を初期化
    VskLogAttr old_attr;
    old_attr.reset();

    // ペアをlog_attrsに展開する
    int old_x = 0;
    for (size_t i = 0; i < VSK_8801_ATTR_PAIR_MAX; ++i)
    {
        auto& pair = pairs[i];

        if (pair.m_x >= 80)
            break;

        for (int x0 = old_x; x0 < pair.m_x; ++x0)
        {
            log_attrs.at(x0) = old_attr;
        }

        vsk_8801_expand_attr_0(old_attr, pair.m_attr_value, color_mode);
        old_x = pair.m_x;
    }

    // 残りを埋める
    for (int x0 = old_x; x0 < 80; ++x0)
    {
        log_attrs.at(x0) = old_attr;
    }
}

// 属性データを展開： log_attrs <-- attr_area
inline void
vsk_8801_expand_attrs(
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X>& log_attrs, // 論理属性値の配列
    VskByte *attr_area,                                     // 属性ペアの配列
    bool color_mode)                                        // カラーモードか？
{
    if (VSK_STATE()->m_text_wider)
        vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area, color_mode);
    else
        vsk_8801_expand_attrs_of_width_80(log_attrs, attr_area, color_mode);
}

// 属性データを格納： log_attrs --> attr_area
void
vsk_8801_store_attrs_of_width_80(
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X>& log_attrs, // 論理属性値の配列
    VskByte *attr_area,                                     // 属性ペアの配列
    bool color_mode)                                        // カラーモードか？
{
    auto *pairs = reinterpret_cast<VSK_8801_ATTR_PAIR *>(attr_area);

    for (size_t i = 0; i < VSK_8801_ATTR_PAIR_MAX; ++i)
    {
        auto& pair = pairs[i];
        pair.reset(color_mode);
    }

    // 論理属性値を初期化
    VskLogAttr old_attr;
    old_attr.reset();

    int iPair = 0;
    bool first = true;
    for (int x = 0; x < 80; ++x)
    {
        auto& log_attr = log_attrs.at(x);
        auto& pair_x = pairs[iPair].m_x;
        auto& attr_value = pairs[iPair].m_attr_value;
        if (color_mode) // カラーモードか？
        {
            // 色かセミグラの属性が変化した？
            if (first ||
                log_attr.m_palette != old_attr.m_palette ||
                log_attr.m_semigra != old_attr.m_semigra)
            {
                first = false;
                // 属性を格納
                pair_x = x;
                attr_value = VSK_8801_ATTR_SET_COLOR(log_attr.m_palette);
                if (log_attr.m_semigra)
                    attr_value |= VSK_8801_ATTR_COLOR_SEMIGRA;
                // 古い属性として覚えておく
                old_attr.m_palette = log_attr.m_palette;
                old_attr.m_semigra = log_attr.m_semigra;
                // 次のペアへ
                if (++iPair >= VSK_8801_ATTR_PAIR_MAX)
                    break;
            }
            if (log_attr.m_effect != old_attr.m_effect ||
                log_attr.m_upperline != old_attr.m_upperline ||
                log_attr.m_underline != old_attr.m_underline)
            {
                // 属性を格納
                pair_x = x;
                attr_value = log_attr.m_effect;
                if (log_attr.m_upperline)
                    attr_value |= VSK_8801_ATTR_UPPERLINE;
                if (log_attr.m_underline)
                    attr_value |= VSK_8801_ATTR_UNDERLINE;
                // 古い属性として覚えておく
                old_attr.m_effect = log_attr.m_effect;
                old_attr.m_upperline = log_attr.m_upperline;
                old_attr.m_underline = log_attr.m_underline;
                // 次のペアへ
                if (++iPair >= VSK_8801_ATTR_PAIR_MAX)
                    break;
            }
        }
        else // 白黒モードか？
        {
            // 属性が変化した？
            if (first ||
                log_attr.m_effect != old_attr.m_effect ||
                log_attr.m_semigra != old_attr.m_semigra ||
                log_attr.m_upperline != old_attr.m_upperline ||
                log_attr.m_underline != old_attr.m_underline)
            {
                first = false;
                // 属性を格納
                pair_x = x;
                attr_value = log_attr.m_effect;
                if (log_attr.m_semigra)
                    attr_value |= VSK_8801_ATTR_MONO_SEMIGRA;
                if (log_attr.m_upperline)
                    attr_value |= VSK_8801_ATTR_UPPERLINE;
                if (log_attr.m_underline)
                    attr_value |= VSK_8801_ATTR_UNDERLINE;
                // 古い属性として覚えておく
                old_attr.m_effect = log_attr.m_effect;
                old_attr.m_semigra = log_attr.m_semigra;
                old_attr.m_upperline = log_attr.m_upperline;
                old_attr.m_underline = log_attr.m_underline;
                // 次のペアへ
                if (++iPair >= VSK_8801_ATTR_PAIR_MAX)
                    break;
            }
        }
    }
}

// 属性データを格納： log_attrs --> attr_area
void
vsk_8801_store_attrs_of_width_40(
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X>& log_attrs, // 論理属性値の配列
    VskByte* attr_area,                                     // 属性ペアの配列
    bool color_mode)                                        // カラーモードか？
{
    auto* pairs = reinterpret_cast<VSK_8801_ATTR_PAIR*>(attr_area);

    for (size_t i = 0; i < VSK_8801_ATTR_PAIR_MAX; ++i)
    {
        auto& pair = pairs[i];
        pair.reset(color_mode);
    }

    // 論理属性値を初期化
    VskLogAttr old_attr;
    old_attr.reset();

    int iPair = 0;
    bool first = true;
    for (int x = 0; x < 40; ++x)
    {
        auto& log_attr = log_attrs.at(x);
        auto& pair_x = pairs[iPair].m_x;
        auto& attr_value = pairs[iPair].m_attr_value;
        if (color_mode) // カラーモードか？
        {
            // 色かセミグラの属性が変化した？
            if (first ||
                log_attr.m_palette != old_attr.m_palette ||
                log_attr.m_semigra != old_attr.m_semigra)
            {
                first = false;
                // 属性を格納
                pair_x = x * 2 + 1;
                attr_value = VSK_8801_ATTR_SET_COLOR(log_attr.m_palette);
                if (log_attr.m_semigra)
                    attr_value |= VSK_8801_ATTR_COLOR_SEMIGRA;
                // 古い属性として覚えておく
                old_attr.m_palette = log_attr.m_palette;
                old_attr.m_semigra = log_attr.m_semigra;
                // 次のペアへ
                if (++iPair >= VSK_8801_ATTR_PAIR_MAX)
                    break;
            }
            if (log_attr.m_effect != old_attr.m_effect ||
                log_attr.m_upperline != old_attr.m_upperline ||
                log_attr.m_underline != old_attr.m_underline)
            {
                // 属性を格納
                pair_x = x * 2 + 1;
                attr_value = log_attr.m_effect;
                if (log_attr.m_upperline)
                    attr_value |= VSK_8801_ATTR_UPPERLINE;
                if (log_attr.m_underline)
                    attr_value |= VSK_8801_ATTR_UNDERLINE;
                // 古い属性として覚えておく
                old_attr.m_effect = log_attr.m_effect;
                old_attr.m_upperline = log_attr.m_upperline;
                old_attr.m_underline = log_attr.m_underline;
                // 次のペアへ
                if (++iPair >= VSK_8801_ATTR_PAIR_MAX)
                    break;
            }
        }
        else // 白黒モードか？
        {
            // 属性が変化した？
            if (first ||
                log_attr.m_effect != old_attr.m_effect ||
                log_attr.m_semigra != old_attr.m_semigra ||
                log_attr.m_upperline != old_attr.m_upperline ||
                log_attr.m_underline != old_attr.m_underline)
            {
                first = false;
                // 属性を格納
                pair_x = x * 2 + 1;
                attr_value = log_attr.m_effect;
                if (log_attr.m_semigra)
                    attr_value |= VSK_8801_ATTR_MONO_SEMIGRA;
                if (log_attr.m_upperline)
                    attr_value |= VSK_8801_ATTR_UPPERLINE;
                if (log_attr.m_underline)
                    attr_value |= VSK_8801_ATTR_UNDERLINE;
                // 古い属性として覚えておく
                old_attr.m_effect = log_attr.m_effect;
                old_attr.m_semigra = log_attr.m_semigra;
                old_attr.m_upperline = log_attr.m_upperline;
                old_attr.m_underline = log_attr.m_underline;
                // 次のペアへ
                if (++iPair >= VSK_8801_ATTR_PAIR_MAX)
                    break;
            }
        }
    }
}

// 属性データを格納： log_attrs --> pairs
void
vsk_8801_store_attrs(
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X>& log_attrs, // 論理属性値の配列
    VskByte* attr_area,                                     // 属性ペアの配列
    bool color_mode)                                        // カラーモードか？
{
    if (VSK_STATE()->m_text_wider)
        vsk_8801_store_attrs_of_width_40(log_attrs, attr_area, color_mode);
    else
        vsk_8801_store_attrs_of_width_80(log_attrs, attr_area, color_mode);
}

////////////////////////////////////////////////////////////////////////////////////

// 8801 VRAM のクラス。
struct Vsk8801VRAM : VskMemoryBlockBase
{
    // マシン状態
    VskMachineState *m_state;
    // 8801 VRAM の実データ
    VskByte m_8801_vram_area[VSK_8801_VRAM_BANK_MAX][VSK_8801_VRAM_SIZE] = { { 0 } };

    // コンストラクタ
    Vsk8801VRAM(VskMachineState *state) : m_state(state)
    {
    }

    // アドレスがメモリーブロックに含まれているか?
    bool includes(VskAddr addr, VskMemSize size) const override
    {
        return VSK_8801_VRAM_START_ADDR <= addr && addr + size <= VSK_8801_VRAM_START_ADDR + VSK_8801_VRAM_SIZE;
    }

    // 1バイト読み込む
    bool read(VskByte *ptr, VskAddr addr) const override
    {
        if (!includes(addr, 1))
            return false;
        assert(0 <= m_state->m_vram_bank && m_state->m_vram_bank < 4);
        auto offset = addr - VSK_8801_VRAM_START_ADDR;
        *ptr = m_8801_vram_area[m_state->m_vram_bank][offset];
        return true;
    }

    // 1バイト書き込む
    bool write(const VskByte *ptr, VskAddr addr) override
    {
        if (!includes(addr, 1))
            return false;
        assert(0 <= m_state->m_vram_bank && m_state->m_vram_bank < 4);
        auto offset = addr - VSK_8801_VRAM_START_ADDR;
        m_8801_vram_area[m_state->m_vram_bank][offset] = *ptr;
        return true;
    }

    // 8801のページを取得
    VskByte *get_page(int screen_mode, int iPage)
    {
        switch (iPage)
        {
        case 0: return &m_8801_vram_area[VSK_8801_VRAM_BANK_1][0];
        case 1: return &m_8801_vram_area[VSK_8801_VRAM_BANK_2][0];
        case 2: return &m_8801_vram_area[VSK_8801_VRAM_BANK_3][0];
        }
        return nullptr;
    }
};

// 8801 フリーエリアのアドレスとサイズ
#define VSK_8801_FREE_AREA_START      0xA000
#define VSK_8801_FREE_AREA_END_MAX    0xE5FF
#define VSK_8801_FREE_AREA_SIZE       (VSK_8801_FREE_AREA_END_MAX - VSK_8801_FREE_AREA_START + 1)

// 8801 フリーエリア
struct Vsk8801FreeArea : VskSimpleMemoryBlock
{
    Vsk8801FreeArea() : VskSimpleMemoryBlock(VSK_8801_FREE_AREA_START, VSK_8801_FREE_AREA_SIZE)
    {
        std::memset(m_ptr, 0, m_size);
    }
};

// 8801のマシン
struct Vsk8801Machine : VskMachine
{
    Vsk32BppImage m_screen_image;                   // スクリーンイメージ
    std::shared_ptr<Vsk8801VRAM> m_vram;            // VRAM
    std::shared_ptr<Vsk8801FreeArea> m_free_area;   // フリーエリア

    // コンストラクタ
    Vsk8801Machine(VskMachineState *state, VskSettings *settings);

    // メモリーのクリア
    bool clear_memory(VskDword addr) override;
    // フリーエリアのサイズ
    VskDword get_free_size() override;
    // フリーエリアの最後のアドレス
    VskDword get_free_ubound() override;
    // 特殊なメモリー読み込み
    bool special_memory_read(VskByte *ptr, VskAddr addr) override;

    // パレットのリセット
    void reset_palette() override;
    // テキスト画面のリセット
    void reset_text() override;
    // グラフィック画面のリセット
    void reset_graphics() override;

    // テキスト画面をクリア
    void clear_text(int y0, int y1) override;
    using VskMachine::clear_text;

    // 下にスクロールする
    void scroll_down(int y0, int y1) override
    {
        for (int y = y0; y < y1; ++y)
        {
            std::memcpy(get_text_area(y), get_text_area(y + 1), VSK_8801_TEXT_VRAM_PITCH);
            line_link(y) = line_link(y + 1);
        }
        clear_text(y1, y1);
    }
    // 上にスクロールする
    void scroll_up(int y0, int y1) override
    {
        for (int y = y1; y > y0; --y)
        {
            std::memcpy(get_text_area(y), get_text_area(y - 1), VSK_8801_TEXT_VRAM_PITCH);
            line_link(y) = line_link(y - 1);
        }
        clear_text(y0, y0);
        line_link(y1) = 0;
    }

    // グラフィック画面をクリアする
    void clear_screen_image() override
    {
        m_screen_image.clear();
    }

    // テキストエリアを取得
    VskByte *get_text_area(int y)
    {
        assert(0 <= y && y < m_state->m_text_height);
        return const_cast<VskByte *>(const_cast<const Vsk8801Machine *>(this)->get_text_area(y));
    }
    const VskByte *get_text_area(int y) const
    {
        assert(0 <= y && y < m_state->m_text_height);
        auto offset = VSK_8801_TEXT_VRAM_OFFSET + y * VSK_8801_TEXT_VRAM_PITCH;
        assert(0 <= offset && offset < VSK_8801_VRAM_SIZE);
        return &m_vram->m_8801_vram_area[0][offset];
    }

    // ANK文字か？（さもなければSJISの全角文字）
    bool is_ank(int x, int y) const override
    {
#ifdef JAPAN
        auto lead = get_ank(x, y);
        if (!vsk_is_sjis_lead(lead) || !get_next_x_y(x, y, x, y))
            return true;
        auto trail = get_ank(x, y);
        return !vsk_is_sjis_trail(trail);
#else
        return true;
#endif
    }

    // 指定した位置のANK文字を取得
    VskByte get_ank(int x, int y) const override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);
        auto text_area = get_text_area(y);
        if (m_state->m_text_wider)
            return text_area[2 * x];
        else
            return text_area[x];
    }

    // 指定した位置にANK文字をセット
    void set_ank(int x, int y, VskByte ch) override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);
        auto text_area = get_text_area(y);
        if (m_state->m_text_wider)
            text_area[2 * x] = ch;
        else
            text_area[x] = ch;
    }

    // 指定した位置のJIS全角文字を取得
    VskWord get_jis(int x, int y) const override;
    // 指定した位置にJIS全角文字をセット
    void set_jis(int x, int y, VskWord jis) override;

    // 指定した位置に文字属性をセット
    void set_attr(int x, int y, const VskLogAttr& attr) override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);

        auto *attr_area = get_attr_area(y);
        std::array<VskLogAttr, VSK_8801_TEXT_MAX_X> log_attrs;
        vsk_8801_expand_attrs(log_attrs, attr_area, m_state->m_color_text);
        log_attrs[x] = attr;
        vsk_8801_store_attrs(log_attrs, attr_area, m_state->m_color_text);
    }

    // 指定した行の文字属性エリアを取得
    VskByte *get_attr_area(int y)
    {
        assert(0 <= y && y < m_state->m_text_height);
        return const_cast<VskByte *>(const_cast<const Vsk8801Machine *>(this)->get_attr_area(y));
    }
    const VskByte *get_attr_area(int y) const
    {
        assert(0 <= y && y < m_state->m_text_height);
        auto offset = VSK_8801_TEXT_VRAM_OFFSET + VSK_8801_TEXT_VRAM_TEXT_WIDTH + y * VSK_8801_TEXT_VRAM_PITCH;
        assert(0 <= offset && offset < VSK_8801_VRAM_SIZE);
        return &m_vram->m_8801_vram_area[0][offset];
    }

    // グラフィック画面を描画する
    void render_graphics()
    {
        if (!m_state->m_show_graphics)
            return;

        if (m_state->m_color_graphics)
            render_color_graphics();
        else
            render_mono_graphics();

        if (vsk_turtle_shown())
            vsk_turtle_draw_cursor(*get_screen_image());
    }

    // 白黒グラフィック画面を描画する
    void render_mono_graphics();
    // カラーグラフィック画面を描画する
    void render_color_graphics();

    // ファンクションキーをテキスト画面にセットする
    void render_function_keys();
    // ANK文字を描画する
    void render_ank(int x, int y, VskByte ch, const VskLogAttr& log_attr);
    // JIS全角文字を描画する
    void render_jis(int x, int y, int next_x, int next_y, VskWord jis, const VskLogAttr& log_attr);

    // テキスト画面を描画する
    void render_text();

    // 全体を描画する
    void render() override
    {
        clear_screen_image();
        render_graphics();
        render_text();
    }

    // 描画したスクリーンイメージを取得する
    Vsk32BppImage *get_screen_image() override
    {
        return &m_screen_image;
    }

    // テスト
    void do_unit_tests();

    // マシンを接続、または接続を切断する
    bool connect(bool do_connect) override
    {
        if (do_connect)
        {
            m_vram = std::make_shared<Vsk8801VRAM>(m_state);
            m_free_area = std::make_shared<Vsk8801FreeArea>();
            m_state->m_memory->add_block(m_vram.get());
            m_state->m_memory->add_block(m_free_area.get());
            VskMachine::connect(true);
            clear_text();
            do_unit_tests();
        }
        else
        {
            VskMachine::connect(false);
            m_state->m_memory->remove_block(m_free_area.get());
            m_state->m_memory->remove_block(m_vram.get());
            m_free_area = nullptr;
            m_vram = nullptr;
        }
        return true;
    }

    // ピクセルを取得するヘルパークラス
    struct ColorGetter : VskColorGetter
    {
        VskMachineState *m_state = nullptr;
        const VskRectI *m_viewport = nullptr;
        VskByte *m_planes[3] = { nullptr };
        int m_num_planes = 0;

        ColorGetter(Vsk8801Machine *machine, const VskRectI* viewport)
        {
            m_state = machine->m_state;
            m_viewport = viewport ? viewport : &m_state->m_viewport;
            m_num_planes = m_state->get_graphics_num_planes();
            for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
                m_planes[iPlane] = machine->m_vram->get_page(m_state->m_screen_mode, iPlane);
        }

        int operator()(int x, int y) override
        {
            if (!(m_viewport->inside(x, y)))
                return -1;

            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            int offset = (y * VSK_8801_GRAPH_VRAM_PLANE_PITCH) + (x / CHAR_BIT);
            int palette = 0;
            for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
            {
                if (m_planes[iPlane][offset] & (1 << ibit))
                    palette |= (1 << iPlane);
            }
            return palette;
        }
    };

    // ピクセルをセットするヘルパークラス
    struct ColorPutter : VskPixelPutter
    {
        VskMachineState *m_state = nullptr;
        const VskRectI *m_viewport = nullptr;
        VskByte *m_planes[3] = { nullptr };
        int m_num_planes = 0;
        VskByte m_palette = 7;

        void set_color(int palette) override
        {
            m_palette = palette;
        }

        ColorPutter(Vsk8801Machine *machine, int palette, const VskRectI *viewport)
        {
            m_state = machine->m_state;
            m_viewport = viewport ? viewport : &m_state->m_viewport;
            m_num_planes = m_state->get_graphics_num_planes();
            if (m_state->m_color_graphics)
            {
                for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
                    m_planes[iPlane] = machine->m_vram->get_page(m_state->m_screen_mode, iPlane);
            }
            else
            {
                m_planes[0] = machine->m_vram->get_page(m_state->m_screen_mode, m_state->m_active_page);
            }
            m_palette = VskByte(palette);
        }

        void operator()(int x, int y) override
        {
            if (!(m_viewport->inside(x, y)))
                return;

            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            int offset = (y * VSK_8801_GRAPH_VRAM_PLANE_PITCH) + (x / CHAR_BIT);
            if (m_state->m_color_graphics)
            {
                for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
                {
                    if (m_palette & (1 << iPlane))
                        m_planes[iPlane][offset] |= (1 << ibit);
                    else
                        m_planes[iPlane][offset] &= ~(1 << ibit);
                }
            }
            else
            {
                if (m_palette)
                    m_planes[0][offset] |= (1 << ibit);
                else
                    m_planes[0][offset] &= ~(1 << ibit);
            }
        }
    };

    // 色を取得するオブジェクトを作成する
    std::shared_ptr<VskColorGetter> get_color_getter(const VskRectI *viewport) override
    {
        return std::make_shared<ColorGetter>(this, viewport);
    }

    // 色をセットするオブジェクトを作成する
    std::shared_ptr<VskPixelPutter> get_color_putter(int palette, const VskRectI *viewport) override
    {
        return std::make_shared<ColorPutter>(this, palette, viewport);
    }

    // タイリングを行うヘルパークラス
    struct TilePutter : VskPixelPutter
    {
        VskMachineState *m_state = nullptr;
        const VskRectI *m_viewport = nullptr;
        VskByte *m_planes[3] = { nullptr };
        VskString m_tile;
        int m_num_planes = 0;
        int m_tile_height = 0;

        TilePutter(Vsk8801Machine *machine, VskString tile, const VskRectI *viewport)
        {
            m_state = machine->m_state;
            m_viewport = viewport ? viewport : &m_state->m_viewport;
            if (m_state->m_color_graphics)
            {
                for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
                    m_planes[iPlane] = machine->m_vram->get_page(m_state->m_screen_mode, iPlane);
            }
            else
            {
                m_planes[0] = machine->m_vram->get_page(m_state->m_screen_mode, m_state->m_active_page);
            }
            m_tile = tile;
            m_num_planes = m_state->get_graphics_num_planes();
            m_tile_height = int(m_tile.size() / m_num_planes);
        }

        void operator()(int x, int y) override
        {
            if (!(m_viewport->inside(x, y)))
                return;

            int x0 = (x % CHAR_BIT);
            int y0 = (y % m_tile_height);
            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            int offset = (y * VSK_8801_GRAPH_VRAM_PLANE_PITCH) + (x / CHAR_BIT);
            for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
            {
                if (m_tile[y0 + iPlane] & (1 << ((CHAR_BIT - 1) - x0)))
                    m_planes[iPlane][offset] |= (1 << ibit);
                else
                    m_planes[iPlane][offset] &= ~(1 << ibit);
            }
        }
    };

    // タイリングを行うオブジェクトを作成する
    std::shared_ptr<VskPixelPutter> get_tile_putter(VskString tile, const VskRectI *viewport) override
    {
        return std::make_shared<TilePutter>(this, tile, viewport);
    }

    // ディスプレイページから表示すべきページのフラグ群を取得
    int get_display_pages_flags(int screen_mode, int display_pages) override;

    bool is_valid_screen_mode(int screen_mode) const override;
    bool is_valid_active_page(int screen_mode, int active_page, bool high_color) const override;

    // 指定したプレーンのグラフィックをクリアする
    void clear_planes(bool blue, bool red, bool green, bool intensity) override;
};

////////////////////////////////////////////////////////////////////////////////////

// Vsk8801Machineのコンストラクタ
Vsk8801Machine::Vsk8801Machine(VskMachineState *state, VskSettings *settings)
    : VskMachine(state, settings)
    , m_screen_image(VSK_SCREEN_WIDTH, VSK_SCREEN_HEIGHT)
{
    reset_palette();
    reset_text();
    reset_graphics();
}

// パレットのリセット
void Vsk8801Machine::reset_palette()
{
    for (int i = 0; i < 16; ++i)
        m_state->m_palette[i] = vsk_get_default_digital_color_8(i);
}

// テキスト画面のリセット
void Vsk8801Machine::reset_text()
{
    m_state->m_text_wider = (m_state->m_text_width == 40);
    m_state->m_text_longer = (m_state->m_text_height == 20);

    if (m_state->m_console_cy0 > m_state->m_text_height - m_state->m_show_function_keys)
        m_state->m_console_cy0 = m_state->m_text_height - m_state->m_show_function_keys;
}

static void vsk_reset_graphics_8801(VskMachineState *state, int width, int height, bool color)
{
    state->m_screen_width = width;
    state->m_screen_height = height;
    state->m_color_graphics = color;
    state->m_viewport = { 0, 0, VskInt(width - 1), VskInt(height - 1) };
    state->m_window = { 0, 0, VskSingle(width - 1), VskSingle(height - 1) };
}

// グラフィック画面のリセット
void Vsk8801Machine::reset_graphics()
{
    switch (m_state->m_screen_mode)
    {
    case 0: vsk_reset_graphics_8801(m_state, 640, 200, true); break;
    case 1: vsk_reset_graphics_8801(m_state, 640, 200, false); break;
    case 2: vsk_reset_graphics_8801(m_state, 640, 400, false); break;
    case 3: vsk_reset_graphics_8801(m_state, 640, 200, true); break;
    case 4: vsk_reset_graphics_8801(m_state, 640, 400, false); break;
    default:
        assert(0);
        break;
    }

    m_state->m_display_pages_flags = get_display_pages_flags(m_state->m_screen_mode, m_state->m_display_pages);
}

// ファンクションキーをテキスト画面にセットする
void Vsk8801Machine::render_function_keys()
{
    if (!m_state->m_show_function_keys)
        return;

    const int y = m_state->m_text_height - 1; // ファンクションキーの行のインデックス
    const bool shift = vsk_is_shift_pressed(); // シフトキーが押されているか？

    // ファンクションキーの行のテキストをクリア
    for (int x = 0; x < m_state->m_text_width; ++x)
        set_ank(x, y, ' ');

    // ファンクションキーの行の文字属性をリセット
    auto *attr_area = get_attr_area(y);
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X> log_attrs;
    vsk_8801_expand_attrs(log_attrs, attr_area, m_state->m_color_text);
    for (auto& log_attr : log_attrs)
    {
        log_attr.reverse(false);
    }

    // F1...F10
    for (int key_no = 1; key_no <= 10; ++key_no)
    {
        // ファンクションキーの位置とサイズを取得
        int x, cx, delta_text;
        if (!get_function_key_position(key_no, x, cx, delta_text, shift))
            continue; // 失敗

        // ファンクションキーのタブを反転する
        for (int ich = 0; ich < cx; ++ich)
        {
            assert(x + ich < m_state->m_text_width);
            log_attrs[x + ich].reverse(true);
        }

        // キーのテキストをセット
        auto& key = m_state->m_function_keys[key_no - 1];
        for (int ich = 0; ich < cx - delta_text; ++ich)
        {
            if (ich < int(key.size()))
                set_ank(x + ich + delta_text, y, key[ich]);
        }
    }

    // テキスト属性を格納
    vsk_8801_store_attrs(log_attrs, attr_area, m_state->m_color_text);
}

// テキスト画面をクリア
void Vsk8801Machine::clear_text(int y0, int y1)
{
    // 各行について処理
    for (int y = y0; y <= y1; ++y)
    {
        auto text_area = get_text_area(y);

        // テキストエリアを0x20 (' ')で埋める
        size_t cdw = VSK_8801_TEXT_VRAM_TEXT_WIDTH / sizeof(VskDword);
        VskDword *pdw = reinterpret_cast<VskDword *>(text_area);
        while (cdw--)
            *pdw++ = 0x20202020;

        // 属性エリアを(0x80, 0xE8)か(0x80, 0x00)で埋め尽くす
        const VskDword dw = (m_state->m_color_text ? 0xE880E880 : 0x00800080);
        cdw = VSK_8801_TEXT_VRAM_ATTR_WIDTH / sizeof(dw);
        while (cdw--)
            *pdw++ = dw;

        // 行リンクを解除
        line_link(y) = 0;
    }
}

// 指定した位置のJIS全角文字を取得
VskWord Vsk8801Machine::get_jis(int x, int y) const
{
    assert(0 <= x && x < m_state->m_text_width);
    assert(0 <= y && y < m_state->m_text_height);
    VskByte lead = get_ank(x, y);
#ifdef JAPAN
    if (vsk_is_sjis_lead(lead))
    {
        int next_x, next_y;
        if (get_next_x_y(next_x, next_y, x, y))
        {
            VskByte trail = get_ank(next_x, next_y);
            VskWord sjis = vsk_make_word(trail, lead);
            if (vsk_is_sjis_code(sjis))
            {
                VskWord jis = vsk_sjis2jis(sjis);
                return jis;
            }
        }
    }
#endif
    return lead;
}

// 指定した位置にJIS全角文字をセット
void Vsk8801Machine::set_jis(int x, int y, VskWord jis)
{
    assert(0 <= x && x < m_state->m_text_width);
    assert(0 <= y && y < m_state->m_text_height);
#ifdef JAPAN
    if (!vsk_is_jis_code(jis))
        return;

    VskWord sjis = vsk_jis2sjis(jis);
    assert(vsk_is_sjis_code(sjis));
    VskByte lead = vsk_high_byte(sjis), trail = vsk_low_byte(sjis);

    int next_x, next_y;
    if (get_next_x_y(next_x, next_y, x, y))
    {
        set_ank(x, y, lead);
        set_ank(next_x, next_y, trail);

        assert(!is_ank(x, y));
        assert(get_jis(x, y) == jis);
    }
    else
    {
        set_ank(x, y, lead);
    }
#endif
}

// ANK文字を描画する
void Vsk8801Machine::render_ank(int x, int y, VskByte ch, const VskLogAttr& log_attr)
{
    bool wider = m_state->m_text_wider; // テキスト画面は40文字の幅か80文字の幅か?
    bool longer = m_state->m_text_longer; // テキスト画面は20文字の高さか25文字の高さか?
    int char_width = (wider ? 16 : 8); // 文字幅をセット
    int char_height = (longer ? 20 : 16); // 文字の高さをセット

    // 文字属性を処理する
    if (log_attr.secret())
        ch = ' ';
    else if (log_attr.blink() && m_state->m_blink_flag == 0)
        ch = ' ';

    // リバース（色調反転）を処理する
    bool reverse = log_attr.reverse();
    if (m_state->m_show_caret &&
        x == m_state->m_caret_x && y == m_state->m_caret_y &&
        (m_state->m_blink_flag & 1) &&
        m_state->is_caret_blinking())
    {
        reverse = !reverse;
    }

    // 文字位置
    int x0 = x * char_width, y0 = y * char_height;

    bool is_color = m_state->m_color_text;  // 色付きか?
    bool is_semigra = log_attr.m_semigra;   // セミグラ文字か?
    VskByte palette = log_attr.m_palette;   // 文字パレット

    // スクリーン描画を助けるオブジェクト
    VskScreenPutter putter(m_screen_image, m_state->text_color_to_web_color(palette));
    // 何も描画しないオブジェクト
    VskNullPutter eraser;
    // アッパーライン（上線）
    bool upperline = log_attr.m_upperline;
    // アンダーライン（下線）
    bool underline = log_attr.m_underline;
    if (is_semigra) // セミグラ文字か?
    {
        // セミグラ文字を描画する
        VskSemiGraAnkGetter getter1;
        if (wider) // 40文字の幅か?
        {
            if (reverse) // リバースか?
                vk_draw_wide_ank(eraser, putter, x0, y0, ch, getter1, underline, upperline);
            else
                vk_draw_wide_ank(putter, eraser, x0, y0, ch, getter1, underline, upperline);
        }
        else
        {
            if (reverse) // リバースか?
                vk_draw_ank(eraser, putter, x0, y0, ch, getter1, underline, upperline);
            else
                vk_draw_ank(putter, eraser, x0, y0, ch, getter1, underline, upperline);
        }
    }
    else // 通常文字か?
    {
        // 通常のANK文字を描画する
        Vsk8801AnkGetter getter0;
        if (wider) // 40文字の幅か?
        {
            if (reverse) // リバースか?
                vk_draw_wide_ank(eraser, putter, x0, y0, ch, getter0, underline, upperline);
            else
                vk_draw_wide_ank(putter, eraser, x0, y0, ch, getter0, underline, upperline);
        }
        else
        {
            if (reverse) // リバースか?
                vk_draw_ank(eraser, putter, x0, y0, ch, getter0, underline, upperline);
            else
                vk_draw_ank(putter, eraser, x0, y0, ch, getter0, underline, upperline);
        }
    }

    // リバースかつ20文字の高さのときに、反転している文字の下部を描画する
    if (reverse && longer)
    {
        vsk_fill_box(putter, x0, y0 + char_height - 4, x0 + char_width - 1, y0 + char_height - 1, &m_state->m_viewport);
    }
}

// JIS全角文字を描画する
void Vsk8801Machine::render_jis(int x, int y, int next_x, int next_y, VskWord jis, const VskLogAttr& log_attr)
{
#ifdef JAPAN
    bool wider = m_state->m_text_wider; // テキスト画面は40文字の幅か80文字の幅か?
    bool longer = m_state->m_text_longer; // テキスト画面は20文字の高さか25文字の高さか?
    int char_width = (wider ? 16 : 8); // 文字幅をセット
    int char_height = (longer ? 20 : 16); // 文字の高さをセット

    // 文字属性を処理する
    if (log_attr.secret())
        jis = 0x2121;
    else if (log_attr.blink() && m_state->m_blink_flag == 0)
        jis = 0x2121;

    // リバース（色調反転）を処理する
    bool reverse = log_attr.reverse();
    if (m_state->m_show_caret &&
        ((x == m_state->m_caret_x && y == m_state->m_caret_y) ||
         (next_x == m_state->m_caret_x && next_y == m_state->m_caret_y)) &&
        (m_state->m_blink_flag & 1) &&
        m_state->is_caret_blinking())
    {
        reverse = !reverse;
    }

    // 文字位置
    int x0 = x * char_width, y0 = y * char_height;
    int x1 = (wider ? next_x * 16 : next_x * 8), y1 = next_y * char_height;
    // 色付きか?
    bool is_color = m_state->m_color_text;
    // テキストの色
    VskByte palette = log_attr.m_palette;
    // スクリーン描画を助けるオブジェクト
    VskScreenPutter putter(m_screen_image, m_state->text_color_to_web_color(palette));
    // 何も描画しないオブジェクト
    VskNullPutter eraser;
    bool upperline = log_attr.m_upperline;  // アッパーライン（上線）
    bool underline = log_attr.m_underline;  // アンダーライン（下線）
    // 漢字のイメージを取得するオブジェクト
    VskKanjiGetter getter;
    if (wider) // 40文字の幅か?
    {
        if (reverse) // リバースか?
            vk_draw_wide_jis(eraser, putter, x0, y0, x1, y1, jis, getter, underline, upperline);
        else
            vk_draw_wide_jis(putter, eraser, x0, y0, x1, y1, jis, getter, underline, upperline);
    }
    else
    {
        if (reverse) // リバースか?
            vk_draw_jis(eraser, putter, x0, y0, x1, y1, jis, getter, underline, upperline);
        else
            vk_draw_jis(putter, eraser, x0, y0, x1, y1, jis, getter, underline, upperline);
    }

    // リバースかつ20文字の高さのときに、反転している文字の下部を描画する
    if (reverse && longer)
    {
        vsk_fill_box(putter, x0, y0 + char_height - 4, x0 + char_width - 1, y0 + char_height - 1, &m_state->m_viewport);
        vsk_fill_box(putter, x1, y1 + char_height - 4, x1 + char_width - 1, y1 + char_height - 1, &m_state->m_viewport);
    }
#endif
}

// テキスト画面を描画する
void Vsk8801Machine::render_text()
{
    if (!m_state->m_show_text)
        return;

    render_function_keys();

    bool is_color = m_state->m_color_text;
    bool wider = m_state->m_text_wider;
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X> log_attrs;

    bool was_lead = false;
    for (int y = 0; y < m_state->m_text_height; ++y)
    {
        auto *attr_area = get_attr_area(y);
        vsk_8801_expand_attrs(log_attrs, attr_area, is_color);

        for (int x = 0; x < m_state->m_text_width; ++x)
        {
            if (was_lead)
            {
                was_lead = false;
                continue;
            }
            VskByte ch = get_ank(x, y);
#ifdef JAPAN
            if (VSK_SETTINGS()->m_text_mode != VSK_TEXT_MODE_GRPH && vsk_is_sjis_lead(ch))
            {
                if (!log_attrs.at(x).m_semigra)
                {
                    int next_x, next_y;
                    if (get_next_x_y(next_x, next_y, x, y))
                    {
                        VskByte next_ch = get_ank(next_x, next_y);
                        if (vsk_is_sjis_trail(next_ch))
                        {
                            VskWord sjis = vsk_make_word(next_ch, ch);
                            assert(vsk_is_sjis_code(sjis));
                            VskWord jis = vsk_sjis2jis(sjis);
                            assert(vsk_is_jis_code(jis));
                            render_jis(x, y, next_x, next_y, jis, log_attrs.at(x));

                            if (y != next_y)
                                vsk_8801_expand_attrs(log_attrs, attr_area, is_color);

                            was_lead = true;
                            continue;
                        }
                    }
                }
            }
#endif
#if 0
            if (line_link(y) && x == m_state->m_text_width - 1)
                ch = '>';
#endif
            render_ank(x, y, ch, log_attrs.at(x));
        }
    }
}

// 白黒グラフィック画面を描画する
void Vsk8801Machine::render_mono_graphics()
{
    int display_flags = m_state->m_display_pages_flags;
    if (display_flags <= 0)
        return;

    if (m_state->m_screen_height == 400)
    {
        VskByte *page = m_vram->get_page(m_state->m_screen_mode, 0);
        VskMonoGetter getter(m_state->m_screen_width, m_state->m_screen_height, page);
        for (int y = 0; y < m_state->m_screen_height; ++y)
        {
            for (int x = 0; x < m_state->m_screen_width; ++x)
            {
                if (getter(x, y))
                    m_screen_image.set_pixel(x, y, vsk_color_white);
            }
        }
    }
    else
    {
        for (int iPage = 0; iPage < 3; ++iPage)
        {
            if (!(display_flags & (1 << iPage)))
                continue;
            VskByte *page = m_vram->get_page(m_state->m_screen_mode, iPage);
            VskMonoGetter getter(m_state->m_screen_width, m_state->m_screen_height, page);
            for (int y = 0; y < m_state->m_screen_height; ++y)
            {
                for (int x = 0; x < m_state->m_screen_width; ++x)
                {
                    if (getter(x, y))
                        m_screen_image.set_pixel(x, y * 2, vsk_color_white);
                }
            }
        }
    }
}

// カラーグラフィック画面を描画する
void Vsk8801Machine::render_color_graphics()
{
    int screen_mode = m_state->m_screen_mode;
    VskByte *plane0 = m_vram->get_page(screen_mode, 0);
    VskByte *plane1 = m_vram->get_page(screen_mode, 1);
    VskByte *plane2 = m_vram->get_page(screen_mode, 2);
    for (int y = 0; y < m_state->m_screen_height; ++y)
    {
        for (int x = 0; x < m_state->m_screen_width; x += CHAR_BIT)
        {
            VskByte* byte0 = &plane0[y * VSK_8801_GRAPH_VRAM_PLANE_PITCH];
            VskByte* byte1 = &plane1[y * VSK_8801_GRAPH_VRAM_PLANE_PITCH];
            VskByte* byte2 = &plane2[y * VSK_8801_GRAPH_VRAM_PLANE_PITCH];
            for (int i = 0; i < CHAR_BIT; ++i)
            {
                int ibit = ((CHAR_BIT - 1) - i);
                VskByte b0 = ((byte0[x / CHAR_BIT] >> ibit) & 0x1);
                VskByte b1 = ((byte1[x / CHAR_BIT] >> ibit) & 0x1);
                VskByte b2 = ((byte2[x / CHAR_BIT] >> ibit) & 0x1);
                VskByte byte = (b0 | (b1 << 1) | (b2 << 2));
                m_screen_image.set_pixel(x + i, y * 2, vsk_fix_color(m_state->palette_to_web_color(byte)));
            }
        }
    }
}

// スクリーンモードが正しいか？
bool Vsk8801Machine::is_valid_screen_mode(int screen_mode) const
{
    return 0 <= screen_mode && screen_mode <= 4;
}

// 描画ページが正しいか？
bool Vsk8801Machine::is_valid_active_page(int screen_mode, int active_page, bool high_color) const
{
    switch (screen_mode)
    {
    case 0: return (0 <= active_page && active_page <= 3);
    case 1: return (0 <= active_page && active_page <= 11);
    case 2: return (0 <= active_page && active_page <= 5);
    case 3: return (0 <= active_page && active_page <= 3);
    case 4: return (0 <= active_page && active_page <= 1);
    }
    assert(0);
    return false;
}

// ディスプレイページから表示すべきページのフラグ群を取得
int Vsk8801Machine::get_display_pages_flags(int screen_mode, int display_pages)
{
    switch (screen_mode)
    {
    case 0: case 1: case 2: case 3: case 4:
        switch (display_pages)
        {
        case 0:
            return 0;
        case 1: return (1 << 0);
        case 2: return            (1 << 1);
        case 3: return (1 << 0) | (1 << 1);
        case 4: return                       (1 << 2);
        case 5: return (1 << 0) |            (1 << 2);
        case 6: return            (1 << 1) | (1 << 2);
        case 7: return (1 << 0) | (1 << 1) | (1 << 2);
        default:
            return -1;
        }
        break;
    }
    return -1;
}

// 指定したプレーンのグラフィックをクリアする
void Vsk8801Machine::clear_planes(bool blue, bool red, bool green, bool intensity)
{
    VskByte *planes[3] = {
        m_vram->get_page(m_state->m_screen_mode, 0),
        m_vram->get_page(m_state->m_screen_mode, 1),
        m_vram->get_page(m_state->m_screen_mode, 2)
    };
    if (blue)
        std::memset(planes[0], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    if (red)
        std::memset(planes[1], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    if (green)
        std::memset(planes[2], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    // No intensity
}

////////////////////////////////////////////////////////////////////////////////////

// 8801マシンを作成する関数
std::shared_ptr<VskMachine> vsk_create_8801_machine(VskMachineState *state, VskSettings *settings)
{
    state->m_palette_mode = VSK_PAL_MODE_8_COLORS_DIGITAL;
    return std::make_shared<Vsk8801Machine>(state, settings);
}

////////////////////////////////////////////////////////////////////////////////////

// フリーエリアのアドレスチェックを行うメモリーのアドレス
#define VSK_8801_FREE_AREA_START_CHECK  0xEB1B
#define VSK_8801_FREE_AREA_END_CHECK    0xE7E8

// フリーエリアの最後のアドレス
VskDword Vsk8801Machine::get_free_ubound()
{
    if (m_state->m_has_turtle)
        return (m_state->m_has_cmd_extension) ? 0xD5FF : 0xDBFF;
    else
        return (m_state->m_has_cmd_extension) ? 0xE0FF : 0xE5FF;
}

// フリーエリアのサイズ
VskDword Vsk8801Machine::get_free_size()
{
    return (get_free_ubound() - VSK_8801_FREE_AREA_START + 1);
}

bool Vsk8801Machine::special_memory_read(VskByte *ptr, VskAddr addr)
{
    switch (addr)
    {
    case VSK_8801_FREE_AREA_START_CHECK + 0:
        *ptr = vsk_low_byte(VSK_8801_FREE_AREA_START);
        return true;
    case VSK_8801_FREE_AREA_START_CHECK + 1:
        *ptr = vsk_high_byte(VSK_8801_FREE_AREA_START);
        return true;
    case VSK_8801_FREE_AREA_END_CHECK + 0:
        *ptr = vsk_low_byte(vsk_machine->get_free_ubound());
        return true;
    case VSK_8801_FREE_AREA_END_CHECK + 1:
        *ptr = vsk_high_byte(vsk_machine->get_free_ubound());
        return true;
    default:
        return false;
    }
}

bool Vsk8801Machine::clear_memory(VskDword addr)
{
    if (!(VSK_8801_FREE_AREA_START <= addr && addr <= VSK_8801_FREE_AREA_END_MAX))
        return false;

    m_free_area->clear();
    return true;
}

void Vsk8801Machine::do_unit_tests()
{
#ifndef NDEBUG
    std::array<VskByte, VSK_8801_ATTR_PAIR_MAX * 2> attr_area;
    std::array<VskLogAttr, VSK_8801_TEXT_MAX_X> log_attrs;

    vsk_reset_attr_area(attr_area.data());
    std::memcpy(attr_area.data(), "\x80\xE8", 2);
    vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(log_attrs[0].m_palette == 7);
    assert(log_attrs[0].m_effect == 0);

    vsk_reset_attr_area(attr_area.data());
    std::memcpy(attr_area.data(), "\x01\x88\x80\xE8", 4);
    vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(log_attrs[0].m_palette == 4);
    assert(log_attrs[0].m_effect == 0);
    assert(log_attrs[1].m_palette == 7);
    assert(log_attrs[1].m_effect == 0);

    vsk_reset_attr_area(attr_area.data());
    std::memcpy(attr_area.data(), "\x02\x88\x80\xE8", 4);
    vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(log_attrs[0].m_palette == 4);
    assert(log_attrs[0].m_effect == 0);
    assert(log_attrs[1].m_palette == 7);
    assert(log_attrs[1].m_effect == 0);

    vsk_reset_attr_area(attr_area.data());
    std::memcpy(attr_area.data(), "\x03\x88\x80\xE8", 4);
    vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(log_attrs[0].m_palette == 4);
    assert(log_attrs[0].m_effect == 0);
    assert(log_attrs[1].m_palette == 4);
    assert(log_attrs[1].m_effect == 0);
    assert(log_attrs[2].m_palette == 7);
    assert(log_attrs[2].m_effect == 0);

    vsk_reset_attr_area(attr_area.data());
    std::memcpy(attr_area.data(), "\x04\x88\x80\xE8", 4);
    vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(log_attrs[0].m_palette == 4);
    assert(log_attrs[0].m_effect == 0);
    assert(log_attrs[1].m_palette == 4);
    assert(log_attrs[1].m_effect == 0);
    assert(log_attrs[2].m_palette == 7);
    assert(log_attrs[2].m_effect == 0);

    vsk_reset_attr_area(attr_area.data());
    std::memcpy(attr_area.data(), "\x01\xE8\x03\x88", 4);
    vsk_8801_expand_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(log_attrs[0].m_palette == 7);
    assert(log_attrs[0].m_effect == 0);
    assert(log_attrs[1].m_palette == 4);
    assert(log_attrs[1].m_effect == 0);
    assert(log_attrs[2].m_palette == 7);
    assert(log_attrs[2].m_effect == 0);

    vsk_8801_store_attrs_of_width_40(log_attrs, attr_area.data(), true);
    assert(attr_area[0] == 1);
    assert(attr_area[1] == 0xE8);
    assert(attr_area[2] == 3);
    assert(attr_area[3] == 0x88);
#endif
}

#endif  // def ENABLE_PC8801
