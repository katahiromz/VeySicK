// 9801 Virtual Machine
#ifdef ENABLE_VM9801

#include "VeySicK.h"            // VeySicK
#include "draw_algorithm.h"     // 描画アルゴリズム
#include "turtle.h"             // タートル

////////////////////////////////////////////////////////////////////////////////////
// 9801 machine

// 9801 VRAM 基本情報
#define VSK_9801_TEXT_VRAM_TEXT_ADDR    0xA0000
#define VSK_9801_TEXT_VRAM_ATTR_ADDR    0xA2000
#define VSK_9801_TEXT_VRAM_TEXT_WIDTH   80
#define VSK_9801_TEXT_VRAM_ATTR_WIDTH   80
#define VSK_9801_TEXT_VRAM_MAX_HEIGHT   25
#define VSK_9801_TEXT_VRAM_PITCH        160
#define VSK_9801_TEXT_VRAM_BLOCK_SIZE   0x2000
#define VSK_9801_TEXT_VRAM_TOTAL_SIZE   (VSK_9801_TEXT_VRAM_BLOCK_SIZE * 2)

// 9801 文字属性
#define VSK_9801_ATTR_SHOW              VskByte(1 << 0)
#define VSK_9801_ATTR_BLINK             VskByte(1 << 1)
#define VSK_9801_ATTR_REVERSE           VskByte(1 << 2)
#define VSK_9801_ATTR_UNDERLINE         VskByte(1 << 3)
#define VSK_9801_ATTR_SEMIGRA           VskByte(1 << 4)
#define VSK_9801_ATTR_BLUE              VskByte(1 << 5)
#define VSK_9801_ATTR_RED               VskByte(1 << 6)
#define VSK_9801_ATTR_GREEN             VskByte(1 << 7)

#define VSK_9801_ATTR_GET_COLOR(attr)   VskByte(((attr) >> 5) & 0x07)
#define VSK_9801_ATTR_SET_COLOR(color)  VskByte(((color) & 0x07) << 5)

#define VSK_9801_LEAD_FIX               VskByte(0x20)
#define VSK_9801_TRAIL_FIX              VskByte(0x80)

// 9801 VRAM クラス
struct Vsk9801TextVRAM : VskSimpleMemoryBlock
{
    VskByte m_9801_text_vram_area[VSK_9801_TEXT_VRAM_TOTAL_SIZE] = { 0 };
    Vsk9801TextVRAM(VskMachineState *state)
        : VskSimpleMemoryBlock(VSK_9801_TEXT_VRAM_TEXT_ADDR,
                               VSK_9801_TEXT_VRAM_TOTAL_SIZE,
                               m_9801_text_vram_area)
    {
    }
};

// 論理文字属性からバイト値へ変換
static VskByte vsk_9801_byte_from_log_attr(const VskLogAttr& log_attr)
{
    uint8_t ret = VSK_9801_ATTR_SET_COLOR(log_attr.m_palette);

    switch (log_attr.m_effect)
    {
    case 0: ret |= VSK_9801_ATTR_SHOW;                                               break;
    case 1:                                                                          break;
    case 2: ret |= VSK_9801_ATTR_SHOW |                         VSK_9801_ATTR_BLINK; break;
    case 3: ret |=                                              VSK_9801_ATTR_BLINK; break;
    case 4: ret |= VSK_9801_ATTR_SHOW | VSK_9801_ATTR_REVERSE;                       break;
    case 5: ret |=                      VSK_9801_ATTR_REVERSE;                       break;
    case 6: ret |= VSK_9801_ATTR_SHOW | VSK_9801_ATTR_REVERSE | VSK_9801_ATTR_BLINK; break;
    case 7: ret |=                      VSK_9801_ATTR_REVERSE | VSK_9801_ATTR_BLINK; break;
    }

    if (log_attr.m_semigra)
        ret |= VSK_9801_ATTR_SEMIGRA;

    if (log_attr.m_underline)
        ret |= VSK_9801_ATTR_UNDERLINE;

    // log_attr.m_upperline is ignored
    return ret;
}

// バイト値から論理文字属性へ変換
static void vsk_9801_log_attr_from_byte(VskLogAttr& log_attr, VskByte byte)
{
    log_attr.reset();

    log_attr.m_palette = VSK_9801_ATTR_GET_COLOR(byte);

    if (!(byte & 1))
        log_attr.m_effect |= VSK_9801_ATTR_SHOW;
    if (byte & 2)
        log_attr.m_effect |= VSK_9801_ATTR_BLINK;
    if (byte & 4)
        log_attr.m_effect |= VSK_9801_ATTR_REVERSE;

    if (byte & VSK_9801_ATTR_SEMIGRA)
        log_attr.m_semigra = true;

    if (byte & VSK_9801_ATTR_UNDERLINE)
        log_attr.m_underline = true;
}

// 9801 グラフィックVRAM
#define VSK_9801_GRAPH_VRAM_PLANE_BLUE          0xA8000
#define VSK_9801_GRAPH_VRAM_PLANE_RED           0xB0000
#define VSK_9801_GRAPH_VRAM_PLANE_GREEN         0xB8000
#define VSK_9801_GRAPH_VRAM_PLANE_INTENSITY     0xE0000
#define VSK_9801_GRAPH_VRAM_PLANE_0             VSK_9801_GRAPH_VRAM_PLANE_BLUE
#define VSK_9801_GRAPH_VRAM_PLANE_1             VSK_9801_GRAPH_VRAM_PLANE_RED
#define VSK_9801_GRAPH_VRAM_PLANE_2             VSK_9801_GRAPH_VRAM_PLANE_GREEN
#define VSK_9801_GRAPH_VRAM_PLANE_3             VSK_9801_GRAPH_VRAM_PLANE_INTENSITY
#define VSK_9801_GRAPH_VRAM_PLANE_MIDDLE        0x03E80
#define VSK_9801_GRAPH_VRAM_PLANE_SIZE          0x08000
#define VSK_9801_GRAPH_VRAM_PLANE_PITCH         80

