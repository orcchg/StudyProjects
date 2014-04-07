#include <cstdlib>
#include <stdio.h>
#include "struct.h"

member* Generate_RA(int k, int lim, int lim_info, int* n)
{
	// Generates array[MAXLIM] of random keys and info
	// -5000 <= keys, info <= 5000
	
	double temp = 0;
	member* pA = new member[MAXLIM];
	*n = k;
	
	for(int i = 0; i < *n; ++i)
	{	
		srand(*n - i);
		temp = 2 * (double)rand() / RAND_MAX * lim;
		srand(*n + i*i);
		temp = 2 * (double)rand() / RAND_MAX * lim_info;
		pA[i].key = temp - lim;
		pA[i].info = temp - lim_info;
	}
	
	printf("***** Generated! *****\n\n");
	
	return pA;
}