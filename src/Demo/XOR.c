// 00 : 0
// 01 : 1
// 10 : 1
// 11 : 0

#include "Demo/XOR.h"
    
void build_xor(){
    char* path = "./src/Demo/XOR.data";
    Neural_Network nn = load_nn(path);
    
    show_nn(nn);
    
    double out = 0;

    size_t len = 2;
    double* values = (double*)calloc(len, sizeof(double));
    values[0] = 0;
    values[1] = 0;
    
    out = feedforward(nn, 2, values);
    printf("out XOR(%.2f, %.2f) = %.2f \n", values[0], values[1], out);

    values[0] = 0;
    values[1] = 1;

    out = feedforward(nn, 2, values);
    printf("out XOR(%.2f, %.2f) = %.2f \n", values[0], values[1], out);

    values[0] = 1;
    values[1] = 0;

    out = feedforward(nn, 2, values);
    printf("out XOR(%.2f, %.2f) = %.2f \n", values[0], values[1], out);

    values[0] = 1;
    values[1] = 1;

    out = feedforward(nn, 2, values);
    printf("out XOR(%.2f, %.2f) = %.2f \n", values[0], values[1], out);

    free(values);
    free_xor(nn);
}

void free_xor(Neural_Network network){
    free_network(network);
}