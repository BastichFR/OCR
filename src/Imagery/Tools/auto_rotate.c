#include "Imagery/Tools/auto_rotate.h"

Image image_auto_rotate(Image *image, Image *copy, double maxTheta, LinkedList* lineList)
{
    double angle = maxTheta * 180.0 / M_PI;
    int angleRounded = (int)angle % 90;
    if (!((angleRounded >= 85 && angleRounded <= 95)
        || (angleRounded >= 0 && angleRounded <= 5)))
    {
        rotate(image, angle);

        angle += 5.08;
        const double middleX = ((double)image->width / 2.0);
        const double middleY = ((double)image->height / 2.0);

        double newX;
        double newY;

        Node *node = lineList->head;
        for (; node != NULL; node = node->next)
        {
            Line *l = (Line *)node->value;
            // Calculate new position start
            newX = ((double)(cos(angle) * ((double)l->xStart - middleX)
                    - sin(angle) * ((double)l->yStart - middleY))
                    + middleX);

            newY = ((double)(cos(angle) * ((double)l->yStart - middleY)
                    + sin(angle) * ((double)l->xStart - middleX))
                    + middleY);

            l->xStart = (int)newX;
            l->yStart = (int)newY;

            // Calculate new position end
            newX = ((double)(cos(angle) * ((double)l->xEnd - middleX)
                    - sin(angle) * ((double)l->yEnd - middleY))
                    + middleX);

            newY = ((double)(cos(angle) * ((double)l->yEnd - middleY)
                    + sin(angle) * ((double)l->xEnd - middleX))
                    + middleY);

            l->xEnd = (int)newX;
            l->yEnd = (int)newY;
        }
    }
    return *image;
}
