#pragma once

typedef struct {
    int x, y;
} Point;

typedef struct {
    int id;
    Point boundup, bounddown;
    int boundR, boundL;
    int width;
    int area;
    char* color;
} Rectangle;

void print_rectangle(const Rectangle* rect);
int get_rectangle(FILEx* fin, Color* color_list, int cl_len, Rectangle* rect);
int get_rectangle_list(FILEx* fin, Color* color_list, int cl_len, Rectangle** rect_list, int* rc_len);
void kill_rectangle_list(Rectangle** rect_list, int len);
int linesweep(Rectangle* rect_list, int len, Color* col_list, int cl_len);
int find_rectanlge_overlap(Rectangle* rect_list, int len);