#define VSK_9801_GRAPH_VRAM_BANK_0              0
#define VSK_9801_GRAPH_VRAM_BANK_1              1

// 9801 グラフィック VRAM
struct Vsk9801GraphVRAM : VskMemoryBlockBase
{
    // マシン状態
    VskMachineState *m_state = nullptr;

    // 9801 VRAM 実データ
    // [bank][plane][offset]
    VskByte m_9801_graph_vram_planes[2][4][VSK_9801_GRAPH_VRAM_PLANE_SIZE] = { { { 0 } } };

    // アドレス
    const VskAddr c_addrs[4] =
    {
        VSK_9801_GRAPH_VRAM_PLANE_0,
        VSK_9801_GRAPH_VRAM_PLANE_1,
        VSK_9801_GRAPH_VRAM_PLANE_2,
        VSK_9801_GRAPH_VRAM_PLANE_3,
    };

    // コンストラクタ
    Vsk9801GraphVRAM(VskMachineState *state) : m_state(state)
    {
    }

    // アドレスがVRAMに含まれているかどうか？
    bool includes(VskAddr addr, VskMemSize size) const override
    {
        if (VSK_9801_GRAPH_VRAM_PLANE_0 <= addr && addr + size <= VSK_9801_GRAPH_VRAM_PLANE_0 + 3 * VSK_9801_GRAPH_VRAM_PLANE_SIZE)
            return true;
        if (VSK_9801_GRAPH_VRAM_PLANE_3 <= addr && addr + size <= VSK_9801_GRAPH_VRAM_PLANE_3 + VSK_9801_GRAPH_VRAM_PLANE_SIZE)
            return true;
        return false;
    }

    // アドレスがどのプレーンに含まれているか？
    int which(VskAddr addr) const
    {
        for (int iPlane = 0; iPlane < 4; ++iPlane)
        {
            if (c_addrs[iPlane] <= addr && addr < c_addrs[iPlane] + VSK_9801_GRAPH_VRAM_PLANE_SIZE)
                return iPlane;
        }
        return -1;
    }

    // VRAMから1バイト読み込み
    bool read(VskByte *ptr, VskAddr addr) const override
    {
        int iPlane = which(addr);
        if (iPlane < 0)
            return false;

        auto offset = addr - c_addrs[iPlane];

        // 区間チェック
        assert(0 <= m_state->m_vram_bank && m_state->m_vram_bank < 2);
        assert(0 <= iPlane && iPlane < 4);
        assert(0 <= offset && offset < VSK_9801_GRAPH_VRAM_PLANE_SIZE);

        *ptr = m_9801_graph_vram_planes[m_state->m_vram_bank][iPlane][offset];
        return true;
    }

    // VRAMへ1バイト書き込み
    bool write(const VskByte *ptr, VskAddr addr) override
    {
        int iPlane = which(addr);
        if (iPlane < 0)
            return false;

        auto offset = addr - c_addrs[iPlane];

        // 区間チェック
        assert(0 <= m_state->m_vram_bank && m_state->m_vram_bank < 2);
        assert(0 <= iPlane && iPlane < 4);
        assert(0 <= offset && offset < VSK_9801_GRAPH_VRAM_PLANE_SIZE);

        m_9801_graph_vram_planes[m_state->m_vram_bank][iPlane][offset] = *ptr;
        return true;
    }

    // VRAMからページを選ぶ
    VskByte *get_page(int screen_mode, int iPage, int iPlane = 0)
    {
        switch (screen_mode)
        {
        case 0:
            switch (iPage)
            {
            case 0: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][iPlane][0];
            case 1: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][iPlane][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            case 2: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][iPlane][0];
            case 3: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][iPlane][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            }
            break;
        case 1:
            assert(iPlane == 0);
            switch (iPage)
            {
            case 0: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][0][0];
            case 1: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][1][0];
            case 2: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][2][0];
            case 3: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][0][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            case 4: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][1][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            case 5: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][2][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            case 6: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][0][0];
            case 7: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][1][0];
            case 8: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][2][0];
            case 9: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][0][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            case 10: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][1][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            case 11: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][2][VSK_9801_GRAPH_VRAM_PLANE_MIDDLE];
            }
            break;
        case 2:
            assert(iPlane == 0);
            switch (iPage)
            {
            case 0: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][0][0];
            case 1: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][1][0];
            case 2: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][2][0];
            case 3: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][0][0];
            case 4: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][1][0];
            case 5: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][2][0];
            }
            break;
        case 3:
            switch (iPage)
            {
            case 0: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_0][iPlane][0];
            case 1: return &m_9801_graph_vram_planes[VSK_9801_GRAPH_VRAM_BANK_1][iPlane][0];
            }
            break;
        }
        return nullptr;
    }

    // カラーの表示ページのページを取得
    int get_color_display_page(int screen_mode, int display_pages)
    {
        switch (screen_mode)
        {
        case 0:
            switch (display_pages)
            {
            case 1: return 0;
            case 2: return 1;
            case 17: return 2;
            case 18: return 3;
            }
            break;
        case 3:
            switch (display_pages)
            {
            case 1: return 0;
            case 17: return 1;
            }
            break;
        }
        return -1;
    }
};

// 9801 フリーエリアのアドレスとサイズ
#define VSK_9801_FREE_AREA_START      0x10C00
#define VSK_9801_FREE_AREA_END_MAX    0x7FFFF
#define VSK_9801_FREE_AREA_SIZE       (VSK_9801_FREE_AREA_END_MAX - VSK_9801_FREE_AREA_START + 1)

