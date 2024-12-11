// VeySicK.h --- VeySicK
#pragma once

//////////////////////////////////////////////////////////////////////////////
// VeySicK 基本情報

#define VEYSICK_VER                  0x00502
#define VEYSICK_TITLE                "VeySicK MATEN Version 0.5.2"
#define VEYSICK_TITLE_FPS            "VeySicK MATEN Version 0.5.2 @ %u fps"
#define VEYSICK_TITLE_FPS_WITH_FILE  "%s on VeySicK MATEN @ %u fps"
#define VEYSICK_COPYRIGHT            "Copyright (C) 2015-2024 katahiromz"
#define VEYSICK_CLASSNAME            "katahiromz's VeySicK"

//////////////////////////////////////////////////////////////////////////////
// VeySicK 基本型

#include "types.h"

// 型のサイズを取得する
size_t vsk_get_type_size(VskType type);

// 文字列に変換
VskString vsk_to_string(VskShort sht);
VskString vsk_to_string(VskWord wrd);
VskString vsk_to_string(VskLong lng);
VskString vsk_to_string(VskDword dwd);
VskString vsk_to_string(VskSingle sng);
VskString vsk_to_string(VskDouble dbl);
VskString vsk_to_string(const VskString& str);

//////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <algorithm>        // For standard algorithm
#include <limits>           // For limits
#include <ctime>            // For Date/Time

#include "mdbg.h" // Debug output

// メモリーリークの検出（Visual C++のみ）
#if defined(_MSC_VER) && !defined(NDEBUG) && !defined(_CRTDBG_MAP_ALLOC)
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif

//////////////////////////////////////////////////////////////////////////////
// 色

typedef VskDword VskWebColor;       // Webカラー
typedef VskDword VskSystemColor;    // システム カラー

// 赤 (Red)
constexpr VskByte vsk_web_color_red(VskWebColor color)
{
    return VskByte(color >> 16);
}

// 緑 (Green)
constexpr VskByte vsk_web_color_green(VskWebColor color)
{
    return VskByte(color >> 8);
}

// 青 (Blue)
constexpr VskByte vsk_web_color_blue(VskWebColor color)
{
    return VskByte(color);
}

// Webカラーをシステムカラーに変換
inline VskSystemColor vsk_fix_color(VskWebColor color)
{
    auto red = vsk_web_color_red(color);
    auto green = vsk_web_color_green(color);
    auto blue = vsk_web_color_blue(color);
    return blue | (green << 8) | (red << 16);
}

#define vsk_color_black 0x000000 // 黒色
#define vsk_color_white 0xFFFFFF // 白色
#define vsk_color_green 0x00FF00 // 明るい緑色

// Webカラーをシステムカラーに変換
inline VskWebColor vsk_make_web_color(VskByte red, VskByte green, VskByte blue)
{
    return blue | (VskDword(green) << 8) | (VskDword(red) << 16);
}

// グラフィック画面のカラーモード
enum VskPaletteMode
{
    VSK_PAL_MODE_8_COLORS_DIGITAL   = 0,
    VSK_PAL_MODE_8_COLORS_SUPER     = 1,
    VSK_PAL_MODE_16_COLORS_SUPER    = 2,
};

// デフォルトの色を取得
VskWebColor vsk_get_default_digital_color_8(int palette);
VskWebColor vsk_get_default_digital_color_16(int palette);
VskWebColor vsk_get_default_analog_color_16(int palette);

// デジタル8色カラーコードからWebカラーを計算
bool vsk_web_color_from_digital_8_color_code(VskWebColor& web_color, VskDword color_code);
// アナログ8色カラーコードからWebカラーを計算
bool vsk_web_color_from_analog_8_color_code(VskWebColor& web_color, VskDword color_code);
// スーパー16色カラーコードからWebカラーを計算
bool vsk_web_color_from_super_16_color_code(VskWebColor& web_color, VskDword color_code);

//////////////////////////////////////////////////////////////////////////////
// VskError - VeySicKのエラー番号

enum VskError
{
#define DEFINE_ERROR(error_no, id, str) id = error_no,
#include "errors.h"
#undef DEFINE_ERROR
    VSK_ERR_UNPRINTABLE = 256,
    VSK_ERR_MAX
};

//////////////////////////////////////////////////////////////////////////////
// encoding - エンコーディング

#include "encoding.h"

//////////////////////////////////////////////////////////////////////////////
// image - イメージ

// イメージハンドル
typedef void *VskImageHandle;

// 1BPPのイメージを作成する関数
VskImageHandle
vsk_create_1bpp_image(int width, int height);

