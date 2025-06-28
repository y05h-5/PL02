#pragma once

typedef struct {
    int x, y;
} Point;

typedef struct {
    int id;
    Point boundup, bounddown;
    int boundR, boundL;
    int width;
} Rectangle;

int get_rectangle(FILEx* fin, Rectangle* rect);
int get_rectangle_list(FILEx* fin, Rectangle** arr_rect, int* len);
int find_rectanlge_overlap(int arrlen, Rectangle* arr_rect);
