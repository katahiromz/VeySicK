#pragma once

bool vsk_sound_init(void);
void vsk_sound_exit(void);
bool vsk_sound_is_playing(void);
bool vsk_sound_wait(VskDword milliseconds);
void vsk_sound_stop(void);
void vsk_sound_beep(int i);
bool vsk_sound_sing(const VskString& str);
bool vsk_sound_play_ssg(const std::vector<VskString>& strs);
bool vsk_sound_play_fm(const std::vector<VskString>& strs);
bool vsk_sound_play_fm_and_ssg(const std::vector<VskString>& strs);
bool vsk_sound_voice_copy(void *ptr, VskInt tone);
bool vsk_sound_is_beeping(void);
bool vsk_sound_voice_reg(int addr, int data);