// XBMから1BPPのイメージを作成する関数
VskImageHandle
vsk_create_1bpp_image_from_xbm(int width, int height, const void *bits);

// 32BPPのイメージを作成する関数
VskImageHandle
vsk_create_32bpp_image(int width, int height, void **ppvBits);

// VskImageクラスの実装
struct VskImageImpl;

// イメージを扱うクラス
struct VskImage : VskObject
{
    struct VskImageImpl *m_pimpl;

    operator VskImageHandle() const;

    VskImage();
    VskImage(VskImageHandle image);
    ~VskImage();

    int width() const;
    int height() const;
    int bpp() const;
    int pitch() const;

    void attach(VskImageHandle image);
    VskImageHandle detach();

    void destroy();

    VskByte *bits(size_t offset = 0);
    const VskByte *bits(size_t offset = 0) const;

    virtual VskSystemColor get_pixel(int x, int y) const { return 0; }
    virtual void set_pixel(int x, int y, VskSystemColor color) { }

    bool inside(int x, int y) const;
};

// 1BPPのイメージを扱うクラス
struct Vsk1BppImage : VskImage
{
    Vsk1BppImage();
    Vsk1BppImage(VskImageHandle image);
    Vsk1BppImage(int width, int height, const void *bits);
};

// 32BPPのイメージを扱うクラス
struct Vsk32BppImage : VskImage
{
    Vsk32BppImage();
    Vsk32BppImage(VskImageHandle image);
    Vsk32BppImage(int width, int height);
    VskWebColor get_pixel(int x, int y) const override;
    void set_pixel(int x, int y, VskSystemColor color) override;
    void clear();
};

//////////////////////////////////////////////////////////////////////////////
// VskScreenPutter - スクリーンイメージにピクセルをセットするクラス

struct VskScreenPutter
{
    VskImage& m_image;
    VskSystemColor m_color;
    VskScreenPutter(VskImage& image, VskWebColor color)
        : m_image(image)
        , m_color(vsk_fix_color(color))
    {
    }
    void operator()(int x, int y)
    {
        m_image.set_pixel(x, y, m_color);
    }
};

//////////////////////////////////////////////////////////////////////////////
// VskColorGetter / VskPixelPutter - 色を取得またはセットするインターフェイス

struct VskColorGetter
{
    virtual int operator()(int x, int y) = 0;
};

struct VskPixelPutter
{
    virtual void operator()(int x, int y) = 0;
    virtual void set_color(int palette) { }
};

//////////////////////////////////////////////////////////////////////////////
// Files - ファイル

// ファイル
struct VskFile : VskObject
{
public:
    // ファイルの種類
    enum TYPE
    {
        TYPE_HOST_FILE, TYPE_SCREEN, TYPE_KEYBOARD, TYPE_CASETTE, TYPE_COM,
        TYPE_LINE_PRINTER
    };

    // ファイルのモード
    enum MODE
    {
        MODE_INPUT, MODE_OUTPUT, MODE_APPEND, MODE_DEFAULT,
    };

    bool is_sequential() const      { return m_type == TYPE_HOST_FILE && m_mode != MODE_DEFAULT; }
    bool is_random() const          { return m_type == TYPE_HOST_FILE && m_mode == MODE_DEFAULT; }
    bool is_keyboard() const        { return m_type == TYPE_KEYBOARD; }
    bool is_screen() const          { return m_type == TYPE_SCREEN; }
    bool is_com() const             { return m_type == TYPE_COM; }
    bool is_line_printer() const    { return m_type == TYPE_LINE_PRINTER; }
    bool is_casette() const         { return m_type == TYPE_CASETTE; }
    bool is_input() const           { return m_mode == MODE_INPUT || m_mode == MODE_DEFAULT; }
    bool is_output() const          { return m_mode == MODE_OUTPUT || m_mode == MODE_APPEND || m_mode == MODE_DEFAULT; }

protected:
    TYPE m_type;
    MODE m_mode;
    friend struct VskFileManager;
    VskFile() = delete;
    VskFile(TYPE type, MODE mode) : m_type(type), m_mode(mode) { }
    virtual ~VskFile() { close(); }

public:
    // Close file (CLOSE)
    virtual void close()                            { flush(); }
    // End of file? (EOF)
    virtual bool eof() const                        { return false; }
    // Column (POS / LPOS)
    virtual int  get_x() const                      { return 0; }
    virtual void set_x(int x)                       { }

    // File position (POS / FPOS / LPOS)
    virtual bool get_pos(VskDword *poffset) const   { return false; }
    virtual bool set_pos(VskDword pos)              { return false; }
    // File size (LOF)
    virtual bool get_size(VskDword *psize) const    { return false; }
    // width of one line (WIDTH# / WIDTH LPRINT)
    virtual int  line_width() const                 { return 1024;  }
    virtual bool line_width(int value)              { return false; }

