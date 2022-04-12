#pragma once

#include <stdio.h>

// 2D point
typedef struct {
	float x;
	float y;
} Point;

float distance(Point p1, Point p2);

int  freadPoint(FILE *fin, Point *pPoint);
void fprintPoint(FILE *fout, Point point);
int  readPoint(Point *pPoint);
void printPoint(Point point);