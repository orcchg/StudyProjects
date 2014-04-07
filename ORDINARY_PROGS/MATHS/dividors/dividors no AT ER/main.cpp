#include <conio.h>
#include <stdio.h>
#include "unsgnlong.h"
#include "support.h"
#include "power.h"
#include "eratosfen.h"
#include "atkin.h"

#define MAXLEN 10000

bool is_simple(ULONG);
ULONG simple_dividor(ULONG,ULONG[]);

const ULONG one = 1;

int main()
{
	ULONG len, N, Nm = 1, M = 1, S = 1, S1 = 0, S2 = 0, S3 = 0, p = 0, q = 0, k = 0;
	ULONG er1 = 0, er2 = 0, at = 0;
	ULONG P[MAXLEN], D[MAXLEN], L[MAXLEN], A[MAXLEN], R[MAXLEN], T[MAXLEN];
	ULONG a, b;
	double eul = 1, eul2 = 1;
	
	printf("Enter N: ");
	scanf("%ld",&N);
	fflush(stdin);
	printf("\n");
	
	
	//----------------------------------------------------------------------------------------------
	//ZERO INITIALIZATION;
	for(ULONG i = 0; i < MAXLEN; i++) 
	{
		L[i] = 0; //POWER OF i-type SIMPLE DIVIDOR array
		D[i] = 0; //ANY DIVIDOR array 						(SORTED)
		P[i] = 0; //SIMPLE DIVIDORS with REPEATS array 		(SORTED)
		A[i] = 0; //SIMPLE DIVIDORS without REPEATS array 	(SORTED)
		R[i] = 0; //SIMPLE NUMBERS < N by Eratosphen 		(SORTED)
		T[i] = 0; //SIMPLE NUMBERS < N by Atkin 			(SORTED)
	}
	//----------------------------------------------------------------------------------------------
	
	
	len = simple_dividor(N,P); //SORTED ARRAY P OF SIMPLE DIVIDORS OF N
	
	
	//----------------------------------------------------------------------------------------------
	//SQRT NORMALIZATON: SQRT(N) = b*SQRT(a), b - MAXIMUM;
	a = N; b = 1;
	for(ULONG i = 1; i < len; )
	{
		if(P[i] == P[i-1])
		{
			b *= P[i-1];
			i += 2;
		} 
		else
		{
			++i;
		}
	}
	a /= b;
	a /= b;
	
	printf("SQRT normalization: a = %d  b = %d\n",a,b);
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	L[0] = 1; //L[j] = ALPHA - POWER OF j-type SIMPLE DIVIDOR OF N
	for(ULONG i = 1; i < len; ++i) 
	{
		if(P[i] == P[i-1]) 
		{
			L[q] = L[q] + 1;
		} 
		else 
		{
			q++;
			L[q] = 1;
		}
	}
	q++; //NUMBER OF ELEMENTS OF L
	printf("\nNumP: %ld",len);
	printf(" ; Q: %ld\n",q);
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	//M - NUMBER OF DIVIDORS OF N
	for(ULONG i = 0; i < MAXLEN; ++i)
	{
		if (L[i] != 0) 
		{
			M = M*(L[i] + 1);
		}
	}
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	//SKIP REPEATS in P array AND WRITE SIMPLE DIVIDORS into A array;
	for(ULONG i = 1; i < len; ++i) 
	{
		ULONG temp = P[i-1];
		A[k] = temp;
		if (P[i] != temp)
		{
			A[++k] = P[i];
		} 
		else 
		{
			A[k] = P[i-1];
		}
	}
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------		
	printf("Simple Dividors:  ");
	if(is_simple(N))
	{
		eul = 1;
		printf("%ld ",one);
	} 
	else 
	{
		for(ULONG i = 0; i < q; ++i) 
		{
			eul *= (1 - 1/(double)A[i]);
			printf("%ld ",A[i]);
		}
	}
	
	for(ULONG i = 0; i < q; ++i) 
	{
		S *= (power(L[i]+1,A[i]) - 1)/(A[i] - 1);
	}
	
	if(is_simple(N)) 
	{
		eul2 = 1;
	} 
	else
	{ 
		eul2 = N*eul;
	}
	printf("\nEuler's number of mutual-simple with N: %6.0lf",eul2); //EULER's NUMBER
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	for(ULONG i = 1; i <= N/2; ++i) 
	{ //D[p] - ANY DIVIDORS OF N
		if (N % i == 0) 
		{
			D[p++] = i;
			S1 += i; //S1 - DIRECT SUM OF ALL DIVIDORS OF N
		}
	}
	D[p] = N;
	S1 += D[p];
	
	for(ULONG i = 0; i < M; ++i) 
	{
		S2 += D[i]; //S2 - ANOTHER DIRECT SUM OF ALL DIVIDORS OF N
	}
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	printf("\n\nList of Multiplicators: \n");
	for(ULONG i = 0; i < len; ++i)
	{
		printf("P[%ld] = %ld\n",i,P[i]);
	}
	
	printf("\nMultiplication: "); 
	for(ULONG i = 0; i < len; ++i) 
	{
		Nm *= P[i];	
	}
	printf("%ld\n",Nm);
	//----------------------------------------------------------------------------------------------
	
	
/*	//----------------------------------------------------------------------------------------------
	er1 = eratosphen(N,R,er2);
	printf("\nNumber of simple numbers < N (Eratosphen): %ld  (review) %ld\n",er1,er2);
	printf("These simple numbers: ");
	for(ULONG i = 0; i < er1; ++i) 
	{
		printf("%ld ",R[i]);
	}
	
	at = atkin(N,T);
	printf("\n\nNumber of simple numbers < N (Atkin): %ld\n",at);
	printf("These simple numbers: ");
	for(ULONG i = 0; i < at; ++i)
	{
		printf("%ld ",T[i]);
	}
	//----------------------------------------------------------------------------------------------
*/	
	
	//----------------------------------------------------------------------------------------------
	printf("\n\nNumber of all dividors: ");
	printf("\nM = %ld ;  ",M);
	for(ULONG i = 0; i <= p; ++i) 
	{
		printf("%ld ",D[i]);
	}
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	if(is_simple(N)) 
	{
		S3 = 1;
	} 
	else 
	{
		S3 = S-N;
	}
	printf("\n\nSum of all dividors EXCEPT N itself: %ld  %ld  %ld\n",S3,S1-N,S2-N);
	printf("Sum of all dividors: %ld  %ld  %ld\n",S,S1,S2);
	//----------------------------------------------------------------------------------------------
	
	
	//----------------------------------------------------------------------------------------------
	if(is_perfect(N,D,p)) 
	{
		printf("\nYes! %ld - is Perfect Number!",N);
	} 
	else 
	{
		printf("\nNo! %ld - is not Perfect.",N);
	}
	//----------------------------------------------------------------------------------------------
	
	_getch();
	return 9;
}