// 9801 フリーエリア
struct Vsk9801FreeArea : VskSimpleMemoryBlock
{
    Vsk9801FreeArea() : VskSimpleMemoryBlock(VSK_9801_FREE_AREA_START, VSK_9801_FREE_AREA_SIZE)
    { }
};

// 9801 マシン
struct Vsk9801Machine : VskMachine
{
    Vsk32BppImage m_screen_image;   // スクリーンイメージ
    std::shared_ptr<Vsk9801TextVRAM> m_text_vram; // テキストVRAM
    std::shared_ptr<Vsk9801GraphVRAM> m_graph_vram; // グラフィック VRAM
    std::shared_ptr<Vsk9801FreeArea> m_free_area;   // フリーエリア

    // コンストラクタ
    Vsk9801Machine(VskMachineState *state, VskSettings *settings);

    // メモリーのクリア
    bool clear_memory(VskDword addr) override;
    // フリーエリアのサイズ
    VskDword get_free_size() override;
    // フリーエリアの最後のアドレス
    VskDword get_free_ubound() override;
    // 特殊なメモリー読み込み
    bool special_memory_read(VskByte *ptr, VskAddr addr) override;

    // システムのリセット
    void reset() override;
    // パレットのリセット
    void reset_palette() override;
    // テキスト画面のリセット
    void reset_text() override;
    // グラフィック画面のリセット
    void reset_graphics() override;

    // テキスト画面の消去
    void clear_text(int y0, int y1) override;
    using VskMachine::clear_text;

    // 下にスクロールする
    void scroll_down(int y0, int y1) override
    {
        for (int y = y0; y < y1; ++y)
        {
            std::memcpy(get_text_area(y), get_text_area(y + 1), VSK_9801_TEXT_VRAM_PITCH);
            std::memcpy(get_attr_area(y), get_attr_area(y + 1), VSK_9801_TEXT_VRAM_PITCH);
            line_link(y) = line_link(y + 1);
        }
        clear_text(y1, y1);
    }

    // 上にスクロールする
    void scroll_up(int y0, int y1) override
    {
        for (int y = y1; y > y0; --y)
        {
            std::memcpy(get_text_area(y), get_text_area(y - 1), VSK_9801_TEXT_VRAM_PITCH);
            std::memcpy(get_attr_area(y), get_attr_area(y - 1), VSK_9801_TEXT_VRAM_PITCH);
            line_link(y) = line_link(y - 1);
        }
        clear_text(y0, y0);
        line_link(y1) = 0;
    }

    // グラフィック画面を消去
    void clear_screen_image() override
    {
        m_screen_image.clear();
    }

    // テキストエリアを取得
    VskByte* get_text_area(int y)
    {
        assert(0 <= y && y < m_state->m_text_height);
        return const_cast<VskByte *>(const_cast<const Vsk9801Machine *>(this)->get_text_area(y));
    }
    const VskByte* get_text_area(int y) const
    {
        assert(0 <= y && y < m_state->m_text_height);
        auto offset = y * VSK_9801_TEXT_VRAM_PITCH;
        assert(0 <= offset && offset < VSK_9801_TEXT_VRAM_TOTAL_SIZE);
        return &(*m_text_vram)[offset];
    }

    // 指定した場所がANK文字かどうか？
    bool is_ank(int x, int y) const override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);
#ifdef JAPAN
        if (m_state->m_text_wider)
            return !(get_text_area(y)[4 * x + 1] & VSK_9801_TRAIL_FIX);
        else
            return !(get_text_area(y)[2 * x + 1] & VSK_9801_TRAIL_FIX);
#else
        return true;
