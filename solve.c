#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "include/file_image_io.h"
#include "include/file_text_io.h"
#include "include/resolver.h"
#include "include/gtk.h"

void exit_help(){
	char help[] = "Usage: path/to/file \n";
	errx(EXIT_FAILURE, "%s", help);
}


int main(int argc, char** argv){ 

	if(argc != 2){
		exit_help();
	}

	size_t len = strlen(argv[1]);
	char path[len + 1];
	strcpy(path, argv[1]);
	path[len] = 0;

	window();

	//get_image_data(path);

	/*

	size_t board[9][9];


	extract_data(path, board);
	resolve_grid(board);
	write_data(path, board);
	*/
	return EXIT_SUCCESS;

}
		