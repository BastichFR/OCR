#include "main.h"

void exit_help()
{
    char help[] = "Usage:\n"
                "   --demo  XOR \n"
                "   --demo  <path/to/solve.txt> \n"
                "   --solve <path/to/solve.png> \n";
    errx(EXIT_FAILURE, "%s", help);
}

void exec_demo(char** argv)
{
    if (strcmp(argv[2], "XOR") == 0)
        build_xor();
    else
    {
        size_t len = strlen(argv[2]);
        char path[len + 1];
        strcpy(path, argv[2]);
        path[len] = 0;

        if(demo_solve_sudoku(path) == EXIT_SUCCESS)
            printf("Sudoku solved !\n");
        else
            printf("Invalid grid !\n");
    }
}

void exec_solve(char** argv)
{
    size_t len = strlen(argv[2]);
    char path[len + 1];
    strcpy(path, argv[2]);
    path[len] = 0;

    exec_main(path);
}

#include <math.h>

int main(int argc, char** argv)
{
    if (argc != 3)
        {
            exit_help();
        }

    if (strcmp(argv[1], "--demo") == 0)
        {
            exec_demo(argv);
        }
    else if (strcmp(argv[1], "--solve") == 0)
        {
            exec_solve(argv);
        }
    else
        {
            exit_help();
        }

    return EXIT_SUCCESS;
}
