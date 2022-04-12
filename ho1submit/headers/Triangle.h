#pragma once

#include "Point.h"

typedef struct {
	Point points[3];
	float area;
} Triangle;

int constructTriangle(Triangle* pTriangle, Point* pts);
void computeTriangleArea(Triangle *pTriagle);
void printTriangleInfo(Triangle triangle);