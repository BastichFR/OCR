#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <err.h>

typedef struct Matrix {
    size_t rows;
    size_t cols;
    double** data;
} Matrix;

void setValue(Matrix* matrix, size_t row, size_t col, double value);

// ============================================================================

Matrix* addScalar(Matrix* matrix, double scalar);
Matrix* subScalar(double scalar, Matrix* matrix);
Matrix* dotScalar(Matrix* matrix, double scalar);

// ============================================================================

Matrix* addMatrix(Matrix* matrix1, Matrix* matrix2);
Matrix* subMatrix(Matrix* matrix1, Matrix* matrix2);
Matrix* dotMatrix(Matrix* matrix1, Matrix* matrix2);

// ============================================================================

Matrix* multiplyMatrix(Matrix* matrix1, Matrix* matrix2);

// ============================================================================

Matrix* funcMatrix(Matrix* matrix, double (func)(double));

// ============================================================================

Matrix* transposeMatrix(Matrix* matrix);

// ============================================================================

double sumMatrix(Matrix* matrix);

// ============================================================================

Matrix* copyMatrix(Matrix* matrix);

// ============================================================================

Matrix* fillMatrix(Matrix* matrix, double value);

Matrix* flatten(Matrix* matrix);

// ============================================================================

void printMatrix(Matrix* matrix);

// ============================================================================

Matrix* createMatrix(size_t rows, size_t cols);
void freeMatrix(Matrix* matrix);


#endif