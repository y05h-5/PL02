#include <stdio.h>
#include <ctype.h>

#include "String_Oper.h"

// Names are words containing only letters
int getName(FILE *in, char *name, int limit) {
	char ch = fgetc(in);
	int  ixLit = 0;

	// Skip leading spaces
	while (isspace(ch)) ch = fgetc(in);
	if (ch == EOF) return EOF;
	// Reading a word of letters
	while (!isspace(ch) && ch != '\n' && ch != EOF) {
		if (!isalpha(ch)) return 0;

		if (ixLit < limit) name[ixLit++] = ch;

		ch = fgetc(in);
	}
	name[ixLit] = '\0';

	return 1;
}

// IDs are words contaning letters and digits
int getId(FILE *in, char *id, int limit) {
	char ch = fgetc(in);
	int  ix = 0;

	// Skip leading spaces
	while (isspace(ch)) ch = fgetc(in);
	if (ch == EOF) return EOF;
	// Reading a word of letters
	while (!isspace(ch) && ch != '\n' && ch != EOF) {
		if (!isalpha(ch) && !isdigit(ch)) return 0;
		if (ix < limit) id[ix++] = ch;
		ch = fgetc(in);
	}
	id[ix] = '\0';

	return 1;
}