#include "Imagery/Color_Treatment/edge_detection.h"

/// @brief Apply the edge detection filter to an image
void edgeDetection(Image* image)
{
    Image new_Image = create_empty_image(image->width, image->height);

    for (unsigned int y = 1; y < image->height - 1; y++)
        {
            for (unsigned int x = 1; x < image->width - 1; x++)
                {
                    int dx = -image->pixels[x - 1][y - 1].red
                      - 2 * image->pixels[x - 1][y].red
                      - image->pixels[x - 1][y + 1].red
                      + image->pixels[x + 1][y - 1].red
                      + 2 * image->pixels[x + 1][y].red
                      + image->pixels[x + 1][y + 1].red;
                    int dy = -image->pixels[x - 1][y - 1].red
                      - 2 * image->pixels[x][y - 1].red
                      - image->pixels[x + 1][y - 1].red
                      + image->pixels[x - 1][y + 1].red
                      + 2 * image->pixels[x][y + 1].red
                      + image->pixels[x + 1][y + 1].red;

                    int gradient = (int)sqrt(dx * dx + dy * dy);
                    // Affecter la valeur du gradient au pixel de la nouvelle image
                    new_Image.pixels[x][y].red = (Uint8)gradient;
                    new_Image.pixels[x][y].green = (Uint8)gradient;
                    new_Image.pixels[x][y].blue = (Uint8)gradient;

                    new_Image.average += gradient;
                }
        }

    image->average = new_Image.average / (new_Image.height * new_Image.width * 3);
    for (unsigned int y = 1; y < image->height - 1; y++)
        {
            for (unsigned int x = 1; x < image->width - 1; x++)
                {
                    image->pixels[x][y] = new_Image.pixels[x][y];
                }
        }
    free_image(&new_Image);
}
