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
	FILE *fout;	// Output file

	int *array; 
	int size;

	if( !openFile( &fin, argv[1], "rt" ) )
	{
		exit( 10 );
	}

	size = prereadArray(fin);

	fclose(fin);

	array = (int *)malloc(size * sizeof(int));
	if (array == NULL)
	{
		printf("Unable to allocate the required memory\n");
		exit(999);
	}

	if (!openFile(&fin, argv[1], "rt"))
	{
		exit(10);
	}

	if( size != loadArray(fin, array, size) )
	{
		printf( "Not enough values in the file \"%s\"\n", argv[1] );
		exit( 33 );
	}
	
	if( fclose( fin )==EOF )
	{
		printf( "Input file has not been closed\n" );
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

