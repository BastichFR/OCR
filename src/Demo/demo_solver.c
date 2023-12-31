#include "Demo/demo_solver.h"

int demo_solve_sudoku(char path[]){
    size_t board[N][N] = {0};
    extract_data(path, board);
    if (resolve_grid(board) == EXIT_SUCCESS)
        {
            write_data(path, board);
            return EXIT_SUCCESS;
        }
    return EXIT_FAILURE;
}

/// @brief Extract data from a file
/// @param path The path of the file
/// @param board The grid to fill
/// @return EXIT_SUCCESS if the data is extracted, EXIT_FAILURE otherwise
int extract_data(char path[], size_t board[N][N])
{
    FILE* file;

    if (access(path, F_OK) == -1)
        {
            errx(1, "invalid path : %s\n", path);
        }

    file = fopen(path, "r");

    if (file == NULL)
        {
            errx(1, "Error while opening %s", path);
        }

    int col = 0;
    int row = 0;
    char caractere;
    while ((caractere = fgetc(file)) != EOF)
        {
            if (caractere == ' ' || caractere == '\n')
                {
                    continue;
                }

            if (col == N)
                {
                    col = 0;
                    row++;
                }

            if (row >= N)
                {
                    break;
                }

            if (caractere == '.')
                {
                    board[row][col] = 0;
                }
            else
                {
                    board[row][col] = (size_t)(caractere - 48);
                }
            col++;
        }

    fclose(file);

    return EXIT_SUCCESS;
}

/// @brief Write data in a file
/// @param path The path of the file
/// @param board The grid to write
/// @return EXIT_SUCCESS if the data is written, EXIT_FAILURE otherwise
int write_data(char path[], size_t board[N][N])
{
    char extension[] = ".result";
    char new_path[strlen(path) + strlen(extension) + 1];

    strcpy(new_path, path);
    strcat(new_path, extension);

    FILE* file = fopen(new_path, "w");

    if (file == NULL)
        {
            errx(1, "Unable to create/open file: %s\n", path);
        }

    for (size_t row = 0; row < 9; row++)
        {
            for (size_t col = 0; col < 9; col++)
                {
                    if (col % 3 == 0 && col != 0)
                        {
                            fprintf(file, "%c", ' ');
                        }

                    if (board[row][col] == 0)
                        {
                            fprintf(file, "%c", '.');
                        }
                    else
                        {
                            fprintf(file, "%c", (char)(board[row][col] + 48));
                        }
                }
            if ((row + 1) % 3 == 0 && row != 0 && row != 8)
                {
                    fprintf(file, "%c", '\n');
                }
            fprintf(file, "\n");
        }
    fclose(file);

    return EXIT_SUCCESS;
}
