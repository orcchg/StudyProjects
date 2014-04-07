#include <stdio.h>
#include "byteprint.h"

void intBitPrint(int integer){

	union {
			int ii;
			unsigned char ar[8];
		} bind;
		
	bind.ii = integer;
	

	byteprint(bind.ar[3]); printf(" ");
	byteprint(bind.ar[2]); printf(" ");
	byteprint(bind.ar[1]); printf(" ");
	byteprint(bind.ar[0]); printf(" ");
}