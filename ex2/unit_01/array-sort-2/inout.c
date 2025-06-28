
#include <stdio.h>
#include <string.h>

// Opening a file with error handling
int openFile( FILE **pFile,	// pointer to a file 
			   char *filename,	// filename is the same as in fopen
			   char *mode		// mode is the same as in fopen
								
			   )
{
	*pFile = fopen( filename, mode );
	if( *pFile == NULL )
	{
		printf( "Can\'t open file \"%s\" ", filename );
		if( strchr( mode, 'r' ) != NULL ) printf( "for reading" );
		else if( strchr( mode, 'w' ) != NULL ) printf( "for writing" );
		else if( strchr( mode, 'a' ) != NULL ) printf( "for appending" );
		else printf( "in unknown mode" );

		printf( "\n" );
      
		return 0;
	}
	return 1;
}

// Loading an array from file
// The reading process stops:
// - when EOF is found;
// - as soon as we read a given number of values (limit);
// - as soon as we read something which is not integer
// The funcion returns the number of loaded values
int loadArray( FILE *fin, int *array, int limit )
{
	int count;

	for( count=0; count<limit; ++count )
	{
		int retScan = fscanf( fin, "%d", &array[ count ] );
		if( retScan == EOF ) break;
		if( retScan != 1 )
		{
			printf( "Value No. %d: Incorrect format\n", count+1 );
			break;
		}
	}
	return count;
}

// Pre-reading process counts all the elements in the input file 
int prereadArray(FILE *fin)
{
	int count = 0; 

	for (; ; )
	{
		int temp;
		int retScan = fscanf(fin, "%d", &temp);
		if (retScan == EOF) break;
		if (retScan != 1)
		{
			printf("Value No. %d: Incorrect format\n", count + 1);
			break;
		}

		count++;
	}
	return count;
}

// Writing an array to file
void writeArray( FILE *fout, int *array, int size )
{
	for( int ix=0; ix<size; ++ix )
	{
		fprintf( fout, "%3d : %d\n", ix, array[ ix ] );
	}
}