#endif
    }

    // ANK文字を取得
    VskByte get_ank(int x, int y) const override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);
        bool wider = (m_state->m_text_wider);
        return get_text_area(y)[wider ? (4 * x) : (2 * x)];
    }
    // ANK文字をセット
    void set_ank(int x, int y, VskByte ch) override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);
        bool wider = (m_state->m_text_wider);
        get_text_area(y)[(wider ? 4 : 2) * x + 0] = (VskByte)ch;
        get_text_area(y)[(wider ? 4 : 2) * x + 1] = 0;
    }

    // JIS全角文字を取得
    VskWord get_jis(int x, int y) const override;
    // JIS全角文字をセット
    void set_jis(int x, int y, VskWord jis) override;

    // 文字属性エリアを取得
    VskByte* get_attr_area(int y)
    {
        assert(0 <= y && y < m_state->m_text_height);
        auto offset = VSK_9801_TEXT_VRAM_BLOCK_SIZE + y * VSK_9801_TEXT_VRAM_PITCH;
        assert(0 <= offset && offset < VSK_9801_TEXT_VRAM_TOTAL_SIZE);
        return &(*m_text_vram)[offset];
    }
    // 文字属性エリアを取得
    const VskByte* get_attr_area(int y) const
    {
        assert(0 <= y && y < m_state->m_text_height);
        auto offset = VSK_9801_TEXT_VRAM_BLOCK_SIZE + y * VSK_9801_TEXT_VRAM_PITCH;
        assert(0 <= offset && offset < VSK_9801_TEXT_VRAM_TOTAL_SIZE);
        return &(*m_text_vram)[offset];
    }

    // 文字属性をセット
    void set_attr(int x, int y, const VskLogAttr& log_attr) override
    {
        assert(0 <= x && x < m_state->m_text_width);
        assert(0 <= y && y < m_state->m_text_height);
        auto attr = vsk_9801_byte_from_log_attr(log_attr);
        get_attr_area(y)[2 * x] = attr;
    }

    // ANK文字を描画
    void render_ank(int x, int y, VskByte ch, VskByte attr)
    {
        VskLogAttr log_attr;
        vsk_9801_log_attr_from_byte(log_attr, attr);
        render_ank(x, y, ch, log_attr);
    }

    // JIS全角文字を描画
    void render_jis(int x, int y, int next_x, int next_y, VskWord jis, VskByte attr)
    {
        VskLogAttr log_attr;
        vsk_9801_log_attr_from_byte(log_attr, attr);
        render_jis(x, y, next_x, next_y, jis, log_attr);
    }

    void render_ank(int x, int y, VskByte ch, const VskLogAttr& log_attr);
    void render_jis(int x, int y, int next_x, int next_y, VskWord jis, const VskLogAttr& log_attr);

    // ピクセルを取得するヘルパークラス
    struct ColorGetter : VskColorGetter
    {
        VskMachineState *m_state = nullptr;
        const VskRectI *m_viewport = nullptr;
        VskByte *m_planes[4] = { nullptr };
        VskByte m_palette;

        ColorGetter(Vsk9801Machine *machine, const VskRectI *viewport)
        {
            m_state = machine->m_state;
            m_viewport = viewport ? viewport : &m_state->m_viewport;
            if (m_state->m_color_graphics)
            {
                m_planes[0] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 0);
                m_planes[1] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 1);
                m_planes[2] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 2);
                m_planes[3] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 3);
            }
            else
            {
                m_planes[0] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 0);
            }
        }

        int operator()(int x, int y) override
        {
            if (!(m_viewport->inside(x, y)))
                return -1;

            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            int offset = (y * VSK_9801_GRAPH_VRAM_PLANE_PITCH) + (x / CHAR_BIT);
            assert(0 <= offset && offset < VSK_9801_GRAPH_VRAM_PLANE_SIZE);
            int palette = 0;
            if (m_state->m_color_graphics)
            {
                for (int i = 0; i < 4; ++i)
                {
                    if (m_planes[i][offset] & (1 << ibit))
                        palette |= (1 << i);
                }
            }
            else
            {
                if (m_planes[0][offset] & (1 << ibit))
                    palette |= 1;
            }
            return palette;
        }
    };

    // ピクセルをセットするヘルパークラス
    struct ColorPutter : VskPixelPutter
    {
        VskMachineState *m_state = nullptr;
        const VskRectI *m_viewport = nullptr;
        VskByte *m_planes[4] = { nullptr };
        VskByte m_palette = 7;
        int m_num_planes = 0;

        void set_color(int palette) override
        {
            m_palette = palette;
        }

        ColorPutter(Vsk9801Machine *machine, int palette, const VskRectI *viewport)
        {
            m_state = machine->m_state;
            m_viewport = viewport ? viewport : &m_state->m_viewport;
            m_num_planes = m_state->get_graphics_num_planes();
            if (m_state->m_color_graphics)
            {
                for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
                    m_planes[iPlane] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, iPlane);
            }
            else
            {
                m_planes[0] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, m_state->m_active_page);
            }
            m_palette = VskByte(palette);
        }

        void operator()(int x, int y) override
        {
            if (!(m_viewport->inside(x, y)))
                return;

            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            int offset = (y * VSK_9801_GRAPH_VRAM_PLANE_PITCH) + (x / CHAR_BIT);
            assert(0 <= offset && offset < VSK_9801_GRAPH_VRAM_PLANE_SIZE);
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

    // ピクセルを取得するオブジェクトを取得する
    std::shared_ptr<VskColorGetter> get_color_getter(const VskRectI *viewport) override
    {
        return std::make_shared<ColorGetter>(this, viewport);
    }

    // ピクセルをセットするオブジェクトを取得する
    std::shared_ptr<VskPixelPutter> get_color_putter(int palette, const VskRectI *viewport) override
    {
        return std::make_shared<ColorPutter>(this, palette, viewport);
    }

    // タイリングを行うヘルパークラス
    struct TilePutter : VskPixelPutter
    {
        VskMachineState *m_state = nullptr;
        const VskRectI *m_viewport = nullptr;
        VskByte *m_planes[4] = { nullptr };
        int m_num_planes = 0;
        VskString m_tile;
        int m_tile_height = 0;

        TilePutter(Vsk9801Machine *machine, VskString tile, const VskRectI *viewport)
        {
            m_state = machine->m_state;
            m_viewport = viewport ? viewport : &m_state->m_viewport;
            m_num_planes = m_state->get_graphics_num_planes();
            if (m_state->m_color_graphics)
            {
                for (int iPlane = 0; iPlane < m_num_planes; ++iPlane)
                    m_planes[iPlane] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, iPlane);
            }
            else
            {
                m_planes[0] = machine->m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, m_state->m_active_page);
            }
            m_tile = tile;
            m_tile_height = int(m_tile.size() / m_num_planes);
        }

        void operator()(int x, int y) override
        {
            if (!(m_viewport->inside(x, y)))
                return;

            int x0 = (x % CHAR_BIT);
            int y0 = (y % m_tile_height);
            int ibit = (CHAR_BIT - 1) - (x % CHAR_BIT);
            int offset = (y * VSK_9801_GRAPH_VRAM_PLANE_PITCH) + (x / CHAR_BIT);
            assert(0 <= offset && offset < VSK_9801_GRAPH_VRAM_PLANE_SIZE);

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

    // カラーグラフィック画面を描画する
    void render_color_graphics();
    // 白黒グラフィック画面を描画する
    void render_mono_graphics();

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

    // ファンクションキーをレンダリングする
    void render_function_keys();

    // テキスト画面を描画する
    void render_text();

    // 画面を描画する
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

    // マシンを接続、または接続を切断する
    bool connect(bool do_connect) override
    {
        if (do_connect)
        {
            m_text_vram = std::make_shared<Vsk9801TextVRAM>(m_state);
            m_graph_vram = std::make_shared<Vsk9801GraphVRAM>(m_state);
            m_free_area = std::make_shared<Vsk9801FreeArea>();
            m_state->m_memory->add_block(m_text_vram.get());
            m_state->m_memory->add_block(m_graph_vram.get());
            m_state->m_memory->add_block(m_free_area.get());
            VskMachine::connect(true);
        }
        else
        {
            VskMachine::connect(false);
            m_state->m_memory->remove_block(m_free_area.get());
            m_state->m_memory->remove_block(m_graph_vram.get());
            m_state->m_memory->remove_block(m_text_vram.get());
            m_free_area = nullptr;
            m_graph_vram = nullptr;
            m_text_vram = nullptr;
        }
        return true;
    }

    // ディスプレイページから表示すべきページのフラグ群を取得
    int get_display_pages_flags(int screen_mode, int display_pages) override;

    bool is_valid_screen_mode(int screen_mode) const override;
    bool is_valid_active_page(int screen_mode, int active_page, bool high_color) const override;

    // 指定したプレーンのグラフィックをクリアする
    void clear_planes(bool blue, bool red, bool green, bool intensity) override;
};

