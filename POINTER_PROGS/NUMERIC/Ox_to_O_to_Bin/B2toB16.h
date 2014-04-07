#include "B2toB10.h"
#include "B10toB16.h"

char* B2_to_B16(char* str)
{
	int N = 0;
	char* pA = new char();
	
	N = B2_to_B10(str);
	pA = B10_to_B16(N);
	
	return pA;
}