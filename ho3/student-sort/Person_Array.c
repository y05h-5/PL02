#include <stdio.h>
#include <stdlib.h>

#include "Person.h"

int countRecords(FILE *in)
{
	int count = 0;

	for (;;)
	{
		Person temp;
		int checkRead = readPerson(in, &temp);
		if (checkRead == EOF) return count;
		if (checkRead != 1)
		{
			printf("Illegal format for the record No.%d\n", count + 1);
			exit(1);
		}
		++count;
	}
}

int loadRecordsFromTextFile(FILE *in, Person *all, int size)
{
	int count;

	for( count=0; count < size; ++count )
	{
		// Complete this loop body
		// (use readPerson() function to read the array element.
		// Do not forget to check the value returned by readPerson() and
		// print messages in case of reading errors.
		// Stop program by using exit(1) if reading errors are detected.
		// ...

	}
	return count;
}

void printRecords( const char *title, FILE *out, const Person *all, int size)
{
	fprintf(out, "%s\n", title);
;	for (int ix = 0; ix < size; ++ix)
	{
		printPersonLine(out, &(all[ix]));
	}
}

void calculateAges(Person *all, int size, const Date *pCurrent)
{
	// By using getAge() function
	// calculate the ages of all the persons in the array "all"
	// ...

}