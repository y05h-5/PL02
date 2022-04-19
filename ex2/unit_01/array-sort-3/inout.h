#ifndef _inout_h_
#define _inout_h_

#include <stdio.h>

int openFile( FILE **pFile, char *filename, char *mode );
int loadArray( FILE *fin, int *array, int limit );
int prereadArray(FILE *fin);
int readArrayToTempFile(FILE *fin, FILE *fTemp);
void writeArray( FILE *fout, int *array, int size );
int loadArrayBin(FILE *fTemp, int *array, int limit);

#endif
