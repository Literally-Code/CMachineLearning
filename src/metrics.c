#include "metrics.h"
#include "ann.h"

void metric_d_ssr(double* out, double* p, double* t, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		out[i] = (p[i] - t[i]);
	}
}

double metric_ssr(double* out, double* p, double* t, size_t size)
{
	double sum = 0;

	for (size_t i = 0; i < size; i++)
	{
		sum += (out[i] = 0.5 * (p[i] - t[i]) * (p[i] - t[i]));
	}
	
	return sum;
}

void metric_ssr_init_delta(struct ANNModel* model, double* t)
{
	Matrix* out_delta = model->deltas[model->n_layers - 1];
	int out_size = model->layer_size[model->n_layers - 1];

	double* dt_dp = (double*)malloc(sizeof(double) * out_size);
	metric_d_ssr(dt_dp);

	for (int i = 0; i < out_size; i++)
	{
		out_delta[i] = out_delta[i] * dt_dp[i];
	}
}
