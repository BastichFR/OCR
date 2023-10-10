#include "Neural_Network/io_nn.h"

int get_nb_weights(const char *begin, const char* end){

    if (begin == end - 1)
        return 0;

    int count = 1;
    for (const char* i = begin; i <= end; i++)
        if (*i == ',')
            count += 1;
    
    return count;
}

void parse_neuron_line(const char* line, double* value, double** weights, size_t* nb_weights) {
    const char *begin = strchr(line, '[');
    const char *end   = strchr(line, ']');

    *nb_weights = get_nb_weights(begin, end);    
    *weights = (double*)calloc(*nb_weights, sizeof(double));

    if (weights == NULL) {
        errx(1, "Error while loading neural network: init weights");
    }

    size_t index = 0;
    *value = atof(strtok((char*)begin, "|"));
    char* token = strtok((char*)begin + 1, ",");
    while (token != NULL) {
        (*weights)[index] = atof(token);
        token = strtok(NULL, ",");
        index++;
    }
    
    *value = atof(line);
}


Neural_Network load_nn(char* path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        errx(1, "Error while loading neural network: load file");
    }

    Neural_Network network;
    network.nb_layers = 0;
    network.layers = NULL;

    char* line = NULL;
    size_t len = 0;

    int nb_layers;
    int nb_neurons;

    double value;
    size_t nb_weights;
    double* weights = NULL;

    double threshold = 0;

    getline(&line, &len, file);
    if (sscanf(line, "Threshold %le", &threshold) == 1)
        getline(&line, &len, file);
    if (sscanf(line, "Layer %d", &nb_layers) == 1) {
        network = set_network(nb_layers, NULL);
        network.nb_layers = nb_layers;
        
        for(int id_layer = 0; id_layer < nb_layers; id_layer++){
            getline(&line, &len, file);

            if (sscanf(line, "Neuron %d", &nb_neurons) == 1) {
                Layer this_layer = set_layer(nb_neurons, NULL);

                for (int id_neuron = 0; id_neuron < nb_neurons; id_neuron++) {
                    getline(&line, &len, file);

                    double* weights = NULL;
                    parse_neuron_line(line, &value, &weights, &nb_weights);

                    Neuron neuron = set_neuron(value, nb_weights, weights, threshold); 
                    neuron.activation = activation;  
                    this_layer.neurons[id_neuron] = neuron;              

                    free(weights);
                }
                network.layers[id_layer] = this_layer;
            }
        }
    } 

    fclose(file);
    free(weights);
    free(line);

    return network;
}



void show_nn(Neural_Network nn){
    printf("Threshold %f\n", nn.layers[0].neurons[0].threshold);
    printf("Layer %ld\n", nn.nb_layers);
    for (size_t i = 0; i < nn.nb_layers; i++)
    {
        printf("Neuron %ld\n", nn.layers[i].nb_neurons);
        for (size_t j = 0; j < nn.layers[i].nb_neurons; j++)
        {
            printf("%.2f|[", nn.layers[i].neurons[j].value);
            if (nn.layers[i].neurons[j].nb_weights > 0) {
                for (size_t k = 0; k < nn.layers[i].neurons[j].nb_weights - 1; k++) 
                {
                    printf("%.2f, ", nn.layers[i].neurons[j].weights[k]);
                }
                printf("%.2f", nn.layers[i].neurons[j].weights[nn.layers[i].neurons[j].nb_weights - 1]);
            }
            printf("]\n");
        }
    }
    printf("\n");
}