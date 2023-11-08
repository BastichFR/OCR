#include "Imagery/Color_Treatment/blackandwhite.h"

/// @brief Black and white an image
/// @param image The image to black and white
void blackandwhite(Image* image)
{
    Pixel* pixel;

    for (unsigned int y = 0; y < image->height; y++)
        {
            for (unsigned int x = 0; x < image->width; x++)
                {
                    pixel = &image->pixels[x][y];

                    if ((pixel->red + pixel->green + pixel->blue) / 3
                        >= image->average)
                        {
                            pixel->red = 255;
                            pixel->green = 255;
                            pixel->blue = 255;
                        }
                    else
                        {
                            pixel->red = 0;
                            pixel->green = 0;
                            pixel->blue = 0;
                        }
                }
        }
}
