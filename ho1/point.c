#include <math.h>
#include "point.h"

float distance(Point p1, Point p2) {
    return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y));
}