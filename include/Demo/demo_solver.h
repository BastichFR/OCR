#ifndef DEMO_SOLVER_H
#define DEMO_SOLVER_H

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#include "Sudoku_resolver/resolver.h"

#define N 9

int demo_solve_sudoku(char path[]);
int extract_data(char path[], size_t board[9][9]);
int write_data(char path[], size_t board[9][9]); 

#endif // DEMO_SOLVER_H