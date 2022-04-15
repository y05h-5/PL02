#pragma once

#define MINUTES_IN_HOUR 60
#define HOURS_IN_DAY 24

typedef struct {
	int day;
	int hours;
	int minutes;
} Time;

typedef struct {
	int minutes;
} TimeSpan;

int requestTime(Time *pTime);
void printTime(Time time);
int requestTimeSpan(TimeSpan *pTimeSpan);
void printTimeSpan(TimeSpan time);
int isTimeValid(Time time);
void addTimeSpan(Time *pTime, TimeSpan span);