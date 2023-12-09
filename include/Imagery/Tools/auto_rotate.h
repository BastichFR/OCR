#ifndef AUTO_ROTATE_H
#define AUTO_ROTATE_H

#include "Imagery/Detection/detection.h"
#include "Imagery/Detection/HoughTransform.h"
#include "Imagery/Tools/rotate.h"

Image image_auto_rotate(Image *image, Image *copy, double maxTheta, LinkedList* lineList);

#endif // AUTO_ROTATE_H
