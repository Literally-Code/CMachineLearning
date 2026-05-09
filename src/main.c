#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ann.h"
#include "actvfn.h"
#include "metrics.h"

int main(int argc, char** argv)
{
    srand(time(0));
    double input[2] = {0, 1};
	double truth[2] = {0.5, 0.5};
	int layer_sizes[3] = {2, 3, 2};
    struct LayerActivator hidden_activator = {sigmoid_layer, d_sigmoid_layer};
	struct LayerActivator out_activator = {sigmoid_layer, d_sigmoid_layer};

	struct ANNModel* model = (struct ANNModel*)malloc(sizeof(struct ANNModel));

	bool build_success = ann_build(2, 3, (int*)layer_sizes, model, hidden_activator, out_activator);

	if (!build_success)
		exit(1);
	
	printf("---BEFORE---\n");
	ann_print(model);

	ann_forward_prop_1D((double*)input, 3, model);

	printf("---AFTER--- Forward prop finished with no errors\n");

	ann_print(model);

	printf("---SAUCE---\n");

	struct MetricHandler metrics = {
		metric_ssr, 
		metric_ssr_init_delta
	};

	ann_back_prop_1D(&metrics, model, truth, 0.05);

	printf("---RESULT---\n");
	ann_print(model);
}

