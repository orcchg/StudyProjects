#include <iostream>
#include <conio.h>
#include <math.h>
using std::cin;
using std::cout;
using std::endl;

int atoi(const char* str) {
	int number = 0;
	int sign = 1;
	
	if (*str == '-') {
		str++;
		sign *= -1;
	}
	while(*str) {
		number += *str - '0';
		number *= 10;
		str++;
	}
	return sign * number / 10;
}
 
int main() {

	char* str1 = new char[100];
	cin >> str1;
	cout << atoi(str1);
	_getch();
	return 0;
}