#include "VeySicK.h"
#include "draw_algorithm.h"
#include "random.h"
#include "sound.h"

//////////////////////////////////////////////////////////////////////////////
// Color - 色（カラー）

// 9801のモノクロ16色の初期値
static const VskWebColor vsk_default_colors_mono[16] =
{             //                       GRB
    0x000000, //  #0: Black         (&H000)
    0xFFFFFF, //  #1: White         (&HFFF)
    0xFFFFFF, //  #2: White         (&HFFF)
    0xFFFFFF, //  #3: White         (&HFFF)
    0xFFFFFF, //  #4: White         (&HFFF)
    0xFFFFFF, //  #5: White         (&HFFF)
    0xFFFFFF, //  #6: White         (&HFFF)
    0xFFFFFF, //  #7: White         (&HFFF)
    0xFFFFFF, //  #8: White         (&HFFF)
    0xFFFFFF, //  #9: White         (&HFFF)
    0xFFFFFF, // #10: White         (&HFFF)
    0xFFFFFF, // #11: White         (&HFFF)
    0xFFFFFF, // #12: White         (&HFFF)
    0xFFFFFF, // #13: White         (&HFFF)
    0xFFFFFF, // #14: White         (&HFFF)
    0xFFFFFF, // #15: White         (&HFFF)
};

// 9801のデジタル8色の初期値
static const VskWebColor vsk_default_colors_digital_8[16] =
{             //                       GRB
    0x000000, //  #0: Black         (&H000)
    0x0000FF, //  #1: Light Blue    (&H00F)
    0xFF0000, //  #2: Light Red     (&H0F0)
    0xFF00FF, //  #3: Light Magenta (&H0FF)
    0x00FF00, //  #4: Light Green   (&HF00)
    0x00FFFF, //  #5: Light Cyan    (&HF0F)
    0xFFFF00, //  #6: Light Yellow  (&HFF0)
    0xFFFFFF, //  #7: Light White   (&HFFF)
    0x000000, //  #8: Black         (&H000)
    0x0000FF, //  #9: Light Blue    (&H00F)
    0xFF0000, // #10: Light Red     (&H0F0)
    0xFF00FF, // #11: Light Magenta (&H0FF)
    0x00FF00, // #12: Light Green   (&HF00)
    0x00FFFF, // #13: Light Cyan    (&HF0F)
    0xFFFF00, // #14: Light Yellow  (&HFF0)
    0xFFFFFF, // #15: Light White   (&HFFF)
};

// 9801のデジタル16色の初期値
static const VskWebColor vsk_default_colors_digital_16[16] =
{             //                       GRB
    0x000000, //  #0: Black         (&H000)
    0x0000FF, //  #1: Light Blue    (&H00F)
    0xFF0000, //  #2: Light Red     (&H0F0)
    0xFF00FF, //  #3: Light Magenta (&H0FF)
    0x00FF00, //  #4: Light Green   (&HF00)
    0x00FFFF, //  #5: Light Cyan    (&HF0F)
    0xFFFF00, //  #6: Light Yellow  (&HFF0)
    0xFFFFFF, //  #7: Light White   (&HFFF)
    0x777777, //  #8: Gray          (&H777)
    0x0000AA, //  #9: Dark Blue     (&H00A)
    0xAA0000, // #10: Dark Red      (&H0A0)
    0xAA00AA, // #11: Dark Magenta  (&H0AA)
    0x00AA00, // #12: Dark Green    (&HA00)
    0x00AAAA, // #13: Dark Cyan     (&HA0A)
    0xAAAA00, // #14: Dark Yellow   (&HAA0)
    0xAAAAAA, // #15: Dark White    (&HAAA)
};

VskWebColor vsk_get_default_mono_color(int palette)
{
    assert(0 <= palette && palette < 16);
    return vsk_default_colors_mono[palette];
}

VskWebColor vsk_get_default_digital_color_8(int palette)
{
    assert(0 <= palette && palette < 16);
    return vsk_default_colors_digital_8[palette];
}

VskWebColor vsk_get_default_digital_color_16(int palette)
{
    assert(0 <= palette && palette < 16);
    return vsk_default_colors_digital_16[palette];
}

// アナログ16色の初期値
static const VskWebColor vsk_default_colors_analog_16[16] =
{             //                       GRB
    0x000000, //  #0: Black         (&H000)
    0x000077, //  #1: Dark Blue     (&H007)
    0x770000, //  #2: Dark Red      (&H070)
    0x770077, //  #3: Dark Magenta  (&H077)
    0x007700, //  #4: Dark Green    (&H700)
    0x007777, //  #5: Dark Cyan     (&H707)
    0x777700, //  #6: Dark Yellow   (&H770)
    0x777777, //  #7: Dark White    (&H777)
    0x444444, //  #8: Light Black   (&H444)
    0x0000FF, //  #9: Light Blue    (&H00F)
    0xFF0000, // #10: Light Red     (&H0F0)
    0xFF00FF, // #11: Light Magenta (&H0FF)
    0x00FF00, // #12: Light Green   (&HF00)
    0x00FFFF, // #13: Light Cyan    (&HF0F)
    0xFFFF00, // #14: Light Yellow  (&HFF0)
    0xFFFFFF, // #15: Light White   (&HFFF)
};

VskWebColor vsk_get_default_analog_color_16(VskByte palette)
{
    assert(0 <= palette && palette < 16);
    return vsk_default_colors_analog_16[palette];
}

int VskMachineState::get_graphics_num_planes() const
{
    if (!m_color_graphics)
        return 1;

    switch (m_color_mode)
    {
    case VSK_COLOR_MODE_8_COLORS_DIGITAL: return 3;
    case VSK_COLOR_MODE_8_COLORS_SUPER: return 3;
    case VSK_COLOR_MODE_16_COLORS_SUPER: return 4;
    }
    return 0;
}

VskWebColor VskMachineState::text_color_to_web_color(VskByte palette) const
{
    assert(palette < _countof(vsk_default_colors_digital_8));
    return vsk_default_colors_digital_8[palette];
}

VskWebColor VskMachineState::palette_to_web_color(VskByte palette) const
{
    assert(palette < _countof(m_palette));
    return m_palette[palette];
}

VskWebColor VskMachineState::color_code_to_web_color(VskDword color_code) const
{
    VskWebColor web_color;
    if (!vsk_machine->is_valid_color_code(color_code, web_color))
        return 0;
    return web_color;
}

//////////////////////////////////////////////////////////////////////////////
// basic types

size_t vsk_get_type_size(VskType type)
{
    switch (type)
    {
    case VSK_TYPE_SINGLE: return sizeof(VskSingle);
    case VSK_TYPE_DOUBLE: return sizeof(VskDouble);
    case VSK_TYPE_INTEGER: return sizeof(VskInt);
    case VSK_TYPE_STRING: return sizeof(VskStringDesc);
#ifdef ENABLE_LONG
    case VSK_TYPE_LONG: return sizeof(VskLong);
#endif
    default: return 0;
    }
}

//////////////////////////////////////////////////////////////////////////////
// VskObject

long VskObject::s_cAliveObjects = 0;

VskObject::VskObject()
{
    //mdbg_printfA("VskObject::VskObject: %p\n", this);
    ++s_cAliveObjects;
}

VskObject::~VskObject()
{
    //mdbg_printfA("VskObject::~VskObject: %p\n", this);
    --s_cAliveObjects;
}

//////////////////////////////////////////////////////////////////////////////
// vsk_to_string - 文字列に変換

VskString vsk_to_string(VskShort sht)
{
    return std::to_string(sht);
}

VskString vsk_to_string(VskWord wrd)
{
    return std::to_string(wrd);
}

VskString vsk_to_string(VskLong lng)
{
    return std::to_string(lng);
}

VskString vsk_to_string(VskDword dwd)
{
    return std::to_string(dwd);
}

VskString vsk_to_string(VskSingle sng)
{
    char buf[256];
    std::sprintf(buf, "%G", sng);
    return VskString(buf);
}

VskString vsk_to_string(VskDouble dbl)
{
    char buf[256];
    std::sprintf(buf, "%.16G", dbl);
    VskString str = buf;
    mstr_replace_all(str, "E", "D");
    return str;
}

VskString vsk_to_string(const VskString& str)
{
    return str;
}

//////////////////////////////////////////////////////////////////////////////
// VskRect - 長方形

template <typename T_VALUE>
bool VskRect<T_VALUE>::intersect(const VskRect<T_VALUE>& other)
{
    if (empty() || other.empty() ||
        m_x0 > other.m_x1 || other.m_x0 > m_x1 ||
        m_y0 > other.m_y1 || other.m_y0 > m_y1)
    {
        set_empty();
        return false;
    }

    m_x0 = std::max(m_x0, other.m_x0);
    m_x1 = std::min(m_x1, other.m_x1);
    m_y0 = std::max(m_y0, other.m_y0);
    m_y1 = std::min(m_y1, other.m_y1);
    assert(!empty());
    return true;
}

