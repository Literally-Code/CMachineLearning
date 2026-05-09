#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ann.h"
#include "matrix.h"

void ann_alloc(struct ANNModel* model, int n_layers)
{
	model->n_layers = n_layers;
	model->layer_size = (int*)malloc(sizeof(int) * n_layers);
	model->activations = (double**)malloc(sizeof(double*) * n_layers);
	model->deltas = (double**)malloc(sizeof(double*) * n_layers);
	model->layers = (struct Matrix**)malloc(sizeof(struct Matrix*) * n_layers);
}

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
	ann_alloc(model, n_layers);

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
		// + 1; The last weight corresponds with the bias
		mx_build(weights, prev_layer_size + 1, curr_layer_size);
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
	double* ps_in = (double*)malloc(sizeof(double) * (input_size + 1));

	for (int i = 0; i < model->n_layers; i++)
	{
		// Allocate more memory to the buffer if the layer is larger than the current buffer
		if (model->layer_size[i] > largest_layer || model->layer_size[i] > input_size) 
		{
			if (buffer != NULL)
			{
				free(buffer);
			}

			if (ps_in != NULL)
			{
				free(ps_in);
			}

			buffer = (double*)malloc(sizeof(double) * model->layer_size[i]);
			ps_in = (double*)malloc(sizeof(double) * (model->layer_size[i] + 1));
			largest_layer = model->layer_size[i];
		}
		
		memcpy(ps_in, prev_activations, sizeof(double) * (model->layers[i]->w - 1));
		// Apply '1' to value of last entry in pseudo-input to account for bias
		ps_in[model->layers[i]->w - 1] = 1;
		mx_dotp(model->activations[i], ps_in, model->layers[i]);

		struct LayerActivator activator = ((i == model->n_layers - 1) ? model->out_activator : model->hidden_activator);
		activator.dfn(buffer, model->activations[i], (size_t)model->layer_size[i]);
		memcpy(model->deltas[i], buffer, sizeof(double) * model->layer_size[i]);

		activator.fn(buffer, model->activations[i], (size_t)model->layer_size[i]);
		memcpy(model->activations[i], buffer, sizeof(double) * model->layer_size[i]);
		prev_activations = model->activations[i];
	}

	if (buffer != NULL && ps_in != NULL)
	{
		free(buffer);
		free(ps_in);
	}

	return true;
}

bool ann_back_prop_1D(struct MetricHandler* metrics, struct ANNModel* model, double* t, double eta)
{
	int n_layers = model->n_layers;
	
	// Propagate backwards
	double delta_sum = 0;
	for (int li = n_layers - 1; li >= 0; li--)
	{
		struct Matrix* weights = model->layers[li];

		if (li == n_layers - 1)
		{
			metrics->init_delta(model, t);
		}
		
		for (int cli = 0; cli < weights->h; cli++)
		{
			// For each ingress weight
			for (int plwi = 0; plwi < weights->w - 1; plwi++)
			{
				int w_index = mx_index(plwi, cli, weights);

				// The magic
				if (li < n_layers - 1)
				{
					model->deltas[li][cli] *= delta_sum;
					delta_sum = 0;
				}

				weights->values[w_index] -= eta * model->activations[li][plwi] * model->deltas[li][cli];
				delta_sum += weights->values[w_index] * model->deltas[li][cli];
			}
		}
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
		printf("-Layer %d\nWeights, Bias\n", i);
		mx_print(model->layers[i]);
		printf("Biases\n");
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
