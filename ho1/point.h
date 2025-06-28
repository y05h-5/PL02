#pragma once

typedef struct {
	float x; float y;
} Point;

int readPoint(Point* p);
float fdistance(Point p1, Point p2);