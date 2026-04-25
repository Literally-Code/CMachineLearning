#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ann.h"
#include "actvfn.h"

int main(int argc, char** argv)
{
    srand(time(0));
    double input[3] = {0.5, 0.5, 0.5};
	int layer_sizes[3] = {2, 2, 2};
    
	struct ANNModel* model = (struct ANNModel*)malloc(sizeof(struct ANNModel));

	bool build_success = ann_build(3, 3, (int*)layer_sizes, model, sigmoid, d_sigmoid);

	if (!build_success)
		exit(1);
	
	printf("---BEFORE---\n");
	ann_print(model);

	ann_forward_prop_1D((double*)input, 3, model);

	printf("---AFTER--- Forward prop finished with no errors\n");

	ann_print(model);
}

