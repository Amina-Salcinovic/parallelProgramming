#include <stdlib.h>
#include <math.h>
#include "sum_algorithms.h"

double do_sum(double* restrict var, long ncells)
{
   double sum = 0.0;
   for (long i = 0; i < ncells; i++){
      sum += var[i];
   }
   return sum;
}

double long_double_sum(double* restrict var, long ncells) {
    long double sum = 0.0L;
    for (long i = 0; i < ncells; i++) {
        sum += var[i];
    }
    return (double)sum;
}

double pairwise_sum(double* restrict var, long start, long end) {
    if (end - start == 1)
        return var[start];
    if (end - start == 0)
        return 0.0;
    long mid = (start + end) / 2;
    double left = pairwise_sum(var, start, mid);
    double right = pairwise_sum(var, mid, end);
    return left + right;
}

double kahan_sum(double* restrict var, long ncells) {
    double sum = 0.0;
    double c = 0.0; 
    for (long i = 0; i < ncells; i++) {
        double y = var[i] - c;
        double t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

double knuth_sum(double* restrict var, long ncells) {
    double sum = 0.0;
    double err = 0.0;
    for (long i = 0; i < ncells; i++) {
        double temp = sum + var[i];
        if (fabs(sum) >= fabs(var[i]))
            err += (sum - temp) + var[i];
        else
            err += (var[i] - temp) + sum;
        sum = temp;
    }
    return sum + err;
}

