// 00 : 0
// 01 : 1
// 10 : 1
// 11 : 0

#include "Demo/XOR.h"

/// @brief Build a neural network to solve the XOR problem
void build_xor()
{
    char* path = "./src/Demo/XOR.data";

    printf("Loading neural network from %s\n", path);

    Neural_Network nn = load_nn(path);

    printf("Neural network loaded\n");

    show_nn(nn);

    Matrix* X = createMatrix(2, 1);
    setValue(X, 0, 0, 0);
    setValue(X, 1, 0, 0);
    setValue(X, 0, 0, 0);
    setValue(X, 1, 0, 1);
    setValue(X, 0, 0, 1);
    setValue(X, 1, 0, 0);
    setValue(X, 0, 0, 1);
    setValue(X, 1, 0, 1);

    Matrix* y = createMatrix(1, 1);
    setValue(y, 0, 0, 0);
    setValue(y, 0, 0, 1);
    setValue(y, 0, 0, 1);
    setValue(y, 0, 0, 0);

    deep_neural_network(X, y, &nn, 0.1, 10000);
    
    show_nn(nn);

    free_xor(nn);
}

void free_xor(Neural_Network network)
{
    free_network(network);
}