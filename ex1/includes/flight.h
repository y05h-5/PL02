#pragma once

typedef struct {
	char* id;
	char* location;
	int hour, minute;
} Flight;

void byebyeFlights(Flight* flights, int len);

int getFlightList(FILEx* file, Flight** flights, int* listlen);

int getUserFlights(char** dprt, char** dstn, Flight* flin, Flight* flout, int finlen, int foutlen, int* num_arrival);
void searchFlight(FILEx* out, const Flight* arr_list, const Flight* dprt_list,
				  int arrlen, int dprtlen, const char* from, const char* to, int num_arrival);