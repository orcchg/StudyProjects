#include "power.h"
#include <limits.h>

unsigned long btod(unsigned long B)
{
	unsigned long i = 0, C = B, temp, N = 0,count=0;
	
	if(B > LONG_MAX)
		return -1;
	
	while(C) {
		C /= 10;
		i++;
	}
	C = B;
	printf("%ld ",i);
	
	while(i) {
		if(i == 1) {
			if(C > 0) {
				N += 1*power(i-1,2);
				count++;
			} else {
				N += 0;
			}
			i--;
		} else {
			temp = C/power(i-1,10);
			if (temp) {
				N += temp*power(i-1,2);
				C -= power(i-1,10);
				count++;
			} 
			i--;
		}
	}
	printf(" %ld\n",count);
	
	return N;
}