#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

bool comp(string A, string B)
{
	return	strcmp(A.c_str(),B.c_str());
}

void Insertion_Sort(string* pA,int n){

	int i;
	string key;

	for(int j = 1; j < n; j++){
		key = pA[j];
		i = j - 1;
		
		while(i >= 0 && (comp(pA[i],key) > 0)){
			pA[i+1] = pA[i];
			i--;
			pA[i+1] = key;
		}
	}
}

int main()
{
	int N;
	string temp;
	
	cin >> N;
	
	string* A = new string[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> A[i];
	}
	
	for(int top = 0; top < N - 1; top++)
	{
		for(int seek = top + 1; seek < N; seek++)
		{
			if(comp(A[top],A[seek]))
			{ 	
				temp = A[top];
				A[top] = A[seek];
				A[seek] = temp;
			} 
		}
	}
	
	int count = 1, j = 0;
	string* R = new string[N];
	
	R[0] = A[0];
	
	for(int i = 1; i < N; ++i)
	{
		if ((comp(A[i],A[i-1]))==0)
		{
			count++;
			R[j] = A[i];
		}
		else
		{
			count = 1;
			++j;
		}
	}
	delete [] A;
	
	Insertion_Sort(R, N);
	
	string* T = new string[N];
	j = 0;
	
	for(int i = 0; i < N; ++i)
	{
		if (!R[i].empty())
		{
			T[j++] = R[i];
		}
	}
	delete [] R;
	
	for(int i = 0; i < j; ++i)
	{
		cout << T[i] << endl;
	}
	delete [] T;
	
//	_getch();
	return 0;
}