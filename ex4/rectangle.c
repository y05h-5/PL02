#include <ctype.h>
#include <stdlib.h>

#include "includes/error_handler.h"
#include "includes/file_handler.h"
#include "includes/rectangle.h"

#define _isIgnorable(X) (X=='#' || X=='(' || X==')' || X==',')

static int get_word(FILEx* file, char** word) {
	int idx = 0;
	(*word) = NULL;
	(*word) = (char*) malloc(sizeof(char));

	char c = fgetc(file->pFile);
	while (isspace(c) || _isIgnorable(c)) c = fgetc(file->pFile);
	if (c==EOF) return EOF;
	while (!isspace(c) && c != EOF && !_isIgnorable(c)) {
    // printf("%c\n",c);
		if (!isalnum(c) && !_isIgnorable(c)) return FAILURE;
        if (!_isIgnorable(c)) {
            (*word) = (char*) realloc((*word), (idx+1)*sizeof(char));
            (*word)[idx++] = c;
        }
        c = fgetc(file->pFile);
	}
	(*word) = realloc((*word), (idx+1)*sizeof(char));
	(*word)[idx] = '\0';
	
	return SUCCESS;
}

static inline int valid_vertices(const Point* vx1, const Point* vx2) {
    if (vx1->x == vx2->x) return INVALID;
    if (vx1->y == vx2->y) return INVALID;
    return VALID;
}

static int construct_rectangle(int id, Rectangle* rect, const Point* vx1, const Point* vx2) {
    ErrorType error = NO_ERROR;
    if (!valid_vertices(vx1, vx2)) error = INVALID_VERTEX;

    if (!error) {
        rect->id = id;
        if (vx1->y > vx2->y) {
            rect->boundup   = *vx1;
            rect->bounddown = *vx2;
        } else {
            rect->boundup   = *vx2;
            rect->bounddown = *vx1;
        }
        if (vx1->x > vx2->x) {
            rect->boundR    = vx1->x;
            rect->boundL    = vx2->x;
            rect->width     = vx1->x - vx2->x;
        } else {
            rect->boundR    = vx2->x;
            rect->boundL    = vx1->x;
            rect->width     = vx2->x - vx1->x;
        }
    } else {
        error_handler(NULL, error);
    }

    return (error)? FAILURE : SUCCESS;
}

int get_rectangle(FILEx* fin, Rectangle* rect) {
    ErrorType error = NO_ERROR;
    char *idc = NULL, *x1c = NULL, *x2c = NULL, *y1c = NULL, *y2c = NULL;
    int id = -1;

    int checkRead = get_word(fin, &idc);
        checkRead = (checkRead)? get_word(fin, &x1c) : FAILURE;    
        checkRead = (checkRead)? get_word(fin, &y1c) : FAILURE;    
        checkRead = (checkRead)? get_word(fin, &x2c) : FAILURE;    
        checkRead = (checkRead)? get_word(fin, &y2c) : FAILURE;
        if (checkRead == EOF) return EOF;
    
    
    int checkRect = FAILURE;
    if (checkRead == FAILURE) return FAILURE;
    else {
        int id = atoi(idc);
        int x1 = atoi(x1c), y1 = atoi(y1c);
        int x2 = atoi(x2c), y2 = atoi(y2c);
        
        printf("#%d (%d,%d) (%d,%d)\n", id, x1, y1, x2, y2);
        
        if (!error)
            checkRect = construct_rectangle(id, rect, &((Point){.x=x1, .y=y1}), &((Point){.x=x2, .y=y2}));
    }
    return (error || !checkRect)? FAILURE : SUCCESS;
}

int get_rectangle_list(FILEx* fin, Rectangle** arr_rect, int* len) {
	ErrorType error = NO_ERROR;
	Rectangle temp = {0};

	*arr_rect = (Rectangle*) malloc(sizeof(Rectangle));
	int idx = 0;

	for(ever) {
		int checkGet = get_rectangle(fin, &((*arr_rect)[idx++]));
		if (checkGet == SUCCESS) {
			(*arr_rect) = realloc((*arr_rect), (idx+1)*sizeof(Rectangle));
		}
		else if (checkGet == FAILURE) {
			error = NUM_ERRORS; // anything is fine if error becomes 'true'
			break;
		}
		else break; // EOF
	}

	*len = idx;
	
	return (error)? FAILURE : SUCCESS;
}

static int rectcmp(const Rectangle* r1, const Rectangle* r2) {
    int overlap = 0;

    if (r2->boundup.x <= r1->boundR && r2->boundup.x >= r1->boundL) {
        if (r2->boundup.y <= r1->boundup.y && r2->boundup.y >= r1->bounddown.y)
            overlap = 1;
        if (r2->bounddown.y <= r1->boundup.y && r2->bounddown.y >= r1->bounddown.y)
            overlap = 1;
    }
    if (r2->bounddown.x <= r1->boundR && r2->bounddown.x >= r1->boundL) {
        if (r2->boundup.y <= r1->boundup.y && r2->boundup.y >= r1->bounddown.y)
            overlap = 1;
        if (r2->bounddown.y <= r1->boundup.y && r2->bounddown.y >= r1->bounddown.y)
            overlap = 1;
    }
    
    return overlap;
}

int find_rectanlge_overlap(int arrlen, Rectangle* arr_rect) {
    ErrorType error = NO_ERROR;
    int no_overlap = 1;

    for (int i = 0; i < arrlen; ++i) {
        for (int j = i+1; j < arrlen; ++j) {
            int overlap = 0;
            if (arr_rect[i].width > arr_rect[j].width)
                overlap = rectcmp(&arr_rect[i], &arr_rect[j]);
            else 
                overlap = rectcmp(&arr_rect[j], &arr_rect[i]);
            if (overlap) {
                no_overlap = 0;
                printf("Rectangle #%d overlaps with rectangle #%d\n", arr_rect[i].id, arr_rect[j].id);
            }
        }
    }
    if (no_overlap) {
        printf("No intersection found\n");
    }

    return (error)? FAILURE : SUCCESS;
}