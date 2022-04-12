#include <stdio.h>
#include <stdlib.h>

#include "point.h"

int main () {
	Point p1,p2;
	float distance;
	int retScan;

	retScan = scanf("%f, %f", &(p1.x), &(p1.y));
	if (retScan != 2){
		printf("Illegal data format\n");
		return EXIT_FAILURE;	
	}	

	retScan = scanf("%f, %f", &(p2.x), &(p2.y));
	if (retScan != 2){
		printf("Illegal data format\n");
		return EXIT_FAILURE;	
	}	

	distance = fdistance(p1, p2);
	
	printf("distance = %.3f\n", distance);
	return EXIT_SUCCESS;
}