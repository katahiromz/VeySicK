#pragma once

#define VSK_8801_SW1_DEFAULT  0x40
#define VSK_8801_SW2_DEFAULT  0x00

#define VSK_9801_SW1_DEFAULT  0x00
#define VSK_9801_SW2_DEFAULT  0x30

// VeySicKのCOM設定
struct VskComSettings
{
    VskDword m_com_default_port = 1;    // 1, 2, 3 or 4
    VskDword m_com_speed = 1200;        // See "com_speed.h"
    VskDword m_com_byte_size = 7;       // 8 or 7
    VskDword m_com_stop_bits = 1;       // 1, 15 or 2
    VskDword m_com_parity = 1;          // 0, 2 or 1
    VskDword m_com_xon_xoff = 0;        // 0 or 1
    VskDword m_com_si_so = 0;           // 0 or 1
};

// VeySicKの設定
struct VskSettings
{
    int m_move_caret_by_mouse_click = false;            // マウスクリックでキャレット位置を移動するか？
    int m_remember_window_pos = true;                   // ウィンドウの位置とサイズを記憶するか？
    int m_x = (int)0x80000000, m_y = (int)0x80000000;   // ウィンドウの位置
    int m_cx = (int)0x80000000, m_cy = (int)0x80000000; // ウィンドウのサイズ
    int m_zoomed = false;                               // 最大化されているか？
    int m_unlimited_mode = true;                        // 無制限モード（実機の制限を乗り越える）
    VskMachineMode m_machine_mode = VSK_MACHINE_MODE_9801;  // マシンモード
    VskTextMode m_text_mode = VSK_TEXT_MODE_GRPH;       // テキストモード
    int m_field_width = 256;                            // フィールド幅
#ifdef ENABLE_VM8801
    VskDword m_8801_sw1 = VSK_8801_SW1_DEFAULT;         // 8801 ディップスイッチ SW1
    VskDword m_8801_sw2 = VSK_8801_SW2_DEFAULT;         // 8801 ディップスイッチ SW2
#endif
#ifdef ENABLE_VM9801
    VskDword m_9801_sw1 = VSK_9801_SW1_DEFAULT;         // 9801 ディップスイッチ SW1
    VskDword m_9801_sw2 = VSK_9801_SW2_DEFAULT;         // 9801 ディップスイッチ SW2
#endif
    VskDword m_draw_odd_lines = 0;                      // 奇数ラインを描画するか？
    VskDword m_empty_loop_wait = 100;                   // 空ループ待ち
    VskDword m_step_exec_wait = 50;                  // 命令実行待ち
    // COM設定
    VskComSettings m_com;

    void reset()
    {
        *this = VskSettings();
    }

    bool load();
    bool save() const;
};
