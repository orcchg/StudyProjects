#include "B2toB10.h"
#include "B10toB8.h"

char* B2_to_B8(char* str)
{
	int N = 0;
	char* pA = new char[100];
	
	N = B2_to_B10(str);
	pA = B10_to_B8(N);
	
	return pA;
}