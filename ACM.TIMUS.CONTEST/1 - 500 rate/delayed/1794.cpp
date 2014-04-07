#include<iostream>
#include <conio.h>
using namespace std;

int main()
{
	int n;
	
	cin >> n;
	
	int* a = new int[n];
	
	for(int i = 1; i <= n; ++i)
	{	
		cin >> a[i-1];
	}