////////////////////////////////////////////////////////////////////////////////////

// コンストラクタ
Vsk9801Machine::Vsk9801Machine(VskMachineState *state, VskSettings *settings)
    : VskMachine(state, settings)
    , m_screen_image(VSK_SCREEN_WIDTH, VSK_SCREEN_HEIGHT)
{
}

// テキスト画面の消去
void Vsk9801Machine::clear_text(int y0, int y1)
{
    // 行ごとに処理
    for (int y = y0; y <= y1; ++y)
    {
        auto text_area = get_text_area(y);
        auto attr_area = get_attr_area(y);

        // { 0x00, 0x20, 0x00, 0x20 }というパターンで初期化
        size_t cdw = VSK_9801_TEXT_VRAM_PITCH / sizeof(VskDword);
        VskDword dw = 0x00200020;
        VskDword *pdw = reinterpret_cast<VskDword *>(text_area);
        while (cdw--)
            *pdw++ = dw;

        // { attr, 0, attr, 0 }というパターンで初期化
        cdw = VSK_9801_TEXT_VRAM_PITCH / sizeof(VskDword);
        auto attr = vsk_9801_byte_from_log_attr(m_state->m_text_attr);
        dw = attr | (attr << 16);
        pdw = reinterpret_cast<VskDword *>(attr_area);
        while (cdw--)
            *pdw++ = dw;

        // 行リンクを解除
        line_link(y) = 0;
    }
}

// JIS全角文字を取得
VskWord Vsk9801Machine::get_jis(int x, int y) const
{
    assert(0 <= x && x < m_state->m_text_width);
    assert(0 <= y && y < m_state->m_text_height);
#ifdef JAPAN
    int next_x, next_y;
    if (get_next_x_y(next_x, next_y, x, y))
    {
        auto text_area = get_text_area(y);
        VskByte lead, trail;
        if (m_state->m_text_wider)
        {
            lead = text_area[4 * x + 0];
            trail = text_area[4 * x + 1];
        }
        else
        {
            lead = text_area[2 * x + 0];
            trail = text_area[2 * x + 1];
        }
        if (trail & VSK_9801_TRAIL_FIX)
        {
            lead += VSK_9801_LEAD_FIX;
            trail &= ~VSK_9801_TRAIL_FIX;
            auto jis = vsk_make_word(trail, lead);
            if (vsk_is_jis_code(jis))
                return jis;
        }
    }
#endif
    return get_ank(x, y);
}

// JIS全角文字をセット
void Vsk9801Machine::set_jis(int x, int y, VskWord jis)
{
    assert(0 <= x && x < m_state->m_text_width);
    assert(0 <= y && y < m_state->m_text_height);
#ifdef JAPAN
    if (!vsk_is_jis_code(jis))
        return;

    VskByte lead = vsk_high_byte(jis), trail = vsk_low_byte(jis);
    lead -= VSK_9801_LEAD_FIX;
    trail |= VSK_9801_TRAIL_FIX;

    auto text_area = get_text_area(y);
    if (m_state->m_text_wider)
    {
        text_area[4 * x + 0] = lead;
        text_area[4 * x + 1] = trail;
    }
    else
    {
        text_area[2 * x + 0] = lead;
        text_area[2 * x + 1] = trail;
    }
    assert(!is_ank(x, y));
    return;
#endif
}

// ANK文字を描画
void Vsk9801Machine::render_ank(int x, int y, VskByte ch, const VskLogAttr& log_attr)
{
    assert(0 <= x && x < m_state->m_text_width);
    assert(0 <= y && y < m_state->m_text_height);
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
    // 文字パレット
    VskByte palette = log_attr.m_palette;
    // スクリーン描画を助けるオブジェクト
    VskScreenPutter putter(m_screen_image, m_state->text_color_to_web_color(palette));
    // 何も描画しないオブジェクト
    VskNullPutter eraser;
    // アンダーライン（下線）
    bool underline = log_attr.m_underline;
    // セミグラ文字か?
    bool is_semigra = log_attr.m_semigra;
    if (is_semigra) // セミグラ文字なら
    {
        // セミグラ文字を描画する
        VskSemiGraAnkGetter getter1;
        if (wider) // 40文字の幅か?
        {
            if (reverse) // リバースか?
                vk_draw_wide_ank(eraser, putter, x0, y0, ch, getter1, underline);
            else
                vk_draw_wide_ank(putter, eraser, x0, y0, ch, getter1, underline);
        }
        else
        {
            if (reverse) // リバースか?
                vk_draw_ank(eraser, putter, x0, y0, ch, getter1, underline);
            else
                vk_draw_ank(putter, eraser, x0, y0, ch, getter1, underline);
        }
    }
    else // 通常文字か?
    {
        // 通常のANK文字を描画する
        Vsk9801AnkGetter getter0;
        if (wider) // 40文字の幅か?
        {
            if (reverse) // リバースか?
                vk_draw_wide_ank(eraser, putter, x0, y0, ch, getter0, underline);
            else
                vk_draw_wide_ank(putter, eraser, x0, y0, ch, getter0, underline);
        }
        else
        {
            if (reverse) // リバースか?
                vk_draw_ank(eraser, putter, x0, y0, ch, getter0, underline);
            else
                vk_draw_ank(putter, eraser, x0, y0, ch, getter0, underline);
        }
    }

    // リバースかつ20文字の高さのときに、反転している文字の下部を描画する
    if (reverse && longer)
    {
        vsk_fill_box(putter, x0, y0 + char_height - 4, x0 + char_width - 1, y0 + char_height - 1);
    }
}

