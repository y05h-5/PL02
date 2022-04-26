#include <stdio.h>
#include <stdlib.h>

#include "Date.h"
#include "Person.h"
#include "Person_Array.h"
#include "Sort.h"

int main(int argc, char* argv[]) {
	FILE *in;
	Person *all;
	int numOfPersons;

	const Date currentDate = {2022, 4, 28};
	
	

	in = fopen("input.txt", "rt");
	if (in == NULL) {
		printf("Unable to open input file\n");
		return EXIT_FAILURE;
	}

	numOfPersons = countRecords(in);
	if (numOfPersons == 0) {
		printf("No data in input file\n");
		return EXIT_FAILURE;
	}

	all = (Person *)malloc(numOfPersons * sizeof(Person));
	if (all == NULL ) {
		printf("Memory allocation error\n");
		return EXIT_FAILURE;
	}

	rewind(in);

	int count = loadRecordsFromTextFile(in, all, numOfPersons);
	if (count != numOfPersons) {
		printf("Unknown error. Please contact the developer\n");
		return EXIT_FAILURE;
	}

	fclose(in);

	calculateAges(all, numOfPersons, &currentDate);

	printRecords("Records loaded from input file", stdout, all, numOfPersons); puts("");

	sortByName(all, numOfPersons);
	printRecords("Records sorted by name", stdout, all, numOfPersons); puts("");

	sortByAge(all, numOfPersons);
	printRecords("Records sorted by age", stdout, all, numOfPersons);

	free(all);
	return EXIT_SUCCESS;
}