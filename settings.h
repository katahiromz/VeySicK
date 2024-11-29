#pragma once

#define VSK_8801_SW1_DEFAULT  0x40
#define VSK_8801_SW2_DEFAULT  0x00

#define VSK_9801_SW1_DEFAULT  0x00
#define VSK_9801_SW2_DEFAULT  0x30

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

    void reset()
    {
        *this = VskSettings();
    }

    bool load();
    bool save() const;
};
