#include <stdio.h>
#include <iostream>
#include <conio.h>

void Insertion_Sort(int* pA,int n){

	int key,i;

	for(int j = 1; j < n; j++){
		key = pA[j];
		i = j - 1;
		
		while(i >= 0 && pA[i] > key){
			pA[i+1] = pA[i];
			i--;
			pA[i+1] = key;
		}
	}
}

int main()
{
	int K;
	int i = 0;
	int sum = 0;
	
	std::cin >> K;
	
	int A[101];
	while(i < K)
	{
			std::cin >> A[i++];
	}
	Insertion_Sort(A, K);
	
	for(int i = 0; i < K/2 + 1; ++i)
	{
		sum += A[i]/2 + 1;
	}
	std::cout << sum;
	
	return 0;
}