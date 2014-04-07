#include <conio.h>
#include <iostream>
#include <cstdio>
#include "mon_name.h"
using namespace std;

int main(){

	int N;
	char* p;
	
	cout << "Enter N: ";
	cin >> N;
	cout << endl;
	
	p = month_name(N);
	cout << "MONTH: " << p << endl;
	
	_getch();
}