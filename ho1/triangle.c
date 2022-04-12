#include "point.h"
#include "triangle.h"
#include "line.h"

int constructTriangle(Triangle* pTriangle, Point p1, Point p2, Point p3) {
    Line line;

    if (!constructLine(&line, p1, p2)) return 0;
    if (isLine(line, p3)) return 0;

    pTriangle->point[0] = p1;
    pTriangle->point[1] = p2;
    pTriangle->point[2] = p3;
}

/*  
  "editor.bracketPairColorization.enabled": true,
  "editor.guides.bracketPairs":"active"
*/