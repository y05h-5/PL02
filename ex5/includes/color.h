#pragma once

#include "file_handler.h"

typedef char* Color;

int get_color_list(FILEx* fcl, Color** colors, int* len);
int check_color(Color* list, const Color color, int cl_len, int rect_id);
void kill_color_list(Color** list, int len);