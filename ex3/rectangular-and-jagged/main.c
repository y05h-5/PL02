#include <stdlib.h>
#include <stdio.h>

#include "Rectangular.h"
#include "Jagged.h"

void testRectArray();
void testJaggedArray();

void main() {
	testRectArray();
	testJaggedArray();

	exit(EXIT_SUCCESS);
}

void testRectArray() {
	int numRows, numCols;

	printf("Exter table sizes:");
	if (scanf("%d %d", &numRows, &numCols) != 2) {
		printf("Input data format error\n");
		exit(EXIT_FAILURE);
	}

	RectangularArray table;

	allocateRectangularArray(&table, numRows, numCols);


	// Setting some table values
	setConsecutiveValuesRectArray(&table);

	// Printing the table
	printRectArray(&table);

	freeRectangularArray(&table);
}

void testJaggedArray() {
	int numRows, numCols;

	printf("Exter table sizes:");
	if (scanf("%d %d", &numRows, &numCols) != 2) {
		printf("Input data format error\n");
		exit(EXIT_FAILURE);
	}

	JaggedArray table;

	allocateJaggedArray(&table, numRows, numCols);

	// Setting some table values
	setConsecutiveValuesJaggedArray(&table);

	// Printing the table
	printJaggedArray(&table);

	freeJaggedArray(&table);
}
