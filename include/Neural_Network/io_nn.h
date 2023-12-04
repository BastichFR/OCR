#ifndef IO_NN_H
#define IO_NN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "Matrix/matrix.h"
#include "Neural_Network/neuroal_network.h"

Neural_Network load_nn(char* path);

void save_nn(Neural_Network nn, char* path);

void show_nn(Neural_Network nn);

#endif