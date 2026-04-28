#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "matrix.h"

bool ann_build(
		int inp_size, 
		int n_layers, int* layerSizes, 
		struct ANNModel* model, 
		struct LayerActivator hidden_activator,
		struct LayerActivator out_activator
	)
{
    if (n_layers < 2)
    {
        perror("Error: model must have at least one input and one output layer.\n");
        return false;
    }

	// Allocate memory for the model
	model->n_layers = n_layers;
	model->layer_size = (int*)malloc(sizeof(int) * n_layers);
	model->activations = (double**)malloc(sizeof(double*) * n_layers);
	model->deltas = (double**)malloc(sizeof(double*) * n_layers);
	model->layers = (struct Matrix**)malloc(sizeof(struct Matrix*) * n_layers);

	// Apply the precursor data
	memcpy(model->layer_size, layerSizes, sizeof(int) * n_layers);
	model->hidden_activator = hidden_activator;
	model->out_activator = out_activator;

	// Initialize layers
	int prev_layer_size = inp_size;

	for (int i = 0; i < n_layers; i++)
	{
		// Allocate for activations and deltas for every layer neuron
		model->activations[i] = (double*)malloc(sizeof(double) * model->layer_size[i]);
		model->deltas[i] = (double*)malloc(sizeof(double) * model->layer_size[i]);
		// Initialize random weights for each layer
		int curr_layer_size = model->layer_size[i];
		struct Matrix* weights = (struct Matrix*)malloc(sizeof(struct Matrix));
		mx_build(weights, prev_layer_size, curr_layer_size);
		mx_rand(weights);
		model->layers[i] = weights;
		prev_layer_size = curr_layer_size;
	}
	return true;
}

bool ann_forward_prop_1D(const double* input, const int input_size, const struct ANNModel* model)
{
	if (input_size != model->layers[0]->w)
	{
		perror("Input size does not fit model hyperparameters\n");
		return false;
	}

	double* prev_activations = input;
	int largest_layer = 0;
	double* buffer = NULL;

	for (int i = 0; i < model->n_layers; i++)
	{
		mx_dotp(model->activations[i], prev_activations, model->layers[i]);
		
		// Allocate more memory to the buffer if the layer is larger than the current buffer
		if (model->layer_size[i] > largest_layer) 
		{
			if (buffer != NULL)
			{
				free(buffer);
			}

			buffer = (double*)malloc(sizeof(double) * model->layer_size[i]);
			largest_layer = model->layer_size[i];
		}

		if (i != model->n_layers - 1)
		{
			model->hidden_activator.dfn(buffer, model->activations[i], (size_t)model->layer_size[i]);
			memcpy(model->deltas[i], buffer, sizeof(double) * model->layer_size[i]);

			model->hidden_activator.fn(buffer, model->activations[i], (size_t)model->layer_size[i]);
			memcpy(model->activations[i], buffer, sizeof(double) * model->layer_size[i]);
		}
		else
		{
			model->out_activator.dfn(buffer, model->activations[i], (size_t)model->layer_size[i]);
			memcpy(model->deltas[i], buffer, sizeof(double) * model->layer_size[i]);

			model->out_activator.fn(buffer, model->activations[i], (size_t)model->layer_size[i]);
			memcpy(model->activations[i], buffer, sizeof(double) * model->layer_size[i]);
		}

		prev_activations = model->activations[i];
	}

	return true;
}

void ann_free(struct ANNModel* model)
{
	for (int i = 0; i < model->n_layers; i++)
	{
		free(model->activations[i]);
		free(model->deltas[i]);
		mx_free(model->layers[i]);
	}

	free(model->layers);
	free(model->activations);
	free(model->deltas);
	free(model);
}

void ann_print(const struct ANNModel* model)
{
	printf("---Hyperparameters---\n");
	printf("Number of Layers: %d\n", model->n_layers);
	printf("Layer Sizes\n");
	for (int i = 0; i < model->n_layers; i++)
	{
		printf("%d ", model->layer_size[i]);
	}
	putchar('\n');
	printf("---Model---\n");
	for (int i = 0; i < model->n_layers; i++)
	{
		printf("-Layer %d\nWeights\n", i);
		mx_print(model->layers[i]);
		printf("Activations/Deltas\n");
		for (int j = 0; j < model->layer_size[i]; j++)
		{
			printf("%f ", model->activations[i][j]);
		}
		putchar('\n');
		for (int j = 0; j < model->layer_size[i]; j++)
		{
			printf("%f ", model->deltas[i][j]);
		}
		putchar('\n');
	}
}
