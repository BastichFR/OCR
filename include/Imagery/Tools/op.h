#ifndef OP_H
#define OP_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include <err.h>

#include "Imagery/Tools/io.h"
#include "Imagery/Tools/image.h"
#include "Imagery/Color_Treatment/blackandwhite.h"
#include "Imagery/Color_Treatment/grayscale.h"

void init_sdl();

void exec_main(const char *path);

#endif // OP_H