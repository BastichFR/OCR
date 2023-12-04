#include "Neural_Network/learning_nn.h"

// Fonction pour faire tourner le réseau de neurones (pour l'apprentissage)
void deep_neural_network(Neural_Network* network, Matrix* Input, Matrix* Output, size_t n_iter, double learning_rate) 
{
    for (size_t i = 0; i < n_iter; i++)
    {
        feedforward(network, Input);
        backpropagation(network, Input, Output, learning_rate);
    }
}
