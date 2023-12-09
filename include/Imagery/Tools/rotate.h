#ifndef ROTATE_H
#define ROTATE_H

#include <err.h>
#include <math.h>
#include <stdio.h>

#include "Imagery/Tools/image.h"

void rotate(Image *image, double angleDegree);

double bilinearly_interpolate(unsigned int top, unsigned int bottom,
                              unsigned int left, unsigned int right,
                              double horizontal_position,
                              double vertical_position, Pixel **pixels);

#endif // ROTATE_H
