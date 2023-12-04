#include "Neural_Network/neuroal_network.h"

// ============================== Initialization ==============================

// Initialize a layer
Layer set_layer(size_t previous_size, size_t size)
{
    Layer layer;
    layer.nb_neurons = size;

    layer.W = createMatrix(size, previous_size);
    layer.Z = createMatrix(size, 1);
    layer.A = createMatrix(size, 1);

    return layer;
}

// Initialize a neural network
Neural_Network set_network(size_t nb_layers, Layer* layers)
{
    Neural_Network network;
    network.nb_layers = nb_layers;

    // Allocate memory for the layers_size array and copy the values
    network.layers = (Layer*)calloc(nb_layers, sizeof(Layer));
    if (network.layers == NULL)
        {
            errx(1, "Error while initiating Neural Network: Network");
        }

    if (layers != NULL)
        {
            for (size_t i = 0; i < nb_layers; i++)
                {
                    network.layers[i] = layers[i];
                }
        }

    return network;
}

// =================================== Free ===================================

// Free memory allocated for a layer
void free_layer(Layer layer)
{
    freeMatrix(layer.W);
    freeMatrix(layer.Z);
    freeMatrix(layer.A);
}

// Free memory allocated for a neural network
void free_network(Neural_Network network)
{
    for (size_t i = 0; i < network.nb_layers; i++)
        {
            free_layer(network.layers[i]);
        }
    free(network.layers);
}

// =========================== Activation functions ===========================

// Sigmoid function
double sigmoid(double x)
{
    return 1 / (1 + exp(-x));
}

Matrix* sigmoidPrime(Matrix* matrix) {
	Matrix* ones = createMatrix(matrix->rows, matrix->cols);
	fillMatrix(ones, 1);

	Matrix* subtracted = subMatrix(ones, matrix);
	Matrix* multiplied = multiplyMatrix(matrix, subtracted);

	freeMatrix(ones);
	freeMatrix(subtracted);

	return multiplied;
}

Matrix* softmax(Matrix* matrix) {

    Matrix* expo = funcMatrix(matrix, exp);
    double total = sumMatrix(expo);
    Matrix* mat = dotScalar(expo, 1 / total);

    freeMatrix(expo);

	return mat;
}

// =================================== Print ==================================

// Print layer
void print_layer(Layer layer)
{
    printf("Layer : \n");
    printf("W: \n");
    printMatrix(layer.W);
    printf("Z: \n");
    printMatrix(layer.Z);
    printf("A: \n");
    printMatrix(layer.A);
}

// ================================== Predict =================================

Matrix* predict(Neural_Network* network, Matrix* input)
{
    feedforward(network, input);

    Layer* layer = &(network->layers[network->nb_layers - 1]);
    Matrix* prediction = copyMatrix(layer->Z);
    Matrix* result = softmax(prediction);

    freeMatrix(prediction);

    return result;
}

// ================================ Feedforward ===============================

// Feedforward a neural network
void feedforward(Neural_Network* network, Matrix* input)
{
    Layer* layer = &(network->layers[0]);
    Matrix* X = input;

    for (size_t c = 0; c < network->nb_layers; c++)
    {
        layer = &(network->layers[c]);

        freeMatrix(layer->Z);
        layer->Z = dotMatrix(layer->W, X);
        freeMatrix(layer->A);
        layer->A = funcMatrix(layer->Z, sigmoid);

        X = layer->A;
    }
}

// ============================== Backpropagation =============================

void backpropagation(Neural_Network* network, Matrix* input, Matrix* output, double learning_rate)
{
    Layer* final;           // output layer
    Layer* previous_layer;  // hidden layer

    for(size_t i = network->nb_layers - 1; i >= 1 ; i--)
    {
        final = &(network->layers[i]);
        previous_layer = &(network->layers[i - 1]);

        Matrix* hidden_inputs  = copyMatrix(previous_layer->Z);
        Matrix* hidden_outputs = copyMatrix(previous_layer->A);
        Matrix* final_inputs   = copyMatrix(final->Z);
        Matrix* final_outputs  = copyMatrix(final->A);

        // Find errors
        Matrix* output_errors = subMatrix(output, final_outputs);
        Matrix* transposed_mat = transposeMatrix(final->W);
        Matrix* hidden_errors = dotMatrix(transposed_mat, output_errors);
        freeMatrix(transposed_mat);


        // Backpropogate
        // output_weights = add(
        //		 output_weights, 
        //     scale(
        // 			  net->lr, 
        //			  dot(
        // 		 			multiply(
        // 						output_errors, 
        //				  	sigmoidPrime(final_outputs)
        //					), 
        //					transpose(hidden_outputs)
        // 				)
        //		 )
        // )
        Matrix* sigmoid_primed_mat = sigmoidPrime(final_inputs);
        Matrix* multiplied_mat = multiplyMatrix(output_errors, sigmoid_primed_mat);
        transposed_mat = transposeMatrix(hidden_outputs);
        Matrix* dot_mat = dotMatrix(multiplied_mat, transposed_mat);
        Matrix* scaled_mat = dotScalar(dot_mat, learning_rate);
        Matrix* added_mat = addMatrix(final->W, scaled_mat);

        freeMatrix(final->W);
        final->W = added_mat;

        freeMatrix(sigmoid_primed_mat);
        freeMatrix(multiplied_mat);
        freeMatrix(transposed_mat);
        freeMatrix(dot_mat);
        freeMatrix(scaled_mat);

    	// hidden_weights = add(
        // 	 net->hidden_weights,
        // 	 scale (
        //			net->learning_rate
        //    	dot (
        //				multiply(
        //					hidden_errors,
        //					sigmoidPrime(hidden_outputs)	
        //				)
        //				transpose(inputs)
        //      )
        // 	 )
        // )
        // Reusing variables after freeing memory
        sigmoid_primed_mat = sigmoidPrime(hidden_inputs);
        multiplied_mat = multiplyMatrix(hidden_errors, sigmoid_primed_mat);
        transposed_mat = transposeMatrix(input);
        dot_mat = dotMatrix(multiplied_mat, transposed_mat);
        scaled_mat = dotScalar(dot_mat, learning_rate);
        added_mat = addMatrix(previous_layer->W, scaled_mat);
        freeMatrix(previous_layer->W);
        previous_layer->W = added_mat;

        freeMatrix(sigmoid_primed_mat);
        freeMatrix(multiplied_mat);
        freeMatrix(transposed_mat);
        freeMatrix(dot_mat);
        freeMatrix(scaled_mat);

        freeMatrix(hidden_inputs);
        freeMatrix(hidden_outputs);
        freeMatrix(final_inputs);
        freeMatrix(final_outputs);
        freeMatrix(output_errors);
        freeMatrix(hidden_errors);

        output = previous_layer->A;
    }
}
