
#ifndef SUM_ALGORITHMS_H
#define SUM_ALGORITHMS_H

/*
 * Standard double precision sum
 */
double do_sum(double* restrict var, long ncells);
double long_double_sum(double* restrict var, long ncells);
double pairwise_sum(double* restrict var, long start, long end);
double kahan_sum(double* restrict var, long ncells);
double knuth_sum(double* restrict var, long ncells);


#endif //SUM_ALGORITHMS_H