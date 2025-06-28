#pragma once
#include "Point.h"

// Line equation: a*x+b*y+c=0
typedef struct {
	// Line coefficients
	float a;
	float b;
	float c;
} Line;

int constructLine(Line* pLine, Point p1, Point p2);
int isInLine(Line line, Point p);