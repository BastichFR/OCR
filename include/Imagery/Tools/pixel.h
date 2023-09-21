#ifndef PIXEL_H
#define PIXEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

#endif // PIXEL_H