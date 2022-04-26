#include <stdio.h>

#include "Date.h"
#include "Person.h"
#include "String_Oper.h"

int readPerson(FILE *in, Person *pPerson)
{
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

void printPerson(FILE *out, const Person *pPerson)
{
	// Complete this function definition:
	// (use printDate() to print birthdate.
	// Do not forget to print age as well.
	// ...
}

void printPersonLine(FILE *out, const Person *pPerson)
{
	// Comlete this function using printDateLine() pattern
	// ...
}