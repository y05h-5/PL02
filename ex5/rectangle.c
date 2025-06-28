#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "includes/color.h"
#include "includes/error_handler.h"
#include "includes/file_handler.h"
#include "includes/rectangle.h"

// #define _isIgnorable(X) (X=='#' || X=='(' || X==')' || X==',')

void print_rectangle(const Rectangle* rect) {
    printf("#%d (%d,%d) (%d,%d) %s\n", rect->id, rect->bounddown.x, rect->bounddown.y, rect->boundup.x, rect->boundup.y, rect->color);
}

static inline int valid_vertices(const Point* vx1, const Point* vx2) {
    if (vx1->x == vx2->x) return INVALID;
    if (vx1->y == vx2->y) return INVALID;
    return VALID;
}

static int construct_rectangle(int id, Rectangle* rect, const Point* vx1, const Point* vx2, const Color cl) {
    ErrorType error = NO_ERROR;
    if (!valid_vertices(vx1, vx2)) error = INVALID_VERTEX;

    if (!error) {
        rect->id = id;
        rect->color = (Color) malloc(sizeof(char)*strlen(cl));
        strcpy(rect->color, cl);
        // printf("%s\n", rect->color);

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
        rect->area = abs(rect->width)*abs(vx2->y - vx1->x);

    } else {
        error_handler(NULL, error);
    }

    return (error)? FAILURE : SUCCESS;
}

int get_rectangle(FILEx* fin, Color* color_list, int cl_len, Rectangle* rect) {
    ErrorType error = NO_ERROR;
    char *idc = NULL, *x1c = NULL, *x2c = NULL, *y1c = NULL, *y2c = NULL;
    Color color = NULL;
    int id = -1;

    int checkRead  = get_word(fin, &idc);
    if (checkRead==SUCCESS) id = atoi(idc);
        checkRead  = (checkRead==SUCCESS)? get_word(fin, &x1c)   : checkRead;    
        checkRead  = (checkRead==SUCCESS)? get_word(fin, &y1c)   : checkRead;    
        checkRead  = (checkRead==SUCCESS)? get_word(fin, &x2c)   : checkRead;    
        checkRead  = (checkRead==SUCCESS)? get_word(fin, &y2c)   : checkRead;
        checkRead  = (checkRead==SUCCESS)? get_word(fin, &color) : checkRead;
    int checkColor = (checkRead==SUCCESS)? check_color(color_list, color, cl_len, id) : FAILURE;
        if (checkRead == EOF) return EOF;
    
    
    int checkRect = FAILURE;
    if (checkRead == FAILURE || checkColor == FAILURE) return FAILURE;
    else {
        int id = atoi(idc);
        int x1 = atoi(x1c), y1 = atoi(y1c);
        int x2 = atoi(x2c), y2 = atoi(y2c);
        
        // printf("#%d (%d,%d) (%d,%d) %s\n", id, x1, y1, x2, y2, color);
        
        if (!error)
            checkRect = construct_rectangle(id, rect, &((Point){.x=x1, .y=y1}), &((Point){.x=x2, .y=y2}), color);
    }
    // print_rectangle(rect);
    // printf("%d %d\n", error, checkRect);
    return (error || checkRect == FAILURE)? FAILURE : SUCCESS;
}

int get_rectangle_list(FILEx* fin, Color* color_list, int cl_len, Rectangle** rect_list, int* rect_len) {
	ErrorType error = NO_ERROR;
	Rectangle temp = {0};

	*rect_list = (Rectangle*) malloc(sizeof(Rectangle));
	int idx = 0;

	for(ever) {
		int checkGet = get_rectangle(fin, color_list, cl_len, &((*rect_list)[idx++]));

		if (checkGet == SUCCESS) {
			(*rect_list) = realloc((*rect_list), (idx+1)*sizeof(Rectangle));
		} else if (checkGet == FAILURE) {
			error = NUM_ERRORS; // anything is fine if error becomes 'true'
            // printf("failed!!!\n");
			break;
		} else { // EOF 
            /*printf("EOF!!\n");*/
            break;
        }
	}

	*rect_len = idx-1;
	return (error)? FAILURE : SUCCESS;
}

void kill_rectangle_list(Rectangle** rect_list, int len) {
    for (int i = 0; i < len; ++i)
        free((*rect_list)[len].color);
    free(*rect_list);
}

static void sort_rectangle_list(Rectangle* rect_list, int len) {
    Rectangle tmp = {0};
    // bubble? sort... because i didnt have time to implement a better method
    for (int i = 0; i < len; ++i) { 
        for (int j = i+1; j < len; ++j) {
            if (rect_list[i].boundL > rect_list[j].boundL) {
                tmp = rect_list[i];
                rect_list[i] = rect_list[j];
                rect_list[j] = tmp;
            }
        }
    }
    for (int n = 0; n < len; ++n)
        print_rectangle(&(rect_list[n])); // print all sorted rectangles
}

static int rectcmp(const Rectangle* r1, const Rectangle* r2) {
    if (strcmp(r1->color, r2->color)) 
        return 0;
    if (r1->bounddown.x > r2->boundup.x || r1->boundup.x < r2->bounddown.x) 
        return 0;
    if (r1->boundup.y < r2->bounddown.y || r1->bounddown.y > r2->boundup.y) 
        return 0;

    return 1;
}

