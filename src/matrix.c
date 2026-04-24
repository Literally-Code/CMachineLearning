#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

void mx_build(struct Matrix* dest, int w, int h)
{
    dest->w = w;
    dest->h = h;
    dest->values = malloc(sizeof(double) * w * h);
}

void mx_free(struct Matrix* mx)
{
    free(mx->values);
	free(mx);

	mx->values = 0;
	mx = 0;
}

void mx_rand(const struct Matrix* dest)
{
    for (int i = 0; i < dest->w * dest->h; i++)
    {
        dest->values[i] = (2 * (double)rand() / RAND_MAX - 1);
    }
}

void mx_print(const struct Matrix* mx)
{
    for (int y = 0; y < mx->h; y++)
    {
        for (int x = 0; x < mx->w; x++)
        {
            printf("%f\t", mx_val(x, y, mx));
        }
        printf("\n");
    }
}

void mx_dotp(double* dest, const double* vector, const struct Matrix* mx)
{
    double sum = 0;
    for (int y = 0; y < mx->h; y++)
    {
        sum = 0;
        for (int x = 0; x < mx->w; x++)
        {
            sum += vector[x] * mx_val(x, y, mx);
        }
        dest[y] = sum;
    }
}
