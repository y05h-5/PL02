#include <stdio.h>
#include <stdbool.h>

#include "Date.h"

int isLeapYear(int year); // See the function definition below...

int readDate(FILE *in, Date *pDate)
{
	int retScan = fscanf(in, "%d %d %d", &(pDate->year), &(pDate->month), &(pDate->day));
	if(retScan == EOF) return EOF;
	if (retScan != 3) return 0;
	return 1;
}

bool isDateLegal(const Date *pDate)
{
	int daysLimit[12] = 
		{ 31,29,31,30,31,30,
		31,31,30,31,30,31 };
	
	bool isLegal = true;
	
	if ((pDate->month < 1) || (pDate->month > 12))
		isLegal = false;
	else if ((pDate->day < 1) || (pDate->day > daysLimit[pDate->month - 1]))
		isLegal = false;
	else if ((pDate->year<1900) || (pDate->year > 2016))
		isLegal = false;
	else if ((pDate->month == 2) && (pDate->day == 29) && (!isLeapYear(pDate->year)))
		isLegal = false;
	return isLegal;
}

void printDate(FILE *out, const Date *pDate)
{
	// Complete this function
	// ...

}

void printDateLine(FILE *out, const Date *pDate)
{	
	printDate(out, pDate);
	fprintf(out, "\n");
}

int getAge(const Date *pBirthDate, const Date *pCurrent)
{
	int age;

	age = pCurrent->year - pBirthDate->year;
	if (age <= 0)
	{
		age = 0;
		return age;
	}

	// Write missting code to compute age
	// ... 


	return age;
}

// Complete definition of this function:
// Function returns 1, if the year is leap,
//          returns 0. otherwise
int isLeapYear(int year)
{
	// Complete the code
	// ...

}
