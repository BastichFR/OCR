#include "Imagery/Tools/image.h"

/// @brief Create an Image from a Surface
/// @param surface The Surface that will be used to create the Image
/// @return An Image that represent the pixels of the Surface
Image create_image(SDL_Surface *surface){
    Image image;

    image.width = surface->w;
    image.height = surface->h;

    // sizeof(Pixel *) => size of the pointer
    image.pixels =  calloc(image.width, sizeof(Pixel *));


    if (image.pixels == NULL)
    {
        errx(EXIT_FAILURE, "Error while allocating memory");
    }

    for(unsigned int x = 0; x < image.width; x++){
        image.pixels[x] = calloc(image.height, sizeof(Pixel));
        if (image.pixels[x] == NULL)
        {
            errx(EXIT_FAILURE, "Error while allocating memory");
        } 
    }

    SDL_Color clr;
    Uint32 pixel;

    for (unsigned int x = 0; x < image.width; x++){
        for (unsigned int y = 0; y < image.height; y++){
            if(surface == NULL){
                image.pixels[x][y].red   = 0;
                image.pixels[x][y].green = 0;
                image.pixels[x][y].blue  = 0;
            } else {
                // Get pixel from surface
                pixel = getpixel(surface, x, y);

                // Get the RGB values from the pixel
                SDL_GetRGB(pixel, surface->format, &clr.r, &clr.g, &clr.b);

                image.pixels[x][y].red   = clr.r;
                image.pixels[x][y].green = clr.g;
                image.pixels[x][y].blue  = clr.b;
            }
        }
    }

    return image;
};


/// @brief Create a Surface from an Image
/// @param image The Image that will be used to create the Surface
/// @return A Surface that represent the new Image
SDL_Surface *image_to_surface(Image *image){
    const unsigned int w = image->width;
    const unsigned int h = image->height;

    SDL_Surface *surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

    for (unsigned int x = 0; x < w; x++)
    {
        for (unsigned int y = 0; y < h; y++)
        {
            // Get pixel from image
            Pixel _pixel = image->pixels[x][y];

            // Get pixel value for SDL
            Uint8 r = _pixel.red;
            Uint8 g = _pixel.green;
            Uint8 b = _pixel.blue;
            Uint32 pixel = SDL_MapRGB(surface->format, r, g, b);

            // Put pixel in img
            putpixel(surface, x, y, pixel);
        }
    }

    return surface;
};


/// @brief Free the data used by the Image
/// @param image The Image to freeT
void free_image(Image *image){

    for(unsigned int x = 0; x < image->width; x++){
        free(image->pixels[x]);
    }
    free(image->pixels);
};