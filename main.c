#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include "matrix.h"

int main(int argc, char** argv)
{
    srand(time(0));
    float vector[2] = {0.5, 0.5};
    float dest[2];
    struct Matrix newMatrix;
    buildMatrix(&newMatrix, 2, 2);
    randMatrix(&newMatrix);
    printMatrix(&newMatrix);
    dotP(dest, vector, &newMatrix);
    printf("%f %f\n", dest[0], dest[1]);
}

