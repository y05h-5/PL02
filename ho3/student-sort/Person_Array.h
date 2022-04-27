#pragma once

#include <stdio.h>

#include "Person.h"

int countRecords2Bin(FILE *in, FILE *bin);
int countRecords(FILE *in);
int loadRecordsFromBinaryFile(FILE *in, Person *all, int size);
int loadRecordsFromTextFile(FILE *in, Person *all, int size);
void calculateAges( Person *all, int size, const Date *current);
void printRecords(const char *title, FILE *out, const Person *all, int size);