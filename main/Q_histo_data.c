/***************************************************************************
*
*    File Q_histo_data.c
*
*    For information about this program, see analysis.README
*
***************************************************************************/
#define MAIN_PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "read.h"

void read_file_paths(char ** paths, char *in_path)
{
	char *par1 = "data";
	char *par2 = "out";

	read_string(paths[0], par1, in_path);
	read_string(paths[1], par2, in_path);
}

void read_nc(int *num, char *in_path)
{
	char *par = "nc";

	read_int(num, par, in_path);
}

void read_nwt(int *num, char *in_path)
{
	char *par = "nwt";

	read_int(num, par, in_path);
}

void read_wt(int *num, int dim, char *in_path)
{
	char *par = "wt";

	read_n_int(num, dim, par, in_path);
}

void write_Q(double **Q, t_head h, int *wt, int nwt, int nc, char *out_path)
{
	FILE *out = NULL;

	out = fopen(out_path, "w");
	
	for(int t = 0; t < nwt; ++t)
	{
		printf("Printing Q for wilson time %.2lf\n", wt[t] * h.eps);
		for(int c = 0; c < nc; ++c)
			fprintf(out, "%.10le\n", Q[c][wt[t] / h.dn]);
	}

	fclose(out);
}

int main(int argc, char **argv)
{
	FILE *in_data;
	char **paths = NULL;
	int nc = 0;
	int nwt = 0;
	int *wt = NULL;
	double **Q = NULL;
	t_head head_file;
	
	if(argc < 2)
	{
		printf("Usage: %s in_file\n", argv[0]);
		return 0;
	}

	paths = (char **) malloc(2 * sizeof(char *));
	for(int i = 0; i < 2; ++i)
		paths[i] = (char *) malloc(50 * sizeof(char));

	read_file_paths(paths, argv[1]);

	read_nc(&nc, argv[1]);
	read_nwt(&nwt, argv[1]);
	wt = (int *) malloc(nwt * sizeof(int));
	read_wt(wt, nwt, argv[1]);

	in_data = fopen(paths[0], "r");
	read_head(&head_file, in_data);
	Q = (double **) malloc(nc * sizeof(double *));
	for(int i = 0; i < nc; ++i)
		Q[i] = (double *) malloc(head_file.t_w_max * sizeof(double));
	read_Qcharge(Q, nc, head_file, in_data);
	fclose(in_data);

	write_Q(Q, head_file, wt, nwt, nc, paths[1]);
	
	for(int i = 0; i < 2; ++i)
		free(paths[i]);
	free(paths);
	for(int i = 0; i < nc; ++i)
		free(Q[i]);
	free(Q);
	free(wt);
	
	return 0;
}
