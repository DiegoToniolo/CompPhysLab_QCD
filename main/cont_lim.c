#define MAIN_PROGRAM

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "global.h"
#include "read.h"
#include "observables.h"
#include "statistics.h"

void read_np_nc(int *n1, int *n2, char *in_path)
{
	char *par1 = "np";
	char *par2 = "nc";

	read_int(n1, par1, in_path);
	read_int(n2, par2, in_path);
}

void read_paths(char **paths, int ns, char *in_path)
{
	char *par1 = "input";
	char *par2 = "output";

	read_n_string(paths, ns, par1, in_path);
	read_string(paths[ns], par2, in_path);
}

void read_ts(double *t0_ass, double *t0, double *v, int np, int n_t0, char *in_path)
{
	char *par1 = "t0/a2";
	char *par2 = "L";
	char *par3 = "t0_ts";

	read_n_double(t0, np, par1, in_path);
	read_n_double(v, np, par2, in_path);
	read_n_double(t0_ass, n_t0, par3, in_path);
}

void read_nt0(int *n_t0, char *in_path)
{
	char *par = "n_t0";
	read_int(n_t0, par, in_path);
}

void compute_x_fit(double *x, int *x_index, t_head h, double t0_a2)
{
	for(int t = 0; t < h.t_w_max; ++t)
	{
		if(t * h.dn * h.eps > t0_a2)
		{
			for(int i = 0; i < 4; ++i)
			{
				x[i] = (t + i - 2) * h.dn * h.eps;
				x_index[i] = t + i -2;
			}
			break;
		}
	}
}

int main(int argc, char **argv)
{
	FILE *in = NULL, *out, *prova;
	int np = 0, nc = 0, n_t0 = 0;
	char **paths = NULL;
	double *L = NULL;
	double *t0_a2 = NULL, *t0_ts = NULL;
	double **ts = NULL, *mean_ts = NULL, *r_jack = NULL;
	double **Q = NULL, **ts_jack = NULL;
	double y[4], x[4], m, q, act_t0 = 0;
	int x_index[4];
	t_head h;
	
	if(argc < 2)
	{
		printf("Usage: %s in_file\n", argv[0]);
		return 0;
	}
	
	read_np_nc(&np, &nc, argv[1]);
	paths = (char **) malloc((np + 1) * sizeof(char *));
	L = (double *) malloc(np * sizeof(double));
	t0_a2 = (double *) malloc(np * sizeof(double));
	for(int i = 0; i < np + 1; ++i)
		paths[i] = (char *) malloc(50 * sizeof(char));
	read_paths(paths, np, argv[1]);
	read_nt0(&n_t0, argv[1]);
	t0_ts = (double *) malloc(n_t0 * sizeof(double));
	read_ts(t0_ts, t0_a2, L, np, n_t0, argv[1]);

	Q = (double **) malloc(nc * sizeof(double *));
	ts = (double **) malloc((n_t0 + 1) * sizeof(double));
	r_jack = (double *) malloc(nc * sizeof(double));
	ts_jack = (double **) malloc((n_t0 + 1) * sizeof(double *));
	mean_ts = (double *) malloc((n_t0 + 1) * sizeof(double *));
	for(int i = 0; i < n_t0 + 1; ++i)
	{
		ts_jack[i] = (double *) malloc(nc * sizeof(double));
		ts[i] = (double *) malloc(nc * sizeof(double));
	}
	out = fopen(paths[np], "w");
	prova = fopen("prova.txt", "w");
	for(int p = 0; p < np; ++p)
	{
		in = fopen(paths[p], "r");
		read_head(&h, in);
		for(int i = 0; i < nc; ++i)
			Q[i] = (double *) malloc(h.t_w_max * sizeof(double));
		read_Qcharge(Q, nc, h, in);

		for(int tw = 0; tw < n_t0 + 1; ++tw)
		{
			if (tw == 0)
				act_t0 = 1.00;
			else
				act_t0 = t0_ts[tw-1];
			compute_x_fit(x, x_index, h, act_t0 * t0_a2[p]);
			for(int c = 0; c < nc; ++c)
			{
				for(int i = 0; i < 4; ++i)
					y[i] = Q[c][x_index[i]];
				fit(&m, &q, x, y, 4);
				ts[tw][c] = t0_a2[p] * t0_a2[p] * top_suc(q + m* act_t0 * t0_a2[p], L[p]);
			}
			mean_ts[tw] = mean(ts[tw], nc);
			for(int c = 0; c < nc; ++c)
				ts_jack[tw][c] = jack(ts[tw], nc, c, mean_ts[tw]);
		}

		fprintf(out, "%le %le %le\n", 1/t0_a2[p], mean_ts[0], sqrt(var_jack(ts_jack[0], nc, mean_ts[0])));

		for(int tw = 1; tw < n_t0 + 1; ++tw)
		{
			for(int c = 0; c < nc; ++c)
			{
				r_jack[c] = ts_jack[tw][c]/ts_jack[0][c];
			}
			fprintf(out, "%le %le %le\n", 1/t0_a2[p], mean_ts[tw]/mean_ts[0], sqrt(var_jack(r_jack, nc, mean_ts[tw]/mean_ts[0])));
		}
		
		for(int i = 0; i < nc; ++i)
			free(Q[i]);
		fclose(in);
	}

	free(Q);
	fclose(out);
	fclose(prova);
	for(int i = 0; i < np+1; ++i)
		free(paths[i]);
	for(int i = 0; i < n_t0 + 1; ++i)
	{
		free(ts_jack[i]);
		free(ts[i]);
	}
	free(r_jack);
	free(mean_ts);
	free(paths);
	free(L);
	free(t0_a2);
	free(ts);
	free(ts_jack);
	free(t0_ts);
	return 0;
}
