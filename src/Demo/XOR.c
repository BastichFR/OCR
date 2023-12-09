// 00 : 0
// 01 : 1
// 10 : 1
// 11 : 0

#include "Demo/XOR.h"

/// @brief Build a neural network to solve the XOR problem
void build_xor()
{
    char* path = "./src/Demo/XOR.data";
    Neural_Network nn = load_nn(path);

    show_nn(nn);

    Matrix* input = createMatrix(2, 1);
    setValue(input, 0, 0, 0);
    setValue(input, 1, 0, 0);

    int expected = 0;

    deep_neural_network(&nn, input, expected, 10000, 0.1);

    show_nn(nn);

    free_xor(nn);
}

void free_xor(Neural_Network network)
{
    free_network(network);
}