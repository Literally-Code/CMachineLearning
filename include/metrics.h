#ifndef ERROR_METRICS_H
#define ERROR_METRICS_H

#include <stddef.h>

struct MetricHandler 
{
	double (*lossfn)(double* p, double* t, size_t size);
	void (*init_delta)(struct ANNModel* model, double* t);
};

void metric_d_ssr(double* out, double* p, double* t, size_t size);
double metric_ssr(double* p, double* t, size_t size);
void metric_ssr_init_delta(struct ANNModel* model, double* t);

#endif
