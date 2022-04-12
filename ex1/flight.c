#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/defines.h"
#include "includes/error_handler.h"
#include "includes/file_handler.h"
#include "includes/flight.h"

static int getWord(FILEx* file, char** word) {
	int idx = 0;
	(*word) = NULL;
	(*word) = (char*) malloc(sizeof(char));

	char c = fgetc(file->pFile);
	while (isspace(c)) c = fgetc(file->pFile);
	if (c==EOF) return EOF;

	while (!isspace(c) && c != EOF) {
		if (!isalpha(c) && !isdigit(c)) return FAILURE;
	    (*word) = (char*) realloc((*word), (idx+1)*sizeof(char));
	    (*word)[idx++] = c;
	  	c = fgetc(file->pFile);
	}
	(*word) = realloc((*word), (idx+1)*sizeof(char));
	(*word)[idx] = '\0';
	
	return SUCCESS;
}
static int getFlightTime(FILEx* file, int* h, int* m) {
	ErrorType error = NO_ERROR;
	int readEOF = fileX_read(2, file, " %d:%d", h, m);
	if (readEOF==UNDEFINED) return FAILURE;
	return (readEOF)? EOF : SUCCESS;
}

int getFlight(FILEx* file, Flight* flight) {
	char *id = NULL, *loc = NULL;
	int hour = 0, minute = 0;

	int checkID = getWord(file, &id);
	if (checkID==EOF || strlen(id) > MAX_ID_LEN) {
		error_handler(file->nFile, DATA_FORMAT);
		return FAILURE;
	}
	int checkLOC  = (checkID)? 	getWord(file, &loc) : FAILURE;
	int checkTIME = (checkLOC)? getFlightTime(file, &hour, &minute) : FAILURE;

	int validFlight = (((checkID+checkLOC+checkTIME) == 3) ||
					  (((checkID+checkLOC) == 2)&&checkTIME==EOF));

	char t[32] = {'\0'};
	strcpy(t, loc);
	if (validFlight) {
		flight->id = (char*) malloc((1+strlen(id))*sizeof(char));
		strcpy(flight->id, id);
		flight->location = (char*) malloc((1+strlen(t))*sizeof(char));
		strcpy(flight->location, t);
		flight->hour = hour;
		flight->minute = minute;
	}
	else { 
		if (checkTIME!=FAILURE)
			error_handler(file->nFile, DATA_FORMAT);
	}
	if (id!=NULL) { free(id); id = NULL; }
	if (loc!=NULL) { free(loc); loc = NULL; }
	if (checkTIME==EOF) { return EOF; } 

	return (validFlight)? SUCCESS : FAILURE;
}

void byebyeFlights(Flight* flights, int len) {
	for (int i = 0; i < len; ++i) {
		free(flights[i].id);
		free(flights[i].location);
		flights[i].id = NULL;
		flights[i].location = NULL;
	}
	free(flights);
	flights = NULL;
}

int getFlightList(FILEx* file, Flight** flights, int* listlen) {
	ErrorType error = NO_ERROR;
	Flight temp = {0};
	*flights = (Flight*) malloc(sizeof(Flight));
	int idx = 0;

	for(ever) {
		int checkGet = getFlight(file, &((*flights)[idx++]));
		if (checkGet==SUCCESS) {
			// printf("%s %s %d:%d\n", (*flights)[idx-1].id, (*flights)[idx-1].location, (*flights)[idx-1].hour, (*flights)[idx-1].minute);
			(*flights) = realloc((*flights), (idx+1)*sizeof(Flight));
		}
		else if (checkGet==FAILURE) {
			error = NUM_ERRORS; // anything is fine if error becomes 'true'
			break;
		}
		else break; // EOF
	}
	*listlen = idx;
	
	return (error)? FAILURE : SUCCESS;
}

