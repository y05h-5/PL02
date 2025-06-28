#pragma once

// Create a table of double but stored as one-dimensional array

typedef struct
{
	double *body; // Pointer to one-dimensional array, which is a storage of all our elements
	int numRows;
	int numCols;
} RectangularArray;

void allocateRectangularArray(RectangularArray *pTable, int numRows, int numCols);
void freeRectangularArray(RectangularArray *pTable);
void setRectArrayElement(RectangularArray *pTable, int ixRow, int ixCol, double value);
double getRectArrayElement(RectangularArray *pTable, int ixRow, int ixCol);
void setConsecutiveValuesRectArray(RectangularArray *pTable);
void printRectArray(RectangularArray *pTable);
