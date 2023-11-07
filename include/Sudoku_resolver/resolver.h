#ifndef RESOLVER_H
#define RESOLVER_H

#include <stddef.h>
#include <stdlib.h>

#define N 9

int solvable(size_t board[N][N]);
int resolve_grid(size_t board[9][9]);

#endif // RESOLVER_H