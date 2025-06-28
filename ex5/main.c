#include <stdio.h>
#include <stdlib.h>

#include "includes/color.h"
#include "includes/defines.h"
#include "includes/error_handler.h"
#include "includes/file_handler.h"
#include "includes/rectangle.h"

#define DEF_INPUT_FILE "inputs/input.txt"
#define DEF_COLOR_FILE "inputs/colors.txt"

int main(int argc, char* argv[]) {
	if (argc > NUM_ARGS) error_handler(NULL, ARG_TOO_MANY);

	FILEx* fin = fileX_init((argc > 1)? argv[1] : DEF_INPUT_FILE, "rt");
	FILEx* fcl = fileX_init((argc > 2)? argv[2] : DEF_COLOR_FILE, "rt");
	if (fin == NULL || fcl == NULL) return EXIT_FAILURE;

	int arrlen = 0;
	int cl_len = 0;
	Color* color_list = NULL;
	Rectangle* rect_list = NULL;
	int checkColor = get_color_list(fcl, &color_list, &cl_len);
	int checkInput = (checkColor)? get_rectangle_list(fin, color_list, cl_len, &rect_list, &arrlen) : FAILURE;

	fileX_kill(fin);
	fileX_kill(fcl);

	int checkSuccess = FAILURE;
	if (checkInput == SUCCESS)
        // checkSuccess = find_rectanlge_overlap(rect_list, arrlen);
		checkSuccess = linesweep(rect_list, arrlen, color_list, cl_len);
	kill_rectangle_list(&rect_list, arrlen);
	kill_color_list(&color_list, cl_len);

	exit_message(checkSuccess);
	return (checkSuccess)? EXIT_SUCCESS : EXIT_FAILURE;
}