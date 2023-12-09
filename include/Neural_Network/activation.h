#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "math.h"

#include "Matrix/matrix.h"

double sigmoid(double x);
double sigmoidPrime(double x);
Matrix* softmax(Matrix* matrix);

#endif // ACTIVATION_H