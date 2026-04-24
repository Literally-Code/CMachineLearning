#ifndef ANN_MODEL_H
#define ANN_MODEL_H

#include <stdbool.h>

// A fully defined, standalone ANN model with an input layer, optional hidden layers, and an output layer
// Can take a vector or flatten a 2D matrix as input
struct ANNModel
{
	int n_layers;				// Number of layers
	int* layer_size;			// Array of each layer size
	struct Matrix** layers;		// (n_layers-1) Weights
	double** activations;		// (n_layers) Activation values of each layer
	double** deltas;				// Deltas for backprop. Become the activation derivative after forwardprop.
	double (*act_fn)(double);	// Activation function
	double (*act_dfn)(double);	// Derivative of activation function
};

bool build_model(int inp_size, int n_layers, int* layerSizes, struct ANNModel* model, double (*act_fn)(double), double (*act_dfn)(double));

bool forward_prop_1D(const double* input, const int input_size, const struct ANNModel* model);

void free_model(struct ANNModel* model);

// A partial ANN model that can be connected with other models (idk maybe not implement this)
struct p_ANNModel
{
	struct ANNModel* parent;
	double* input;
	double* output;
};

#endif
