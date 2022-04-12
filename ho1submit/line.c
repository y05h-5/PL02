#include "Point.h"
#include "Line.h"

int constructLine(Line* pLine, Point p1, Point p2) {
	if (p1.x==p2.x && p1.y== p2.y) return 0; // Points are the same, not a line

	pLine->a = p2.y - p1.y;
	pLine->b = p1.x - p2.x;
	pLine->c = -p1.x*pLine->a - p1.y*pLine->b;
	// (parallelism to axes makes no problem)

	return 1;
}

int isInLine(Line line, Point p) {
	return !(line.a*p.x + line.b*p.y + line.c);
}


