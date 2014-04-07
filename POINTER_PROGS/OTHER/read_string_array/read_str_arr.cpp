#include <iostream>
#include <string.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main()
{
	int N, j = 0;
	
	cin >> N;
	
	char** a = new char*[N];
	
	for(int i = 0; i < N; ++i)
	{
		a[i] = new char[31];
		scanf("%s", a[i]);
	}
	
	for(int i = 0; i < N; ++i)
	{
		printf("%s\n", a[i]);
	}
	
	_getch();
	return 0;
}