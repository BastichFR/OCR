#ifndef PERSPECTIVE_CORRECTION_H
#define PERSPECTIVE_CORRECTION_H

#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Imagery/Detection/square_detection.h"
#include "Imagery/Detection/HoughTransform.h"
#include "Imagery/Tools/image.h"

#define _MAX 9
#define N 9

/**
 * @brief
 *
 * @param vect_A
 * @param vect_B
 * @param cross_P
 */

void crossProduct(double vect_A[], double vect_B[], double cross_P[]);

/**
 * @brief
 *
 * @param source
 * @param dest
 * @param transformation_matrix
 * @param transformation_matrix_inv
 */

void perspectiveMatrix(int src[4][2], double dst[4][2],
                       double **transformation_matrix,
                       double **transformation_matrix_inv);

/**
 * @brief
 *
 * @param image
 * @param selected_square

 * @return Image
 */

Image correctPerspective(Image *image, Square *selected_square,char* path);

/**
 * @brief
 *
 * @param cinMatrix
 * @param coutMatrix
 * @param sizeMatrix
 */

void inverseMat(double cinMatrix[9][9], double coutMatrix[9][9],
                int sizeMatrix);

/**
 * @brief
 *
 * @param mat
 * @param n
 */

void freeMat(double **mat, int n);

/**
 * @brief
 *
 * @param A
 * @param B
 * @param size
 */

void multiplyMat(double **A, double **B, int size);

/**
 * @brief
 *
 * @param M
 * @param M_inv
 */
void inverse3x3Mat(double **M, double **M_inv);

void multiplyMatStat(double M[][_MAX], double v[_MAX], double v_out[_MAX],
                     int size);

/**
 * @brief
 *
 * @param M
 * @param v
 * @param v_out
 * @param size
 */
void multiplyMatBis(double **M, double *v, double *v_out, int size);

/**
 * @brief
 *
 * @param size
 * @return double**
 */
double **allocMat(int size);

void Minor(double minorMatrix[9][9], int colMatrix, int sizeMatrix,
           double newMinorMatrix[9][9]);
           
void Cofactor(double cinMatrix[9][9], double sizeMatrix, double determinte,
              double coutMatrix[9][9], double transposeMatrix[9][9]);

void Transpose(double cofactorMatrix[9][9], double sizeMatrix,
               double determinte, double coutMatrix[9][9],
               double transposeMatrix[9][9]);
               
void multiplyMatStat(double M[][_MAX], double v[_MAX], double v_out[_MAX],
                     int size);
void inverse3x3Mat(double **M, double **M_inv);
double **allocMat(int size);
void multiplyMatBis(double **M, double *v, double *v_out, int size);
void freeMat(double **mat, int n);
#endif
