#pragma comment(linker, "/STACK:16777216")

#include <iostream>
#include <conio.h>

void Q_S(int*, int, int);

void Quick_Sort(int* pA, int n){

	Q_S(pA,0,n-1);
}

void Q_S(int* pA, int p, int r){

	int i,j,q,temp;
	
	i = p;
	j = r;
	q = (p+r)/2;
	
	do {
		while((pA[i] < pA[q]) && (i < r))
			i++;
		while((pA[q] < pA[j]) && (j > p))
			j--;
		
		if(i <= j){
			temp = pA[i];
			pA[i] = pA[j];
			pA[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);
	
	if(p < j)
		Q_S(pA,p,j);
	if(i < r)
		Q_S(pA,i,r);
}

int Glob[10];
int count = 0;

int main()
{

	int K, n, L;
do 
{
	std::cin >> n;
	int* pA = new int[n + 1];
	L = n ;//+ 1;
	
while(L > 0)
{	
	K = L;
	int Even_Sum = 1;
	int Odd_Sum = 1;

	if (K % 2 == 0)
	{
		while(K % 2 == 0)
		{
			K /= 2;
		}
	}
	
	if (K == 1)
	{
		pA[K] = 1;
	}
	else
	{
		int M = 0, c = 0;
		
		while(K > 1)
		{
			if ((K - 1)/2 % 2 == 0)
			{
				M = (K - 1)/2;
				K = M + 1;
			}
			else
			{
				K = (K - 1)/2;
				M = K + 1;
			}
			
			if (M/2 % 2 == 0)
			{
				Even_Sum += Odd_Sum;
			}
			else
			{
				c = Odd_Sum;
				Odd_Sum += Even_Sum;
				Even_Sum = c;
			}
		}
		
	}
	pA[L--] = Odd_Sum;
}
	
	pA[1] = 1;
	pA[0] = 0;
	
//	Insertion_Sort(pA, n + 1);
	Quick_Sort(pA, n + 1);
	
/*	for(int i = 0; i <= n; ++i)
	{
		std::cout << pA[i] << std::endl;
	}*/
	
	Glob[count++] = pA[n];
	
//	delete [] pA;
}
while(n);	

for(int i = 0; i < count - 1; ++i)
{
	std::cout << Glob[i] << std::endl;
}
//	_getch();	
	return 0;
}