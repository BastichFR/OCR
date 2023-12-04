#ifndef LEARNING_NN_H
#define LEARNING_NN_H

#include "Neural_Network/neuroal_network.h"
#include "Neural_Network/io_nn.h"
#include "Matrix/matrix.h"


void deep_neural_network(Neural_Network* network, Matrix* Input, Matrix* Output, size_t n_iter, double learning_rate) ;

#endif // LEARNING_NN_H