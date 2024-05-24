#define MAIN_PROGRAM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "read.h"

int main(int argc, char **argv)
{
	FILE *in = NULL;
	int n_conf;

	if(argc < 2)
	{
		printf("Usage: %s infile\n", argv[0]);
		return 0;
	}

	in = fopen(argv[1], "r");
	if(read_n_config(&n_conf, in))
	{
		printf("Unsuccessful computation of the number of configurations.\n");
		fclose(in);
		return 0;
	}
	printf("Number of configurations: %d\n", n_conf);
	
	fclose(in);
	return 0;
}
