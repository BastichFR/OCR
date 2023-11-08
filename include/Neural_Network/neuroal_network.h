#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

typedef struct Neuron
{
    double bias;
    double value;
    double threshold;
    double* weights;
    size_t nb_weights;
    double (*activation)(struct Neuron neuron);
} Neuron;

typedef struct Layer
{
    size_t nb_neurons;
    Neuron* neurons;
} Layer;

typedef struct Neural_Network
{
    size_t nb_layers;
    Layer* layers;
} Neural_Network;

Neuron set_neuron(double bias, size_t nb_weights, double* weights, double threshold);
Layer set_layer(size_t nb_neurons, Neuron* neurons);
Neural_Network set_network(size_t nb_layers, Layer* layers);

void free_neuron(Neuron neuron);
void free_layer(Layer layer);
void free_network(Neural_Network network);


double activation(Neuron neuron);


int feedforward(Neural_Network network, size_t nb_values, double* values);


void softmax();


#endif