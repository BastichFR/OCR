#include "Neural_Network/neuroal_network.h"

// ========================================== Initialization ==========================================

// Initialize a layer
Layer set_layer(size_t previous_size, size_t size)
{
    Layer layer;
    layer.nb_neurons = size;

    layer.W = createMatrix(size, previous_size);
    layer.B = createMatrix(size, 1);
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

// =============================================== Free ===============================================

// Free memory allocated for a layer
void free_layer(Layer layer)
{
    freeMatrix(layer.W);
    freeMatrix(layer.B);
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

// ======================================= Activation functions =======================================

// Sigmoid function
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

// Sigmoid derivative function
double sigmoid_derivative(double x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}


// Print layer
void print_layer(Layer layer)
{
    printf("Layer : \n");
    printf("W: \n");
    printMatrix(layer.W);
    printf("B: \n");
    printMatrix(layer.B);
    printf("Z: \n");
    printMatrix(layer.Z);
    printf("A: \n");
    printMatrix(layer.A);
}


// ============================================ Loss function ==========================================

double log_loss(Matrix* y, Matrix* A)
{
    double loss = 0;

    for (size_t i = 0; i < y->cols; i++)
        {
            loss += y->data[0][i] * log(A->data[0][i]) + (1 - y->data[0][i]) * log(1 - A->data[0][i]);
        }

    return -loss / y->cols;
}

// =========================================== Feedforward ============================================

// Feedforward a neural network
void feedforward(Matrix* data, Neural_Network* network)
{
    Layer* layer;

    Matrix* X = data;

    for (size_t c = 0; c < network->nb_layers; c++)
    {
        layer = &(network->layers[c]);

        

        layer->Z = addMatrix(dotMatrix(layer->W, X), layer->B);
        layer->A = funcMatrix(layer->Z, sigmoid);

        X = layer->A;
    }
}


// ========================================= Gradient functions =======================================


Matrix* dW_gradient(Matrix* A, Matrix* X, Matrix* Y)
{
    //assert(X->cols == A->rows && A->cols == Y->cols && X->rows == Y->rows);

    Matrix* t0 = transposeMatrix(X);
    Matrix* t1 = subMatrix(A, Y);


    printf("dW_gradient input dimensions:\n");
    printf("t0: %lu x %lu\n", t0->rows, t0->cols);
    printf("t1: %lu x %lu\n", t1->rows, t1->cols);

    Matrix* dW = dotMatrix(t1, t0);

    freeMatrix(t0);
    freeMatrix(t1);

    return dW;
}


Matrix* dB_gradient(Matrix* A, Matrix* Y)
{
    //assert(A->rows == Y->rows && A->cols == Y->cols);

    return subMatrix(A, Y);
}


// ========================================= Backpropagation ==========================================


void update_parameters(Matrix* dW, Matrix* db, Layer* layer, double learning_rate)
{
    double scaling_factor = dW->cols;

    Matrix* scaled_dW = dotScalar(dW, learning_rate/scaling_factor);
    double scaled_db = -learning_rate/scaling_factor * sumMatrix(db);


    Matrix* updated_W = subMatrix(layer->W, scaled_dW);
    Matrix* updated_B = addScalar(layer->B, scaled_db);

    freeMatrix(scaled_dW);
    freeMatrix(layer->W);
    freeMatrix(layer->B);

    layer->W = updated_W;
    layer->B = updated_B;
}


void backpropagation(Matrix* Y_true, Neural_Network* network, double learning_rate)
{
    size_t C = network->nb_layers;

    Layer* layer = &(network->layers[C - 1]);
    Layer* prev_layer = &(network->layers[C - 2]);
    
    Matrix* dZ = subMatrix(layer->A, Y_true);

    // Rétropropagation à travers les couches
    for (size_t c = C - 1; c > 0; c--)
    {
        layer = &(network->layers[c]);
        prev_layer = &(network->layers[c - 1]);

        Matrix* dW = dW_gradient(prev_layer->A, prev_layer->A, Y_true);
        Matrix* dB = dB_gradient(prev_layer->A, Y_true);

        // Mise à jour des paramètres de la couche
        update_parameters(dW, dB, layer, learning_rate);

        Matrix* dZ_prev = dotMatrix(transposeMatrix(layer->W), dZ);

        freeMatrix(dZ);
        freeMatrix(dW);
        freeMatrix(dB);

        dZ = dZ_prev;
    }

    freeMatrix(dZ);
}