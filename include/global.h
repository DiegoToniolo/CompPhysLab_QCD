
/*******************************************************************************
*
* File global.h
*
* Global parameters and arrays
*
*******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

#define N 64

#if defined MAIN_PROGRAM
  #define EXTERN
#else
  #define EXTERN extern
#endif

EXTERN double xx[N];
typedef struct head
{
	int dn, t_w_max, t_max;
	double eps;
} t_head;

#undef EXTERN

#endif