// JIS全角文字を描画
void Vsk9801Machine::render_jis(int x, int y, int next_x, int next_y, VskWord jis, const VskLogAttr& log_attr)
{
    assert(0 <= x && x < m_state->m_text_width);
    assert(0 <= y && y < m_state->m_text_height);
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
    int x1 = next_x * char_width, y1 = next_y * char_height;
    // テキストの色
    VskByte palette = log_attr.m_palette;
    // スクリーン描画を助けるオブジェクト
    VskScreenPutter putter(m_screen_image, m_state->text_color_to_web_color(palette));
    // 漢字のイメージを取得するオブジェクト
    VskKanjiGetter getter;
    // 何も描画しないオブジェクト
    VskNullPutter eraser;
    // アンダーライン（下線）
    bool underline = log_attr.m_underline;
    if (wider) // 40文字の幅か?
    {
        if (reverse) // リバースか?
            vk_draw_wide_jis(eraser, putter, x0, y0, x1, y1, jis, getter, underline);
        else
            vk_draw_wide_jis(putter, eraser, x0, y0, x1, y1, jis, getter, underline);
    }
    else
    {
        if (reverse) // リバースか?
            vk_draw_jis(eraser, putter, x0, y0, x1, y1, jis, getter, underline);
        else
            vk_draw_jis(putter, eraser, x0, y0, x1, y1, jis, getter, underline);
    }

    // リバースかつ20文字の高さのときに、反転している文字の下部を描画する
    if (reverse && longer)
    {
        vsk_fill_box(putter, x0, y0 + char_height - 4, x0 + char_width - 1, y0 + char_height - 1);
        vsk_fill_box(putter, x1, y1 + char_height - 4, x1 + char_width - 1, y1 + char_height - 1);
    }
#endif
}

// ファンクションキーをレンダリングする
void Vsk9801Machine::render_function_keys()
{
    if (!m_state->m_show_function_keys)
        return;

    int y = m_state->m_text_height - 1; // ファンクションキーの行のインデックス
    const bool shift = vsk_is_shift_pressed(); // シフトキーが押されているか？

    // ファンクションキーの行のテキストをクリア
    auto* attr_area = get_attr_area(y);
    VskByte attr = VSK_9801_ATTR_SHOW | VSK_9801_ATTR_SET_COLOR(7);
    for (int x = 0; x < m_state->m_text_width; ++x)
    {
        set_ank(x, y, ' ');
        attr_area[2 * x] = attr;
        attr_area[2 * x] &= ~VSK_9801_ATTR_REVERSE;;
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
            attr_area[(x + ich) * 2] |= VSK_9801_ATTR_REVERSE;

        // キーのテキストをセット
        auto key = m_state->m_function_keys[key_no - 1];
        for (int ich = 0; ich < cx - delta_text; ++ich)
        {
            if (ich < int(key.size()))
                set_ank(x + ich + delta_text, y, key[ich]);
        }
    }
}

// パレットのリセット
void Vsk9801Machine::reset_palette()
{
    switch (m_state->m_palette_mode)
    {
    case VSK_PAL_MODE_8_COLORS_DIGITAL:
    case VSK_PAL_MODE_8_COLORS_SUPER:
        for (int i = 0; i < _countof(m_state->m_palette); ++i)
            m_state->m_palette[i] = vsk_get_default_digital_color_8(i);
        break;
    case VSK_PAL_MODE_16_COLORS_SUPER:
        for (int i = 0; i < _countof(m_state->m_palette); ++i)
            m_state->m_palette[i] = vsk_get_default_digital_color_16(i);
        break;
    }
}

// テキスト画面のリセット
void Vsk9801Machine::reset_text()
{
    m_state->m_text_wider = (m_state->m_text_width == 40);
    m_state->m_text_longer = (m_state->m_text_height == 20);

    if (m_state->m_console_y0 + m_state->m_console_cy0 > m_state->m_text_height - m_state->m_show_function_keys)
        m_state->m_console_cy0 = m_state->m_text_height - m_state->m_show_function_keys - m_state->m_console_y0;
}

static void vsk_reset_graphics_9801(VskMachineState *state, int width, int height, bool color)
{
    state->m_screen_width = width;
    state->m_screen_height = height;
    state->m_color_graphics = color;
    state->m_viewport = { 0, 0, VskInt(width - 1), VskInt(height - 1) };
    state->m_window = { 0, 0, VskSingle(width - 1), VskSingle(height - 1) };
}

// グラフィック画面のリセット
void Vsk9801Machine::reset_graphics()
{
    switch (m_state->m_screen_mode)
    {
    case 0: vsk_reset_graphics_9801(m_state, 640, 200, true); break;
    case 1: vsk_reset_graphics_9801(m_state, 640, 200, false); break;
    case 2: vsk_reset_graphics_9801(m_state, 640, 400, false); break;
    case 3: vsk_reset_graphics_9801(m_state, 640, 400, true); break;
    default: assert(0); break;
    }

    m_state->m_display_pages_flags = get_display_pages_flags(m_state->m_screen_mode, m_state->m_display_pages);
}

