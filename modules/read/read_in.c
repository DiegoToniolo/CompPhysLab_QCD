/**************************************************************************
*	File read_in.c
*
*	Functions for reading input files.
*
*   The externally accessible functions are:
*
*	  void read_string(char *string, char *set, char *in_path)
*	    Search in the file in_path the string in set. If found, it
*	    reads and returns the next string.
*
*	  void read_n_string(char **string, int dim, char *set, char *in_path)
*	    Search in the file in_path the string in set. If found, it
*	    reads and returns the next 'dim' strings.
*
*	  void read_int(int *num, char *set, char *in_path)
*	    Search in the file in_path the string in set. If found, it
*	    reads and returns the integer number after the string.
*
*	  void read_n_int(int *num, int dim, char *set, char *in_path)
*	    Search in the file in_path the string in set. If found, it
*	    reads and returns the 'dim' integer numbers after the string.
*
*	  void read_double(double *num, char *set, char *in_path)
*	    Search in the file in_path the string in set. If found, it
*	    reads and returns the double number after the string.
*
*	  void read_n_double(double *num, int dim, char *set, char *in_path)
*	    Search in the file in_path the string in set. If found, it
*	    reads and returns the 'dim' double numbers after the string.
*
**************************************************************************/
#define READ_IN_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"

void read_string(char *string, char *set, char *in_path)
{
	FILE *in = NULL;
	char line_read[50];

	in = fopen(in_path, "r");
	if(in == NULL)
	{
		printf("Input file not opened\n");
		exit(0);
	}

	while(fscanf(in, "%s", line_read) == 1)
	{
		if(strcmp(line_read, set) == 0)
		{
			if(fscanf(in, "%s", line_read));
			strcpy(string, line_read);
			break;	
		}
	}
	
	fclose(in);
}

void read_n_string(char **string, int dim, char *set, char *in_path)
{
	FILE *in = NULL;
	char line_read[50];

	in = fopen(in_path, "r");
	if(in == NULL)
	{
		printf("Input file not opened\n");
		exit(0);
	}

	while(fscanf(in, "%s", line_read) == 1)
	{
		if(strcmp(line_read, set) == 0)
		{
			for(int i = 0; i < dim; ++i)
			{
				if(fscanf(in, "%s", line_read));
				strcpy(string[i], line_read);
			}
			break;	
		}
	}
	
	fclose(in);
}

void read_int(int *num, char *set, char *in_path)
{
	FILE *in = NULL;
	char line_read[50];

	in = fopen(in_path, "r");
	if(in == NULL)
	{
		printf("Input file not opened\n");
		exit(0);
	}

	while(fscanf(in, "%s", line_read) == 1)
	{
		if(strcmp(line_read, set) == 0)
		{
			if(fscanf(in, "%s", line_read));
			*num = atoi(line_read);
			break;	
		}
	}
		
	fclose(in);
}

void read_n_int(int *num, int dim, char *set, char *in_path)
{
	FILE *in = NULL;
	char line_read[50];

	in = fopen(in_path, "r");
	if(in == NULL)
	{
		printf("Input file not opened\n");
		exit(0);
	}

	while(fscanf(in, "%s", line_read) == 1)
	{
		if(strcmp(line_read, set) == 0)
		{
			for(int i = 0; i < dim; ++i)
			{
				if(fscanf(in, "%s", line_read));
				num[i] = atoi(line_read);
			}
			break;	
		}
	}
		
	fclose(in);
}

void read_double(double *num, char *set, char *in_path)
{
	FILE *in = NULL;
	char line_read[50];

	in = fopen(in_path, "r");
	if(in == NULL)
	{
		printf("Input file not opened\n");
		exit(0);
	}

	while(fscanf(in, "%s", line_read) == 1)
	{
		if(strcmp(line_read, set) == 0)
		{
			if(fscanf(in, "%s", line_read));
			*num = atof(line_read);
			break;	
		}
	}
		
	fclose(in);
}

void read_n_double(double *num, int dim, char *set, char *in_path)
{
	FILE *in = NULL;
	char line_read[50];

	in = fopen(in_path, "r");
	if(in == NULL)
	{
		printf("Input file not opened\n");
		exit(0);
	}

	while(fscanf(in, "%s", line_read) == 1)
	{
		if(strcmp(line_read, set) == 0)
		{
			for(int i = 0; i < dim; ++i)
			{
				if(fscanf(in, "%s", line_read));
				num[i] = atof(line_read);
			}
			break;	
		}
	}
		
	fclose(in);
}
