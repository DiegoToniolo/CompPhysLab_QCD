#define OBSERVABLES_C

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

double xl_xk(int delta_times)
{
	double sum = 0.0;

	for(int i = 0; i < N; ++i)
	{	
		sum += xx[i%N] * xx[(i+ delta_times)%N];
	}
	return sum/N;
}

double x2l_x2k(int delta_times)
{
	double sum = 0;

	for(int i = 0; i < N; ++i)
	{
		sum += xx[i%N] * xx[i%N] * xx[(i+ delta_times)%N] * xx[(i+ delta_times)%N];
	}
	return sum/(double)N;
}

double xl_xk_not_imp(int l, int k)
{
	return xx[l]*xx[k];
}

double x2l_x2k_not_imp(int l, int k)
{
	return xx[l]*xx[l]*xx[k]*xx[k];
}

double top_suc(double Q_charge, double v)
{
	return Q_charge * Q_charge / (double)(v*v*v*v);
}
