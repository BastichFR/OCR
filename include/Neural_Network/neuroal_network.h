#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>


int activation(double value);

typedef struct Neuron
{
    double value;
    size_t nb_weights;
    double* weights;
    int (*activation)(double value);
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

// Initialise or free a Neuron
Neuron set_neuron(double value, size_t nb_weights, double* weights);
void free_neuron(Neuron neuron);

// Initialise or free a Layer
Layer set_layer(size_t nb_neurons, Neuron* neurons);
void free_layer(Layer layer);

// Initialise or free a Network
Neural_Network set_network(size_t nb_layers, Layer* layers);
void free_network(Neural_Network network);



void softmax();

int feedforward(Neural_Network network, size_t nb_values, double* values);

#endif