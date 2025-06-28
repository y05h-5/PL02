#include <stdio.h>
#include <math.h>

#include "headers/Triangle.h"
#include "headers/Point.h"
#include "headers/Line.h"

int constructTriangle(Triangle* pTriangle, Point pts[]) {
	Line line;

	if (!constructLine(&line, pts[0], pts[1])) return 0; // If no line bw p1 and p2, no triangle either

	if (isInLine(line, pts[2])) return 0; // if p3 belongs to the line, no triangle

	// Here we can construct a valid triangle
	for (int i = 0; i < 3; ++i) {
        pTriangle->points[i] = (Point) {
            .x = pts[i].x,
            .y = pts[i].y
        };
	}

    return 1;
}

void computeTriangleArea(Triangle* pTriangle) {
	float side[3];

	side[0] = distance(pTriangle->points[0], pTriangle->points[1]);
	side[1] = distance(pTriangle->points[1], pTriangle->points[2]);
	side[2] = distance(pTriangle->points[0], pTriangle->points[2]);

	float semiPerim = (side[0] + side[1] + side[2]) / 2;
	pTriangle->area = sqrt(semiPerim*(semiPerim - side[0])*(semiPerim - side[1])*(semiPerim - side[2]));
}

void printTriangleInfo(Triangle triangle) {
	printf("\nTriangle Information:\n");
	
	for (int i = 0; i < 3; ++i) {
		printf("	vertex #%d: (%.3f, %.3f)\n", i+1, triangle.points[i].x, triangle.points[i].y);
	}
	puts("");

	printf("	Area: %f\n\n", triangle.area);
}
