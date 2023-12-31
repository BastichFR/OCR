#ifndef SQUARE_DETECTION_H
#define SQUARE_DETECTION_H

#include <math.h>

#include "Imagery/Detection/HoughTransform.h"

/**
 * @brief
 *
 * @param linelist
 * @return MyList
 */
LinkedList *simplifyLines(LinkedList *linelist);

/**
 * @brief Get the Square object
 *
 * @param lineList
 * @param line
 * @param index
 * @return Square
 */
Square getSquare(LinkedList *lineList, Line *line, int index);

/**
 * @brief Get the Intersection object
 *
 * @param line1
 * @param line2
 * @param width
 * @param height
 * @return Dot
 */
Dot getIntersection(Line *line1, Line *line2, int width, int height);

/**
 * @brief
 *
 * @param lineList
 * @param width
 * @param height
 * @param image
 * @param draw
 * @return LinkedList
 */
LinkedList findSquare(LinkedList *lineList, int width, int height, Image *image);

/**
 * @brief Get the All Square object
 *
 * @param lineList
 * @param width
 * @param height
 * @param image
 * @return LinkedList
 */
LinkedList *getAllSquare(LinkedList *lineList, int width, int height, Image *image);

/**
 * @brief
 *
 * @param square
 * @param width
 * @param height
 * @return int
 */
int isSquare(Square *square, unsigned int width, unsigned int height,
             double SQUARE_FACTOR);

/**
 * @brief Get the Line Length object
 *
 * @param line
 * @return double
 */
double getLineLength(Line *line);

/**
 * @brief
 *
 * @param squareList
 * @param image
 * @return Square
 */
Square sortSquares(LinkedList *squareList, Image *image);

/**
 * @brief
 *
 * @param square
 * @param image
 * @return int
 */
int canBeSudokuGrid(Square *square, Image *image);

/**
 * @brief
 *
 * @param square
 * @param image
 * @param width
 * @param height
 * @param thickness
 */
void drawSquare(Square *square, Image *image, int width, int height,
                int thickness);

double getSquareFactor(Image *image);

/**
 * @brief Get the Better Corner object
 *
 * @param square
 * @return Dot
 */
Dot getBetterCorner(Square *square);

/**
 * @brief
 *
 * @param square
 */
void compute_Square(Square *square);

/**
 * @brief Get the Perimeter object
 *
 * @param square
 * @return double
 */
double getPerimeter(Square *square);

double getFactor(Square *square);

#endif
