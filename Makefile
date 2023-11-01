# Makefile

CC = gcc
CFLAGS = -Wall -Wextra #-Werror

INCLUDE_FLAGS = -Iinclude

# Dossiers Sources
SRC_DIRS = 	src/Imagery/Tools\
			src/Imagery/Color_Treatment\
			src/Imagery/Detection\
			src/Neural_Network\
			src/Demo\

# C files
CSOLVER = solver.c
CSDL = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

# Chemins pour les en-têtes
INCLUDE_DIRS = include
INCLUDE_FLAGS = $(foreach dir,$(INCLUDE_DIRS),-I$(dir))

# Libs
LGTK = `pkg-config --cflags --libs gtk+-3.0`
LSDL = -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lm

all: solver

solver: $(CSOLVER) $(CSDL)
	@${CC} ${CFLAGS} -g -o solver $^ ${INCLUDE_FLAGS} ${LSDL}
	@echo Successfully compiled $@

.PHONY: all clean

clean:
	rm -f solver
	@echo Successfully removed

# TODO trouver un moyen d'opti le build (faire des .o)
# END
