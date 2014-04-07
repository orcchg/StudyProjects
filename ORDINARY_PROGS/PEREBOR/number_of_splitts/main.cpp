#include <conio.h>
#include <stdio.h>

typedef long ULONG;

ULONG Pk_split(ULONG,ULONG);

int main()
{
	int N;
	ULONG P;
	printf("Number of splitts; Enter N: ");
	scanf("%d",&N);
	printf("\n");
	
	ULONG* ArrP = new ULONG[N];
	
	P = Pk_split(N,N);
	
	printf("P = %ld\n\n",P);
	
	for(int y = 0; y < N; y++) {
		ArrP[y] = Pk_split(y+1,y+1);
		printf("%d:  %ld\n",y+1,ArrP[y]);
	}
	
	delete [] ArrP;
	
	_getch();
}

ULONG Pk_split(ULONG n, ULONG k)
{
	ULONG p = 0;
	if(k == 1) return 1;
	if(n < 0) return 0;
	if(n == 0) return 1;
	{
		p = Pk_split(n - k,k) + Pk_split(n,k - 1);
	}
	return p;
}