//////////////////////////////////////////////////////////////////////////////
// vsk_abc_to_kana

// ABCを半角カナに変換
VskByte vsk_abc_to_kana(VskByte ch, bool shift)
{
    if (shift)
    {
        switch (ch)
        {
        case ' ': return ' ';       // Space
        case '#': return 0xA7;      // small A
        case '$': return 0xA9;      // small U
        case '%': return 0xAA;      // small E
        case '&': return 0xAB;      // small O
        case '\'': return 0xAC;     // small YA
        case '(': return 0xAD;      // small YU
        case ')': return 0xAE;      // small YO
        case '0': case '~': return 0xA6;    // WO
        case 'E': case 'e': return 0xA8;    // small I
        case '\\': case '-': case '_': return 0xB0;   // prolonged sound
        case '[': case '{': return 0xA2;    // left bracket
        case ']': case '}': return 0xA3;    // right bracket
        case 'Z': case 'z': return 0xAF;    // small TSU
        case '<': case ',': return 0xA4;    // Japanese comma
        case '>': case '.': return 0xA1;    // Japanese period
        case '?': case '/': return 0xA5;    // center dot
        default: return 0;
        }
    }

    switch (ch)
    {
    case ' ': return ' ';       // Space
    case '1': return 0xC7;      // NU
    case '2': return 0xCC;      // FU
    case '3': return 0xB1;      // A
    case '4': return 0xB3;      // U
    case '5': return 0xB4;      // E
    case '6': return 0xB5;      // O
    case '7': return 0xD4;      // YA
    case '8': return 0xD5;      // YU
    case '9': return 0xD6;      // YO
    case '0': return 0xDC;      // WA
    case '-': return 0xCE;      // HO
    case '^': return 0xCD;      // HE
    case '|': return 0xB0;      // prolonged sound

    case 'Q': case 'q': return 0xC0;      // TA
    case 'W': case 'w': return 0xC3;      // TE
    case 'E': case 'e': return 0xB2;      // I
    case 'R': case 'r': return 0xBD;      // SU
    case 'T': case 't': return 0xB6;      // KA
    case 'Y': case 'y': return 0xDD;      // N
    case 'U': case 'u': return 0xC5;      // NA
    case 'I': case 'i': return 0xC6;      // NI
    case 'O': case 'o': return 0xD7;      // RA
    case 'P': case 'p': return 0xBE;      // SE
    case '`': case '@': return 0xDE;      // voiced consonant
    case '{': case '[': return 0xDF;      // small circle

    case 'A': case 'a': return 0xC1;      // CHI
    case 'S': case 's': return 0xC4;      // TO
    case 'D': case 'd': return 0xBC;      // SHI
    case 'F': case 'f': return 0xCA;      // HA
    case 'G': case 'g': return 0xB7;      // KI
    case 'H': case 'h': return 0xB8;      // KU
    case 'J': case 'j': return 0xCF;      // MA
    case 'K': case 'k': return 0xC9;      // NO
    case 'L': case 'l': return 0xD8;      // RI
    case '+': case ';': return 0xDA;      // RE
    case '*': case ':': return 0xB9;      // KE
    case '}': case ']': return 0xD1;      // MU

    case 'Z': case 'z': return 0xC2;      // TSU
    case 'X': case 'x': return 0xBB;      // SA
    case 'C': case 'c': return 0xBF;      // SO
    case 'V': case 'v': return 0xCB;      // HI
    case 'B': case 'b': return 0xBA;      // KO
    case 'N': case 'n': return 0xD0;      // MI
    case 'M': case 'm': return 0xD3;      // MO
    case '<': case ',': return 0xC8;      // NE
    case '>': case '.': return 0xD9;      // RU
    case '?': case '/': return 0xD2;      // ME
    case '_': case '\\': return 0xDB;     // RO

    default: return 0;
    }
} // vsk_abc_to_kana

//////////////////////////////////////////////////////////////////////////////
// マシン

VskMachinePtr vsk_machine;

std::shared_ptr<VskMachineImpl> vsk_create_machine_impl(void);

VskMachineState::VskMachineState()
    : m_memory(std::make_shared<VskMemoryModel>())
{
    vsk_vars_map = std::make_shared<VskVarMap>();
    m_pimpl = vsk_create_machine_impl();
}

VskMachineState::VskMachineState(VskMachineMode mode)
    : m_memory(std::make_shared<VskMemoryModel>())
{
    vsk_vars_map = std::make_shared<VskVarMap>();
    m_pimpl = vsk_create_machine_impl();
    m_machine_mode = mode;
}

VskMachineState::~VskMachineState()
{
    m_pimpl = nullptr;
    vsk_vars_map = nullptr;
}

VskMachine::VskMachine(VskMachineState *state) : m_state(state)
{
}

VskMachine::~VskMachine()
{
}

// マシンを作成する
VskMachinePtr VskMachine::create_machine(VskMachineState *state)
{
#ifdef ENABLE_PC8801
    if (state->m_machine_mode == VSK_MACHINE_MODE_8801)
        return vsk_create_8801_machine(state);
#endif
#ifdef ENABLE_PC9801
    if (state->m_machine_mode == VSK_MACHINE_MODE_9801)
        return vsk_create_9801_machine(state);
#endif
#ifdef ENABLE_PC8801
    state->m_machine_mode = VSK_MACHINE_MODE_9801;
    return vsk_create_9801_machine(state);
#elif defined(ENABLE_PC9801)
    state->m_machine_mode = VSK_MACHINE_MODE_8801;
    return vsk_create_8801_machine(state);
#else
    return nullptr;
#endif
}

// マシンの接続または接続の切断
bool vsk_connect_machine(VskMachineState *state, bool do_connect)
{
    if (do_connect)
    {
        vsk_init_sound();
        vsk_init_rand(0);

        vsk_lock();
        vsk_machine = VskMachine::create_machine(state);
        vsk_machine->connect(true);
        vsk_unlock();
    }
    else
    {
        vsk_lock();
        vsk_machine->connect(false);
        vsk_machine = nullptr;
        vsk_unlock();

        vsk_exit_sound();
    }
    return true;
}

// テキスト画面において１つ次のx-y位置を取得する
bool VskMachine::get_next_x_y(int& next_x, int& next_y, int x, int y) const
{
    if (x + 1 < m_state->m_text_width)
    {
        next_x = x + 1;
        next_y = y;
        return true;
    }
    if (y + 1 < m_state->m_text_height)
    {
        next_x = 0;
        next_y = y + 1;
        return true;
    }
    next_x = x;
    next_y = y;
    return false;
}

// テキスト画面において１つ前のx-y位置を取得する
bool VskMachine::get_prev_x_y(int& prev_x, int& prev_y, int x, int y) const
{
    if (x > 0)
    {
        prev_x = x - 1;
        prev_y = y;
        return true;
    }
    if (y > 0)
    {
        prev_x = m_state->m_text_width - 1;
        prev_y = y - 1;
        return true;
    }
    prev_x = x;
    prev_y = y;
    return false;
}

// HELPキーが押されたときの処理
void VskMachine::help()
{
    vsk_help();
}

// １つ前の単語へ移動
void VskMachine::back_word()
{
    int x = m_state->m_caret_x, y = m_state->m_caret_y;
    while (get_prev_x_y(x, y, x, y))
    {
        fix_text_pos(x, y, false);
        if (y < m_state->m_console_y0)
            break;
        auto ank = get_ank(x, y);
        if (!vsk_isalnum(ank))
            continue;
        if (x == 0)
        {
            assert(y >= 0);
            m_state->m_caret_x = x;
            m_state->m_caret_y = y;
            return;
        }
        ank = get_ank(x - 1, y);
        if (!vsk_isalnum(ank))
        {
            assert(y >= 0);
            m_state->m_caret_x = x;
            m_state->m_caret_y = y;
            return;
        }
    }
}

// １つ次の単語へ移動
void VskMachine::forward_word()
{
    int x = m_state->m_caret_x, y = m_state->m_caret_y;
    while (get_next_x_y(x, y, x, y))
    {
        fix_text_pos(x, y, true);
        if (y >= m_state->m_console_y0 + m_state->m_console_cy0)
            break;
        auto ank = get_ank(x, y);
        if (!vsk_isalnum(ank))
            continue;
        if (x == 0)
        {
            assert(y >= 0);
            m_state->m_caret_x = x;
            m_state->m_caret_y = y;
            return;
        }
        ank = get_ank(x - 1, y);
        if (!vsk_isalnum(ank))
        {
            assert(y >= 0);
            m_state->m_caret_x = x;
            m_state->m_caret_y = y;
            return;
        }
    }
}

