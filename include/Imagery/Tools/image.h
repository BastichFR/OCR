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
    int          average;
    Pixel**      pixels;
    char*        path;
} Image;

Image create_image(SDL_Surface *surface, char* path);

Image create_empty_image(size_t width, size_t height, char* path);

SDL_Surface* image_to_surface(Image *image);

void free_image(Image *image);

void pixel_same_value(Pixel *pixel, unsigned int value);

int* pixel_neighbors(Image *image,unsigned int x,unsigned int y);

Image copy_image(Image *copiedImage);

#endif // SCREEN_H
