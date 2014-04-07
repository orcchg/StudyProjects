#include "B8toB10.h"
#include "B10toB2.h"

char* B8_to_B2(char* str)
{
	int N = 0;
	char* pA = new char[100];
	
	N = B8_to_B10(str);
	pA = B10_to_B2(N);
	
	return pA;
}