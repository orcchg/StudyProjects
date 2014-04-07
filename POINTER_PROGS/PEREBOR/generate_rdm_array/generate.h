#include <cstdlib>
#include "struct.h"

member* Generate_RA(int* n)
{
	// Generates array[MAXLIM] of random keys and info
	// -5000 <= keys, info <= 5000
	
	srand(239);
	double temp = 0;
	member* pA = new member[MAXLIM];
	*n = 1000;
	
	for(int i = 0; i < *n; ++i)
	{	
		temp = (double)rand()/RAND_MAX;
		pA[i].key = 10000*temp - 5000;
		pA[i].info = 10000*temp - 5000;
	}
	
	return pA;
}