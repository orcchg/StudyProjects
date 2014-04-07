#include <cstring>
#include <cstdio>
#include "inverse.h"
#include "power.h"

#if !defined(B10toB8)

#define B10toB8

char* B10_to_B8(int N)
{
	int i = 0, j = 0, C = N, temp = 0;
	char* pA = new char[100];
	char* pB = new char[100];
	char* ptr = 0;
	
/*	while(C) {
 		C /= 8;
		i++;
	}
	C = N;
	
	while(C) {
		temp = C / power(i-j-1,8);
		pA[j] = temp + '0';
		C = C - temp*power(i-j-1,8);
		j++;
	}
*/
	while(C) {
		sprintf(pB, "%d", C % 8);
		pA = strcat(pA,pB);
		C /= 8;
	}
	delete [] pB;
	
	ptr = inverse(pA,strlen(pA));
	delete [] pA;
	
	return ++ptr;
}

#endif