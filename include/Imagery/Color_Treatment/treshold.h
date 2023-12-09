#ifndef TRESHOLD_H
#define TRESHOLD_H

#include <math.h>
#include "Imagery/Tools/image.h"

void image_adaptative_threshold(Image *image);

float noiseLevel(Image *image);

void image_invert(Image *image);
#endif // TRESHOLD_H
