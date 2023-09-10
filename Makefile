# Makefile

CC = gcc
CFLAGS = -Wall -Wextra
SUCC = echo Successfully compiled

GTK = `pkg-config --cflags --libs gtk+-3.0`


solve: solve.c src/*.c 
	${CC} ${CFLAGS} -o solve solve.c src/*.c
	${SUCC}


clean:
	rm -f solve
	rm -f grids/grid_00.*
	echo Successfully removed

# END
