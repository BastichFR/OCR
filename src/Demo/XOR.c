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

    Matrix* Input = createMatrix(2, 4);
    setValue(Input, 0, 0, 0);
    setValue(Input, 1, 0, 0);
    setValue(Input, 0, 1, 0);
    setValue(Input, 1, 1, 1);
    setValue(Input, 0, 2, 1);
    setValue(Input, 1, 2, 0);
    setValue(Input, 0, 3, 1);
    setValue(Input, 1, 3, 1);


    Matrix* Output = createMatrix(1, 4);
    setValue(Output, 0, 0, 0);
    setValue(Output, 0, 1, 1);
    setValue(Output, 0, 2, 1);
    setValue(Output, 0, 3, 0);

    deep_neural_network(&nn, Input, Output, 1000, 0.01);
    

    feedforward(&nn, Input);
    printMatrix(nn.layers[nn.nb_layers - 1].A);

    show_nn(nn);

    save_nn(nn, path);

    Matrix* prediction = predict(&nn, Input);
    printMatrix(prediction);

    freeMatrix(Input);
    freeMatrix(Output);

    free_xor(nn);
}

void free_xor(Neural_Network network)
{
    free_network(network);
}