#include "B16toB10.h"
#include "B10toB8.h"

char* B16_to_B8(char* str)
{
	int N = 0;
	char* pA = new char[100];
	
	N = B16_to_B10(str);
	pA = B10_to_B8(N);
	
	return pA;
}