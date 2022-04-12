#include <stdio.h>
#include <stdlib.h>

#include "point.h"

int main () {
	Point p1,p2;
	float distance;
	int retScan;

	if (readPoint(&p1) != 1) return EXIT_FAILURE;
	if (readPoint(&p2) != 1) return EXIT_FAILURE;

	distance = fdistance(p1, p2);
    	
	printf("distance = %.3f\n", distance);
	return EXIT_SUCCESS;
}