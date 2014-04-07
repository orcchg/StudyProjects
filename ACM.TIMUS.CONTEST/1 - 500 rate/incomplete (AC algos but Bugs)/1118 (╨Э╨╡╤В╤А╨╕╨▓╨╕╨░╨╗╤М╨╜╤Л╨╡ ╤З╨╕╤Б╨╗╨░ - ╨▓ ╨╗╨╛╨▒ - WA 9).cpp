#include <stdio.h>
#include <conio.h>

const int MAXLEN = 1000;

typedef long ULONG;

//-----------------------------------------------
inline bool is_simple(ULONG N)
{
	ULONG k = N,l = 2;
	
	while(l != N) {
		if(k % l == 0) {
			return false;
		} else {
			l++;
		}
	}
	return (l == N);
}
//-----------------------------------------------

//-----------------------------------------------
inline ULONG simple_dividor(ULONG N, ULONG P[])
{
	ULONG k = N,l = 2,i = 0;
	
	while(k != 1) {
		l = 2;
		while(k % l != 0) {
			l++;
		}
	P[i++] = l;
	k /= l;
	}
	
	if(i) {
		return i;
	} else {
		return 1;
	}
}
//-----------------------------------------------

//-----------------------------------------------
inline ULONG power(ULONG n, ULONG a) {

	ULONG k = n, c = a, b = 1;
	
	while(k) {
		if (k % 2 == 0) {
			c *= c;
			k /= 2;
		} else {
			b *= c;
			k--;
		}
	}
	return b;
}
//-----------------------------------------------


int main()
{
	ULONG I, J, p = 0;
	
	scanf("%ld%ld", &I, &J);
	
	if (I == 1)
	{
		printf("%ld\n", 1);
		return 0;
	}
	
	for(int i = J; i >= I; --i)
	{
		if (is_simple(i))
		{
			printf("%ld\n", i);
	//		_getch();
			return 0;
		}
	}
	
	double* trivia = new double[J - I + 1];
	
	for(int N = I; N <= J; ++N)
	{
		int len = 0;
		
		ULONG* P = new ULONG[MAXLEN];
		ULONG* A = new ULONG[MAXLEN];
		ULONG* L = new ULONG[MAXLEN];
		
		double S = 1;
		
		len = simple_dividor(N,P);
		// HERE IS N;
		
		//-----------------------------------------------
		// SKIP REPEATS in P array AND WRITE SIMPLE DIVIDORS into A array;
		ULONG k = 0;
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
		//-----------------------------------------------
		
		//-----------------------------------------------
		// L[j] = ALPHA - POWER OF j-type SIMPLE DIVIDOR OF N
		ULONG q = 0;
		L[0] = 1; 
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
		//-----------------------------------------------
		
		//-----------------------------------------------
		// SUM OF ALL DIVIDORS of NUMBER N
		if (is_simple(N))
		{
			S = 1;
		}
		else
		{
			for(ULONG i = 0; i <= q; ++i) 
			{
				S *= (power(L[i]+1,A[i]) - 1)/(A[i] - 1);
			}
			S -= N;
		}
		//-----------------------------------------------
		
		trivia[p++] = S/N;
		
		delete [] P;
		delete [] A;
		delete [] L;
	}
	
	int indx = 0;
	double min = trivia[0];
	for(int i = 1; i < p; ++i)
	{
		if (trivia[i] < min)
		{
			min = trivia[i];
			indx = i;
		}
	}
	
	delete [] trivia;
	
	printf("%ld\n", indx + I);
	
//	_getch();
	return 0;
}