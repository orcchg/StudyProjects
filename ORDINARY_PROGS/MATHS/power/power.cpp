#include <cstdio>
#include <conio.h>
#include <iostream>
using namespace std;

int power(int, int);

int main () {

	int c,n,m;
	
	cout << "Enter a: ";
	cin >> c;
		
	cout << "Enter n: ";
	cin >> n;
	
	m=power(c,n);
	
	cout << m;
	
	_getch();
	
	return 0;
	}
	
int power(int a, int n) {
	
	int k=n, b=1, c=a;
	
while (k!=0){	
	if(k % 2 == 0){
		k/=2;
		c*=c;
	} else {
		k--;
		b*=c;
	}
}
	return (b);
}
		