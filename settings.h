#pragma once

// VeySicK�̐ݒ�
struct VskSettings
{
    int m_move_caret_by_mouse_click = false;            // �}�E�X�N���b�N�ŃL�����b�g�ʒu���ړ����邩�H
    int m_remember_window_pos = true;                   // �E�B���h�E�̈ʒu�ƃT�C�Y���L�����邩�H
    int m_x = (int)0x80000000, m_y = (int)0x80000000;   // �E�B���h�E�̈ʒu
    int m_cx = (int)0x80000000, m_cy = (int)0x80000000; // �E�B���h�E�̃T�C�Y
    int m_zoomed = false;                               // �ő剻����Ă��邩�H

    void reset()
    {
        *this = VskSettings();
    }

    bool load();
    bool save() const;
};
