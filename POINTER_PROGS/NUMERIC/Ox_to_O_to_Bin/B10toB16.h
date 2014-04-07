#include <cstring>
#include "power.h"

#if !defined(B10toB16)

#define B10toB16

char* B10_to_B16(int N)
{
	/* str = {0,...,9,A,B,C,D,E,F} ;
	 * A = 10;
	 * B = 11;
	 * C = 12;
	 * D = 13;
	 * E = 14;
	 * F = 15;
	 */
	 int i = 0, C = N, temp = 0;
	 char* pA = new char();
	 char ch;
	 
	while(C) {
		C/=16;
		i++;
	}
	C = N;
	
	for(int j = 0; j < i; j++) {
		temp = C / power(i-j-1,16);
		if(temp < 10 && temp >= 0) {
			pA[j] = temp + '0';
		} else if (temp >= 10 && temp < 16) {
			switch(temp) {
				case 10:
					pA[j] = 'A';
					break;
				case 11:
					pA[j] = 'B';
					break;
				case 12:
					pA[j] = 'C';
					break;
				case 13:
					pA[j] = 'D';
					break;
				case 14:
					pA[j] = 'E';
					break;
				case 15:
					pA[j] = 'F';
					break;
				default:
					break; //IMMPOSSIBLE POSITION
			}
		}
		C = C - temp*power(i-j-1,16);
	}
	
	return pA;
}

#endif