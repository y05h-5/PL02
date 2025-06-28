#include <stdio.h>
#include <ctype.h>

#include "Date.h"
#include "String_Oper.h"

int getConfig(FILE* conf, char* fin, char* fout, Date* date, char* sort) {
	char ch = fgetc(conf);
	
	int i = 0;
	while(isspace(ch)) ch = fgetc(conf);
	if(ch == EOF) return EOF;
	while (!isspace(ch) && ch != '\n' && ch != EOF) {
		if (!isalpha(ch) && !ispunct(ch)) return 0;
		if (i < MAX_FILENAME_LENGTH) fin[i++] = ch;
		ch = fgetc(conf);
	}
	fin[i] = '\0';

	i = 0;
	while(isspace(ch) || ch == '\n') ch = fgetc(conf);
	if(ch == EOF) return EOF;
	while (!isspace(ch) && ch != '\n' && ch != EOF) {
		if (!isalpha(ch) && !ispunct(ch)) return 0;
		if (i < MAX_FILENAME_LENGTH) fout[i++] = ch;
		ch = fgetc(conf);
	}
	fout[i] = '\0';

	int retScan = fscanf(conf, "%d/%d/%d", &(date->year), &(date->month), &(date->day));
	if(retScan == EOF) return EOF;
	if (retScan != 3) return 0;

	i = 0;
	while(isspace(ch) || ch == '\n') ch = fgetc(conf);
	if(ch == EOF) return EOF;
	while (!isspace(ch) && ch != '\n' && ch != EOF) {
		if (!isalpha(ch)) return 0;
		if (i < MAX_SORT_TYPE_LENGTH) sort[i++] = ch;
		ch = fgetc(conf);
	}
	sort[i] = '\0';

	return 1;
}

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