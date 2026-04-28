#include <math.h>
#include "actvfn.h"

double sigmoid(double x)
{
	return 1 / (1 + exp(-x));
}

double d_sigmoid(double x)
{
	double fn_res = sigmoid(x);
	return fn_res * (1 - fn_res);
}

void sigmoid_layer(double* out, double* x, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		out[i] = sigmoid(x[i]);
	}
}

void d_sigmoid_layer(double* out, double* x, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		out[i] = d_sigmoid(x[i]);
	}
}


void softmax_layer(double* out, double* x, size_t size)
{
	double expsum = 0;
	for (int i = 0; i < size; i++)
	{
		expsum += exp(x[i]);
	}

	for (int i = 0; i < size; i++)
	{
		out[i] = exp(x[i]) / expsum;
	}
}

void d_softmax_layer(double* out, double* x, size_t size)
{
	
}
