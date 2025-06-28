#include <stdio.h>
#include <stdlib.h>

#include "includes/defines.h"
#include "includes/error_handler.h"
#include "includes/file_handler.h"
#include "includes/rectangle.h"

#define DEF_INPUT_FILE "inputs/input.txt"

int main(int argc, char* argv[]) {
	if (argc > NUM_ARGS) error_handler(NULL, ARG_TOO_MANY);

	FILEx* fin = fileX_init((argc > 1)? argv[1] : DEF_INPUT_FILE, "rt");
	if (fin == NULL) return EXIT_FAILURE;
	int arrlen = 0;
	Rectangle* rect_list = NULL;
	int checkInput = get_rectangle_list(fin, &rect_list, &arrlen);
	int checkSuccess = FAILURE;

	if (checkInput == SUCCESS)
        checkSuccess = find_rectanlge_overlap(arrlen, rect_list);

	free(rect_list);
	exit_message(checkSuccess);
	return (checkSuccess)? EXIT_SUCCESS : EXIT_FAILURE;
}	