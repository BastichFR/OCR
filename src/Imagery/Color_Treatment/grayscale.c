#include "Imagery/Color_Treatment/grayscale.h"

/// @brief Grayscale an image
/// @param image The image to grayscale
void grayscale(Image* image)
{
    Pixel pixel;
    double average;

    for (unsigned int y = 0; y < image->height; y++)
        {
            for (unsigned int x = 0; x < image->width; x++)
                {
                    pixel = image->pixels[x][y];

                    average =
                      0.3 * pixel.red + 0.59 * pixel.green + 0.11 * pixel.blue;

                    image->pixels[x][y].red = average;
                    image->pixels[x][y].green = average;
                    image->pixels[x][y].blue = average;
                }
        }
}
