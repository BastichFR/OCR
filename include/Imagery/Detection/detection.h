#ifndef DETECTION_H
#define DETECTION_H

#include <math.h>
#include "Imagery/Tools/image.h"
#include "Imagery/Detection/HoughTransform.h"
#include "Imagery/Detection/square_detection.h"
#include "Imagery/Tools/auto_rotate.h"
#include "Imagery/Detection/distortion_correction.h"

Image detection(Image *image, Image *copy, Image *simplifiedImage);


#endif // DETECTION_H
