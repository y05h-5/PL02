#pragma once

#include <stdio.h>

#define MAX_FILENAME_LENGTH 24
#define MAX_SORT_TYPE_LENGTH 5

int getConfig(FILE* conf, char* fin, char* fout, Date* date, char* sort);
int getName(FILE *in, char *name, int limit);
int getId(FILE *in, char *id, int limit);
