# Makefile

# Variables
SRC		= src/
BUILD 	= build/
NAME 	= solver
INCLUDE = include

# Flags
CC 		= gcc
CFLAGS 	= -Werror -pedantic -Wall -Wextra -Wabi=11 -I${INCLUDE} -g
LDFLAGS = #-fsanitize=address
LDLIBS 	=

# Libs
LGTK 	= `pkg-config --cflags --libs gtk+-3.0`
LSDL 	= -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lm

# Files
FILES 	= $(shell find $(SRC) -type f -name '*.c')
OBJ 	= $(patsubst $(SRC)%.c, $(BUILD)%.o, $(FILES))

all: info build

build: $(OBJ)
	@${CC} ${CFLAGS} ${LDFLAGS} -g -o ${NAME} $(OBJ) ${LGTK} ${LSDL}

clean:
	@rm -rf $(BUILD)
	@rm -f $(NAME)

re: clean build
	@echo "re done"

run: build
	./${NAME}

info:
	@echo "Informations about ORC project : "
	@echo
	@echo "-------------- PROJET OCR -------------- "
	@cat AUTHORS
	@echo "----------------- RUN ------------------ "
	@echo "make		: display informations & build"
	@echo "make info	: display informations"
	@echo "make build	: build the project"
	@echo "make clean	: clean the project"
	@echo "make re		: rebuild the project"
	@echo "make run	: run the project"
	@echo "---------------- USAGE ----------------- "
	@echo "./solver --demo  XOR"
	@echo "./solver --demo  <path/to/solve.txt>"
	@echo "./solver --solve <path/to/solve.png>" 
	@echo "---------------------------------------- "

demo: build
	cat grids/grid_00
	./${NAME} --demo grids/grid_00
	cat grids/grid_00.result

# Rules	
$(BUILD)%.o: $(SRC)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I${INCLUDE} ${LGTK} ${LSDL}



.PHONY: all build clean re run info