    // input (INPUT / INPUT# / INPUT$ / LINE INPUT / LINE INPUT# / KINPUT)
    virtual VskError read_bin(void *ptr, VskDword size)         { return VSK_ERR_BAD_CALL; }
    virtual VskError read_line(std::string& data)               { return VSK_ERR_BAD_CALL; }
    // output (PRINT / PRINT# / WRITE / WRITE#)
    virtual VskError write_bin(const void *ptr, VskDword size)  { return VSK_ERR_BAD_CALL; }
    virtual VskError write_str(const std::string& str)          { return VSK_ERR_BAD_CALL; }
    virtual VskError write_line(const std::string& data)        { return VSK_ERR_BAD_CALL; }
    // flush
    virtual void flush() { }
    // COM parameters
    virtual bool set_com_params(VskString params) { return true; }
};
typedef std::shared_ptr<VskFile> VskFilePtr;

// 安全地帯のパスファイル名か？
bool vsk_is_safe_zone_pathname(VskString pathname, bool for_write);
// ファイル記述子（file descriptor）をパースする
bool vsk_parse_file_descriptor(VskString descriptor, VskFile::TYPE& type, VskString& device, VskString& raw_path);

// ファイル管理
struct VskFileManager : VskObject
{
    std::map<int, VskFilePtr> m_file_no_to_file_map;

    VskError open(VskFilePtr& file, VskString descriptor, VskFile::MODE mode = VskFile::MODE_DEFAULT);
    VskError open_host_file(VskFilePtr& file, const VskString& raw_path, VskFile::MODE mode = VskFile::MODE_DEFAULT, VskFile::TYPE type = VskFile::TYPE_HOST_FILE);
    VskError open_screen(VskFilePtr& file, VskFile::MODE mode = VskFile::MODE_DEFAULT);
    VskError open_keyboard(VskFilePtr& file, VskFile::MODE mode = VskFile::MODE_DEFAULT);
    VskError open_line_printer(VskFilePtr& file, VskFile::MODE mode = VskFile::MODE_DEFAULT);
    VskError open_com_file(VskFilePtr& file, VskString device, const VskString& params);

    // association - ファイル番号とファイルの関連付け
    VskFilePtr assoc(int file_no);
    void assoc(int file_no, VskFilePtr file);

    void close(int file_no);
    void close(VskFilePtr file);
    void close_all();
};

// ファイルを全部閉じる
void vsk_file_close_all(void);

//////////////////////////////////////////////////////////////////////////////
// memory model - メモリーモデル

#include "mem.h"

struct VskMachineState;

//////////////////////////////////////////////////////////////////////////////
// VskVarMemoryBlock --- 変数メモリーブロック

struct VskVarMemoryBlock : VskSimpleMemoryBlock
{
    VskMachineState *m_state = nullptr;
    VskVarMemoryBlock(VskMachineState *state);

    VskAddr base_addr() const override;
};
extern std::shared_ptr<VskVarMemoryBlock> vsk_vars_block;

//////////////////////////////////////////////////////////////////////////////
// VskStrMemoryBlock --- 文字列メモリーブロック

struct VskStrMemoryBlock : VskSimpleMemoryBlock
{
    VskMachineState *m_state = nullptr;
    VskStrMemoryBlock(VskMachineState *state);
};
extern std::shared_ptr<VskStrMemoryBlock> vsk_str_block;

//////////////////////////////////////////////////////////////////////////////
// 文字の論理属性値

struct VskLogAttr
{
    VskDword m_palette : 7;      // 0～7: black, blue, ..., yellow, white
    VskDword m_effect : 7;       // 0～7: secret, blink, and/or reverse
    VskDword m_semigra : 1;      // 0 or 1
    VskDword m_upperline : 1;    // 0 or 1
    VskDword m_underline : 1;    // 0 or 1

    void reset()
    {
        std::memset(this, 0, sizeof(*this));
        m_palette = 7;
    }
    bool secret() const { return (m_effect & 1); }
    bool blink() const { return (m_effect & 2); }
    bool reverse() const { return (m_effect & 4); }
    void secret(bool value) {
        if (value)
            m_effect |= 1;
        else
            m_effect &= ~1;
    }
    void blink(bool value) {
        if (value)
            m_effect |= 2;
        else
            m_effect &= ~2;
    }
    void reverse(bool value) {
        if (value)
            m_effect |= 4;
        else
            m_effect &= ~4;
    }
    bool operator==(const VskLogAttr& other) const
    {
        return std::memcmp(this, &other, sizeof(other)) == 0;
    }
    bool operator!=(const VskLogAttr& other) const
    {
        return std::memcmp(this, &other, sizeof(other)) != 0;
    }
};