// キャレット位置の単語を消す
void VskMachine::delete_word()
{
    for (;;)
    {
        auto ank = get_ank(m_state->m_caret_x, m_state->m_caret_y);
        if (!vsk_isalnum(ank))
            break;
        do_delete();
    }
}

// 行テキスト内の横位置を取得
int VskMachine::get_line_column() const
{
    int root = get_line_root(m_state->m_caret_y);
    int x = m_state->m_caret_x, y = m_state->m_caret_y;
#ifdef JAPAN
    fix_text_pos(x, y, false);
#endif
    return (y - root) * m_state->m_text_width + x;
}

// 論理行の横位置をセットする
void VskMachine::set_line_column(int column)
{
    int root = get_line_root(m_state->m_caret_y);
    int& x = m_state->m_caret_x;
    int& y = m_state->m_caret_y;
    y = root + (column / m_state->m_text_width);
    x = column % m_state->m_text_width;
    fix_caret_pos(false);
}

// 入力テキストを取得する
VskString VskMachine::get_input_text() const
{
    auto text = get_line_text(m_state->m_caret_y);
    if (text.find(m_state->m_input_prompt) == 0)
    {
        text.erase(0, m_state->m_input_prompt.size());
    }
    mstr_trim(text, " \t\r\n");
    return text;
}

// キャレットの現在位置から１字消す
void VskMachine::do_delete()
{
    auto text = get_line_text(m_state->m_caret_y);
    int column = get_line_column();
#ifdef JAPAN
    if (vsk_is_sjis_code(text[column], text[column + 1]))
        text.erase(column, 1);
#endif
    text.erase(column, 1);
    set_line_text(m_state->m_caret_y, text);
}

// 行テキストの根本の行を取得
int VskMachine::get_line_root(int y) const
{
    while (y > m_state->m_console_y0)
    {
        if (!line_link(y - 1))
            break;
        --y;
    }
    return y;
}

// 行テキストを取得
VskString VskMachine::get_line_text(int y) const
{
    VskString ret;
    bool was_lead = false;
    for (y = get_line_root(y); y < m_state->m_console_y0 + m_state->m_console_cy0; ++y)
    {
        for (int x = 0; x < m_state->m_text_width; ++x)
        {
#ifdef JAPAN
            if (was_lead)
            {
                was_lead = false;
                continue;
            }
            if (!is_ank(x, y))
            {
                auto jis = get_jis(x, y);
                assert(vsk_is_jis_code(jis));
                auto sjis = vsk_jis2sjis(jis);
                assert(vsk_is_sjis_code(sjis));
                ret += vsk_high_byte(sjis);
                ret += vsk_low_byte(sjis);
                was_lead = true;
                continue;
            }
#endif
            ret += get_ank(x, y);
        }

        if (!line_link(y))
            break;
    }
    return ret;
}

// ホームポジションへ移動
void VskMachine::move_to_top()
{
    m_state->m_caret_x = 0;
    m_state->m_caret_y = m_state->m_console_y0;
}

// 画面の下の方に移動
void VskMachine::move_to_bottom()
{
    // テキスト画面を逆順にスキャン
    for (int y = m_state->m_console_y0 + m_state->m_console_cy0 - 1;
         y >= m_state->m_console_y0;
         --y)
    {
        auto text = get_line_text(y);
        mstr_trim_right(text, " \t");
        if (text.size()) // 何か、空白以外の文字がある
        {
            // そこの一つ下にキャレットを移動
            m_state->m_caret_x = 0;
            m_state->m_caret_y = y + 1;
            break;
        }
    }
}

// 下にスクロールする
void VskMachine::scroll_down()
{
    scroll_down(m_state->m_console_y0, m_state->m_console_y0 + m_state->m_console_cy0 - 1);
}

// 編集モードでROLLUPが押された
void VskMachine::edit_up()
{
    VskLineNo line_number = 0;
    int y;

    // テキスト画面をスキャン
    for (y = m_state->m_console_y0;
         y < m_state->m_console_y0 + m_state->m_console_cy0;
         ++y)
    {
        auto text = get_line_text(y);
        mstr_trim_right(text, " \t\r\n");
        line_number = vsk_line_number_from_line_text(text);
        if (line_number)
            break;
    }

    if (y >= m_state->m_console_y0 + m_state->m_console_cy0)
        y = m_state->m_console_y0 + m_state->m_console_cy0 - 1;

    scroll_up();

    // テキストをセット
    auto text = vsk_get_next_line_text(line_number, line_number ? -1 : 0);
    set_line_text(y, text);

    assert(y >= 0);
    VSK_STATE()->m_caret_x = 0;
    VSK_STATE()->m_caret_y = y;
}

// 編集モードでROLLDOWNが押された
void VskMachine::edit_down()
{
    VskLineNo line_number = 0;
    int y;

    // テキスト画面を逆順にスキャン
    for (y = m_state->m_console_y0 + m_state->m_console_cy0 - 1;
         y >= m_state->m_console_y0;
         --y)
    {
        auto text = get_line_text(y);
        mstr_trim_right(text, " \t\r\n");
        line_number = vsk_line_number_from_line_text(text);
        if (line_number)
            break;
    }

    if (y < m_state->m_console_y0)
        y = m_state->m_console_y0;

    bool scrolled = false;
    if (y + 1 >= m_state->m_console_y0 + m_state->m_console_cy0)
    {
        scroll_down();
        scrolled = true;
    }
    else
    {
        ++y;
    }

    // テキストをセット
    auto text = vsk_get_next_line_text(line_number, +1);
    if (text.empty() && !scrolled)
    {
        scroll_down();
        if (y > m_state->m_console_y0)
            --y;
    }
    set_line_text(y, text);

    assert(y >= 0);
    VSK_STATE()->m_caret_x = 0;
    VSK_STATE()->m_caret_y = y;
}

// 上にスクロールする
void VskMachine::scroll_up()
{
    scroll_up(m_state->m_console_y0, m_state->m_console_y0 + m_state->m_console_cy0 - 1);
}

// 行テキストをセットする
void VskMachine::set_line_text(int y, VskString text)
{
    // 行テキストが長すぎなら、削る
    std::string str;
    bool was_lead = false;
    for (size_t ich = 0; ich < text.size(); ++ich)
    {
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        if (vsk_is_sjis_code(text[ich], text.c_str()[ich + 1]))
        {
            if (int(ich + 2) >= m_state->m_console_cy0 * m_state->m_text_width)
                break;
            str += text[ich];
            str += text.c_str()[ich + 1];
            was_lead = true;
            continue;
        }
        if (int(ich + 1) >= m_state->m_console_cy0 * m_state->m_text_width)
            break;
        str += text[ich];
    }
    text = std::move(str);

    // 行テキストをセット
    size_t ich = 0;
    was_lead = false;
    for (y = get_line_root(y); y < m_state->m_console_y0 + m_state->m_console_cy0; ++y)
    {
        for (int x = 0; x < m_state->m_text_width; ++x, ++ich)
        {
            // 無視すべき場所は無視する
            if (was_lead)
            {
                was_lead = false;
                continue;
            }

            // 行テキストを超える部分は空白にする
            if (ich >= text.size())
            {
                set_ank(x, y, ' ');
                set_attr(x, y, m_state->m_text_attr);
                continue;
            }

#ifdef JAPAN
            // マルチバイト文字？
            if (vsk_is_sjis_code(text[ich], text[ich + 1]))
            {
                auto sjis = vsk_make_word(text[ich + 1], text[ich]);
                auto jis = vsk_sjis2jis(sjis);
                set_jis(x, y, jis);
                set_attr(x, y, m_state->m_text_attr);
                was_lead = true;
                continue;
            }
#endif
            // 1バイト文字
            set_ank(x, y, text[ich]);
            set_attr(x, y, m_state->m_text_attr);
        }

        if (ich >= text.size())
            break;

        if (!line_link(y)) // 行リンクがない？
        {
            if (y == m_state->m_console_y0 + m_state->m_console_cy0 - 1) // スクロール画面の底か？
            {
                scroll_down(); // 下にスクロール

                m_state->m_caret_y--; // キャレットを一つ上に

                --y;
            }
            else
            {
                // 上にスクロール
                scroll_up(y + 1, m_state->m_console_y0 + m_state->m_console_cy0 - 1);
            }

            // 行リンクをセット
            line_link(y) = 1;
        }
    }
}

// キャレット位置以降を削除
void VskMachine::delete_after()
{
    auto text = get_line_text(m_state->m_caret_y);
    int column = get_line_column();
    text.erase(column);
    set_line_text(m_state->m_caret_y, text);
}

// 行を消す
void VskMachine::delete_line()
{
    line_link(m_state->m_caret_y) = 0;
    set_line_text(m_state->m_caret_y, "");
    m_state->m_caret_x = 0;
}

