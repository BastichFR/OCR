#ifndef LEARNING_NN_H
#define LEARNING_NN_H

#include "Neural_Network/neuroal_network.h"
#include "Neural_Network/io_nn.h"
#include "Matrix/matrix.h"


void deep_neural_network(Matrix* X, Matrix* y, Neural_Network* network, double learning_rate, size_t n_iter);

#endif // LEARNING_NN_H