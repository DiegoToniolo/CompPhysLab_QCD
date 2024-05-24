#define MAIN_PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "read.h"

int main(int argc, char **argv)
{
	FILE *in = NULL;
	int head_int[3], n_conf;
	double eps;
	double *Q_charge = NULL;
	
	if(argc < 2)
	{
		printf("Usage: %s input_test_file\n", argv[0]);
		return 0;
	}

	in = fopen(argv[1], "r");
//	out = fopen(argv[2], "w");

	if(read_head(head_int, &eps, in))
	{
		printf("Head of file not read successfully.\n");
		fclose(in);
		return 0;
	}
	printf("Interval of evolution saved: %d;\n", head_int[0]);
	printf("Total number of steps saved: %d;\n", head_int[1]);
	printf("Time slices: %d\n", head_int[2]);
	printf("Wilson time pace: %0.2le\n", eps);

	Q_charge = (double*) malloc((head_int[1]+1) * sizeof(double));
	
	if(read_Qcharge_conf(Q_charge, &n_conf, head_int[1]+1, head_int[2], in))
	{
		printf("Topological charge of conf %d not read successfully.\n", n_conf);
		free(Q_charge);
		fclose(in);
		return 0;
	}

	printf("Configuration number %d\n", n_conf);
	for(int i = 0; i < head_int[1] + 1; ++i)
		printf("Q charge at t = %d -> %lf\n", head_int[0]*i, Q_charge[i]);

	free(Q_charge);
	fclose(in);

	return 0;	
}