//////////////////////////////////////////////////////////////////////////////
// machine state - マシン状態

#define VSK_SCREEN_WIDTH 640
#define VSK_SCREEN_HEIGHT 400

// マシンモード
enum VskMachineMode
{
    VSK_MACHINE_MODE_8801,  // 8801モード
    VSK_MACHINE_MODE_9801,  // 9801モード
};

// テキストモード
enum VskTextMode
{
    VSK_TEXT_MODE_SJIS,     // SJISモード
    VSK_TEXT_MODE_GRPH,     // GRPHモード
    VSK_TEXT_MODE_JIS,      // JISモード
};

// machine detailed implementation
struct VskMachineImpl;

// エラー情報
struct VskErrorInfo
{
    VskError    m_error_code     = VSK_NO_ERROR;    // エラーコード
    VskLineNo   m_error_line     = 0;               // エラー行番号
    VskColumnNo m_error_column   = 0;               // エラー桁番号
    void clear()
    {
        m_error_code = VSK_NO_ERROR;
        m_error_line = 0;
        m_error_column = 0;
    }
};

// 待ちの種類
enum VskWaitFor
{
    VSK_NO_WAIT = 0,
    VSK_WAIT_FOR_COMMAND,
    VSK_WAIT_FOR_INPORT,
    VSK_WAIT_FOR_INPUT,
    VSK_WAIT_FOR_INPUT_dollar,
    VSK_WAIT_FOR_INPUT_sharp,
    VSK_WAIT_FOR_DRAW,
    VSK_WAIT_FOR_TURTLE,
    VSK_WAIT_FOR_PLAY,
    VSK_WAIT_FOR_SLEEP,
};

// マシン状態
struct VskMachineState
{
    std::shared_ptr<VskMachineImpl> m_pimpl;                            // 実装詳細

    // text console
    int m_text_width                        = 80;                       // テキスト画面の幅（文字単位）
    int m_text_height                       = 25;                       // テキスト画面の高さ（文字単位）
    bool m_text_wider                       = false;                    // テキスト画面の文字の幅が2倍か？
    bool m_text_longer                      = false;                    // テキスト画面の文字の高さが比較的高いか？
    bool m_show_text                        = true;                     // テキスト画面を表示するか？
    int m_blink_interval                    = 500;                      // キャレットの点滅間隔（ミリ秒）
    int m_blink_flag                        = 0;                        // キャレットの点滅フラグ
    bool m_show_caret                       = true;                     // キャレットを表示するか？
    int m_caret_x                           = 0;                        // キャレットの水平位置（文字単位）
    int m_caret_y                           = 0;                        // キャレットの垂直位置（文字単位）
    int m_console_y0                        = 0;                        // コンソールのスクロール範囲の最初の行の垂直位置
    int m_console_cy0                       = 25;                       // コンソールのスクロール範囲の行数
    VskLogAttr m_text_attr                  = { 7 };                    // テキスト画面のテキスト属性
    VskByte m_line_link[25]                 = { 0 };                    // 行リンク（次の行とつながっているか？）
    int m_input_dollar_length               = 0;                        // INPUT$の長さ
    VskString m_input_string                = "";                       // INPUT$/INPUT#のバッファ

    // graphic screen
    int m_screen_mode                       = 0;            // スクリーンモード
    int m_screen_width                      = 640;          // スクリーンの幅（ピクセル単位）
    int m_screen_height                     = 200;          // スクリーンの高さ（ピクセル単位）
    int m_active_page                       = 0;            // 描画ページ
    int m_display_pages                     = 1;            // 表示ページ
    bool m_show_graphics                    = true;         // グラフィック画面を表示するか？
    VskPointS m_last_point_in_world         = { 0, 0 };     // LP (Last referenced Point) ワールド座標
    int m_vram_bank                         = 0;            // VRAMのバンク番号
    int m_display_pages_flags               = 0;            // 表示ページのフラグ
    VskRectS m_window                       = { 0, 0, 640 - 1, 200 - 1 };   // ワールド座標の範囲
    VskRectI m_viewport                     = { 0, 0, 640 - 1, 200 - 1 };   // ビューポート座標の範囲
    bool is_height_200() const {
        return m_screen_height == 200;
    }

