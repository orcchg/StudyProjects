#include <stdio.h>

int main(void){

	unsigned c,a=0;
	
    for( ; (c=getchar())!='\n' ; a = ( a * 10 + c - '0' ) % 7 );
	
    printf("%u\n",a);
	
    return 0;
}