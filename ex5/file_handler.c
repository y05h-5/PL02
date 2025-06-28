#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/error_handler.h"
#include "includes/file_handler.h"

#define _isIgnorable(X) (X=='#' || X=='(' || X==')' || X==',')
#define _isNegativeSign(X) (X=='-')

// function to open a file (exits the process if fails)
static int file_open(FILE** pFile, const char* nFile, const char* mode) {
    *pFile = fopen(nFile, mode);
    if (*pFile == NULL) {
        error_handler(nFile, FILE_LOAD_FAILED);
        return FAILURE;
    }
    return SUCCESS;
}

static void file_close(FILE* pFile, const char* nFile) {
    if (pFile == NULL) error_handler(nFile, FILE_CLOSE_FAILED);
    fclose(pFile);
}


// function to initialize a FILEx object
FILEx* fileX_init(const char* name, const char* mode) {
    FILEx* file = malloc(sizeof(FILE)+strlen(name)*sizeof(char));
    if (file==NULL) {
        error_handler(name, MALLOC_FAILURE);
        return NULL;
    }

    int success = file_open(&file->pFile, name, mode);

    if (success) {
        file->nFile = malloc(strlen(name)*sizeof(char));
        strcpy(file->nFile,name);
    }
    return (success)? file : NULL;
}

int fileX_kill(FILEx* file) {
    int exit_value = SUCCESS;
    if (file==NULL) {
        error_handler(file->nFile, FILE_CLOSE_FAILED);
        return FAILURE;
    }
    // printf("closing file \"%s\"\n", file->nFile);
    file_close(file->pFile, file->nFile);
    free(file->nFile);
    free(file);

    return SUCCESS;
}


int fileX_read(int argc, FILEx* input, const char* format, ...) {
    if (input->pFile == NULL) {
        error_handler(input->nFile, FILE_LOAD_FAILED);
        return UNDEFINED;
    }

    // printf("Reading input file \"%s\"\n", input->nFile);
    puts("hi");
    
    va_list args;
    va_start(args, format);
    int checkScan = vfscanf(input->pFile, format, args);
    va_end(args);
    puts("hi");

    if (checkScan==EOF) {
		error_handler(input->nFile, DATA_FORMAT);
		return UNDEFINED;
	}
	if (checkScan != argc) {
        error_handler(input->nFile, DATA_TYPE);
        return UNDEFINED;
    }

    ErrorType error = NO_ERROR;
    int invisible_input = getc(input->pFile);
    int eof = (invisible_input == EOF)? 1 : 0;
    while(!eof && invisible_input != '\n' /*&& invisible_input != EOF*/) {
        eof = (invisible_input == EOF)? 1 : 0;

        if (!eof && invisible_input != ' ' && invisible_input != '\n') {
            error = DATA_FORMAT;
        }
        invisible_input = (eof)? EOF : getc(input->pFile);
    }

    if (error) error_handler(input->nFile, DATA_FORMAT);

    return (error)? UNDEFINED : eof;
}

int fileX_write(FILEx* output, const char* content, ...) {
    if (output->pFile == NULL) error_handler(output->nFile, FILE_LOAD_FAILED);
    
    va_list args;
    va_start(args, content);
    int write_success = vfprintf(output->pFile, content, args); // -1 if there's encoding failure
    va_end(args);

    if (write_success < 0) error_handler(output->nFile, FILE_WRITE_FAILED);
    // else printf("Output file \"%s\" has been created/updated.\n", output->nFile);

    return write_success;
}

int get_word(FILEx* file, char** word) {
	int idx = 0;
	(*word) = NULL;
	(*word) = (char*) malloc(sizeof(char));


	char c = fgetc(file->pFile);
	while (isspace(c) || _isIgnorable(c)) c = fgetc(file->pFile);
	if (c==EOF) return EOF;
	while (!isspace(c) && c != EOF && !_isIgnorable(c)) {
    // printf("%c\n",c);
		if (!_isNegativeSign(c) && !isalnum(c) && !_isIgnorable(c)) return FAILURE;
        if (!_isIgnorable(c) || _isNegativeSign(c)) {
            (*word) = (char*) realloc((*word), (idx+1)*sizeof(char));
            (*word)[idx++] = c;
        }
        c = fgetc(file->pFile);
	}
	(*word) = realloc((*word), (idx+1)*sizeof(char));
	(*word)[idx] = '\0';
	
	return SUCCESS;
}