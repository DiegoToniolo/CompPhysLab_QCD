#define STATISTICS_C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"

double mean(double * data, int n_data)
{
	double sum = 0.0;

	for(int i = 0; i < n_data; ++i)
		sum += data[i];

	return sum / (double)n_data;
}

double exp_val_x2(double *data, int n_data)
{
	double sum = 0.0;

	for(int i = 0; i < n_data; ++i)
	{
		sum += data[i] * data[i];
	}

	return sum / (double)n_data;
}

double autocorr(double *data, int n_data, int t_mark, double average)
{
	double sum = 0.0;

	for(int i = 0; i < n_data - t_mark; ++i)
	{
		sum += data[i] * data[i + t_mark];
	}

	return (sum / (n_data - t_mark)) - (average*average);
}

double jack(double *data, int n_data, int index, double average)
{		
	return average - (data[index] - average)/(n_data - 1);
}

double var_jack(double *data, int n_data, double average)
{
	double sum = 0;

	for(int i = 0; i < n_data; ++i)
		sum += (data[i] - average)*(data[i] - average);

	return sum*(n_data - 1)/n_data;
}

double weighted_mean(double *data, double *err, int n_data)
{
	double sum = 0;
	double sum_w = 0;
	for(int i = 0; i < n_data; ++i)
	{
		sum += data[i]/(err[i]*err[i]);
		sum_w += 1.0/(err[i]*err[i]);
	}

	return sum/sum_w;
}

void fit(double *m, double *q, double *x, double *y, int n)
{
	double sumx = 0, sumy = 0, sumx2 = 0, sumxy = 0, d = 0;
	for(int i = 0; i < n; ++i)
	{
		sumx += x[i];
		sumy += y[i];
		sumx2 += x[i] * x[i];
		sumxy += x[i] * y[i];
	}
	d = n * sumx2 - sumx * sumx;
	*q = (sumy * sumx2 - sumxy * sumx)/d;
	*m = (n * sumxy - sumx * sumy)/d;
}
