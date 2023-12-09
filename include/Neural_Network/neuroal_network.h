#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <err.h>

#include "Neural_Network/activation.h"
#include "Matrix/matrix.h"

typedef struct Layer
{
    size_t nb_neurons;
    Matrix* W;
    Matrix* B;
    Matrix* Z;
    Matrix* A;

} Layer;

typedef struct Neural_Network
{
    size_t nb_layers;
    Layer* layers;
} Neural_Network;

Layer set_layer(size_t previous_size, size_t size);
void free_layer(Layer layer);

Neural_Network set_network(size_t nb_layers, Layer* layers);
void free_network(Neural_Network network);

void initiate_nn(Neural_Network network);

Matrix* feedforward(Neural_Network* network, Matrix* input);

void backpropagation(Neural_Network* network, Matrix* data, int expected, double learning_rate);

#endif