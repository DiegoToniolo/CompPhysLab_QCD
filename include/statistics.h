/*********************************************************************
*
* File observables.h
*
* It contains all declaration of the function to do statistical
* analysis.
*
*********************************************************************/
#ifndef STATISTICS_H
#define STATISTICS_H

#ifndef STATISTICS_C
extern double mean(double * data, int n_data);
extern double exp_val_x2(double *data, int n_data);
extern double autocorr(double *data, int n_data, int t_mark, double average);
extern double jack(double *data, int n_data, int index, double average);
extern double var_jack(double *data, int n_data, double average);
extern double weighted_mean(double *data, double *err, int n_data);
extern void fit(double *m, double *q, double *x, double *y, int n);
#endif

#endif
