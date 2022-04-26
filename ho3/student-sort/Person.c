#include <stdio.h>

#include "Date.h"
#include "Person.h"
#include "String_Oper.h"

int readPerson(FILE *in, Person *pPerson) {
	int checkRead;
	checkRead = getName(in, pPerson->name, MAX_NAME_LENGTH);
	if (checkRead == EOF) return EOF;
	if (checkRead == 0) return 0;

	checkRead = getId(in, pPerson->id, MAX_ID_LENGTH);
	if (checkRead == EOF) return EOF;
	if (checkRead == 0) return 0;

	checkRead = readDate(in, &(pPerson->birthDate));
	if (checkRead == EOF) return EOF;
	if (checkRead == 0) return 0;

	return 1;
}

void printPerson(FILE *out, const Person *pPerson) {
	fprintf(out, "Name: %s\n", pPerson->name);
	fprintf(out, "ID: %s\n", pPerson->id);
	fprintf(out, "Born in: ");
	printDate(out, &(pPerson->birthDate));
	fprintf(out, " (%d yo)", pPerson->age);
}

void printPersonLine(FILE *out, const Person *pPerson) {
	printPerson(out, pPerson);
	fprintf(out, "\n");
}