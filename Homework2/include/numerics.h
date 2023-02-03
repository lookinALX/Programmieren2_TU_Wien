#pragma once

#include "Vector.h"

struct Vector *num_linspace(double start, double stop, size_t n);
struct Vector *num_sample(const struct Vector *x, double (*func)(double));
struct Vector *num_interpolate(const struct Vector *xinterp, const struct Vector *x,
                          const struct Vector *f);
struct Vector *num_grad(const struct Vector *x, const struct Vector *f);
double num_integrate(const struct Vector *x, const struct Vector *f);
