#include <cstring>
#include "power.h"

#if !defined(B16toB10)

#define B16toB10

int B16_to_B10(char* str)
{
	/* str = {0,...,9,A,B,C,D,E,F} ;
	 * A = 10;
	 * B = 11;
	 * C = 12;
	 * D = 13;
	 * E = 14;
	 * F = 15;
	 */
	 int len = strlen(str);
	 int* pA = new int[len];
	 int N = 0;
	 char ch;
	 
	 for(int i = 0; i < len; i++) {
		ch = *(str+i);
		if (ch >= '0' && ch <= '9') {
			pA[i] = ch - '0';
		} else {
			switch (ch) {
				case 'A':
					pA[i] = 10;
					break;
				case 'B':
					pA[i] = 11;
					break;
				case 'C':
					pA[i] = 12;
					break;
				case 'D':
					pA[i] = 13;
					break;
				case 'E':
					pA[i] = 14;
					break;
				case 'F':
					pA[i] = 15;
					break;
				default:
					break; //IGNORE OTHER SYMBOLS
			}
		}
		N += pA[i]*power(len-i-1,16);
	}
	
	return N;
}

#endif