static int group_rectangle_color(Rectangle** group[], const Rectangle* rlist, int len, const Color* clist, int clen, int* nelements[]) {
    (*group) = (Rectangle**) malloc(sizeof(Rectangle));
    (*nelements) = (int*) malloc(sizeof(int));
    int clcnt = 0;
    for (int c = 0; c < clen; ++c) {
        int cnt = 0;
        int incrementcheck = 0;
        for (int r = 0; r < len; ++r) {
            if (!strcmp(clist[c], rlist[r].color)) {
                // printf("%s\n", clist[c]);
                if (cnt == 0) {
                    (*group)[clcnt] = (Rectangle*) malloc(sizeof(Rectangle));
                    (*nelements)[clcnt] = 1;
                    incrementcheck = 1;
                } else {
                    (*group)[clcnt] = (Rectangle*) realloc((*group)[clcnt], sizeof(Rectangle)*(cnt+1));
                    (*nelements)[clcnt] += 1;
                }
                (*group)[clcnt][cnt++] = rlist[r];
                // print_rectangle(&((*group)[clcnt][cnt-1]));
            }
        }
        if (incrementcheck) {
            ++clcnt;
            (*nelements) = realloc((*nelements), sizeof(int)*(clcnt+1));
        }
    }
    return clcnt;
}

static int calculate_overlap_area(const Rectangle* r1, const Rectangle* r2) {
    int area = 0;

    int left   = MAX(r1->boundL, r2->boundL);
    int right  = MIN(r1->boundR, r2->boundR);
    int dx     = abs(left - right);

    int top    = MIN(r1->boundup.y, r2->boundup.y);
    int buttom = MAX(r1->bounddown.y, r2->bounddown.y);
    int dy     = abs(top - buttom);

    return dx*dy;
}

static Rectangle get_overlap_rectangle(const Rectangle* r1, const Rectangle* r2) {
    int left   = MAX(r1->boundL, r2->boundL);
    int right  = MIN(r1->boundR, r2->boundR);
    int dx     = abs(left - right);

    int top    = MIN(r1->boundup.y, r2->boundup.y);
    int buttom = MAX(r1->bounddown.y, r2->bounddown.y);
    int dy     = abs(top - buttom);

    return (Rectangle) {
        .id = -1,
        .boundup = (Point) {.x = right, .y = top},
        .bounddown = (Point) {.x = left, .y = buttom},
        .boundL = left,
        .boundR = right,
        .width = dx,
        .area = dy*dx,
        .color = NULL
    };
}

static int get_num_elements(int cnt[], int n, int* idx) {
    int max = cnt[0];
    *idx = 0;
    for (int i = 1; i < n; ++i) {
        if (max < cnt[i]) {
            max = cnt[i];
            *idx = i;
        }
    }
    return max;
}

int linesweep(Rectangle* rect_list, int len, Color* col_list, int cl_len) {
    ErrorType error = NO_ERROR;
    int no_overlap = 1;

    sort_rectangle_list(rect_list, len);

    Rectangle** grouped = NULL;
    int* nelements = NULL;
    int n_grp = group_rectangle_color(&grouped, rect_list, len, col_list, cl_len, &nelements);
    // print_rectangle(&(grouped[0][0]));
    int total_area[n_grp];
    Rectangle common_area[n_grp];
    int cnt_elements[n_grp];

    for (int i = 0; i < n_grp; ++i) {
        int total[nelements[i]];
        Rectangle common[nelements[i]];
        int cnt[nelements[i]];    
            cnt_elements[i] = 0;
        for (int j = 0; j < nelements[i]; ++j) {
            int area = 0;
            total[j] = grouped[i][j].area;
            common[j] = grouped[i][j];
            cnt[j] = 1;
            for (int k = 1; k < nelements[i]; ++k) {
                if (rectcmp(&(grouped[i][j]), &(grouped[i][k]))) {
                    common[j] = get_overlap_rectangle(&(common[j]), &(grouped[i][k]));
                    area = calculate_overlap_area(&(grouped[i][j]), &(grouped[i][k]));
                    total[j] += (grouped[i][k].area) - area;
                    // printf("c:%d t:%d\n", area, total[j]);
                    cnt[j] = (k==0)? 2:cnt[j]+1;
                    no_overlap = 0;
                }
            }
        }
        int idx = 0;
        cnt_elements[i] = get_num_elements(cnt, nelements[i], &idx);
        total_area[i] = total[idx] + common[idx].area;
        common_area[i] = common[idx];
        // printf("c:%d t:%d\n", common_area[i].area, total_area[i]);
        // printf("%d %d\n",nelements[i], cnt_elements[i]);
    }

    int index = 0;
    int cnt_ovl = get_num_elements(cnt_elements, n_grp, &index);
    int total_area_ovl = total_area[index];
    Rectangle common_area_ovl = common_area[index];
    if (no_overlap) printf("No intersection found\n");
    else {
        puts("");
        printf("# of rectanlges: %d\n", cnt_ovl);
        printf("color: %s\n", grouped[index][0].color);
        printf("total area: %d\n", total_area_ovl);
        printf("common area: %d\n", common_area_ovl.area);
    }
    return (error)? FAILURE : SUCCESS;
}

int find_rectanlge_overlap(Rectangle* rect_list, int len) {
    ErrorType error = NO_ERROR;
    int no_overlap = 1;
    int num_overlap = 0;

    sort_rectangle_list(rect_list, len);

    for (int i = 0; i < len; ++i) {
        for (int j = i+1; j < len; ++j) {
            int overlap = 0;
            if (rect_list[i].width > rect_list[j].width)
                overlap = rectcmp(&rect_list[i], &rect_list[j]);
            else 
                overlap = rectcmp(&rect_list[j], &rect_list[i]);
            if (overlap) {
                no_overlap = 0;
                printf("Rectangle #%d overlaps with rectangle #%d\n", rect_list[i].id, rect_list[j].id);
            }
        }
    }

    if (no_overlap) printf("No intersection found\n");

    return (error)? FAILURE : SUCCESS;
}