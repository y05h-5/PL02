#pragma once

typedef struct {
	char* id;
	char* location;
	int hour, minute;
} Flight;

void byebyeFlights(Flight* flights, int len);

int getFlight(FILEx* file, Flight* flight);
int getFlightList(FILEx* file, Flight** flights, int* listlen);

int getUserFlight(char** dprt, char** dstn);
int getUserFlight1(char** dprt, char** dstn, Flight* flin, Flight* flout, int finlen, int foutlen);
void searchFlight(FILEx* out, const Flight* arr_list, const Flight* dprt_list,
				  int arrlen, int dprtlen, const char* from, const char* to);