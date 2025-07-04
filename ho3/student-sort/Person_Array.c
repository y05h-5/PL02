#include <stdio.h>
#include <stdlib.h>

#include "Person.h"

int countRecords2Bin(FILE *in, FILE *bin) {
	int count = 0; 
	for (;;) {
		Person tmp;
		int checkRead = readPerson(in, &tmp);
		if (checkRead == EOF) return count;
		if (checkRead != 1) {
			printf("Illegal format for the record No.%d\n", count + 1);
			exit(1);
		}
		fwrite(&tmp, sizeof(Person), 1, bin);
		// fwrite(&(tmp.name),sizeof(char)*(MAX_NAME_LENGTH+1), 1, bin);
		// fwrite(&(tmp.id),sizeof(char)*(MAX_ID_LENGTH+1), 1, bin);
		// fwrite(&(tmp.birthDate.year),sizeof(int), 1, bin);
		// fwrite(&(tmp.birthDate.month),sizeof(int), 1, bin);
		// fwrite(&(tmp.birthDate.day),sizeof(int), 1, bin);
		++count;
	}
	return count;
}

int countRecords(FILE *in) {
	int count = 0;

	for (;;) {
		Person temp;
		int checkRead = readPerson(in, &temp);
		if (checkRead == EOF) return count;
		if (checkRead != 1) {
			printf("Illegal format for the record No.%d\n", count + 1);
			exit(1);
		}
		++count;
	}

	return count; // added by me
}

int loadRecordsFromBinaryFile(FILE *bin, Person *all, int size) {
	int count;
	int checkRead = 0;

	for(count=0; count < size; ++count) {
		checkRead = readPersonBin(bin, &(all[count]));
		if (checkRead == EOF || checkRead == 0) {
			printf("loadfromfile error\n");
			exit(1);		
		}
	}
	return count;
}

int loadRecordsFromTextFile(FILE *in, Person *all, int size) {
	int count;
	int checkRead = 0;

	for( count=0; count < size; ++count ) {
		// Complete this loop body
		// (use readPerson() function to read the array element.
		// Do not forget to check the value returned by readPerson() and
		// print messages in case of reading errors.
		// Stop program by using exit(1) if reading errors are detected.
		// ...
		checkRead = readPerson(in, &(all[count]));
		if (checkRead == EOF || checkRead == 0) {
			printf("loadfromfile error\n");
			exit(1);		
		}
	}
	return count;
}

void printRecords( const char *title, FILE *out, const Person *all, int size) {
	fprintf(out, "%s\n", title);
	for (int ix = 0; ix < size; ++ix) {
		printPersonLine(out, &(all[ix]));
	}
}

void calculateAges(Person *all, int size, const Date *pCurrent) {
	// By using getAge() function
	// calculate the ages of all the persons in the array "all"
	// ...
	for (int i = 0; i < size; ++i) {
		all[i].age = getAge(&(all[i].birthDate), pCurrent);
	}
}