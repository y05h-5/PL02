
// Array sorting by using bubble sort
void sortArray( int *a, int n )
{
	for( int i = 1; i < n; i++ )
	{
		for( int j = n-1; j>=i; j-- )
		{
			if( a[ j ] < a[ j-1 ] )
			{
				int copy;
	
				copy = a[ j ];
				a[ j ] = a[ j-1 ];
				a[ j-1 ] = copy;
			}
		}
	}
}
