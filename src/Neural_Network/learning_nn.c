#include "Neural_Network/learning_nn.h"

// Fonction pour faire tourner le réseau de neurones (pour l'apprentissage)
void deep_neural_network(Matrix* X, Matrix* y, Neural_Network* network, double learning_rate, size_t n_iter) 
{
    for (size_t i = 0; i < n_iter; i++)
    {
        feedforward(X, network);
        backpropagation(y, network, learning_rate);

        double loss = log_loss(y, network->layers[network->nb_layers - 1].A);
        printf("Iteration %zu, Loss: %f\n", i, loss);
    }
}
