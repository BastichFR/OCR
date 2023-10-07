#include "Neural_Network/neuroal_network.h"


// Initialize a neuron
Neuron set_neuron(double value, size_t nb_weights, double* weights) {
    Neuron neuron;
    neuron.value = value;
    neuron.nb_weights = nb_weights;

    neuron.weights = (double*)calloc(nb_weights, sizeof(double));
    if (neuron.weights == NULL) {
        errx(1, "Error while initiating Neural Network: Neuron");
    }

    if (weights != NULL)
    {
        for (size_t i = 0; i < nb_weights; i++) {
            neuron.weights[i] = weights[i];
        }
    }

    return neuron;
}

// Initialize a layer
Layer set_layer(size_t nb_neurons, Neuron* neurons) {
    Layer layer;
    layer.nb_neurons = nb_neurons;

    layer.neurons = (Neuron*)calloc(nb_neurons, sizeof(Neuron));
    if (layer.neurons == NULL) {
        errx(1, "Error while initiating Neural Network: Layer");
    }

    if (neurons != NULL)
    {
        for (size_t i = 0; i < nb_neurons; i++) {
            layer.neurons[i] = neurons[i];
        }
    }

    return layer;
}

// Initialize a neural network
Neural_Network set_network(size_t nb_layers, Layer* layers) {
    Neural_Network network;
    network.nb_layers = nb_layers;

    // Allocate memory for the layers_size array and copy the values
    network.layers = (Layer*)calloc(nb_layers, sizeof(Layer));
    if (network.layers == NULL) {
        errx(1, "Error while initiating Neural Network: Network");
    }

    if (layers != NULL)
    {
        for (size_t i = 0; i < nb_layers; i++) {
            network.layers[i] = layers[i];
        }
    }

    return network;
}

// Free memory allocated for a neuron
void free_neuron(Neuron neuron) {
    free(neuron.weights);
}

// Free memory allocated for a layer
void free_layer(Layer layer) {
    for (size_t i = 0; i < layer.nb_neurons; i++) {
        free_neuron(layer.neurons[i]);
    }
    free(layer.neurons);
}

// Free memory allocated for a neural network
void free_network(Neural_Network network) {
    for (size_t i = 0; i < network.nb_layers; i++) {
        free_layer(network.layers[i]);
    }
    free(network.layers);
}

int activation(double value){
    return value ? value >= 0 : 0;
}

int feedforward(Neural_Network network, size_t nb_values, double* values)
{
    if (network.layers[0].nb_neurons != nb_values)
    {
        errx(1, "Wrong inputs feedforward, invalid entries : values");
    }

    // Set inputs
    Layer input = network.layers[0];
    Neuron* in = input.neurons;
    for (size_t i = 0; i < input.nb_neurons; i++)
        in[i].value = values[i];

    // set hidden layers
    for (size_t id_layer = 1; id_layer < network.nb_layers; id_layer++)
    {
        Layer layer = network.layers[id_layer];
        Layer previous_layer = network.layers[id_layer - 1];
        for (size_t id_neuron = 0; id_neuron < layer.nb_neurons; id_neuron++)
        {
            Neuron* neuron = layer.neurons;
            neuron[id_neuron].value = 0; 
            for (size_t id = 0; id < previous_layer.nb_neurons; id++)
            {
                Neuron p = previous_layer.neurons[id];
                double val = p.activation(p.value) * neuron[id_neuron].weights[id];
                neuron[id_neuron].value += val;
            }
        }
    }

    // Set output


    // Get output
    double out_value = 0;
    Layer output = network.layers[network.nb_layers - 1];
    Neuron* out = output.neurons;
    for (size_t i = 0; i < output.nb_neurons; i++){
        out_value += out[i].value;
    }

    return out_value;
}


int activation();

void softmax(); 