#include "Neural_Network/activation.h"

// =========================== Activation functions ===========================

// Sigmoid function
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

double sigmoidPrime(double x) {
    return sigmoid(x) * (1 - sigmoid(x));
}

Matrix* softmax(Matrix* matrix) {

    Matrix* expo = funcMatrix(matrix, exp);
    double total = sumMatrix(expo);
    Matrix* mat = dotScalar(expo, 1 / total);

    freeMatrix(expo);

	return mat;
}