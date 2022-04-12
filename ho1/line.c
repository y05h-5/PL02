#include "point.h"
#include "line.h"

int constructLine(Line* pLine, Point p1, Point p2) {
    if (p1.x==p2.x && p1.y==p2.y) return 0;

    pLine->a = p2.y-p1.y;
    pLine->b = p1.x-p2.x;
    pLine->c = -p1.x * pLine->a - p1.y * pLine->b;
    
    return 1;
}

int isLine(Line line, Point p) {
    return 
}