// テキスト画面を描画する
void Vsk9801Machine::render_text()
{
    if (!m_state->m_show_text)
        return;

    render_function_keys();

    for (int y = 0; y < m_state->m_text_height; ++y)
    {
        auto text_area = get_text_area(y);
        for (int x = 0; x < m_state->m_text_width; ++x)
        {
            auto attr_area = get_attr_area(y);
            auto attr = attr_area[2 * x];
            int next_x, next_y;
            if (get_next_x_y(next_x, next_y, x, y))
            {
                VskByte lead, trail;
                if (m_state->m_text_wider)
                {
                    lead = text_area[4 * x + 0];
                    trail = text_area[4 * x + 1];
                }
                else
                {
                    lead = text_area[2 * x + 0];
                    trail = text_area[2 * x + 1];
                }
#ifdef JAPAN
                if (trail & VSK_9801_TRAIL_FIX)
                {
                    lead += VSK_9801_LEAD_FIX;
                    trail &= ~VSK_9801_TRAIL_FIX;
                    VskWord jis = vsk_make_word(trail, lead);
                    if (vsk_is_jis_code(jis))
                    {
                        render_jis(x, y, next_x, next_y, jis, attr);

                        x = next_x;
                        y = next_y;
                        text_area = get_text_area(y);
                        continue;
                    }
                }
#endif
            }
            auto ch = get_ank(x, y);
#if 0
            if (line_link(y) && x == m_state->m_text_width - 1)
                ch = '>';
#endif
            render_ank(x, y, ch, attr);
        }
    }
}

