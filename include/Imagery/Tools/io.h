#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>

SDL_Surface* Load_SDL_img(const char *path);
int Save_SDL_img(SDL_Surface *image, const char *path);

#endif // IO_H