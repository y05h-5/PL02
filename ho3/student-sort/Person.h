#pragma once
#include <stdio.h>

#include "Date.h"

#define MAX_NAME_LENGTH 10
#define MAX_ID_LENGTH 12

typedef struct
{
	char name[MAX_NAME_LENGTH + 1];
	char id[MAX_ID_LENGTH + 1];
	Date birthDate;
	int age;
} Person;

int readPerson(FILE *in, Person *pPerson);
void printPerson(FILE *out, const Person *pPerson);
void printPersonLine(FILE *out, const Person *pPerson);