#include "B8toB10.h"
#include "B10toB16.h"

char* B8_to_B16(char* str)
{
	int N = 0;
	char* pA = new char();
	
	N = B8_to_B10(str);
	pA = B10_to_B16(N);
	
	return pA;
}