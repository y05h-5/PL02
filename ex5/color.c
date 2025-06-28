#include <stdlib.h>
#include <string.h>

#include "includes/color.h"
#include "includes/defines.h"
#include "includes/error_handler.h"
#include "includes/file_handler.h"

static int get_color(FILEx* fcl, Color* color) {
    Color tmp = NULL;
    int checkInput = get_word(fcl, &tmp);
    *color = (Color) malloc(sizeof(char)*strlen(tmp));

    if (checkInput == SUCCESS)
        strcpy(*color, tmp);
    else if (checkInput == EOF)
        return EOF;
    else
        error_handler(fcl->nFile, DATA_FORMAT); // change ErrorType later
    
    return checkInput;
}

int get_color_list(FILEx* fcl, Color** colors, int* len) {
    int idx = 0;
    int checkGet = FAILURE;
    ErrorType error = NO_ERROR;

    *colors = (Color*) malloc(sizeof(Color*));

    for(ever) {
        checkGet = get_color(fcl, &((*colors)[idx++]));

        if (checkGet == SUCCESS)
			*colors = realloc(*colors, (idx+1)*sizeof(Color*));
        else if (checkGet == FAILURE) {
            error = NUM_ERRORS; // anything is fine if error becomes 'true'
			break;
        }
        else break; // eof
    }
    *len = idx-1;

    return (error)? FAILURE : SUCCESS;
}

int check_color(Color* color_list, const Color color, int cl_len, int rect_id) {
    for (int i = 0; i < cl_len; ++i) {
        if (!strcmp(color_list[i], color))
            return SUCCESS;
    }
    error_handler(&rect_id, INVALID_COLOR);
    return FAILURE;
}

void kill_color_list(Color** list, int len) {
    for (int i = 0; i < len; ++i)
        free((*list)[i]);
    free (*list);
}