// 行の一番最後に移動
void VskMachine::move_to_line_end()
{
    auto text = get_line_text(m_state->m_caret_y);
    mstr_trim_right(text, " \t");
    m_state->m_caret_y = get_line_root(m_state->m_caret_y) + int(text.size()) / m_state->m_text_width;
    m_state->m_caret_x = text.size() % m_state->m_text_width;
}

// BackSpace処理
void VskMachine::back_space()
{
    if (m_state->m_caret_x > 0 ||
        (m_state->m_caret_y > m_state->m_console_y0 && line_link(m_state->m_caret_y - 1)))
    {
        move_left();
    }

    do_delete();
}

// Tab処理
void VskMachine::tab()
{
    print(VskString(8 - m_state->m_caret_x % 8, ' '));
}

// ホームポジションへ移動
void VskMachine::home()
{
    m_state->m_caret_x = m_state->m_caret_y = 0;
}

// テキストの実行
void VskMachine::direct_execute(const VskString& text)
{
    m_state->error_clear();
    vsk_direct_execute(text);
}

// ステップ実行を行う
void VskMachine::step()
{
    // ステップ実行を行う
    vsk_step();
}

// エラーがあったか？
bool VskMachine::had_error() const
{
    return VSK_STATE()->error_code() != 0;
}

// エラーを発生させる
bool VskMachine::do_error(VskError error)
{
    return vsk_error(error);
}

// ラインフィード処理
void VskMachine::line_feed()
{
    auto text = get_line_text(m_state->m_caret_y);
    int y = get_line_root(m_state->m_caret_y) + int(text.size()) / m_state->m_text_width;
    if (y >= m_state->m_console_y0 + m_state->m_console_cy0)
    {
        scroll_down();
        --y;
    }
    assert(y >= 0);
    m_state->m_caret_y = y;
    m_state->m_caret_x = 0;
}

// 改行処理
void VskMachine::carriage_return(bool do_execute)
{
    if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
    {
        auto text = get_input_text();
        line_feed();
        vsk_enter_input_text(text);
        return;
    }

    if (!do_execute)
    {
        m_state->m_caret_x = 0;
        return;
    }

    auto text = get_line_text(m_state->m_caret_y);
    line_feed();
    direct_execute(text);
}

// 入力モードの切り替え
void VskMachine::toggle_insert()
{
    m_state->m_insert_mode = !m_state->m_insert_mode;
}

// キャレットを右に移動
void VskMachine::move_right()
{
    if (m_state->m_caret_x + 1 < m_state->m_text_width) // 右に余裕がある？
    {
        // 右に移動
        ++m_state->m_caret_x;
        fix_caret_pos(true);
        return;
    }

    // 行リンクをセット
    line_link(m_state->m_caret_y) = 1;

    // 下に余裕があるか？
    if (m_state->m_caret_y + 1 < m_state->m_console_y0 + m_state->m_console_cy0)
    {
        // 次の行の先頭へ移動
        m_state->m_caret_x = 0;
        ++m_state->m_caret_y;
        fix_caret_pos(true);
        return;
    }

    // 下にスクロールして行の先頭に移動
    scroll_down();
    m_state->m_caret_x = 0;
    fix_caret_pos(true);
}

// キャレットを左に移動
void VskMachine::move_left()
{
    if (m_state->m_wait_for == VSK_WAIT_FOR_INPUT)
    {
        // キャレットの左に余裕がある？
        if (m_state->m_caret_x > int(m_state->m_input_prompt.size()))
        {
            // 左に移動
            --m_state->m_caret_x;
            fix_caret_pos(false);
        }
        return;
    }

    if (m_state->m_caret_x > 0) // キャレットの左に余裕がある？
    {
        // 左に移動
        --m_state->m_caret_x;
        fix_caret_pos(false);
        return;
    }

    if (m_state->m_caret_y > m_state->m_console_y0) // キャレットの上に余裕がある？
    {
        // 一つ上の行の終わりへ移動
        m_state->m_caret_x = m_state->m_text_width - 1;
        --m_state->m_caret_y;
        fix_caret_pos(false);

        // 行リンクをセット
        line_link(m_state->m_caret_y) = 1;
    }
}

// キャレットを上に移動
void VskMachine::move_up()
{
    if (m_state->m_wait_for == VSK_WAIT_FOR_INPUT)
        return;

    if (m_state->m_caret_y > m_state->m_console_y0)
        --m_state->m_caret_y;
    fix_caret_pos(false);
}

// キャレットを下に移動
void VskMachine::move_down()
{
    if (m_state->m_wait_for == VSK_WAIT_FOR_INPUT)
        return;
    if (m_state->m_caret_y + 1 < m_state->m_console_y0 + m_state->m_console_cy0)
        ++m_state->m_caret_y;
    fix_caret_pos(false);
}

// キャレット位置を修正する
void VskMachine::fix_caret_pos(bool go_next)
{
    int x = m_state->m_caret_x, y = m_state->m_caret_y;
    fix_text_pos(m_state->m_caret_x, m_state->m_caret_y, go_next);
    if (x != m_state->m_caret_x && y != m_state->m_caret_y && go_next)
    {
        line_link(y) = 1;
    }
}

// テキスト座標を修正する
void VskMachine::fix_text_pos(int& x, int& y, bool go_next) const
{
#ifdef JAPAN
    int prev_x, prev_y;
    if (get_prev_x_y(prev_x, prev_y, x, y) && !is_ank(prev_x, prev_y))
    {
        if (go_next)
        {
            get_next_x_y(x, y, x, y);
        }
        else
        {
            x = prev_x;
            y = prev_y;
        }
    }
#endif
}

// STOPキー（Ctrl+C）が押された
void VskMachine::stop()
{
    vsk_stop();
}

// ベルを鳴らす
void VskMachine::beep(int number)
{
    vsk_sound_beep(number);
}

// キーボードからの１文字入力処理
void VskMachine::keyboard_ch(VskWord ch)
{
    // WAIT文待ちのときは受け付けない
    if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPORT)
        return;

    // 制御コードは特別な処理が必要
    if (ch < 0x20)
    {
        control_code(VskByte(ch + '@'));
        return;
    }

    // 実行中は入力を受け付けない
    if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
        return;

    // 挿入モードの場合は行テキストを使用
    if (m_state->m_insert_mode)
    {
        auto text = get_line_text(m_state->m_caret_y);
        int column = get_line_column();
#ifdef JAPAN
        if (vsk_is_sjis_code(ch))
        {
            text.insert(column, 1, vsk_high_byte(ch));
            text.insert(column + 1, 1, vsk_low_byte(ch));
        }
        else
#endif
        {
            text.insert(column, 1, VskByte(ch));
        }
        mstr_trim_right(text, " \t");
        set_line_text(m_state->m_caret_y, text);
        move_right();
        return;
    }

    // それ以外の場合は普通に出力
    print_ch(ch);
}

// 制御コードの処理
void VskMachine::control_code(VskByte ch)
{
    // WAIT文待ちのときは入力を受け付けない
    if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPORT)
        return;

    switch (ch)
    {
    case '@': // NUL
        break;
    case 'A': // HELP
        help();
        break;
    case 'B': // BACK WORD
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        back_word();
        set_insert_mode(false);
        break;
    case 'C': // STOP
        stop();
        break;
    case 'D': // DELETE WORD
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        delete_word();
        set_insert_mode(false);
        break;
    case 'E': // DELETE LINE AFTER CARET
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        delete_after();
        set_insert_mode(false);
        break;
    case 'F': // FORWARD WORD
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        forward_word();
        break;
    case 'G': // BEL
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        beep();
        break;
    case 'H': // BACKSPACE
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        back_space();
        break;
    case 'I': // Tab
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        tab();
        break;
    case 'J': // LF
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        line_feed();
        set_insert_mode(false);
        break;
    case 'K': // Home
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        home();
        set_insert_mode(false);
        break;
    case 'L': // Clear
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        clear_text();
        home();
        set_insert_mode(false);
        break;
    case 'M': // CR
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        carriage_return(true);
        set_insert_mode(false);
        break;
    case 'R': // Insert
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        toggle_insert();
        break;
    case 'U': // DELETE LINE
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        delete_line();
        set_insert_mode(false);
        break;
    case 'X': // MOVE TO LINE END
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        if (VSK_STATE()->m_wait_for == VSK_WAIT_FOR_INPUT)
            return;
        move_to_line_end();
        set_insert_mode(false);
        break;
    case '\\': // Right
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        move_right();
        set_insert_mode(false);
        break;
    case ']': // Left
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        move_left();
        set_insert_mode(false);
        break;
    case '^': // Up
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        move_up();
        set_insert_mode(false);
        break;
    case '_': // Down
        if (VSK_STATE()->m_wait_for == VSK_NO_WAIT)
            return;
        move_down();
        set_insert_mode(false);
        break;
    }
}

