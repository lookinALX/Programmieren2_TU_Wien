#pragma once

#include <stdbool.h> // bool
#include <math.h>    // fabs
#include <float.h>   // DBL_EPSILON

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

bool compare_releps(double a, double b)
{
  if (a == b) return true;
  double reldiff1 = fabs(a - b) / fabs(a);
  double reldiff2 = fabs(a - b) / fabs(b);
  double reldiffmax = reldiff1 > reldiff2 ? reldiff1 : reldiff2;
  return reldiffmax <= 20 * DBL_EPSILON;
}

bool compare_abseps(double a, double b, double eps)
{
  return fabs(a - b) < eps;
}
