// Complete this module following the Hands-on 1 discussion 
// and hints you can find in the source code comments

#include <stdio.h>

#include "timing.h"

int requestTime(Time *pTime) {
	int hours, minutes;

	printf("Enter departure time (hours:minutes)\n");
	int retScan = scanf("%d:%d", &hours, &minutes);
	if (retScan != 2) {
		printf("Illegal departure time input format\n");
		return 0;
	}

	pTime->day = 0;
	pTime->hours = hours;
	pTime->minutes = minutes;

	return 1;
}

void printTime(Time time) {
	if (time.day != 0) printf("Day:%d, ", time.day);
	printf("%d:%d\n", time.hours, time.minutes);
}

int requestTimeSpan(TimeSpan *pTimeSpan) {
	int hours, minutes;

	printf("Enter journey time\n");
	int retScan = scanf("%d:%d", &hours, &minutes);
	if (retScan != 2) {
		printf("Illegal journey time input format\n");
		return 0;
	}
	if (hours < 0) {
		printf("Illegal journey hours (should not be negative)\n");
		return 0;
	}

	if (minutes < 0 || minutes >= MINUTES_IN_HOUR) {
		printf("Illegal journey minutes (should be in the range %d..%d)\n", 0, MINUTES_IN_HOUR - 1);
		return 0;
	}

	pTimeSpan->minutes = hours * MINUTES_IN_HOUR + minutes;

	return 1;
}

void printTimeSpan(TimeSpan time) {
	printf("%d minutes\n", time.minutes);
}

int isTimeValid(Time time) {
	// Implement this function
	// You need:
	// 1) to check that time.hours are within the range 0..HOURS_IN_DAY
	// 2) to check that time.minutes are within the range 0..MINUTES_IN_HOUR
	// The function returns 1, if the time value is O.k., otherwise it returns 0
	if (time.hours < 0 || time.hours >= HOURS_IN_DAY) {
		printf("Hours need to be within the range of 0 to %d\n", HOURS_IN_DAY);
		return 0;
	}
	if (time.minutes < 0 || time.minutes >= MINUTES_IN_HOUR) {
		printf("Minutes need to be within the range of 0 to %d\n", MINUTES_IN_HOUR);
		return 0;
	}
	return 1;
}

void addTimeSpan(Time *pTime, TimeSpan span) {
	int tempMinutes = (pTime->minutes + span.minutes);
	int addHours = tempMinutes / MINUTES_IN_HOUR;
	
	pTime->minutes = tempMinutes % MINUTES_IN_HOUR;
	int tempHours = pTime->hours + addHours;
	pTime->hours = tempHours % HOURS_IN_DAY;
	pTime->day = 1 + tempHours / HOURS_IN_DAY;
}