// インサートモードをセットする
void VskMachine::set_insert_mode(bool insert)
{
    m_state->m_insert_mode = insert;
}

// 制御コードを出力する
void VskMachine::print_control(VskByte ch)
{
    switch (ch)
    {
    case '@': // NUL
        break;
    case 'A': // HELP
        break;
    case 'B': // BACK WORD
        break;
    case 'C': // STOP
        break;
    case 'D': // DELETE WORD
        break;
    case 'E': // DELETE LINE AFTER CARET
        break;
    case 'F': // FORWARD WORD
        break;
    case 'G': // BEL
        beep();
        break;
    case 'H': // BACKSPACE
        back_space();
        break;
    case 'I': // Tab
        tab();
        break;
    case 'J': // LF
        line_feed();
        break;
    case 'K': // Home
        home();
        break;
    case 'L': // Clear
        clear_text();
        home();
        break;
    case 'M': // CR
        carriage_return();
        break;
    case 'R': // Insert
        break;
    case 'U': // DELETE ONE LINE
        break;
    case 'X': // MOVE TO LINE END
        break;
    case '\\': // Right
        move_right();
        break;
    case ']': // Left
        move_left();
        break;
    case '^': // Up
        move_up();
        break;
    case '_': // Down
        move_down();
        break;
    }
}

// 文字を出力する
void VskMachine::print_ch(VskWord ch, bool do_control)
{
    // 制御コードは特別な処理が必要かも
    if (do_control && ch < ' ')
    {
        print_control(ch + '@');
        return;
    }

    // キャレット位置を取得
    int x = m_state->m_caret_x, y = m_state->m_caret_y;

#ifdef JAPAN
    if (vsk_is_sjis_code(ch)) // SJISコードの全角文字なら？
    {
        // 必要ならスクロール処理
        if (x + 2 >= m_state->m_text_width &&
            y + 1 >= m_state->m_console_y0 + m_state->m_console_cy0)
        {
            scroll_down();
            m_state->m_caret_x = (x + 2) - m_state->m_text_width;
            m_state->m_caret_y--;
        }
        // 全角文字をセット
        VskWord jis = vsk_sjis2jis(ch);
        assert(vsk_is_jis_code(jis));
        set_jis(m_state->m_caret_x, m_state->m_caret_y, jis);
    }
    else
#endif
    {
        // 半角文字をセット
        set_ank(m_state->m_caret_x, m_state->m_caret_y, VskByte(ch));
    }

    // テキスト属性をセット
    set_attr(m_state->m_caret_x, m_state->m_caret_y, m_state->m_text_attr);

    // 右に移動
    move_right();
}

// 文字列を出力する
void VskMachine::print(const VskString& str)
{
    bool was_lead = false;

    // 文字列中の各バイトについて処理
    for (size_t ich = 0; ich < str.size(); ++ich)
    {
        // 無視すべきバイトは無視する
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        VskByte ch = str[ich];
#ifdef JAPAN
        // 全角文字は特別な処理が必要
        if (vsk_is_sjis_code(ch, str.c_str()[ich + 1]))
        {
            VskByte lead = ch, trail = str.c_str()[ich + 1];
            VskWord sjis = vsk_make_word(trail, lead);
            assert(vsk_is_sjis_code(sjis));
            print_ch(sjis);
            was_lead = true;
            continue;
        }
#endif
        // それ以外は普通に出力
        print_ch(ch);
    }
}

// テキスト画面をクリップボードにコピー
VskString VskMachine::copy_text_screen()
{
    bool was_lead = false;

    // 一行ずつ処理
    VskString ret;
    for (int y = 0; y < m_state->m_text_height; ++y)
    {
        // 1バイトずつ処理
        for (int x = 0; x < m_state->m_text_width; ++x)
        {
#ifdef JAPAN
            // 無視すべきバイトは無視する
            if (was_lead)
            {
                was_lead = false;
                continue;
            }
            // 全角文字をちゃんと処理する
            if (!is_ank(x, y))
            {
                auto jis = get_jis(x, y);
                assert(vsk_is_jis_code(jis));
                auto sjis = vsk_jis2sjis(jis);
                assert(vsk_is_sjis_code(sjis));
                ret += vsk_high_byte(sjis);
                ret += vsk_low_byte(sjis);
                was_lead = true;
                continue;
            }
#endif
            // それ以外は普通に追加
            uint8_t ank = get_ank(x, y);
            if (ank < 0x20)
                ret += '?'; // 制御文字を隠す
            else
                ret += get_ank(x, y);
        }
        // 改行文字を追加
        ret += "\r\n";
    }

    return ret;
}

// 生文字列を出力する
void VskMachine::print_raw(const VskString& str)
{
    bool was_lead = false;

    // 文字列中の各バイトについて処理
    for (size_t ich = 0; ich < str.size(); ++ich)
    {
        // 無視すべきバイトは無視する
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        VskByte ch = str[ich];
#ifdef JAPAN
        // JISの全角文字は特別な処理が必要
        if (vsk_is_sjis_code(ch, str.c_str()[ich + 1]))
        {
            VskByte lead = ch, trail = str.c_str()[ich + 1];
            VskWord jis = vsk_sjis2jis(lead, trail);
            assert(vsk_is_jis_code(jis));
            print_ch(jis);
            was_lead = true;
            continue;
        }
#endif
        // それ以外は制御文字を含めてそのまま出力
        print_ch(ch, false);
    }
}

// 文字列を入力する
void VskMachine::keyboard_str(const VskString& str)
{
    bool was_lead = false;

    // 文字列中の各バイトについて処理
    for (size_t ich = 0; ich < str.size(); ++ich)
    {
        // 無視すべきバイトは無視する
        if (was_lead)
        {
            was_lead = false;
            continue;
        }
        auto ch = str[ich];
#ifdef JAPAN
        // JISの全角文字は特別な処理が必要
        if (vsk_is_sjis_code(ch, str.c_str()[ich + 1]))
        {
            auto lead = ch, trail = str.c_str()[ich + 1];
            auto sjis = vsk_make_word(trail, lead);
            assert(vsk_is_sjis_code(sjis));
            keyboard_ch(sjis);
            was_lead = true;
            continue;
        }
#endif
        // それ以外は普通に入力
        keyboard_ch(ch);
    }
}

// ファンクションキーの処理
void VskMachine::function_key(int index, bool shift)
{
    vsk_function_key(index, shift);
}

bool VskMachine::hit_text_char(int& text_x, int& text_y, int client_x, int client_y) const
{
    text_x = (m_state->m_text_wider) ? (client_x / 16) : (client_x / 8);
    text_y = (m_state->m_text_longer) ? (client_y / 20) : (client_y / 16);
    return (0 <= text_x && text_x < m_state->m_text_width &&
            0 <= text_y && text_y < m_state->m_text_height);
}

// ファンクションキーの位置を調べる
int VskMachine::hit_test_function_key(int x, int y) const
{
    const bool shift = vsk_is_shift_pressed(); // Shiftキーが押されているか

    if (!m_state->m_show_function_keys)
        return -1;

    auto text_y = m_state->m_text_height - 1;
    if (text_y != y)
        return -1;

    for (int key_no = 1; key_no <= 10; ++key_no)
    {
        int x0, cx, delta_text;
        if (!get_function_key_position(key_no, x0, cx, delta_text, shift))
            continue;

        if (x0 <= x && x < x0 + cx)
            return key_no;
    }

    return -1;
}

// ファンクションキーの位置を調べる
bool VskMachine::get_function_key_position(int key_no, int& x, int& cx, int& delta_text, bool shift) const
{
    if (!m_state->m_show_function_keys)
        return false;

    if (is_8801_mode())
    {
        delta_text = 1;
        if (m_state->m_text_wider)
        {
            static const int c_pos[] = { 2, 9, 16, 23, 30 };
            cx = 6;
            if (shift)
            {
                if (6 <= key_no && key_no <= 10)
                {
                    x = c_pos[key_no - 6];
                    return true;
                }
            }
            else
            {
                if (1 <= key_no && key_no <= 5)
                {
                    x = c_pos[key_no - 1];
                    return true;
                }
            }
        }
        else
        {
            static const int c_pos[] = { 5, 19, 33, 47, 61 };
            cx = 12;
            if (shift)
            {
                if (6 <= key_no && key_no <= 10)
                {
                    x = c_pos[key_no - 6];
                    return true;
                }
            }
            else
            {
                if (1 <= key_no && key_no <= 5)
                {
                    x = c_pos[key_no - 1];
                    return true;
                }
            }
        }
    }
    else
    {
        delta_text = 0;
        cx = 6;
        if (m_state->m_text_wider)
        {
            static const int c_pos[] = { 3, 10, 17, 24, 31 };
            if (shift)
            {
                if (6 <= key_no && key_no <= 10)
                {
                    x = c_pos[key_no - 6];
                    return true;
                }
            }
            else
            {
                if (1 <= key_no && key_no <= 5)
                {
                    x = c_pos[key_no - 1];
                    return true;
                }
            }
        }
        else
        {
            static const int c_pos[] = { 4, 11, 18, 25, 32, 42, 49, 56, 63, 70};
            if (1 <= key_no && key_no <= 10)
            {
                x = c_pos[key_no - 1];
                return true;
            }
        }
    }

    return false;
}

