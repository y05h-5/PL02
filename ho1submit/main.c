#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Include all necessary files you need...
#include "headers/Line.h"
#include "headers/Point.h"
#include "headers/Triangle.h"

int main() {
	Point pts[3];

	puts("Input 3 verteces:");
	for(int i = 0; i < 3; ++i) {
		printf("vertex #%d: ", i+1);
		readPoint(&pts[i]);
	}

	Triangle tri;
	int triangleValid = constructTriangle(&tri, pts);

	if (triangleValid) {
		computeTriangleArea(&tri);
		printTriangleInfo(tri);
		puts("Program terminating with success...");
	} else {
        puts("");
		puts("Triangle was not constructed.");
		puts("Check your inputs.");
		puts("Program terminating with failure...");
        puts("");
	}

	return (triangleValid)? EXIT_SUCCESS : EXIT_FAILURE;
}