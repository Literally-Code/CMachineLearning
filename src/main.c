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

	bool build_success = build_model(3, 3, &layer_sizes, model, sigmoid, d_sigmoid);

	if (!build_success)
		exit(1);
	
	forward_prop_1D(&input, 3, &model);

	printf("Forward prop finished with no errors\n");
}

