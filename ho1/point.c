#include <stdio.h>
#include <math.h>
#include "point.h"

int readPoint(Point* p) {
	int retScan = scanf("%f %f", &(p->x), &(p->y));
	
    if (retScan != 2){
		printf("Illegal data format\n");
		return 0;	
	}

    return 1;	
}

float fdistance(Point p1, Point p2) {
    return sqrt((p2.x-p1.x)*(p2.x-p1.x) + (p2.y-p1.y)*(p2.y-p1.y));
}