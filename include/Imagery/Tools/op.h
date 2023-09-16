#ifndef OP_H
#define OP_H

#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <err.h>

#include "Imagery/Tools/image.h"
#include "Imagery/Color_Treatment/blackandwhite.h"

void init_sdl();

void exec_main(const char *path);

#endif // OP_H