#ifndef MATRIX_H
#define MATRIX_H

struct Matrix
{
	int w, h;
	double* values;
};

static inline int mx_index(int x, int y, const struct Matrix* mx)
{
	return (y * mx->w + x);
}

static inline double mx_val(int x, int y, const struct Matrix* mx)
{
	return mx->values[mx_index(x, y, mx)];
}

void mx_build(struct Matrix* dest, int w, int h);
void mx_free(struct Matrix* mx);
void mx_rand(const struct Matrix* dest);
void mx_print(const struct Matrix* mx);
void mx_dotp(double* dest, const double* vector, const struct Matrix* mx);

#endif
