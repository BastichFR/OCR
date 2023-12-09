#include "Imagery/Tools/rotate.h"

void rotate(Image *image, double angleDegree)
{
    const unsigned int width = image->width;
    const unsigned int height = image->height;

    const double middleX = ((double)width / 2.0);
    const double middleY = ((double)height / 2.0);

    const double angle = angleDegree * M_PI / 180.0;

    // Create two dimensional array of pixels
    Pixel **_pixels = calloc(image->width, sizeof(Pixel*));

    if (_pixels == NULL)
    {
        errx(EXIT_FAILURE, "Error while allocating memory");
    }

    for (unsigned int x = 0; x < image->width; x++)
    {
        _pixels[x] = calloc(image->height, sizeof(Pixel));
        if (_pixels[x] == NULL)
        {
            errx(EXIT_FAILURE, "Error while allocating memory");
        }
    }

    for (unsigned int x = 0; x < image->width; x++)
    {
        for (unsigned int y = 0; y < image->height; y++)
        {
            _pixels[x][y].red = image->pixels[x][y].red;
            _pixels[x][y].green = image->pixels[x][y].green;
            _pixels[x][y].blue = image->pixels[x][y].blue;
        }
    }
    
    // Copy of all pixel
    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            // Consider that the image is in grayscale
            pixel_same_value(&(image->pixels[x][y]), 0);
        }
    }

    double newX;
    double newY;
    // Four pixels around
    unsigned int top;
    unsigned int bottom;
    unsigned int left;
    unsigned int right;
    for (unsigned int x = 0; x < width; x++)
    {
        for (unsigned int y = 0; y < height; y++)
        {
            // Calculate new position
            newX = ((double)(cos(angle) * ((double)x - middleX)
                             - sin(angle) * ((double)y - middleY))
                    + middleX);
            newY = ((double)(cos(angle) * ((double)y - middleY)
                             + sin(angle) * ((double)x - middleX))
                    + middleY);

            // Get the four locations around pixels
            // floor() : Round at inferior
            top = floor(newY);
            bottom = top + 1;
            left = floor(newX);
            right = left + 1;

            if (top < height && bottom < height && left < width
                && right < width)
            {
                unsigned int interpolated = bilinearly_interpolate(
                    top, bottom, left, right, newX, newY, _pixels);
                pixel_same_value(&(image->pixels[x][y]), interpolated);
            }
        }
    }

    for (unsigned int i = 0; i < width; i++)
    {
        free(_pixels[i]);
    }
    free(_pixels);
}

double bilinearly_interpolate(unsigned int top, unsigned int bottom,
                              unsigned int left, unsigned int right,
                              double horizontal_position,
                              double vertical_position, Pixel **pixels)
{
    double top_left = pixels[left][top].red;
    double top_right = pixels[right][top].red;
    double bottom_left = pixels[left][bottom].red;
    double bottom_right = pixels[right][bottom].red;

    double horizontal_progress = horizontal_position - (double)left;
    double vertical_progress = vertical_position - (double)top;

    double top_block = top_left + horizontal_progress * (top_right - top_left);

    double bottom_block =
        bottom_left + horizontal_progress * (bottom_right - bottom_left);

    return top_block + vertical_progress * (bottom_block - top_block);
}
