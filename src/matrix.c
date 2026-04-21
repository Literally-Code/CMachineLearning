#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void buildMatrix(struct Matrix* dest, int w, int h)
{
    dest->w = w;
    dest->h = h;
    dest->values = malloc(sizeof(float) * w * h);
}

void freeMatrix(struct Matrix* matrix)
{
    free(matrix->values);
}

void randMatrix(struct Matrix* dest)
{
    for (int i = 0; i < dest->w * dest->h; i++)
    {
        dest->values[i] = (2 * (float)rand() / RAND_MAX - 1);
    }
}

void printMatrix(struct Matrix* matrix)
{
    for (int y = 0; y < matrix->h; y++)
    {
        for (int x = 0; x < matrix->w; x++)
        {
            printf("%f\t", matrix->values[x + matrix->w * y]);
        }
        printf("\n");
    }
}

void dotP(float* dest, float* vector, struct Matrix* matrix)
{
    float sum = 0;
    for (int y = 0; y < matrix->h; y++)
    {
        sum = 0;
        for (int x = 0; x < matrix->w; x++)
        {
            sum += vector[y] * matrix->values[x + matrix->w * y];
        }
        dest[y] = sum;
    }
}

void buildModel(int n_layers, int* layerSizes, struct ANNModel* model)
{
    if (n_layers < 2)
    {
        perror("Error: model must have at least one input and one output layer.\n");
        return;
    }   
}

