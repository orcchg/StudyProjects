#include <conio.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

typedef uint64_t ULONG;

int main()
{
	ULONG K,m=1,D,E;
	
	printf("MAXIMUM: 18,446,744,073,709,551,615\n");
	printf("Enter K: ");
	scanf("%llu",&K);
	printf("\n");
	
	printf("%llu\n\n",K);
	
	D = K;
	for(m = 1; E<<1 > D; m++) {
		D *= K;
		E = D;
		printf("%llu\n",m);
	}
	
	printf("D = %llu\nm = %llu\nPow = %llu\n",D,m,pow(D,m));
	
	_getch();
}