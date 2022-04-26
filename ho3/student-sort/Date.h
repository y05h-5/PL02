#pragma once

#include <stdio.h>
#include <stdbool.h>

typedef struct
{
	// Complete definition according
	// to hands-on materials
	// ...
} Date;

int readDate(FILE *in, Date *pDate);
bool isDateLegal( const Date *pDate);
void printDate(FILE *out, const Date *pDate);
void printDateLine(FILE *out, const Date *pDate);
int getAge(const Date *pDate, const Date *pCurrent);