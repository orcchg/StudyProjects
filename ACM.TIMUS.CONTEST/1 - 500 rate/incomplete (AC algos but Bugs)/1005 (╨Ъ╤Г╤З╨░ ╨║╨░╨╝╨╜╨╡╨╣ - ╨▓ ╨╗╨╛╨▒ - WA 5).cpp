#include <iostream>
using std::cin;
using std::cout;

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
	int N, heap_one = 0, heap_two = 0, dif = 0;
	
	cin >> N;
	
	int* W = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> W[i];
	}
	
	Insertion_Sort(W, N);
	heap_one += W[N - 1];
	
	for(int i = N - 2; i >= 0; --i)
	{
		if (heap_one - heap_two >= 0)
		{
			heap_two += W[i];
		}
		else
		{
			heap_one += W[i];
		}
	}
	
	dif = heap_one - heap_two;
	
	if (dif < 0)
	{
		dif *= -1;
	}
	
	cout << dif;
	return 0;
}