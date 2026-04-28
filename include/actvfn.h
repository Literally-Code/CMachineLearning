#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include <stddef.h>

struct LayerActivator
{
	void (*fn)(double*, double*, size_t);
	void (*dfn)(double*, double*, size_t);
};

double sigmoid(double x);
double d_sigmoid(double x);

void sigmoid_layer(double* out, double* x, size_t size);
void d_sigmoid_layer(double* out, double* x, size_t size);

void softmax_layer(double* out, double* x, size_t size);
void d_softmax_layer(double* out, double* x, size_t size);

#endif
