#pragma once
#include "point.h"

typedef struct {
    Point point[3];
    float area;
} Triangle;

int readTriangle() {
    return 0;
}

int constructTriangle(Triangle* pTriangle, Point p1, Point p2, Point p3);