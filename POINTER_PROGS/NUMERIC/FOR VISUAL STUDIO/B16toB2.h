#include "B16toB10.h"
#include "B10toB2.h"

char* B16_to_B2(char* str)
{
	int N = 0;
	char* pA = new char();
	
	N = B16_to_B10(str);
	pA = B10_to_B2(N);
	
	return pA;
}