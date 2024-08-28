/**************************************************************************
*	File observables.c
*
*	Functions for the computation of various correlators of observables.
*
*   The externally accessible functions are:
*
*	  double xl_xk(int delta_times)
*	    Compute the correlation function of the operator x inserted two
*	    times with a time difference delta_times, averaged over the
*       possible position of insertion with that time difference.
*
*	  double x2l_x2k(int delta_times)
*	    Compute the correlation function of the operator x^2 inserted two
*	    times with a time difference delta_times, averaged over the
*       possible position of insertion with that time difference.
*
*	  double top_suc(double Q_charge, double v)
*	    Compute the topological susceptibility given the topological
*	    charge Q_charge and the length of the lattice l.
*
**************************************************************************/
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

double top_suc(double Q_charge, double l)
{
	return Q_charge * Q_charge / (double)(l*l*l*l);
}
