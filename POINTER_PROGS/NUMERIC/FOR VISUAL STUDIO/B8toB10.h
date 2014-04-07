#include <cstring>
#include "power.h"

#if !defined(B8toB10)

#define B8toB10

int B8_to_B10(char* str)
{
	 int len = strlen(str);
	 int* pA = new int[len];
	 int N = 0;
	 char ch;
	 
	 for(int i = 0; i < len; i++) {
		ch = *(str+i);
		pA[i] = ch - '0';
		N += pA[i]*power(len-i-1,8);
	}
	
	return N;
}

#endif