static int getUserFlight(char** airport, Flight* list, int len, int* flight_num) {
    ErrorType error = NO_ERROR;
    // int flight_num = -1;
    *flight_num = -1;
	int retScan = 0;
	char cleanbuffer = '\0';
	*airport = NULL;

    for (int i = 0; i < len; ++i) {
        printf("        [%d] %s  %d:%d\n", i, list[i].location, list[i].hour, list[i].minute);
    }
	printf("    Your Flight: ");  
	retScan = scanf("%d", flight_num);
 	for (;(cleanbuffer=getchar())!='\n' && cleanbuffer!=EOF;) {
		if (cleanbuffer!=' ' && cleanbuffer!='\n' && cleanbuffer!=EOF)
			error = INPUT_FORMAT;
	}

	if (retScan != 1) error = DATA_TYPE;
	else if (!error && (*flight_num >= len || *flight_num < 0)) {
        printf("Flight #%d does not exist.\n", *flight_num);
        error = FLIGHT_NUM;
    }

    if (!error) {
		*airport = (char*) malloc(strlen(list[*flight_num].location)*sizeof(char));
        strcpy(*airport, list[*flight_num].location);
	} else {
		error_handler(NULL, error);
		if (*airport!=NULL) free(*airport);
    }

    return (error)? FAILURE:SUCCESS;
}

int getUserFlights(char** dprt, char** dstn, Flight* arrList, Flight* dprList, int arrlen, int dprlen, int* num_arrival) {
	ErrorType error = NO_ERROR;
	int checkArrival = FAILURE, checkDepart = FAILURE;
	int flight_num = -1; 

    printf("\nInput your flight data\n");
	
    printf("	Arriving From: \n");
    checkArrival = getUserFlight(dprt, arrList, arrlen, &flight_num);
    if (!checkArrival) return FAILURE;
    *num_arrival = flight_num;

    printf("	Departing To: \n");
    checkDepart = getUserFlight(dstn, dprList, dprlen, &flight_num);
    if (!checkDepart) return FAILURE;
   
    return SUCCESS;
}

static void print_flight(FILEx* out, Flight* flight, int nl) {
	if (!nl) printf("	");
	printf("%s %s %d:%d  ", flight->id, flight->location, flight->hour, flight->minute);
	fileX_write(out, "%s %s %d:%d  ", flight->id, flight->location, flight->hour, flight->minute);
	if (nl) { 
		puts("");
		fileX_write(out, "\n");
	}
}

static int findMatched(Flight** dst, const Flight* flist, int flen, const char* loc, int flight_num) {
	*dst = (Flight*) malloc(sizeof(Flight));
	int num_matched = 0;

	for (int i = flight_num; i < flen; ++i) {
		int different = strcmp(flist[i].location, loc);
		if (!different) {
			*dst = realloc((*dst), (++num_matched)*sizeof(Flight));
			(*dst)[num_matched-1] = flist[i];
		}
	}
	return num_matched;
}

void searchFlight(FILEx* out, const Flight* arr_list, const Flight* dprt_list,
				  int arrlen, int dprtlen, const char* from, const char* to, int num_arrival) 
{
	enum {NO_NEW_LINE, NEW_LINE};
	int skip = 0;

	printf("\nWe have %d arrival flights and %d departure flights today.\n",arrlen, dprtlen);
	printf("Checking for flights from %s to %s...\n", from, to);

	Flight* arr_matched = NULL;
	int num_matchedA = findMatched(&arr_matched, arr_list, arrlen, from, num_arrival);
	if (num_matchedA==0) skip = 1;

	Flight* dptr_matched = NULL;
	int num_matchedD = 0;
	if (!skip) {
		num_matchedD = findMatched(&dptr_matched, dprt_list, dprtlen, to, 0);
		if (num_matchedD==0) skip = 1;
	}

    printf("\nAvailable connected flights:\n");
    fileX_write(out, "Available connected flights:\n");
	if (!skip) {
		int matched = 0;
		for (int a = 0; a < num_matchedA; ++a) {
			for (int d = 0; d < num_matchedD; ++d) {
				if (arr_matched[a].hour > dptr_matched[d].hour) continue;
				if (arr_matched[a].hour == dptr_matched[d].hour) {
					if (arr_matched[a].minute > dptr_matched[d].minute) continue;
				}
				print_flight(out, &arr_matched[a], NO_NEW_LINE);
				print_flight(out, &dptr_matched[d], NEW_LINE);
				matched++;
			}
		}
		printf("\n%d connected flights found.\n", matched);
        if (!matched) skip = 1;
	}
    if (skip) {
		printf("\nNo connected flights found.\n");
		printf("We are sorry for the inconvenience.\n");
		fileX_write(out, "No connected flights found.\n");
		fileX_write(out, "We are sorry for the inconvenience.\n");
	}
	printf("output file was created.\n");
}