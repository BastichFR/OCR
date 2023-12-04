#include "Neural_Network/io_nn.h"

// ============================== Load ==============================

void parse_neuron_line(const char* line, Layer* layer, const size_t index)
{
    const char* begin = strchr(line, '[');
    const char* end = strchr(line, ']');

    char* token = strtok((char*)begin + 1, ",");
    for (size_t i = 0;token != NULL && token != end; i++)
    {

        setValue(layer->W, index, i, atof(token));
        token = strtok(NULL, ",");

    }
}

Neural_Network load_nn(char* path)
{
    FILE* file = fopen(path, "r");

    if (file == NULL) {
        errx(1, "Error while loading neural network: load file");
    }

    char* line = NULL;
    size_t len = 0;

    Neural_Network network;
    size_t previous_size;

    // Get threshold & input size
    getline(&line, &len, file);
    if (sscanf(line, "dataIn %ld", &previous_size) == 1){
        getline(&line, &len, file);
    }

    // Get number of layers
    if (sscanf(line, "Layer %ld", &network.nb_layers) == 1)
        network = set_network(network.nb_layers, NULL);

    // For each layer
    for (size_t id_layer = 0; id_layer < network.nb_layers; id_layer++)
    {
        // Get number of neurons
        int size;
        getline(&line, &len, file);
        if (sscanf(line, "Neuron %d", &size) == 1)
        {
            // For each neuron
            Layer layer = set_layer(previous_size, size);
            for (int index = 0; index < size; index++)
            {
                getline(&line, &len, file);
                parse_neuron_line(line, &layer, index);
            }
            network.layers[id_layer] = layer;
        }
    }

    fclose(file);
    free(line);

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
    fprintf(file, "Layer %ld\n", nn.nb_layers);
    for (size_t i = 0; i < nn.nb_layers; i++) {

        Layer layer = nn.layers[i];
        size_t nb_neurons = nn.layers[i].W->cols;
        fprintf(file, "Neuron %ld\n", nb_neurons);
        for (size_t j = 0; j < nb_neurons; j++) {

            fprintf(file, "[");
            for (size_t k = 0; k < layer.W->rows; k++) {

                fprintf(file, "%.2f", layer.W->data[k][j]);
                if (k < nn.layers[i].W->rows - 1)
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
    printf("Layer %ld\n", nn.nb_layers);
    for (size_t i = 0; i < nn.nb_layers; i++) {

        Layer layer = nn.layers[i];
        size_t nb_neurons = nn.layers[i].W->cols;
        printf("Neuron %ld\n", nb_neurons);
        for (size_t j = 0; j < nb_neurons; j++) {

            printf("[");
            for (size_t k = 0; k < layer.W->rows; k++) {

                printf("%.2f", layer.W->data[k][j]);
                if (k < nn.layers[i].W->rows - 1)
                    printf(", ");
            }

            printf("]\n");
        }

    }
    
    printf("\n");
}