    // colors
    bool m_color_text                       = false;        // テキスト画面がカラーか？
    bool m_color_graphics                   = true;         // グラフィック画面がカラーか？
    int m_text_color                        = 7;            // テキストの色
    int m_fore_color                        = 7;            // グラフィック画面の前景色
    int m_back_color                        = 0;            // グラフィック画面の背景色
    int m_border_color                      = -1;           // グラフィック画面の境界色
    bool m_green_console                    = false;        // テキスト画面がモノクロのとき緑色で表示するか？
    VskPaletteMode m_palette_mode           = VSK_PAL_MODE_8_COLORS_DIGITAL;  // パレットモード
    VskWebColor m_palette[16];                              // パレット番号からWebカラーへ

    int get_graphics_num_planes() const;

    VskWebColor text_color_to_web_color(VskByte palette) const;
    VskWebColor palette_to_web_color(VskByte palette) const;

    // Function keys-related
    bool m_show_function_keys               = true;
    std::vector<VskString> m_function_keys =
    {
        "load \"",
        "auto ",
        "go to ",
        "list ",
        "run\r",
        "save \"",
        "key ",
        "print ",
        "edit .\r",
        "cont\r",
    };

    // memory model
    std::shared_ptr<VskMemoryModel> m_memory;
    VskDword m_segment                      = 0;
    VskType def_var_types['Z' - 'A' + 1]    = { 0 };

    // errors
    VskErrorInfo m_error;
    VskError&       error_code()    { return m_error.m_error_code; }
    VskLineNo&      error_line()    { return m_error.m_error_line; }
    VskColumnNo&    error_column()  { return m_error.m_error_column; }
               void error_clear()   { m_error.clear(); }

    // misc
    VskWaitFor m_wait_for                   = VSK_NO_WAIT;  // 何を待っているのか
    VskString m_input_prompt                = "";           // 入力プロンプト
    VskLong m_input_wait_start              = 0;            // 入力待ち開始
    VskLong m_input_wait_interval           = 0;            // 入力待ち間隔
    VskIndexList m_input_wait_default_path  = { };          // 入力待ち終了コントロールパス
    bool m_insert_mode                      = false;        // 挿入モード
    bool m_auto_mode                        = false;        // AUTOモード (行番号自動入力)
    bool m_kanji_mode                       = false;        // 漢字モード
    bool m_kana_mode                        = false;        // カナモード
    bool m_has_cmd_extension                = false;        // 拡張命令が有効か？
    bool m_has_turtle                       = false;        // タートルグラフィック拡張命令が有効か？
    bool m_edit_mode                        = false;        // 編集モード (EDIT文による)
    int m_option_base                       = -1;           // -1: default, 0: zero, 1: one
    int m_how_many_files                    = 15;           // 使用できるファイルの個数
    int m_wait_inport_port                  = 0;            // 待っているインポート
    int m_wait_inport_data1                 = 0;            // インポート待ちのデータ1
    int m_wait_inport_data2                 = 0;            // インポート待ちのデータ2
    VskFilePtr m_screen_device;
    VskFilePtr m_keyboard_device;
    VskFilePtr m_line_printer;
    std::shared_ptr<VskFileManager> m_file_manager;

    bool is_caret_blinking() const;

    VskMachineState();
    ~VskMachineState();
};

//////////////////////////////////////////////////////////////////////////////
// VeySicKの設定

#include "settings.h"

//////////////////////////////////////////////////////////////////////////////

std::shared_ptr<VskFileManager> vsk_get_file_manager(void);
VskFilePtr vsk_get_screen_device(void);
VskFilePtr vsk_get_keyboard_device(void);
VskFilePtr vsk_get_line_printer(void);

// ボーダーカラーをセット
void vsk_reset_border_color(int border_color);

// VeySicK マシン
struct VskMachine : VskObject
{
    // マシン状態
    VskMachineState *m_state = nullptr;
    VskSettings *m_settings = nullptr;

    VskMachine(VskMachineState *state, VskSettings *settings);
    ~VskMachine();

    bool is_8801_mode() const;
    bool is_9801_mode() const;
    bool is_grph_mode() const;
    bool is_jis_mode() const;
    bool is_sjis_mode() const;
    bool has_turtle() const;
    bool has_cmd_extension() const;

    // アドレスの解決
    VskAddr resolve_addr(VskAddr segment, VskAddr offset) const
    {
        return (segment << 4) | offset;
    }
    VskAddr resolve_addr(VskAddr addr) const
    {
        return resolve_addr(m_state->m_segment, addr);
    }
    VskAddr unresolve_addr(VskAddr* segment, VskAddr addr) const
    {
        *segment = (addr >> 4) & 0xFF00;
        return (addr & 0x0FFF);
    }
    VskAddr unresolve_addr(VskAddr addr) const
    {
        return (addr - (m_state->m_segment << 4)) & 0x0FFF;
    }
    VskError binary_load(const char *filename, VskAddr addr, VskDword& size);
    VskError binary_save(const char *filename, VskAddr addr, VskDword size);
    VskError binary_load_with_header(const char *filename, VskAddr addr, VskDword& size, VskAddr& call_addr);
    VskError binary_save_with_header(const char *filename, VskAddr addr, VskDword size);

