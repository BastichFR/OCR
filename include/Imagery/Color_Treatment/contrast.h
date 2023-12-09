#ifndef CONTRAST_H
#define CONTRAST_H

#include <math.h>
#include "Imagery/Tools/image.h"

float image_max_color(Image *image);
void image_normalize_brightness(Image *image);
void image_levels(Image *image, size_t n);
void image_invertion(Image *image);

#endif // CONTRAST_H
