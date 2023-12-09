#include "Neural_Network/io_nn.h"

// ============================== Load ==============================

Neural_Network load_nn(char* path) {
    
    FILE* file = fopen(path, "r");

    if (file == NULL) {
        errx(1, "Error while loading neural network: load file");
    }

    Neural_Network network;

    size_t previous_size = 0;
    size_t len = 0;

    char* line = NULL;
    
    getline(&line, &len, file);
    if (sscanf(line, "dataIn %ld", &previous_size) == 1) {
        getline(&line, &len, file);
    }


    if (sscanf(line, "Layer %ld", &network.nb_layers) == 1) {

        network = set_network(network.nb_layers + 1, NULL);
        Layer input_layer = set_layer(previous_size, 1);
        network.layers[0] = input_layer;

        getline(&line, &len, file);
    }

    for (size_t i = 1; i < network.nb_layers; i++) {

        size_t size = 0;
        if (sscanf(line, "Neuron %ld", &size) == 1) {

            Layer layer = set_layer(previous_size, size);
            
            for (size_t index = 0; index < layer.W->rows; index++) {
                getline(&line, &len, file);

                char* token = strtok(line + 1, ", ");
                for (size_t j = 0; token != NULL && j < layer.W->cols; j++) {
                    setValue(layer.W, index, j, atof(token));
                    token = strtok(NULL, ", ");
                }
            }

            previous_size = size;
            network.layers[i] = layer;
        }
        
        getline(&line, &len, file);
    }

    fclose(file);
    return network;
}


// ============================== Save ==============================

void save_nn(Neural_Network nn, char* path)
{
    FILE* file = fopen(path, "w");

    if (file == NULL) {
        errx(1, "Error while saving neural network: save file");
    }

    fprintf(file, "dataIn %ld\n", nn.layers[0].W->rows);
    fprintf(file, "Layer %ld\n", nn.nb_layers - 1);
    for (size_t i = 1; i < nn.nb_layers; i++) {

        Layer layer = nn.layers[i];
        size_t nb_neurons = nn.layers[i].W->cols;
        fprintf(file, "Neuron %ld\n", nb_neurons);

        for (size_t row = 0; row < layer.W->rows; row++) {
            fprintf(file, "[");
            for (size_t col = 0; col < layer.W->cols; col++)
            {
                fprintf(file, "%.2f", layer.W->data[row][col]);
                if (col < layer.W->cols - 1)
                    fprintf(file, ", ");
            }
            fprintf(file, "]\n");
        }
    }

    fclose(file);
}

// ============================== Show ==============================

void show_nn(Neural_Network nn)
{
    printf("dataIn %ld\n", nn.layers[0].W->rows);
    printf("Layer %ld\n", nn.nb_layers - 1);
    for (size_t i = 1; i < nn.nb_layers; i++) {

        Layer layer = nn.layers[i];
        size_t nb_neurons = nn.layers[i].W->cols;
        printf("Neuron %ld\n", nb_neurons);

        for (size_t row = 0; row < layer.W->rows; row++) {
            printf("[");
            for (size_t col = 0; col < layer.W->cols; col++)
            {
                printf("%.2f", layer.W->data[row][col]);
                if (col < layer.W->cols - 1)
                    printf(", ");
            }
            printf("]\n");
        }
    }
    printf("\n");
}
