#include <conio.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#define MAXLEN 100

bool is_power_of_Q(int,int);

int main()
{
	int N,Q;
	int s[MAXLEN];
	
	cout << "Enter N and Q: ";
	cin >> N;
	cin >> Q;
	cout << endl;
	
	cout << "Enter numbers: ";
	for(int i=0; i<N; i++) {
		cin >> s[i];
		cout << " ";
//		cout << "s[" << i << "]: " << s[i] << endl;
	}
		
	for(int i=0; i<N; i++) {
		if(is_power_of_Q(s[i],Q))
			cout << s[i] << " ";
	}
	
	_getch();
}

bool is_power_of_Q(int N,int Q)
{
	int i=0;
	for(i=1; i<N; i*=Q)
		;
	return (i == N);
}