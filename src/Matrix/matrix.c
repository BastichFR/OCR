#include "Matrix/matrix.h"


// =================================================================================================

void setValue(Matrix* matrix, size_t row, size_t col, double value)
{
    if (row >= matrix->rows || col >= matrix->cols)
        {
            errx(1, "Error: Index out of bounds : setValue()\n");
        }
    matrix->data[row][col] = value;
}

// =================================================================================================



Matrix* addScalar(Matrix* matrix, double scalar)
{
    Matrix* result = createMatrix(matrix->rows, matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            result->data[i][j] = matrix->data[i][j] + scalar;
        }
    }

    return result;
}

Matrix* subScalar(double scalar, Matrix* matrix)
{
    Matrix* result = createMatrix(matrix->rows, matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            result->data[i][j] = scalar - matrix->data[i][j];
        }
    }

    return result;
}

Matrix* dotScalar(Matrix* matrix, double scalar) 
{
    Matrix* result = createMatrix(matrix->rows, matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
                result->data[i][j] = matrix->data[i][j] * scalar;
            }
    }

    return result;
}

// =================================================================================================

Matrix* addMatrix(Matrix* matrix1, Matrix* matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
        {
            errx(1, "Error: Matrix dimensions must agree : addMatrix()\n");
        }

    Matrix* result = createMatrix(matrix1->rows, matrix2->cols);

    for (size_t i = 0; i < matrix1->rows; i++)
        {
            for (size_t j = 0; j < matrix1->cols; j++)
                {
                    result->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];
                }
        }

    return result;

}

Matrix* subMatrix(Matrix* matrix1, Matrix* matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        errx(1, "Error: Matrix dimensions must agree : subMatrix()\n");
    }

    Matrix* result = createMatrix(matrix1->rows, matrix2->cols);

    for (size_t i = 0; i < matrix1->rows; i++)
        {
            for (size_t j = 0; j < matrix1->cols; j++)
                {
                    result->data[i][j] = matrix1->data[i][j] - matrix2->data[i][j];
                }
        }

    return result;

}

Matrix* dotMatrix(Matrix* matrix1, Matrix* matrix2)
{
    if (matrix1->cols != matrix2->rows)
        {
            errx(1, "Error: Matrix dimensions must agree : dotMatrix()\n");
        }

    Matrix* result = createMatrix(matrix1->rows, matrix2->cols);

    for (size_t i = 0; i < result->rows; i++)
        {
            for (size_t j = 0; j < result->cols; j++)
                {
                    for (size_t k = 0; k < matrix1->cols; k++)
                        {
                            result->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
                        }
                }
        }

    return result;
}

// =================================================================================================

Matrix* multiplyMatrix(Matrix* matrix1, Matrix* matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
        {
            errx(1, "Error: Matrix dimensions must agree : multiplyMatrix()\n");
        }

    Matrix* result = createMatrix(matrix1->rows, matrix2->cols);

    for (size_t i = 0; i < matrix1->rows; i++)
        {
            for (size_t j = 0; j < matrix1->cols; j++)
                {
                    result->data[i][j] = matrix1->data[i][j] * matrix2->data[i][j];
                }
        }

    return result;
}

// =================================================================================================

Matrix* funcMatrix(Matrix* matrix, double (func)(double))
{
    Matrix* result = createMatrix(matrix->rows, matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++)
        {
            for (size_t j = 0; j < matrix->cols; j++)
                {
                    setValue(result, i, j, func(matrix->data[i][j]));
                }
        }

    return result;
}

// =================================================================================================

Matrix* transposeMatrix(Matrix* matrix)
{
    Matrix* result = createMatrix(matrix->cols, matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++)
        {
            for (size_t j = 0; j < matrix->cols; j++)
                {
                    result->data[j][i] = matrix->data[i][j];
                }
        }

    return result;
}

// =================================================================================================

Matrix* copyMatrix(Matrix* matrix)
{
    Matrix* result = createMatrix(matrix->rows, matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            result->data[i][j] = matrix->data[i][j];
        }
    }
    return result;
}

// =================================================================================================

double sumMatrix(Matrix* matrix)
{
    double sum = 0;

    for (size_t i = 0; i < matrix->rows; i++)
        {
            for (size_t j = 0; j < matrix->cols; j++)
                {
                    sum += matrix->data[i][j];
                }
        }

    return sum;
}

Matrix* fillMatrix(Matrix* matrix, double value)
{
    for (size_t i = 0; i < matrix->rows; i++)
        {
            for (size_t j = 0; j < matrix->cols; j++)
                {
                    matrix->data[i][j] = value;
                }
        }

    return matrix;
}

// =================================================================================================

Matrix* flatten(Matrix* matrix)
{
    Matrix* result = createMatrix(1, matrix->rows * matrix->cols);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            result->data[0][i * matrix->cols + j] = matrix->data[i][j];
        }
    }

    return result;
}

// =================================================================================================

void printMatrix(Matrix* matrix) 
{
    for (size_t i = 0; i < matrix->rows; i++) {
        printf("[");
        for (size_t j = 0; j < matrix->cols; j++) {
            printf("%.2f", matrix->data[i][j]);
            if (j < matrix->cols - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
    printf("\n");
}

// =================================================================================================

Matrix* createMatrix(size_t rows, size_t cols) 
{
    Matrix* matrix = malloc(sizeof(Matrix));

    if (matrix == NULL) {
        errx( 1, "Error: Memory allocation failed : createMatrix(0)\n");
    }

    matrix->rows = rows;
    matrix->cols = cols;
    
    // Allocation de mémoire pour les lignes
    matrix->data = calloc(rows, sizeof(double*));

    if (matrix->data == NULL) {
        errx( 1, "Error: Memory allocation failed : createMatrix(1)\n");
    }
    
    // Allocation de mémoire pour les colonnes
    for (size_t i = 0; i < rows; i++) {
        matrix->data[i] = calloc(cols, sizeof(double));
        if (matrix->data[i] == NULL) {
            errx( 1, "Error: Memory allocation failed : createMatrix(2)\n");
        }
    }
    
    return matrix;
}

void freeMatrix(Matrix* matrix) 
{
    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}
