#ifndef IMAGE_H
#define IMAGE_H

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Imagery/Tools/pixel.h"

/// @brief Structure thar represent a Pixel on the Image
typedef struct{
    Uint8 red;
    Uint8 green;
    Uint8 blue;
} Pixel;


/// @brief Structure that represent the image 
typedef struct {
    unsigned int width;
    unsigned int height;
    Pixel **pixels;
} Image;

Image create_image(SDL_Surface *surface);

SDL_Surface *image_to_surface(Image *image);


void free_image(Image *image);

#endif // SCREEN_H