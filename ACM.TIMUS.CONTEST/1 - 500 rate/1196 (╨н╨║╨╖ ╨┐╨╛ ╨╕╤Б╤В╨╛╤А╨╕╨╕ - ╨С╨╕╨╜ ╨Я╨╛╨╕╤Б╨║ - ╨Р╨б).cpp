#include <iostream>
#include <stdio.h>
#include <conio.h>
using namespace std;

//----------------------------------------------------

bool Binary_Search(int* a, int k, int low , int high )
             {
                 int middle;
                 while(low <= high)
                 {
                    middle = low + (high - low)/2;
                    if (k == a[middle]) return a[middle];
                    else if(k < a[middle]) high = middle-1;
                         else low = middle+1; 
                 } 
             return 0;
             }

//----------------------------------------------------

int main()
{
	int N, M;
	
	scanf("%d", &N);
//	fflush(stdin);
	
	int* T = new int[N];
	
	for(int i = 0; i < N; ++i)
	{
		scanf("%d", &T[i]);
//		fflush(stdin);
	}
	
	cin >> M;
	
	int* S = new int[M];
	
	for(int i = 0; i < M; ++i)
	{
		scanf("%d", &S[i]);
//		fflush(stdin);
	}
	
	int Count = 0;
	for(int i = 0; i < M; ++i)
	{
		if (Binary_Search(T, S[i], 0, N - 1))
		{
			Count++;
		}
	}
	
	delete [] T;
	delete [] S;
	
	cout << Count;
	
	return 0;
}