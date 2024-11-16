#pragma once

bool vsk_init_sound(void);
void vsk_exit_sound(void);
void vsk_sound_beep(int i);
bool vsk_sound_sing(const VskString& str);
bool vsk_sound_play_ssg(const std::vector<VskString>& strs);
bool vsk_sound_play_fm(const std::vector<VskString>& strs);
bool vsk_sound_play_fm_and_ssg(const std::vector<VskString>& strs);
