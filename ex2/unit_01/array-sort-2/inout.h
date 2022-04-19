#ifndef _inout_h_
#define _inout_h_

#include <stdio.h>

int openFile( FILE **pFile, char *filename, char *mode );
int loadArray( FILE *fin, int *array, int limit );
int prereadArray(FILE *fin);
void writeArray( FILE *fout, int *array, int size );

#endif