// 文法エラーを発生させる
void VskMachine::syntax_error()
{
    do_error(VSK_ERR_SYNTAX);
}

// "Illegal function call"エラーを発生させる
void VskMachine::bad_call()
{
    do_error(VSK_ERR_BAD_CALL);
}

// テキスト画面をクリア
void VskMachine::clear_text()
{
    clear_text(m_state->m_console_y0, m_state->m_console_y0 + m_state->m_console_cy0 - 1);
}

// グラフィック画面をクリア
void VskMachine::clear_graphic()
{
    clear_graphic(&m_state->m_viewport);
}

// グラフィック画面をクリア
void VskMachine::clear_graphic(const VskRectI *rect)
{
    fill_box(rect->m_x0, rect->m_y0, rect->m_x1, rect->m_y1, 0);
}

// ワールド座標をスクリーン座標に
VskPointD VskMachine::world_to_screen(VskPointD pt) const
{
    VskDouble wx = m_state->m_window.width(),   wy = m_state->m_window.height();
    int vx = m_state->m_viewport.width(), vy = m_state->m_viewport.height();
    return { (pt.m_x - m_state->m_window.m_x0) * vx / wx,
             (pt.m_y - m_state->m_window.m_y0) * vy / wy };
}

// スクリーン座標をワールド座標に
VskPointD VskMachine::screen_to_world(VskPointD pt) const
{
    VskDouble wx = m_state->m_window.width(),   wy = m_state->m_window.height();
    int vx = m_state->m_viewport.width(), vy = m_state->m_viewport.height();
    return { pt.m_x * wx / vx + m_state->m_window.m_x0,
             pt.m_y * wy / vy + m_state->m_window.m_y0 };
}

// ワールド座標をクライアント座標に
VskPointD VskMachine::world_to_client(VskPointD pt) const
{
    auto wx = m_state->m_window.width(), wy = m_state->m_window.height();
    int vx = m_state->m_viewport.width(), vy = m_state->m_viewport.height();
    return { (((pt.m_x - m_state->m_window.m_x0) * vx / wx) + m_state->m_viewport.m_x0),
             (((pt.m_y - m_state->m_window.m_y0) * vy / wy) + m_state->m_viewport.m_y0) };
}

// ワールド座標をクライアント座標に
VskSizeI VskMachine::world_to_client(VskSizeD siz) const
{
    auto wx = m_state->m_window.width(), wy = m_state->m_window.height();
    int vx = m_state->m_viewport.width(), vy = m_state->m_viewport.height();
    return { vsk_round(siz.m_cx * vx / wx), vsk_round(siz.m_cy * vy / wy) };
}

// クライアント座標をワールド座標に
VskPointD VskMachine::client_to_world(VskPointI pt) const
{
    auto wx = m_state->m_window.width(), wy = m_state->m_window.height();
    int vx = m_state->m_viewport.width(), vy = m_state->m_viewport.height();
    return { (pt.m_x - m_state->m_viewport.m_x0) * wx / vx + m_state->m_window.m_x0,
             (pt.m_y - m_state->m_viewport.m_y0) * wy / vy + m_state->m_window.m_y0 };
}

// ピクセルを取得
int VskMachine::get_pixel(int x0, int y0)
{
    if (auto getter = get_color_getter(nullptr))
    {
        int ret = (*getter)(x0, y0);
        return ret;
    }
    return -1;
}

// 点を描画
void VskMachine::set_pixel(int x0, int y0, int palette)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        (*putter)(x0, y0);
    }
}

// 直線を描画
void VskMachine::draw_line(int x0, int y0, int x1, int y1, int palette, VskWord line_style)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        if (line_style != 0xFFFF)
        {
            if (auto putter2 = std::make_shared<VskLinePutter<VskPixelPutter>>(putter.get(), line_style))
            {
                vsk_draw_line(*putter2, x0, y0, x1, y1, &m_state->m_viewport);
            }
        }
        else
        {
            vsk_draw_line(*putter, x0, y0, x1, y1, &m_state->m_viewport);
        }
    }
}

// 長方形を描画
void VskMachine::draw_box(int x0, int y0, int x1, int y1, int palette, VskWord line_style)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        if (line_style != 0xFFFF)
        {
            if (auto putter2 = std::make_shared<VskLinePutter<VskPixelPutter>>(putter.get(), line_style))
            {
                vsk_draw_box(*putter2, x0, y0, x1, y1, &m_state->m_viewport);
            }
        }
        else
        {
            vsk_draw_box(*putter, x0, y0, x1, y1, &m_state->m_viewport);
        }
    }
}

// 長方形を塗りつぶす
void VskMachine::fill_box(int x0, int y0, int x1, int y1, int palette, const VskString& tile)
{
    if (tile.empty())
    {
        if (auto putter = get_color_putter(palette, nullptr))
        {
            vsk_fill_box(*putter, x0, y0, x1, y1, &m_state->m_viewport);
        }
    }
    else
    {
        assert(is_valid_tile(tile));
        if (auto putter = get_tile_putter(tile, nullptr))
        {
            vsk_fill_box(*putter, x0, y0, x1, y1, &m_state->m_viewport);
        }
    }
}

// タイル文字列をチェックする
bool VskMachine::is_valid_tile(const VskString& tile) const
{
    if (tile.empty())
        return false;
    int cPlanes = m_state->get_graphics_num_planes();
    return (tile.size() % cPlanes) == 0;
}

bool VskMachine::is_valid_color(int palette) const
{
    switch (m_state->m_color_mode)
    {
    case VSK_COLOR_MODE_8_COLORS_DIGITAL:
    case VSK_COLOR_MODE_8_COLORS_SUPER:
        return 0 <= palette && palette < 8;
    case VSK_COLOR_MODE_16_COLORS_SUPER:
        return 0 <= palette && palette < 16;
    default:
        assert(0);
        return false;
    }
}

bool VskMachine::is_valid_color_code(VskDword color_code, VskWebColor& web_color) const
{
    switch (VSK_STATE()->m_color_mode)
    {
    case VSK_COLOR_MODE_8_COLORS_DIGITAL:
        if (!(0 <= color_code && color_code < 8))
            return false;
        web_color = vsk_get_default_digital_color_8(color_code);
        break;
    case VSK_COLOR_MODE_8_COLORS_SUPER:
        {
            if (!(0 <= color_code && color_code <= 0777))
                return false;
            auto blue = (color_code & 0xF) * 255 / 0xF;
            auto red = ((color_code >> 4) & 0xF) * 255 / 0xF;
            auto green = ((color_code >> 8) & 0xF) * 255 / 0xF;
            web_color = vsk_make_web_color(VskByte(red), VskByte(green), VskByte(blue));
        }
        break;
    case VSK_COLOR_MODE_16_COLORS_SUPER:
        {
            if (!(0 <= color_code && color_code <= 0xFFF))
                return false;
            auto blue = (color_code & 0xF) * 255 / 0xF;
            auto red = ((color_code >> 4) & 0xF) * 255 / 0xF;
            auto green = ((color_code >> 8) & 0xF) * 255 / 0xF;
            web_color = vsk_make_web_color(VskByte(red), VskByte(green), VskByte(blue));
        }
        break;
    }

    return true;
}

// 円を描く
void VskMachine::draw_circle(int x0, int y0, int r, int palette)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        vsk_draw_circle(*putter, x0, y0, r, &m_state->m_viewport);
    }
}

// 円を塗りつぶす
void VskMachine::fill_circle(int x0, int y0, int r, int palette)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        vsk_fill_circle(*putter, x0, y0, r, &m_state->m_viewport);
    }
}

// 楕円を描く
void VskMachine::draw_ellipse(int x0, int y0, int x1, int y1, int palette)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        vsk_draw_ellipse(*putter, x0, y0, x1, y1, &m_state->m_viewport);
    }
}

// 楕円を塗りつぶす
void VskMachine::fill_ellipse(int x0, int y0, int x1, int y1, int palette, const VskString& tile)
{
    if (tile.empty())
    {
        if (auto putter = get_color_putter(palette, nullptr))
        {
            vsk_fill_ellipse(*putter, x0, y0, x1, y1, &m_state->m_viewport);
        }
    }
    else
    {
        assert(is_valid_tile(tile));
        if (auto putter = get_tile_putter(tile, nullptr))
        {
            vsk_fill_ellipse(*putter, x0, y0, x1, y1, &m_state->m_viewport);
        }
    }
}

