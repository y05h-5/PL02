#include <stdlib.h>
#include <stdio.h>

#include "Rectangular.h"

void allocateRectangularArray(RectangularArray *pTable, int numRows, int numCols) {
	if (numRows <= 0 || numCols <= 0) {
		printf("Error while allocating table memomry: wrong sizes\n");
		exit(EXIT_FAILURE);
	}
	pTable->numRows = numRows;
	pTable->numCols = numCols;

	pTable->body = (double *)malloc(numRows * numCols * sizeof(double));
	if (pTable->body == NULL) {
		exit(EXIT_FAILURE);
	}
}

void freeRectangularArray(RectangularArray *pTable) {
	free(pTable->body);
}

void setRectArrayElement(RectangularArray *pTable, int ixRow, int ixCol, double value) {
	int internalIndex = ixRow * pTable->numCols + ixCol;
	pTable->body[internalIndex] = value;
}

double getRectArrayElement(RectangularArray *pTable, int ixRow, int ixCol) {
	int internalIndex = ixRow * pTable->numCols + ixCol;
	return pTable->body[internalIndex];
}

void setConsecutiveValuesRectArray(RectangularArray *pTable) {
	double value_to_set = 0;
	for (int ixRow = 0; ixRow < pTable->numRows; ++ixRow) {
		for (int ixCol = 0; ixCol < pTable->numCols; ++ixCol) {
			value_to_set++; // We are setting the consecutive values begginning from 1 (just as example!)
			setRectArrayElement(pTable, ixRow, ixCol, value_to_set);
		}
	}
}

void printRectArray(RectangularArray *pTable) {
	for (int ixRow = 0; ixRow < pTable->numRows; ++ixRow) {
		for (int ixCol = 0; ixCol < pTable->numCols; ++ixCol) {
			printf("%.2lf ", getRectArrayElement(pTable, ixRow, ixCol));
		}
		printf("\n");
	}
}
