#pragma once

// Create a table of double stored as a jagged array (usual, normal :)

typedef struct {
	double **body; // Pointer to standard two-dimensional array, which is a storage of all our elements
	int numRows;
	int numCols;
} JaggedArray;

void allocateJaggedArray(JaggedArray *pTable, int numRows, int numCols);
void freeJaggedArray(JaggedArray *pTable);
void setJaggedArrayElement(JaggedArray *pTable, int ixRow, int ixCol, double value);
double getJaggedArrayElement(JaggedArray *pTable, int ixRow, int ixCol);
void setConsecutiveValuesJaggedArray(JaggedArray *pTable);
void printJaggedArray(JaggedArray *pTable);
