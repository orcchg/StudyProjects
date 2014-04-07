//Количество разложений Q(N) числа N на неупорядоченные слагаемые без повторений. N = 5 = 5 = 4 + 1 = 3 + 2; Q(5) = 3;
//Разложения считаются различными, если множества слагаемых различны. Q(N,K) - каждое слагаемое <= K;
//Q(N,K) = Q(N-K,K-1) + Q(N,K-1); Q(1,K) = Q(0,K) = 1 при K > 0, и Q(N,K) = 0 при K < 0;

#include <conio.h>
#include <stdio.h>

int Q_n_k(int,int);

int main()
{
	int N;
	printf("Enter N: ");
	scanf("%d",&N);
	printf("\n");
	fflush(stdin);
	
	printf("Q = %d",Q_n_k(N,N));
	_getch();
}

int Q_n_k(int n,int k)
{
	int q = 0;
	if(k <= 0) { 
		return 0;
	} else if(n < 2) {
		return 1;
	} else {
		q = Q_n_k(n-k,k-1) + Q_n_k(n,k-1);
		return q;
	}
}