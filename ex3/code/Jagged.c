#include <stdlib.h>
#include <stdio.h>

#include "includes/Jagged.h"

void allocateJaggedArray(JaggedArray *pTable, int numRows, int numCols) {
	if (numRows <= 0 || numCols <= 0) {
		printf("Error while allocating table memory: wrong sizes\n");
		exit(EXIT_FAILURE);
	}
	pTable->numRows = numRows;
	pTable->numCols = numCols;

	pTable->body = (double **)malloc(numRows * sizeof(double*));
	if (pTable->body == NULL) {
		printf("Error while allocating table memory\n");
		exit(EXIT_FAILURE);
	}

	for (int ixRow = 0; ixRow < pTable->numRows; ++ixRow) {
		pTable->body[ixRow] = (double*)malloc(numCols * sizeof(double));
		if (pTable->body[ixRow] == NULL) {
			printf("Error while allocating table memory\n");
			exit(EXIT_FAILURE);
		}
	}
}

void freeJaggedArray(JaggedArray *pTable) {
	for (int ixRow = 0; ixRow < pTable->numRows; ++ixRow) {
		free(pTable->body[ixRow]);
	}
	free(pTable->body);
}

void setJaggedArrayElement(JaggedArray *pTable, int ixRow, int ixCol, double value) {
	pTable->body[ixRow][ixCol] = value;
}

double getJaggedArrayElement(JaggedArray *pTable, int ixRow, int ixCol) {
	return pTable->body[ixRow][ixCol];
}

void setConsecutiveValuesJaggedArray(JaggedArray *pTable) {
	double value_to_set = 0;
	for (int ixRow = 0; ixRow < pTable->numRows; ++ixRow) {
		for (int ixCol = 0; ixCol < pTable->numCols; ++ixCol) {
			value_to_set++; // We are setting the consecutive values begginning from 1 (just as example!)
			setJaggedArrayElement(pTable, ixRow, ixCol, value_to_set);
		}
	}
}

void printJaggedArray(JaggedArray *pTable) {
	for (int ixRow = 0; ixRow < pTable->numRows; ++ixRow) {
		for (int ixCol = 0; ixCol < pTable->numCols; ++ixCol) {
			printf("%.2lf ", getJaggedArrayElement(pTable, ixRow, ixCol));
		}
		printf("\n");
	}
}