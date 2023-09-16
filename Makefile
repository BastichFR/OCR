# Makefile

CC = gcc -I../../include/
CFLAGS = -Wall -Wextra #-Werror
SUCC = @echo Successfully compiled

# Dossiers Sources
SRC_DIRS = src/Imagery/Tools src/Imagery/Color_Treatment

# C files
CSOLVE = solve.c
CSDL = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
CGUI = src/GUI/gtk.c

# Chemins pour les en-têtes
INCLUDE_DIRS = include
INCLUDE_FLAGS = $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Libs
LGTK = `pkg-config --cflags --libs gtk+-3.0`
LSDL = -I/usr/include/SDL -lSDL -lSDL_image -lSDLmain

solve: $(CSOLVE) $(CSDL)
	${CC} ${CFLAGS} -g -o solve $^ ${INCLUDE_FLAGS} ${LSDL}
	${SUCC}

clean:
	rm -f solve
	rm -f grids/grid_00.*
	@echo Successfully removed

# END