    virtual void reset() { }
    virtual void reset_palette() { }
    virtual void reset_border_color() { vsk_reset_border_color(m_state->m_border_color); }
    virtual void reset_text() { }
    virtual void reset_graphics() { }

    virtual void clear_text();
    virtual void clear_text(int y0, int y1) { }
    virtual void clear_graphic();
    void clear_graphic(int back_color);
    void clear_graphic(const VskRectI* rect);
    virtual void clear_graphic(const VskRectI* rect, int back_color);
    virtual void clear_planes(bool blue, bool red, bool green, bool intensity) { }
    virtual void clear_screen_image() { }
    virtual bool clear_memory(VskDword addr) { return true; }
    virtual VskDword get_free_size() { return 0; }
    virtual VskDword get_free_ubound() { return 0; }
    virtual bool special_memory_read(VskByte *ptr, VskAddr addr) { return false; }

    virtual VskByte& line_link(int y)       { return m_state->m_line_link[y]; }
    virtual VskByte  line_link(int y) const { return m_state->m_line_link[y]; }

    virtual Vsk32BppImage *get_screen_image() { return nullptr; }
    virtual void render() { }
    virtual bool connect(bool do_connect);

    virtual bool is_ank(int x, int y) const { return true; }
    virtual VskByte get_ank(int x, int y) const { return 0; }
    virtual void set_ank(int x, int y, VskByte ch) { }

    virtual void set_attr(int x, int y, const VskLogAttr& attr) { }

    virtual VskWord get_jis(int x, int y) const { return 0; }
    virtual void set_jis(int x, int y, VskWord jis) { }

    virtual std::shared_ptr<VskColorGetter> get_color_getter(const VskRectI *viewport) { return nullptr; }
    virtual std::shared_ptr<VskPixelPutter> get_color_putter(int palette, const VskRectI *viewport) { return nullptr; }
    virtual std::shared_ptr<VskPixelPutter> get_tile_putter(VskString tile, const VskRectI *viewport) { return nullptr; }

    virtual bool get_next_x_y(int& next_x, int& next_y, int x, int y) const;
    virtual bool get_prev_x_y(int& prev_x, int& prev_y, int x, int y) const;

    void print_ch(VskWord ch, bool do_control = true);
    void keyboard_ch(VskWord ch);
    void print_control(VskByte ch);
    void control_code(VskByte ch);
    void print(const VskString& str);
    void print_raw(const VskString& str);
    void keyboard_str(const VskString& str);
    virtual void scroll_down(int y0, int y1) { }
    virtual void scroll_up(int y0, int y1) { }
    void scroll_down();
    void scroll_up();
    void edit_down();
    void edit_up();
    void move_to_top();
    void move_to_bottom();

    void function_key(int index, bool shift = false);
    bool get_function_key_position(int key_no, int& x, int& cx, int& delta_text, bool shift = false) const;
    int hit_test_function_key(int x, int y) const;
    bool hit_text_char(int& text_x, int& text_y, int client_x, int client_y) const;

    void pen(int x, int y, bool pressed);
    void stop();
    void help();
    void back_word();
    void forward_word();
    void delete_word();
    void delete_after();
    void delete_line();
    void back_space();
    void tab();
    void home();
    void line_feed();
    void carriage_return(bool do_execute = false);
    void direct_execute(const VskString& text);
    bool do_error(VskError error);
    bool had_error() const;
    void toggle_insert();
    void move_right();
    void move_left();
    void move_up();
    void move_down();
    void move_to_line_end();
    void do_delete();
    void set_insert_mode(bool insert);
    void fix_caret_pos(bool go_next);
    void fix_text_pos(int& x, int& y, bool go_next) const;
    VskString copy_text_screen();
    void syntax_error();
    void bad_call();

    int get_line_root(int y) const;
    VskString get_line_text(int y) const;
    VskString get_line_text() const;
    int get_line_column() const;
    void set_line_text(int y, VskString text);
    void set_line_column(int column);
    VskString get_input_text() const;