// 弧を描く
void VskMachine::draw_arc(int x0, int y0, int x1, int y1, VskDouble start_angle, VskDouble end_angle, int palette)
{
    if (auto putter = get_color_putter(palette, nullptr))
    {
        vsk_draw_arc(*putter, x0, y0, x1, y1, start_angle, end_angle);
    }
}

// 弧を塗りつぶす
void VskMachine::fill_arc(int x0, int y0, int x1, int y1, VskDouble start_angle, VskDouble end_angle, int palette, const VskString& tile)
{
    if (tile.empty())
    {
        if (auto putter = get_color_putter(palette, nullptr))
        {
            vsk_fill_arc(*putter, x0, y0, x1, y1, start_angle, end_angle, &m_state->m_viewport);
        }
    }
    else
    {
        assert(is_valid_tile(tile));
        if (auto putter = get_tile_putter(tile, nullptr))
        {
            vsk_fill_arc(*putter, x0, y0, x1, y1, start_angle, end_angle, &m_state->m_viewport);
        }
    }
}

// 塗りつぶす
void VskMachine::flood_fill(int x0, int y0, int fill_color, int border_color, const VskString& tile)
{
    if (auto color_getter = get_color_getter(nullptr))
    {
        VskBorderGetter<VskColorGetter> border_getter(border_color, color_getter.get());
        if (tile.size())
        {
            if (auto putter = get_tile_putter(tile, nullptr))
            {
                vsk_flood_fill(*putter, border_getter, x0, y0, &m_state->m_viewport);
            }
        }
        else
        {
            if (auto putter = get_color_putter(fill_color, nullptr))
            {
                vsk_flood_fill(*putter, border_getter, x0, y0, &m_state->m_viewport);
            }
        }
    }
}

// スクロールを描画する
void VskMachine::draw_scroll(int dx, int dy, int fill_color)
{
    if (auto getter = get_color_getter(nullptr))
    {
        if (auto putter = get_color_putter(7, nullptr))
        {
            vsk_draw_scroll(*putter, *getter, dx, dy, fill_color, &m_state->m_viewport);
        }
    }
}

// 漢字を描画する
void VskMachine::draw_kanji(int x, int y, VskWord jis, const VskString& op, int fore_color, int back_color, bool is_9801)
{
    if (auto getter = get_color_getter(nullptr))
    {
        if (auto putter = get_color_putter(7, nullptr))
        {
            vsk_draw_kanji(*putter, *getter, jis, x, y, fore_color, back_color, op, is_9801);
        }
    }
}

// イメージを取得する
bool VskMachine::get_image(int x0, int y0, int cx, int cy, void *ptr, size_t size, int M)
{
    if (auto getter = get_color_getter(nullptr))
    {
        return vsk_get_image(*getter, x0, y0, cx, cy, (uint8_t *)ptr, size, M);
    }
    return false;
}

// イメージを描画する
bool VskMachine::put_image(int x0, int y0, const void *ptr, size_t size, int M, const VskString& op)
{
    if (auto getter = get_color_getter(nullptr))
    {
        if (auto putter = get_color_putter(7, nullptr))
        {
            return vsk_put_image(*putter, *getter, x0, y0, (const uint8_t *)ptr, size, M, op);
        }
    }
    return false;
}

// テストパターン
void VskMachine::test_pattern(int type)
{
    clear_graphic();
    clear_text();
    reset_palette();
    reset_text();
    reset_graphics();
    move_to_top();

    switch (type)
    {
    case -1:
        // 日本語の混ざったテキストを出力する
        m_state->m_text_mode = VSK_TEXT_MODE_SJIS;
        for (int y = 0, i = 0; y < 20; ++y)
        {
            for (int x = 0; x < m_state->m_text_width; ++x)
            {
                switch ((x + y) % 3)
                {
                case 0:
                    print("a");
                    break;
                case 1:
                    print("\x82\xA0");
                    break;
                case 2:
                    print("\x82\xA2");
                    break;
                }
            }
        }
        break;
    case 0:
        // BASIC起動風のテキストを表示する
        print(VEYSICK_TITLE "\n");
        print(VEYSICK_COPYRIGHT "\n");
        switch (m_state->m_machine_mode)
        {
        case VSK_MACHINE_MODE_8801:
            print("Started in 8801 mode\n");
            break;
        case VSK_MACHINE_MODE_9801:
            print("Started in 9801 mode\n");
            break;
        case VSK_MACHINE_MODE_VSK:
            print("Started in VSK mode\n");
            break;
        }
        print("99999 Bytes free\n");
        VSK_STATE()->m_wait_for = VSK_NO_WAIT;
        vsk_enter_command_level();
        break;
    case 1:
        // テレビの放送終了したときみたいな、カラーバー表示
        {
            int width = m_state->m_screen_width, height = m_state->m_screen_height;
            int i = 0;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 7);
            ++i;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 6);
            ++i;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 5);
            ++i;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 4);
            ++i;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 3);
            ++i;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 2);
            ++i;
            fill_box(width * i / 7, 0, width * (i + 1) / 7 - 1, height, 1);
            ++i;
            int y = height * 6 / 7;
            i = 0;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 1);
            ++i;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 0);
            ++i;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 3);
            ++i;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 0);
            ++i;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 5);
            ++i;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 0);
            ++i;
            fill_box(width * i / 7, y, width * (i + 1) / 7 - 1, height, 15);
            ++i;
        }
        break;
    case 2:
        // 文字を並べる
        for (int y = 0; y < 16; ++y)
        {
            for (int x = 0; x < 16; ++x)
            {
                set_ank(x, y, x + y * 16);
                set_color(x, y, (x + y) % 8);
            }
        }
        break;
    }
}

//////////////////////////////////////////////////////////////////////////////
// ファイル

#include <pshpack1.h>
struct BSAVE_HEADER
{
    VskByte m_magic;
    VskWord m_start_addr;
    VskWord m_end_addr;
    VskWord m_call_addr;
};
#include <poppack.h>

#define BSAVE_MAGIC VskByte(0xFE)

bool VskMachine::binary_load(const char *filename, VskAddr addr, VskDword& size, VskAddr& call_addr)
{
    auto file_manager = vsk_get_file_manager();
    VskFilePtr file;
    auto error = file_manager->open(file, filename, VskFile::MODE_INPUT);
    if (error)
    {
        do_error(error);
        return false;
    }

    if (!file->get_size(&size))
    {
        do_error(VSK_ERR_DISK_IO_ERROR);
        return false;
    }

    if (size < sizeof(BSAVE_HEADER))
    {
        do_error(VSK_ERR_BAD_OPERATION);
        return false;
    }

    std::vector<uint8_t> data;
    data.resize(size);

    error = file->read_bin(&data[0], size);
    if (error)
    {
        do_error(error);
        return false;
    }

    BSAVE_HEADER* header = reinterpret_cast<BSAVE_HEADER*>(data.data());
    if (header->m_magic != BSAVE_MAGIC)
    {
        do_error(VSK_ERR_BAD_CALL);
        return false;
    }
    if (addr == VskAddr(-1))
        addr = header->m_start_addr;

    size = header->m_end_addr - header->m_start_addr;
    data.erase(data.begin(), data.begin() + sizeof(BSAVE_HEADER));

    addr = resolve_addr(header->m_start_addr);

    for (size_t i = addr; i < addr + size; ++i)
    {
        if (is_8801_mode())
        {
            if ((0x8000 <= i && i <= 0x83FF) ||
                (0xE600 <= i && i <= 0xFFFF) ||
                (has_cmd_exst() && (0xE100 <= i && i <= 0xE5FF)))
            {
                bad_call();
                return false;
            }
        }
        m_state->m_memory->write(&data[i - addr], i, 1);
    }

    call_addr = header->m_call_addr;
    return true;
}

bool VskMachine::binary_save(const char *filename, VskAddr addr, VskDword size)
{
    std::vector<uint8_t> data;
    data.resize(size);

    for (size_t i = addr; i < addr + size; ++i)
    {
        if (is_8801_mode() && 0x8000 <= i && i <= 0x83FF)
        {
            bad_call();
            return false;
        }
        m_state->m_memory->read(&data[i - addr], i, 1);
    }

    auto file_manager = vsk_get_file_manager();
    VskFilePtr file;
    auto error = file_manager->open(file, filename, VskFile::MODE_OUTPUT);
    if (error)
    {
        do_error(error);
        return false;
    }

    VskAddr offset = unresolve_addr(addr);

    BSAVE_HEADER header =
    {
        BSAVE_MAGIC, VskWord(offset), VskWord(offset + size), 0
    };

    error = file->write_bin(&header, sizeof(header));
    if (!error)
        error = file->write_bin(data.data(), size);
    if (error)
    {
        unlink(filename);
        do_error(error);
        return false;
    }

    return true;
}

