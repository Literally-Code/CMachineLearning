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
