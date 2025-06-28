#include <stdio.h>
#include <stdlib.h>

// Complete the project following the Hands-on 1 discussion 
// and hints you can find in the source code comments

#include "timing.h"

int main()
{
	Time departure;
	TimeSpan journey;

	Time arrival; // unused?

	if(requestTime(&departure) != 1) return EXIT_FAILURE;

	if (!isTimeValid(departure)) {
		puts("Invalid time value.");
		exit(EXIT_FAILURE);
	}
	
	// Print departure time to the console
	printf("Departure Time: ");
	printTime(departure);

	// Request and print the journay tine (TimeSpan object) in similar manner
	// as in the above code for requesting and printing departure time
	if(requestTimeSpan(&journey) != 1) return EXIT_FAILURE;

	printf("Journey Time: ");
	printTimeSpan(journey);

	// Compute arrival time for given departure and journey time
	// using  addTimeSpan() function
	addTimeSpan(&departure, journey);
	
	// for readability's sake
	arrival = (Time) {
		.day = departure.day,
		.hours = departure.hours,
		.minutes = departure.minutes
	};

	// Check that the results as printed correctly,
	// then modify this code with using printTime() function
	printf("Arrival time on the day %d - %02d:%02d\n", arrival.day, arrival.hours, arrival.minutes);
	return EXIT_SUCCESS;
}