bool VskMachine::load(VskString filename, std::string& data)
{
    data.clear();

    auto file_manager = vsk_get_file_manager();
    VskFilePtr file;
    auto error = file_manager->open(file, filename, VskFile::MODE_INPUT);
    if (error)
        error = file_manager->open(file, filename + ".bas", VskFile::MODE_INPUT);
    if (error)
        error = file_manager->open(file, filename + ".BAS", VskFile::MODE_INPUT);
    if (error)
    {
        do_error(error);
        return false;
    }

    VskDword size;
    if (!file->get_size(&size))
    {
        do_error(VSK_ERR_DISK_IO_ERROR);
        return false;
    }

    if (size)
    {
        data.resize(size);

        error = file->read_bin(&data[0], size);
        if (error)
        {
            do_error(error);
            return false;
        }

        mstr_replace_all(data, "\r\n", "\n");
        mstr_replace_all(data, "\r", "\n");
    }

    return true;
}

bool VskMachine::save(VskString filename, const std::string& data)
{
    auto file_manager = vsk_get_file_manager();
    VskFilePtr file;
    auto error = file_manager->open(file, filename, VskFile::MODE_OUTPUT);
    if (error)
    {
        do_error(error);
        return false;
    }

    std::string text = data;
    mstr_replace_all(text, "\r\n", "\n");
    mstr_replace_all(text, "\r", "\n");

    if (text.size())
    {
        error = file->write_bin(&text[0], text.size());
        if (error)
        {
            do_error(error);
            return false;
        }
    }

    return true;
}

// ファイル番号とファイルの関連付け
VskFilePtr VskFileManager::assoc(int file_no)
{
    auto it = m_file_no_to_file_map.find(file_no);
    if (it == m_file_no_to_file_map.end())
        return nullptr;
    return it->second;
}
void VskFileManager::assoc(int file_no, VskFilePtr file)
{
    assert(file);
    m_file_no_to_file_map[file_no] = file;
}

// ファイル管理を取得
std::shared_ptr<VskFileManager> vsk_get_file_manager(void)
{
    auto& device = VSK_STATE()->m_file_manager;
    if (!device)
        device = std::make_shared<VskFileManager>();
    return device;
}

// 画面印字
struct VskScreenPrinter : VskFile
{
    int  get_x() const override {
        return VSK_STATE()->m_caret_x;
    }
    void set_x(int x) {
        VSK_STATE()->m_caret_x = x;
        vsk_machine->fix_caret_pos(false);
    }

    int  line_width() const override    { return VSK_STATE()->m_text_width; }
    bool line_width(int value) override { return false; }

    VskError write_str(const std::string& str) override {
        vsk_machine->print(str);
        return VSK_NO_ERROR;
    }
    VskError write_line(const std::string& data) override {
        vsk_machine->print(data + "\n");
        return VSK_NO_ERROR;
    }
};

// 画面出力用
VskFilePtr vsk_get_screen_device(void)
{
    auto& device = VSK_STATE()->m_screen_device;
    if (!device)
        device = std::make_shared<VskScreenPrinter>();
    return device;
}

// 画面印字を開く
VskError VskFileManager::open_screen(VskFilePtr& file, VskFile::MODE mode)
{
    if (mode == VskFile::MODE_OUTPUT || mode == VskFile::MODE_DEFAULT)
    {
        file = vsk_get_screen_device();
        return VSK_NO_ERROR;
    }
    return VSK_ERR_BAD_CALL;
}

VskError VskFileManager::open(VskFilePtr& file, VskString descriptor, VskFile::MODE mode)
{
    VskFile::TYPE type;
    VskString device, raw_path;
    if (!vsk_parse_file_descriptor(descriptor, type, device, raw_path))
        return VSK_ERR_FILE_NOT_FOUND;

    VskError error;
    switch (type)
    {
    case VskFile::TYPE_HOST_FILE:
        error = open_host_file(file, raw_path, mode);
        break;
    case VskFile::TYPE_SCREEN:
        error = open_screen(file, mode);
        break;
    case VskFile::TYPE_KEYBOARD:
    case VskFile::TYPE_CASETTE:
    case VskFile::TYPE_COM:
        return VSK_ERR_NO_FEATURE;
    case VskFile::TYPE_LINE_PRINTER:
        error = open_line_printer(file, mode);
        break;
    }

    return error;
}

struct VskLinePrinter : VskFile
{
    int m_x = 0;

    int  get_x() const override         { return m_x; }
    void set_x(int x) override          { m_x = x; }

    int  line_width() const override    { return VSK_STATE()->m_line_printer_width; }
    bool line_width(int value) override { VSK_STATE()->m_line_printer_width = value; return true; }

    VskError write_str(const std::string& str) override {
        for (auto ch : str) {
            write_ch(ch);
        }
        return VSK_NO_ERROR;
    }
    VskError write_line(const std::string& data) override {
        return write_str(data + "\r\n");
    }
    void write_ch(char ch) {
        if (ch == '\r')
            return;
        std::fwrite(&ch, 1, 1, stdout);
        if (ch == '\n') {
            m_x = 0;
        } else {
            ++m_x;
        }
        return;
    }
};

// ラインプリンタ出力用
VskFilePtr vsk_get_line_printer(void)
{
    auto& device = VSK_STATE()->m_line_printer;
    if (!device)
        device = std::make_shared<VskLinePrinter>();
    return device;
}

VskError VskFileManager::open_line_printer(VskFilePtr& file, VskFile::MODE mode)
{
    if (mode == VskFile::MODE_OUTPUT || mode == VskFile::MODE_DEFAULT)
    {
        file = vsk_get_line_printer();
        return VSK_NO_ERROR;
    }
    return VSK_ERR_BAD_CALL;
}

void VskFileManager::close(int file_no)
{
    auto it = m_file_no_to_file_map.find(file_no);
    if (it != m_file_no_to_file_map.end())
    {
        m_file_no_to_file_map.erase(it);
    }
}

void VskFileManager::close(VskFilePtr file)
{
    for (auto& pair : m_file_no_to_file_map)
    {
        if (pair.second == file)
        {
            close(pair.first);
            return;
        }
    }
}

void VskFileManager::close_all()
{
    m_file_no_to_file_map.clear();
}

// ファイルを全部閉じる
void vsk_file_close_all(void)
{
    VSK_STATE()->m_file_manager = nullptr;
    VSK_STATE()->m_screen_device = nullptr;
    VSK_STATE()->m_line_printer = nullptr;
}

//////////////////////////////////////////////////////////////////////////////

bool VskMachine::draw(VskString str)
{
    // TODO:
    return false;
}

bool VskMachine::connect(bool do_connect)
{
    if (do_connect) // 接続する
    {
        if (m_state->m_machine_mode == VSK_MACHINE_MODE_8801)
            m_state->m_segment = 0;

        vsk_vars_block = std::make_shared<VskVarMemoryBlock>(m_state);
        vsk_str_block = std::make_shared<VskStrMemoryBlock>(m_state);
        m_state->m_memory->add_block(vsk_vars_block.get());
        m_state->m_memory->add_block(vsk_str_block.get());
    }
    else // 接続を切断する
    {
        vsk_file_close_all();
        m_state->m_memory->remove_block(vsk_str_block.get());
        m_state->m_memory->remove_block(vsk_vars_block.get());
        vsk_str_block = nullptr;
        vsk_vars_block = nullptr;
    }
    return true;
}

// コメントを処理する
void vsk_process_comment(VskString text)
{
    vsk_upper(text);

    VskMachineMode old_machine_mode = VSK_STATE()->m_machine_mode;
    VskMachineMode new_machine_mode = old_machine_mode;

    // (VeySicK拡張)
    if (text.find("{GRPH}") != text.npos)
        VSK_STATE()->m_text_mode = VSK_TEXT_MODE_GRPH;
    if (text.find("{SJIS}") != text.npos)
        VSK_STATE()->m_text_mode = VSK_TEXT_MODE_SJIS;
    if (text.find("{JIS}") != text.npos)
        VSK_STATE()->m_text_mode = VSK_TEXT_MODE_JIS;
    if (text.find("{8801}") != text.npos)
        new_machine_mode = VSK_MACHINE_MODE_8801;
    if (text.find("{9801}") != text.npos)
        new_machine_mode = VSK_MACHINE_MODE_9801;
    if (text.find("{VSK}") != text.npos)
        new_machine_mode = VSK_MACHINE_MODE_VSK;

    if (old_machine_mode != new_machine_mode)
    {
        auto* state = VSK_STATE();
        vsk_connect_machine(state, false);
        state->m_machine_mode = new_machine_mode;
        vsk_connect_machine(state, true);
    }

    assert(vsk_machine);
    assert(VSK_STATE());
}

void VskMachine::pen(int x, int y, bool pressed)
{
    vsk_pen(x, y, pressed);
}
