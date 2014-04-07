#include <stdio.h>

void byteprint(unsigned char ch){

union {
		unsigned char ss;
		struct {
			unsigned b0 :1; unsigned b1 :1;
			unsigned b2 :1; unsigned b3 :1;
			unsigned b4 :1; unsigned b5 :1;
			unsigned b6 :1; unsigned b7 :1;
		} byte;
	} bind;
	
	bind.ss = ch;
	printf("%u%u%u%u%u%u%u%u",bind.byte.b7,bind.byte.b6,bind.byte.b5,bind.byte.b4,
							  bind.byte.b3,bind.byte.b2,bind.byte.b1,bind.byte.b0);
}