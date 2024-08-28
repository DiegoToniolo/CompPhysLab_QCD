/**********************************************************************************
*	File read_data.c
*
*	Functions for reading data produced by the program ym1.c.
*
*   The externally accessible functions are:
*
*	  void read_head(t_head *head_file, FILE *in)
*	    It reads the head of the data file.
*
*	  void read_Qcharge_conf(double *Q_charge, t_head head_file, FILE *in)
*	    It reads and compute the topological charge of a configuration
*	    of the fields.
*
*	  void read_Qcharge(double **Q_charge, int n_conf, t_head head_file, FILE *in)
*	    It reads the topological charge for every n_conf configuration
*       available.
*
*********************************************************************************/
#define READ_DATA_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

void read_head(t_head *head_file, FILE *in)
{
	int read = 0, head_int[3];
	double head_double;

	read += fread(head_int, sizeof(int), 3, in);
	read += fread(&head_double, sizeof(double), 1, in);

	if(read != 4)
	{
		printf("Head of data file not read successfully\n");
		exit(0);
	}
	head_file->dn = head_int[0];
	head_file->t_w_max = head_int[1]+1;
	head_file->t_max = head_int[2];
	head_file->eps = head_double;
}

void read_Qcharge_conf(double *Q_charge, t_head head_file, FILE *in)
{
	double **matrix = NULL;
	int read = 0, flag = 0, n_conf;

	read += fread(&n_conf, sizeof(int), 1, in);
	if(read != 1)
	{
		printf("Number of the configuration in elaboration not read successfully\n");
		exit(0);
	}
	matrix = (double **) malloc(head_file.t_w_max * sizeof(double*));
	for(int i = 0; i < head_file.t_w_max; ++i)
		matrix[i] = (double *) malloc(head_file.t_max * sizeof(double));

	for(int type_data = 0; type_data < 3; ++type_data)
	{	
		for(int t_wilson = 0; t_wilson <head_file.t_w_max; ++t_wilson)
		{
			for(int t_slice = 0; t_slice < head_file.t_max; ++t_slice)
			{
				read = fread(&(matrix[t_wilson][t_slice]), sizeof(double), 1, in);
				if(read != 1)
					flag = 1;
			}
		}

		if(type_data == 2)
		{
			for(int t_wilson = 0; t_wilson < head_file.t_w_max; ++t_wilson)
			{
				Q_charge[t_wilson] = 0;
				for(int t_slice = 0; t_slice < head_file.t_max; ++t_slice)
					Q_charge[t_wilson] += matrix[t_wilson][t_slice];
			}	
		}
	}

	for(int i = 0; i < head_file.t_w_max; ++i)
		free(matrix[i]);
	free(matrix);

	if(flag)
	{
		printf("Configuration %d not read successfully\n", n_conf);
		exit(0);
	}	
}

void read_Qcharge(double **Q_charge, int n_conf, t_head head_file, FILE *in)
{	
	for(int i = 0; i < n_conf; i++)
		read_Qcharge_conf(Q_charge[i], head_file, in);
}