    VskPointI world_to_view(const VskPointS& pt) const;
    VskPointS view_to_world(const VskPointI& pt) const;
    VskPointI view_to_screen(const VskPointI& pt) const;
    VskPointI screen_to_view(const VskPointI& pt) const;
    VskPointI screen_to_view(const VskPointS& pt) const;
    VskPointS screen_to_world(const VskPointI& pt) const;
    VskPointS screen_to_world(const VskPointS& pt) const;
    VskPointI world_to_screen(const VskPointS& pt) const;
    VskPointS world_to_client(const VskPointI& pt) const { return world_to_client(VskPointS{ VskSingle(pt.m_x), VskSingle(pt.m_y) }); }
    VskPointS world_to_client(const VskPointS& pt) const;
    VskPointS client_to_world(const VskPointI& pt) const;
    virtual bool is_valid_screen_mode(int screen_mode) const { return true; }
    virtual bool is_valid_active_page(int screen_mode, int active_page, bool high_color) const { return true; }
    virtual int get_display_pages_flags(int screen_mode, int display_pages) { return -1; }

    bool is_valid_tile(const VskString& tile) const;
    bool is_valid_color(int palette) const;

    int get_pixel(int x0, int y0);
    void set_pixel(int x0, int y0, int palette);
    void draw_line(int x0, int y0, int x1, int y1, int palette, VskWord line_style = 0xFFFF);
    void draw_box(int x0, int y0, int x1, int y1, int palette, VskWord line_style = 0xFFFF, const VskRectI* clipping = nullptr);
    void fill_box(int x0, int y0, int x1, int y1, int palette, const VskString& tile = "");
    void draw_circle(int x0, int y0, int r, int palette);
    void fill_circle(int x0, int y0, int r, int palette);
    void draw_ellipse(int x0, int y0, int x1, int y1, int palette);
    void fill_ellipse(int x0, int y0, int x1, int y1, int palette, const VskString& tile = "");
    void draw_arc(int x0, int y0, int x1, int y1, VskDouble start_angle, VskDouble end_angle, int palette);
    void fill_arc(int x0, int y0, int x1, int y1, VskDouble start_angle, VskDouble end_angle, int palette, const VskString& tile = "");
    void flood_fill(int x0, int y0, int fill_color, int border_color, const VskString& tile = "");
    void draw_scroll(int dx0, int dy0, int fill_color);
    void draw_kanji(int x, int y, VskWord jis, const VskString& op, int fore_color, int back_color, bool is_9801);
    bool get_image(int x0, int y0, int cx, int cy, void *ptr, size_t size, int M);
    bool put_image(int x0, int y0, const void *ptr, size_t size, int M, const VskString& op);
    bool put_image(int x0, int y0, const void *ptr, size_t size, int M, const VskString& op, int fore_color, int back_color);

    static std::shared_ptr<VskMachine> create_machine(VskMachineState *state, VskSettings *settings);
    void test_pattern(int type);
    bool step();

    VskError load(VskString filename, std::string& data);
    VskError save(VskString filename, const std::string& data);
    bool run();
};

// マシンへのポインタ
struct VskMachine;
typedef std::shared_ptr<VskMachine> VskMachinePtr;
extern VskMachinePtr vsk_machine;

// マシン状態へのポインタ
#define VSK_STATE() vsk_machine->m_state
// マシンの実装へのポインタ
#define VSK_IMPL() vsk_machine->m_state->m_pimpl
// 設定へのポインタ
#define VSK_SETTINGS() vsk_machine->m_settings

// マシンを作成する関数
#ifdef ENABLE_VM8801
    std::shared_ptr<VskMachine> vsk_create_8801_machine(VskMachineState *state, VskSettings *settings);
#endif
#ifdef ENABLE_VM9801
    std::shared_ptr<VskMachine> vsk_create_9801_machine(VskMachineState *state, VskSettings *settings);
#endif

