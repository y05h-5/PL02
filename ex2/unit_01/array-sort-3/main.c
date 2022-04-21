#include <stdio.h>
#include <stdlib.h>

#include "main.h"

// #define _MYDEBUG

void main( 
	int argc,	
	char *argv[]
	)
{
	if( argc < 3 )
	{
		printf( "Not enough command line parameters\n" );
		exit( 1 );
	}
	// In here:
	// argv[0] - program name
	// argv[1] - input file name
	// argv[2] - output file name

	FILE *fin;	// Input file
	FILE *fBinData; // Binary file to store all the array elements
	FILE *fout;	// Output file

	int *array; 
	int size;

	if( !openFile( &fin, argv[1], "rt" ) )
	{
		exit( 10 );
	}

	if (!openFile(&fBinData, "data.dat", "wb"))
	{
		exit(14);
	}

	size = readArrayToTempFile(fin,fBinData);

	fclose(fin);
	fclose(fBinData);

	array = (int *)malloc(size * sizeof(int));
	if (array == NULL)
	{
		printf("Unable to allocate the required memory\n");
		exit(999);
	}

	if (!openFile(&fBinData, "data.dat", "rb"))
	{
		exit(15);
	}

	if( size != loadArrayBin(fBinData, array, size) )
	{
		printf( "Not enough values in the file \"%s\"\n", argv[1] );
		exit( 33 );
	}
	
	if( fclose( fBinData )==EOF )
	{
		printf( "Binary file has not been closed\n" );
	}

	// In debug mode we print the initial array
#ifdef _MYDEBUG	
	writeArray( stdout, array, size );
#endif

	sortArray( array, size );	

	if( !openFile( &fout, argv[2], "wt" ) )
	{
		exit( 11 );
	}
	
	writeArray( fout, array, size );

	free(array);

	if( fclose( fout )==EOF )
	{
		printf( "Output file has not been closed\n" );
		exit( 21 );
	}

	exit( 0 );
}

