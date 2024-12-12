#pragma once

#include "VeySicK.h"

VskImageHandle
text_to_bitmap(int& total_pages, std::string& text, int max_x = 120, int max_y = 80, int margin = 16, int page = 1, bool is_8801 = false, bool bold = false);
