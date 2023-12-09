#include "Imagery/Tools/image.h"

/// @brief Create an Image from a Surface
/// @param surface The Surface that will be used to create the Image
/// @return An Image that represent the pixels of the Surface
Image create_image(SDL_Surface* surface, char* path)
{
    Image image;
    image.width = surface->w;
    image.height = surface->h;
    image.path = path;
    
    // sizeof(Pixel *) => size of the pointer
    image.pixels = calloc(image.width, sizeof(Pixel*));
    image.average = 0;
    
    if (image.pixels == NULL)
        {
            errx(EXIT_FAILURE, "Error while allocating memory");
        }

    for (unsigned int x = 0; x < image.width; x++)
        {
            image.pixels[x] = calloc(image.height, sizeof(Pixel));
            if (image.pixels[x] == NULL)
                {
                    errx(EXIT_FAILURE, "Error while allocating memory");
                }
        }

    SDL_Color clr;
    Uint32 pixel;

    for (unsigned int x = 0; x < image.width; x++)
        {
            for (unsigned int y = 0; y < image.height; y++)
                {
                    if (surface == NULL)
                        {
                            image.pixels[x][y].red = 0;
                            image.pixels[x][y].green = 0;
                            image.pixels[x][y].blue = 0;
                        }
                    else
                        {
                            // Get pixel from surface
                            pixel = getpixel(surface, x, y);

                            // Get the RGB values from the pixel
                            SDL_GetRGB(pixel, surface->format, &clr.r, &clr.g,
                                       &clr.b);

                            image.pixels[x][y].red = clr.r;
                            image.pixels[x][y].green = clr.g;
                            image.pixels[x][y].blue = clr.b;

                            image.average += clr.r + clr.g + clr.b;
                        }
                }
        }

    image.average = image.average / (image.height * image.width * 3);

    return image;
}

/// @brief Create an empty Image
/// @param width  the width  of the image
/// @param height the height of the image
/// @return An empty Image
Image create_empty_image(size_t width, size_t height, char* path)
{
    Image image;

    image.width = width;
    image.height = height;
    image.path = path;
    // sizeof(Pixel *) => size of the pointer
    image.pixels = calloc(image.width, sizeof(Pixel*));
    image.average = 0;

    if (image.pixels == NULL)
        {
            errx(EXIT_FAILURE, "Error while allocating memory");
        }

    for (unsigned int x = 0; x < image.width; x++)
        {
            image.pixels[x] = calloc(image.height, sizeof(Pixel));
            if (image.pixels[x] == NULL)
                {
                    errx(EXIT_FAILURE, "Error while allocating memory");
                }
        }

    for (unsigned int x = 0; x < image.width; x++)
        {
            for (unsigned int y = 0; y < image.height; y++)
                {
                    image.pixels[x][y].red = 0;
                    image.pixels[x][y].green = 0;
                    image.pixels[x][y].blue = 0;
                }
        }

    return image;
}

/// @brief Create a Surface from an Image
/// @param image The Image that will be used to create the Surface
/// @return A Surface that represent the new Image
SDL_Surface* image_to_surface(Image* image)
{
    const unsigned int w = image->width;
    const unsigned int h = image->height;

    SDL_Surface* surface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);

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
}

Image copy_image(Image *copiedImage)
{
    Image image;

    image.width = copiedImage->width;
    image.height = copiedImage->height;
    image.path = copiedImage->path;
    // sizeof(Pixel *) => size of the pointer
    image.pixels = calloc(image.width, sizeof(Pixel*));
    image.average = 0;

    if (image.pixels == NULL)
    {
        errx(EXIT_FAILURE, "Error while allocating memory");
    }

    for (unsigned int x = 0; x < image.width; x++)
    {
        image.pixels[x] = calloc(image.height, sizeof(Pixel));
        if (image.pixels[x] == NULL)
        {
            errx(EXIT_FAILURE, "Error while allocating memory");
        }
    }

    for (unsigned int x = 0; x < image.width; x++)
    {
        for (unsigned int y = 0; y < image.height; y++)
        {
            image.pixels[x][y].red = copiedImage->pixels[x][y].red;
            image.pixels[x][y].green = copiedImage->pixels[x][y].green;
            image.pixels[x][y].blue = copiedImage->pixels[x][y].blue;
        }
    }

    return image;
}

/// @brief Free the data used by the Image
/// @param image The Image to freeT
void free_image(Image* image)
{
    for (unsigned int x = 0; x < image->width; x++)
        {
            free(image->pixels[x]);
        }
    free(image->pixels);
}

void pixel_same_value(Pixel *pixel, unsigned int value)
{
    pixel->red = value;
    pixel->green = value;
    pixel->blue = value;
}

int* pixel_neighbors(Image *image,unsigned int x,unsigned int y)
{
    unsigned int h = image->height;
    unsigned int w = image->width;
    int* neighbors = malloc(sizeof(int) * 9);
    for (int i = 0; i < 9; ++i)
    {
        neighbors[i] = 0;
    }
    neighbors[4] = image->pixels[x][y].red;

    if (x > 0)
    {
        if (y > 0)
            neighbors[0] = image->pixels[x - 1][y - 1].red;
        neighbors[3] = image->pixels[x - 1][y].red;
        if (y < h - 1)
            neighbors[6] = image->pixels[x - 1][y + 1].red;
    }
    if (x < w - 1)
    {
        if (y > 0)
            neighbors[2] = image->pixels[x + 1][y - 1].red;
        neighbors[5] = image->pixels[x + 1][y].red;
        if (y < h - 1)
            neighbors[8] = image->pixels[x + 1][y + 1].red;
    }
    if (y > 0)
    {
        if (x > 0)
            neighbors[0] = image->pixels[x - 1][y - 1].red;
        neighbors[1] = image->pixels[x][y - 1].red;
        if (x < w - 1)
            neighbors[2] = image->pixels[x + 1][y - 1].red;
    }
    if (y != h - 1)
    {
        if (x > 0)
            neighbors[6] = image->pixels[x - 1][y + 1].red;
        neighbors[7] = image->pixels[x][y + 1].red;
        if (x < w - 1)
            neighbors[8] = image->pixels[x + 1][y + 1].red;
    }
    return neighbors;
}

