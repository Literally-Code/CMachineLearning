struct Matrix
{
	int w, h;
	float* values;
};

struct ANNModel
{
	int n_layers;
	int* layer_size;
	struct Matrix* layers;
	float* activations;
	float* gradient;
};

void buildMatrix(struct Matrix* dest, int w, int h);
void freeMatrix(struct Matrix* matrix);
void randMatrix(struct Matrix* dest);
void printMatrix(struct Matrix* matrix);
void dotP(float* dest, float* vector, struct Matrix* matrix);

