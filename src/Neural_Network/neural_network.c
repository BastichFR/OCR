#include "Neural_Network/neuroal_network.h"

// ============================== Initialization ==============================

// Initialize a layer
Layer set_layer(size_t previous_size, size_t size)
{
    Layer layer;
    layer.nb_neurons = size;

    layer.W = createMatrix(size, previous_size);
    layer.Z = createMatrix(size, 1);
    layer.A = createMatrix(size, 1);

    return layer;
}

// Initialize a neural network
Neural_Network set_network(size_t nb_layers, Layer* layers)
{
    Neural_Network network;
    network.nb_layers = nb_layers;

    // Allocate memory for the layers_size array and copy the values
    network.layers = (Layer*)calloc(nb_layers, sizeof(Layer));
    if (network.layers == NULL)
        {
            errx(1, "Error while initiating Neural Network: Network");
        }

    if (layers != NULL)
        {
            for (size_t i = 0; i < nb_layers; i++)
                {
                    network.layers[i] = layers[i];
                }
        }

    return network;
}

// =================================== Free ===================================

// Free memory allocated for a layer
void free_layer(Layer layer)
{
    freeMatrix(layer.W);
    freeMatrix(layer.Z);
    freeMatrix(layer.A);
}

// Free memory allocated for a neural network
void free_network(Neural_Network network)
{
    for (size_t i = 0; i < network.nb_layers; i++)
        {
            free_layer(network.layers[i]);
        }
    free(network.layers);
}

// =================================== Print ==================================

// Print layer
void print_layer(Layer layer)
{
    printf("Layer : \n");
    printf("W: \n");
    printMatrix(layer.W);
    printf("Z: \n");
    printMatrix(layer.Z);
    printf("A: \n");
    printMatrix(layer.A);
}

// =================================== Init ===================================

// Initialize a neural network (random values)
void initiate_nn(Neural_Network network){

    for (size_t i = 1; i < network.nb_layers; i++)
    {
        Layer layer = network.layers[i];
        for (size_t row = 0; row < layer.W->rows; row++)
        {
            for (size_t col = 0; col < layer.W->cols; col++)
            {
                layer.W->data[row][col] = rand() % 100 / 100.0;
            }
        }
    }
}

// ================================ Feedforward ===============================

// Feedforward a neural network
Matrix* feedforward(Neural_Network* network, Matrix* input)
{
    Layer* layer = &(network->layers[0]);
    Matrix* X = input;

    for (size_t c = 1; c < network->nb_layers; c++)
    {
        layer = &(network->layers[c]);

        freeMatrix(layer->Z);
        layer->Z = dotMatrix(layer->W, X);
        freeMatrix(layer->A);
        layer->A = funcMatrix(layer->Z, sigmoid);

        X = layer->A;
    }

    return X;
}

// ============================== Backpropagation =============================

void update(Layer layer, Matrix* dW, double learning_rate){
    Matrix* s1 = dotScalar(dW, learning_rate);

    printf("s1: \n");
    printMatrix(s1);

    printf("layer.W: \n");
    printMatrix(layer.W);

    layer.W = subMatrix(layer.W, s1); 
    freeMatrix(s1);
}

void backpropagation(Neural_Network* network, Matrix* data, int expected, double learning_rate)
{
    feedforward(network, data);

    for (size_t i = network->nb_layers - 1; i > 0; i--)
    {
        // X.T
        Matrix* d1 = transposeMatrix(network->layers[i - 1].A);

        // (A - Y)
        Matrix* d2 = addScalar(network->layers[i].A, -expected);
        
        // X.T * (A - Y) 
        Matrix* dW = dotMatrix(d1, d2);

        update(network->layers[i], dW, learning_rate);

        freeMatrix(d1);
        freeMatrix(d2);
        freeMatrix(dW);
    }
}

