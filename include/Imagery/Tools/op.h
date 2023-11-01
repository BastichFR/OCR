#ifndef OP_H
#define OP_H

#include <err.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Imagery/Tools/io.h"
#include "Imagery/Tools/image.h"

#include "Imagery/Color_Treatment/grayscale.h"
#include "Imagery/Color_Treatment/noise_filter.h"
#include "Imagery/Color_Treatment/blackandwhite.h"
#include "Imagery/Color_Treatment/edge_detection.h"

void init_sdl();

void exec_main(const char *path);

#endif // OP_H