// かなモードでアルファベットを半角カナに変換
VskByte vsk_abc_to_kana(VskByte ch, bool shift);
// Shiftキーが押されているか？
bool vsk_is_shift_pressed(void);
// Ctrlキーが押されているか？
bool vsk_is_ctrl_pressed(void);
// Altキーが押されているか？
bool vsk_is_alt_pressed(void);
// キーが押されているか？
bool vsk_is_pressed(int vk);
// 直接実行
void vsk_direct_execute(const VskString& text);
// ステップ実行
bool vsk_step(void);
// 入力ポートの値を取得
VskInt vsk_inport_8801(VskInt port);
// 入力ポートの値を取得
VskInt vsk_inport_9801(VskInt port);
// マシンの接続または接続の切断
bool vsk_connect_machine(VskMachineState *state, VskSettings *settings, bool do_connect);
// コメントを処理する
void vsk_process_comment(VskString text);
// STOP (Ctrl+C)を処理する
void vsk_stop(void);
// ファンクションキーを処理する
void vsk_function_key(int index, bool shift);
// HELPを処理する
void vsk_help(void);
// エラーを処理する
bool vsk_error(VskError error);
// ライトペンを処理する
void vsk_pen(int x, int y, bool pressed);
// マウスを処理する
bool vsk_mouse(int x, int y, int left, int right);
// マウスの位置と表示・非表示
void vsk_set_mouse_pos(int x0, int y0, bool visible);
// マウスをクリッピングする
void vsk_mouse_clip(int x0, int y0, int x1, int y1);
// コマンドレベルへ入る
void vsk_enter_command_level(bool show_ok = true);
// VeySicK.exeのあるフォルダを返す
VskString vsk_get_root(void);
// ドライブのパスを取得
VskString vsk_get_drive_path(int drive_no);
// ファイル名群を取得する
VskError vsk_files_helper(std::vector<VskString>& files, VskString& device, VskString path);
VskError vsk_files_helper(std::vector<VskString>& files, VskString& device, VskInt drive_no);
// INKEY$ 用
extern VskByte vsk_inkey;
// マウスクリックでキャレット位置を移動する
void vsk_caret_move_by_mouse_click(int text_x, int text_y);
// スクリーンショットを保存する
bool vsk_save_screenshot(bool text, bool graphics, bool half);
// テキストを出力
void vsk_print(const VskString& str);
// テキストを出力
template <typename T_TYPE>
inline void vsk_print(T_TYPE value)
{
    vsk_print(vsk_to_string(value));
}
// 入力テキストを入れる
void vsk_enter_input_text(const VskString& text);
// 入力プロンプトを表示する
void vsk_show_input_prompt(void);
// ミリ秒を返す
VskLong vsk_get_tick_count(void);
// ロックする
void vsk_lock(void);
// ロックを解除
void vsk_unlock(void);
// ミリ秒待つ
void vsk_sleep(uint32_t wait);
// ページアップ
void vsk_page_up(void);
// ページダウン
void vsk_page_down(void);
// 行テキストから行番号を取得する
VskLineNo vsk_line_number_from_line_text(const VskString& line, char **endptr = nullptr);
// 指定した行番号の前後の行を取得する
VskString vsk_get_next_line_text(VskLineNo number, int which);
// IMEをオンまたはオフにする
void vsk_ime_on_off(bool on);
// フィールドを閉じる
void vsk_field_close(int fileno);
// タートルが表示されているか？
bool vsk_turtle_shown(void);
// タートルの位置をスクリーン座標で返す
VskPointS vsk_turtle_pos_in_screen(void);
// タートルの向きをラジアンで返す
VskSingle vsk_turtle_direction_in_radian(void);
// アプリを終了する
void vsk_app_quit(void);
// ディレクトリを変更する
VskError vsk_chdir(const char *dirname);
// ディレクトリを作成する
VskError vsk_mkdir(const char *dirname);
// 空のディレクトリを削除する
VskError vsk_rmdir(const char *dirname);
// ファイルを削除する
VskError vsk_delete_file(const char *filename);
// パスからファイル名を取り除く
VskString vsk_path_remove_filename(const VskString& pathname);
// 現在のディレクトリを取得する
VskString vsk_getcwd(void);
// BEEP音を鳴らす
void vsk_beep(int number = -1);
// 文字列から数値を読み取る
bool vsk_scan_number(VskString& str, const char *ptr, bool *minus = nullptr, char **dot = nullptr, char **exp = nullptr, char **endptr = nullptr);
// マシンをリセットする
void vsk_reset(VskMachineMode mode);
// ローカル日時を取得
void vsk_get_datetime(int& year_xxxx, int& month, int& day, int& hour, int& minute, int& second);
// ローカル日時を設定
void vsk_set_datetime(int year_xxxx, int month, int day, int hour, int minute, int second);
// 二桁の年を四桁の年に変換
int vsk_year_xxxx_from_year_xx(int year_xx);
// 四桁の年を二桁の年に変換
int vsk_year_xx_from_year_xxxx(int year_xxxx);
// 電源はONか？
extern bool vsk_power_on;
// １バイト中のビット群を逆順にしたものを返す関数
VskByte vsk_reverse_byte(VskByte x);
// 外字を標準フォントから取得
bool vsk_kpload_extension(VskWord jis, VskDword code, VskString ope);
// ラインプリンタを更新する
void vsk_update_line_printer(void);
// 入力テキストを分割する
void vsk_split_input_text(std::vector<VskString>& data, const VskString& text);
// 現在のプロセスに管理者権限があるか？
bool vsk_is_process_elevated(void);
// プログラムのタイトル情報をセットする
void vsk_set_program_title(const VskString& pathname);
