#include <string.h>
#include <err.h>
#include "include/Imagery/Tools/op.h"
#include "Demo/XOR.h"

#include "Demo/XOR.h"

void exit_help(){
	char help[] = 	"Usage:\n"
					"--demo \"XOR\"\n"
					"--solve <path>\n";
	errx(EXIT_FAILURE, "%s", help);
}


void exec_demo(char** argv)
{
	if (strcmp(argv[2],  "XOR") == 0)
		build_xor();
	else
		exit_help();
}

void solve(char** argv)
{
	size_t len = strlen(argv[2]);
	char path[len + 1];
	strcpy(path, argv[2]);
	path[len] = 0;

	exec_main(path);
}


int main(int argc, char** argv){ 

	if(argc != 3){
		exit_help();
	}

	if (strcmp(argv[1], "--demo") == 0)	{
		exec_demo(argv);
	} else if (strcmp(argv[1], "--solve") == 0) {
        solve(argv);
	} else {
        exit_help();
	}
	
	return EXIT_SUCCESS;
}
		
