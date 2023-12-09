#include "Imagery/Color_Treatment/treshold.h"
#include <math.h>
#include <stdio.h>
/// @brief an image
/// @param image The image to black and white

void image_invert(Image *image)
{
    int whitePixel = 0;
    int blackPixel = 0;

    for (unsigned int i = 0; i < image->width; i++)
    {
        for (unsigned int j = 0; j < image->height; j++)
        {
            if (image->pixels[i][j].blue == 0)
                blackPixel++;
            else
                whitePixel++;
        }
    }
    
    if (whitePixel > blackPixel) {
        for (unsigned int i = 0; i < image->width; i++)
        {
	    for (unsigned int j = 0; j < image->height; j++)
	    {
	        pixel_same_value(&(image->pixels[i][j]),
	                         255 - image->pixels[i][j].blue);
	    }
        }
    }
}

float noiseLevel(Image *image)
{
    float count = 0.0;
    double medium = 0.0;
    int* neighbors;
    for (unsigned int x = 0; x < image->width; x++)
    {
        for (unsigned int y = 0; y < image->height; y++)
        {
            medium = 0.0;
            neighbors = pixel_neighbors(image, x, y);
            for (unsigned int k = 0; k < 9; k++)
            {
                medium += neighbors[k];
            }
            free(neighbors);
            medium /= 9;

            double val = 1 - (image->pixels[x][y].red / medium);
            if (val < 0)
            {
                val *= -1;
            }
            if (val > 0.5)
            {
                count++;
            }
        }
    }

    return count;
}

void image_adaptative_threshold(Image *image)
{
    const unsigned int width = image->width;
    const unsigned int height = image->height;

    const float nlevel = noiseLevel(image) > 300 ? 0.5 : 0.15;

    const int s2 = fmax(width, height) / 16;
    unsigned long *integral_image =
        calloc(width * height, sizeof(unsigned long));
    long sum = 0;
    unsigned int count = 0;
    int x1, y1, x2, y2;

    for (unsigned int y = 0; y < height; y++)
    {
        sum += image->pixels[0][y].red;
        integral_image[y] = sum;
    }

    for (unsigned int x = 1; x < width; x++)
    {
        sum = 0;
        for (unsigned int y = 0; y < height; y++)
        {
            sum += image->pixels[x][y].red;
            integral_image[x * height + y] =
                integral_image[(x - 1) * height + y] + sum;
        }
    }
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            x1 = fmax(x - s2, 1);
            x2 = fmin(x + s2, width - 1);
            y1 = fmax(y - s2, 1);
            y2 = fmin(y + s2, height - 1);
            count = (x2 - x1) * (y2 - y1);
            sum = integral_image[x2 * height + y2];
            sum -= integral_image[x2 * height + (y1 - 1)];
            sum -= integral_image[(x1 - 1) * height + y2];
            sum += integral_image[(x1 - 1) * height + (y1 - 1)];
            if (image->pixels[x][y].red * count < sum * (1.0 - nlevel))
            {
                pixel_same_value(&(image->pixels[x][y]), 0);
            }
            else
            {
                pixel_same_value(&(image->pixels[x][y]), 255);
            }
        }
    }
    free(integral_image);
    image_invert(image);
}