// カラーグラフィック画面を描画する
void Vsk9801Machine::render_color_graphics()
{
    int screen_mode = m_state->m_screen_mode;
    int display_page = m_graph_vram->get_color_display_page(screen_mode, m_state->m_display_pages);
    if (display_page < 0)
        return;
    VskByte *plane0 = m_graph_vram->get_page(screen_mode, display_page, 0);
    VskByte *plane1 = m_graph_vram->get_page(screen_mode, display_page, 1);
    VskByte *plane2 = m_graph_vram->get_page(screen_mode, display_page, 2);
    VskByte *plane3 = m_graph_vram->get_page(screen_mode, display_page, 3);
    if (m_state->m_screen_height == 400)
    {
        for (int y = 0; y < m_state->m_screen_height; ++y)
        {
            VskByte *byte0 = &plane0[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
            VskByte *byte1 = &plane1[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
            VskByte *byte2 = &plane2[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
            VskByte *byte3 = &plane3[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
            for (int x = 0; x < m_state->m_screen_width; x += CHAR_BIT)
            {
                for (int i = 0; i < CHAR_BIT; ++i)
                {
                    int ibit = ((CHAR_BIT - 1) - i);
                    VskByte b0 = ((byte0[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte b1 = ((byte1[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte b2 = ((byte2[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte b3 = ((byte3[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte byte = (b0 | (b1 << 1) | (b2 << 2) | (b3 << 3));
                    auto sys_color = vsk_fix_color(m_state->palette_to_web_color(byte));
                    m_screen_image.set_pixel(x + i, y, sys_color);
                }
            }
        }
    }
    else
    {
        for (int y = 0; y < m_state->m_screen_height; ++y)
        {
            for (int x = 0; x < m_state->m_screen_width; x += CHAR_BIT)
            {
                VskByte* byte0 = &plane0[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
                VskByte* byte1 = &plane1[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
                VskByte* byte2 = &plane2[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
                VskByte* byte3 = &plane3[y * VSK_9801_GRAPH_VRAM_PLANE_PITCH];
                for (int i = 0; i < CHAR_BIT; ++i)
                {
                    int ibit = ((CHAR_BIT - 1) - i);
                    VskByte b0 = ((byte0[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte b1 = ((byte1[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte b2 = ((byte2[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte b3 = ((byte3[x / CHAR_BIT] >> ibit) & 0x1);
                    VskByte byte = (b0 | (b1 << 1) | (b2 << 2) | (b3 << 3));
                    auto sys_color = vsk_fix_color(m_state->palette_to_web_color(byte));
                    m_screen_image.set_pixel(x + i, y * 2, sys_color);
                    if (VSK_SETTINGS()->m_draw_odd_lines)
                        m_screen_image.set_pixel(x + i, y * 2 + 1, sys_color);
                }
            }
        }
    }
}

// 白黒グラフィック画面を描画する
void Vsk9801Machine::render_mono_graphics()
{
    int display_flags = m_state->m_display_pages_flags;
    if (display_flags <= 0)
        return;

    if (m_state->m_screen_height == 400)
    {
        for (int iPage = 0; iPage < 12; ++iPage)
        {
            if (!(display_flags & (1 << iPage)))
                continue;
            VskByte *page = m_graph_vram->get_page(m_state->m_screen_mode, iPage);
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
    }
    else
    {
        for (int iPage = 0; iPage < 12; ++iPage)
        {
            if (!(display_flags & (1 << iPage)))
                continue;
            VskByte *page = m_graph_vram->get_page(m_state->m_screen_mode, iPage);
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

// スクリーンモードが正しいか？
bool Vsk9801Machine::is_valid_screen_mode(int screen_mode) const
{
    return 0 <= screen_mode && screen_mode <= 3;
}

// 描画ページが正しいか？
bool Vsk9801Machine::is_valid_active_page(int screen_mode, int active_page, bool high_color) const
{
    if (high_color)
    {
        switch (screen_mode)
        {
        case 0: return (0 <= active_page && active_page <= 3);
        case 1: return (0 <= active_page && active_page <= 15);
        case 2: return (0 <= active_page && active_page <= 7);
        case 3: return (0 <= active_page && active_page <= 1);
        }
    }
    else
    {
        switch (screen_mode)
        {
        case 0: return (0 <= active_page && active_page <= 3);
        case 1: return (0 <= active_page && active_page <= 11);
        case 2: return (0 <= active_page && active_page <= 5);
        case 3: return (0 <= active_page && active_page <= 1);
        }
    }
    assert(0);
    return false;
}

// ディスプレイページから表示すべきページのフラグ群を取得
int Vsk9801Machine::get_display_pages_flags(int screen_mode, int display_pages)
{
    switch (screen_mode)
    {
    case 0:
        switch (display_pages)
        {
        case 0: case 8: case 16: case 24:
            return 0;
        case 1: return (1 << 0);
        case 2: return (1 << 1);
        case 17: return (1 << 2);
        case 18: return (1 << 3);
        default:
            return -1;
        }
        break;
    case 1:
        switch (display_pages)
        {
        case 0: case 8: case 16: case 24:
            return 0;
        case 1: return (1 << 0);
        case 2: return (1 << 1);
        case 3: return (1 << 0) | (1 << 1);
        case 4: return (1 << 2);
        case 5: return (1 << 0) | (1 << 2);
        case 6: return (1 << 1) | (1 << 2);
        case 7: return (1 << 0) | (1 << 1) | (1 << 2);
        case 9: return (1 << 3);
        case 10: return (1 << 4);
        case 11: return (1 << 3) | (1 << 4);
        case 12: return (1 << 5);
        case 13: return (1 << 3) | (1 << 5);
        case 14: return (1 << 4) | (1 << 5);
        case 15: return (1 << 3) | (1 << 4) | (1 << 5);
        case 17: return (1 << 6);
        case 18: return (1 << 7);
        case 19: return (1 << 6) | (1 << 7);
        case 20: return (1 << 8);
        case 21: return (1 << 6) | (1 << 8);
        case 22: return (1 << 7) | (1 << 8);
        case 23: return (1 << 6) | (1 << 7) | (1 << 8);
        case 25: return (1 << 9);
        case 26: return (1 << 10);
        case 27: return (1 << 9) | (1 << 10);
        case 28: return (1 << 11);
        case 29: return (1 << 9) | (1 << 11);
        case 30: return (1 << 10) | (1 << 11);
        case 31: return (1 << 9) | (1 << 10) | (1 << 11);
        }
        break;
    case 2:
        switch (display_pages)
        {
        case 0: case 8: case 16: case 24:
            return 0;
        case 1: return (1 << 0);
        case 2: return (1 << 1);
        case 3: return (1 << 0) | (1 << 1);
        case 4: return (1 << 2);
        case 5: return (1 << 0) | (1 << 2);
        case 6: return (1 << 1) | (1 << 2);
        case 7: return (1 << 0) | (1 << 1) | (1 << 2);
        case 17: return (1 << 3);
        case 18: return (1 << 4);
        case 19: return (1 << 3) | (1 << 4);
        case 20: return (1 << 5);
        case 21: return (1 << 3) | (1 << 5);
        case 22: return (1 << 4) | (1 << 5);
        case 23: return (1 << 3) | (1 << 4) | (1 << 5);
        }
        break;
    case 3:
        switch (display_pages)
        {
        case 0: case 8: case 16: case 24:
            return 0;
        case 1: return (1 << 0);
        case 17: return (1 << 1);
        }
        break;
    }
    return -1;
}

// 指定したプレーンのグラフィックをクリアする
void Vsk9801Machine::clear_planes(bool blue, bool red, bool green, bool intensity)
{
    VskByte *planes[4] = {
        m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 0),
        m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 1),
        m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 2),
        m_graph_vram->get_page(m_state->m_screen_mode, m_state->m_active_page, 3)
    };
    if (blue)
    {
        std::memset(planes[0], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    }
    if (red)
    {
        std::memset(planes[1], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    }
    if (green)
    {
        std::memset(planes[2], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    }
    if (intensity)
    {
        std::memset(planes[3], 0, m_state->m_screen_width * m_state->m_screen_height / CHAR_BIT);
    }
}

// システムのリセット
void Vsk9801Machine::reset()
{
    m_state->m_segment = 0;

    auto sw1 = VSK_SETTINGS()->m_9801_sw1;
    auto sw2 = VSK_SETTINGS()->m_9801_sw2;

    m_state->m_text_width = (sw2 & 0x20) ? 80 : 40;
    m_state->m_text_height = (sw2 & 0x10) ? 25 : 20;

    m_state->m_console_y0 = 0;
    m_state->m_console_cy0 = 25;

    reset_palette();
    reset_text();
    reset_graphics();

    m_state->m_color_text   = false;
    m_state->m_text_attr.reset();
    m_state->m_text_color   = 7;
    m_state->m_fore_color   = 7;
    m_state->m_back_color   = 0;
    m_state->m_border_color = -1;

    clear_graphic();
    clear_text();
    move_to_top();

    test_pattern(0);
}

////////////////////////////////////////////////////////////////////////////////////

// 9801 マシンを作成する関数
std::shared_ptr<VskMachine> vsk_create_9801_machine(VskMachineState *state, VskSettings *settings)
{
    return std::make_shared<Vsk9801Machine>(state, settings);
}

////////////////////////////////////////////////////////////////////////////////////

// フリーエリアの最後のアドレス
VskDword Vsk9801Machine::get_free_ubound()
{
    return VSK_9801_FREE_AREA_END_MAX;
}

// フリーエリアのサイズ
VskDword Vsk9801Machine::get_free_size()
{
    return (get_free_ubound() - VSK_9801_FREE_AREA_START + 1);
}

bool Vsk9801Machine::special_memory_read(VskByte *ptr, VskAddr addr)
{
    return false;
}

bool Vsk9801Machine::clear_memory(VskDword addr)
{
    if (!(addr <= VSK_9801_FREE_AREA_END_MAX))
        return false;

    m_free_area->clear();
    return true;
}

#endif  // def ENABLE_VM9801
