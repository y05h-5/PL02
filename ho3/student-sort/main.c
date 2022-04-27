#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Date.h"
#include "Person.h"
#include "Person_Array.h"
#include "Sort.h"
#include "String_Oper.h"

int main(int argc, char* argv[]) {
	FILE* config;
	FILE *in, *out;
	FILE *bin;
	Person *all;
	int numOfPersons;

	char fin_name[MAX_FILENAME_LENGTH], fout_name[MAX_FILENAME_LENGTH];
	Date currentDate;
	char sort_type[MAX_SORT_TYPE_LENGTH];
	// const Date currentDate = {2022, 4, 28};
	
	if(argc != 2) {
		printf("Config file name must be specified.\n");
		exit(1);
	}

	config = fopen(argv[1], "rt");
	if(config == NULL) {
		printf("Unable to open config file\n");
		return EXIT_FAILURE;		
	}

	int checkConfig = getConfig(config, fin_name, fout_name, &currentDate, sort_type);
	if (!checkConfig) {
		printf("Invalid config file format.\n");
		return EXIT_FAILURE;
	}

	in = fopen(fin_name, "rt");
	bin = fopen("data.bin", "wb");
	if (in == NULL) {
		printf("Unable to open input file\n");
		return EXIT_FAILURE;
	} if (bin == NULL) {
		printf("Unable to open internal data file\n");
		return EXIT_FAILURE;
	}

	// numOfPersons = countRecords(in);
	numOfPersons = countRecords2Bin(in, bin);
	
	if (numOfPersons == 0) {
		printf("No data in input file\n");
		return EXIT_FAILURE;
	}

	all = (Person *)malloc(numOfPersons * sizeof(Person));
	if (all == NULL ) {
		printf("Memory allocation error\n");
		return EXIT_FAILURE;
	}

	fclose(in);
	fclose(bin);
	// rewind(in);

	bin = fopen("data.bin", "rb");
	if (bin == NULL) {
		printf("Unable to open internal data file\n");
		return EXIT_FAILURE;
	}

	int count = loadRecordsFromBinaryFile(in, all, numOfPersons);
	// int count = loadRecordsFromTextFile(in, all, numOfPersons);
	if (count != numOfPersons) {
		printf("Unknown error. Please contact the developer\n");
		return EXIT_FAILURE;
	}

	// fclose(in);

	int open_out = strcmp(fout_name, "stdout");
	if (open_out != 0) {
		out = fopen(fout_name, "wt");
	} else {
		out = stdout;
	}

	calculateAges(all, numOfPersons, &currentDate);

	printRecords("Records loaded from input file", out, all, numOfPersons); puts("");

	int sortbyage = strcmp(sort_type, "age")? 0 : 1;

	if (sortbyage) {		
		sortByAge(all, numOfPersons);
		printRecords("Records sorted by age", out, all, numOfPersons);
	}
	else {
		sortByName(all, numOfPersons);
		printRecords("Records sorted by name", out, all, numOfPersons); puts("");
	}

	if (open_out != 0) fclose(out);

	free(all);
	return EXIT_SUCCESS;
}