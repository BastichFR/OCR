#include "Imagery/Detection/detection.h"

/// @brief an image
/// @param image The image to black and white

Image detection(Image *image, Image *copy, Image *_simplifiedImage)
{
    const unsigned int w = image->width;
    const unsigned int h = image->height;
    
    //Image tempImage = copy_image(copy);

    double maxTheta;
    
    LinkedList list = houghtransform(image, copy,
                                     &maxTheta);
                                     
    LinkedList *resultingList = simplifyLines(&list);

    Pixel color = { .red = 0, .green = 255, .blue = 0 };
    Node *node = resultingList->head;
    for (; node != NULL; node = node->next)
    {
        Line *line = (Line *)node->value;
        draw_line(_simplifiedImage, w, h, line, &color, 2, 1);
    }
    
    image_auto_rotate(image, copy, maxTheta, &list);
    Image _squareImage = copy_image(image);
    LinkedList squares = findSquare(resultingList, w, h, &_squareImage);
    Square lastSquare = sortSquares(&squares, image);
    drawSquare(&lastSquare, &_squareImage, w, h, 2);
    free_list(&squares);
    free_list(resultingList);
    Image img = correctPerspective(&_squareImage, &lastSquare,image->path);
    return img;
}

