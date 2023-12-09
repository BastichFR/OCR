#include "Imagery/Color_Treatment/blackandwhite.h"

/// @brief an image
/// @param image The image to black and white

float image_max_color(Image *image)
{
    float m = 0;
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            if (image->pixels[x][y].red > m)
                m = image->pixels[x][y].red;
        }
    }

    return m;
}

void image_normalize_brightness(Image *image)
{
    float m = image_max_color(image);
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            pixel_same_value(&(image->pixels[x][y]), 
                             255 - image->pixels[x][y].red * (255.f / m));
        }
    }
}

void image_levels(Image *image, size_t n)
{
    for (size_t x = 0; x < image->width; x++)
    {
        for (size_t y = 0; y < image->height; y++)
        {
            float v = image->pixels[x][y].red;
            for (size_t i = 0; i < n; i++)
            {
                if (v >= i * (255.f / n) && v <= (i + 1) * (255.f / n))
                {
                    pixel_same_value(&(image->pixels[x][y]),
                                     (i + 1) * (255.f / n));
                }
            }
        }
    }
}

void image_invertion(Image *image)
{
    for (unsigned int y = 0; y < image->height; y++)
    {
    	for (unsigned int x = 0; x < image->width; x++)
	{
	    pixel_same_value(&(image->pixels[x][y]),
                             255 - image->pixels[x][y].blue);
        }
    }
}


