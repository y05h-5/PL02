#pragma once
#include "point.h"

typedef struct {
    float a, b, c;
} Line;

int constructLine (Line* pLine, Point p1, Point p2);
int isLine(Line line, Point p);
int isLine1(const Line* line, const Point* p);
