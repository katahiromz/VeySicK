#pragma once

// VeySicKの設定
struct VskSettings
{
    int m_move_caret_by_mouse_click = false;            // マウスクリックでキャレット位置を移動するか？
    int m_remember_window_pos = true;                   // ウィンドウの位置とサイズを記憶するか？
    int m_x = (int)0x80000000, m_y = (int)0x80000000;   // ウィンドウの位置
    int m_cx = (int)0x80000000, m_cy = (int)0x80000000; // ウィンドウのサイズ
    int m_zoomed = false;                               // 最大化されているか？
    int m_unlimited_mode = true;                        // 無制限モード（実機の制限を乗り越える）
    VskMachineMode m_machine_mode = VSK_MACHINE_MODE_9801;

    void reset()
    {
        *this = VskSettings();
    }

    bool load();
    bool save() const;
};
