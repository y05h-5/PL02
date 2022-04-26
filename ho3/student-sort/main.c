#include <stdio.h>
#include <stdlib.h>

#include "Date.h"
#include "Person.h"
#include "Person_Array.h"
#include "Sort.h"

int main()
{
	FILE *in;
	Person *all;
	int numOfPersons;

	Date currentDate= { 2020, 4, 24};
	
	in = fopen("input.txt", "rt");
	if (in == NULL)
	{
		printf("Unable to open input file\n");
		return EXIT_FAILURE;
	}

	numOfPersons = countRecords(in);
	if (numOfPersons == 0)
	{
		printf("No data in input file\n");
		return EXIT_FAILURE;
	}

	all = (Person *)malloc(numOfPersons * sizeof(Person));
	if (all == NULL )
	{
		printf("Memory allocation error\n");
		return EXIT_FAILURE;
	}

	rewind(in);

	int count = loadRecordsFromTextFile(in, all, numOfPersons);
	if (count != numOfPersons)
	{
		printf("Unknown error. Please contact the developer\n");
		return EXIT_FAILURE;
	}

	fclose(in);

	calculateAges(all, numOfPersons, &currentDate);

	printRecords("Records loaded from input file", stdout, all, numOfPersons);

	sortByName(all, numOfPersons);
	printRecords("Records sorted by name", stdout, all, numOfPersons);

	sortByAge(all, numOfPersons);
	printRecords("Records sorted by age", stdout, all, numOfPersons);

	free(all);
	return EXIT_SUCCESS;
}