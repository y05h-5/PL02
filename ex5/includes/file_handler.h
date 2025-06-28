#pragma once
#include <stdio.h>

#include "defines.h"

/***
 * extended FILE structure containing... 
 * 1.FILE* pFile: pointer to a FILE object
 * 2.char* nFile: name of the file in char string
 */
typedef struct {
    FILE* pFile;
    char* nFile;
} FILEx;

/****** function prototypes ******/
FILEx* fileX_init(const char* name, const char* mode);
int fileX_kill(FILEx* file);

int fileX_read(int argc, FILEx* fileX, const char* format, ...);
int fileX_write(FILEx* fileX, const char* content, ...);

int get_word(FILEx* file, char** word);