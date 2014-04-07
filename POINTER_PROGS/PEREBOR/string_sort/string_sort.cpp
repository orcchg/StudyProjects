#include <iostream>
#include <conio.h>
#include <cstring>
#include <stdlib.h>
using namespace std;

int comp(string A, string B)
{
	if (A < B) return -1;
	if (A > B) return 1;
	return 0;
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
			if(A[top] > A[seek])
			{ 	
				temp = A[top];
				A[top] = A[seek];
				A[seek] = temp;
			} 
		}
	}
	
	for(int i = 0; i < N; ++i)
	{
		cout << A[i] << endl;
	}
	
	_getch();
	return 0;
}