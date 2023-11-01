#include <stdlib.h>

#define N 9

/// @brief Find an empty cell in the grid
/// @param board The grid to resolve
/// @param v1 The first value of the empty cell
/// @param v2 The second value of the empty cell
/// @return EXIT_SUCCESS if an empty cell is found, EXIT_FAILURE otherwise
int find_empty(size_t board[N][N], size_t *v1, size_t *v2){
	for(size_t i = 0; i < N; i++){
		for(size_t j = 0; j < N; j++){ 
			if(board[i][j] == 0){
				*v1 = i;
				*v2 = j;
				return EXIT_SUCCESS;
			}
		}
	}
	return EXIT_FAILURE;
}


/// @brief Check if a number is valid in a position
/// @param board The grid to resolve
/// @param x The x position
/// @param y The y position
/// @param num The number to check
/// @return EXIT_SUCCESS if the number is valid, EXIT_FAILURE otherwise
int is_pos_valid(size_t board[N][N], size_t x, size_t y, size_t num){
	
	for(size_t i = 0; i < N; i++){
		// is row valid
		if(board[x][i] == num && i != y){
			return EXIT_FAILURE;
		}

		// is col valid
		if(board[i][y] == num && i != x){
			return EXIT_FAILURE;
		}
	}

	// is block valid
	size_t b_i = x - (x%3);
	size_t b_j = y - (y%3);

	for(size_t i = 0; i < 3; i++){
		for(size_t j = 0; j < 3; j++){
			if(board[b_i+i][b_j+j] == num \
				&& b_i + i != x && b_j + j != y){
				return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}


/// @brief Resolve a grid (backtracking algorithm)
/// @param board The grid to resolve
/// @return EXIT_SUCCESS if the grid is resolved, EXIT_FAILURE otherwise
int resolve_grid(size_t board[N][N]){
	
	size_t x, y;

	if(find_empty(board, &x, &y) == EXIT_FAILURE){
		return EXIT_SUCCESS;
	}

	for(size_t num = 1; num <= N; num++){
		if(is_pos_valid(board, x, y, num) == EXIT_SUCCESS){
			board[x][y] = num;

			if (resolve_grid(board) == EXIT_SUCCESS){
				return EXIT_SUCCESS;
			}

			board[x][y] = 0;
		}
	}
	return EXIT_FAILURE;
}
