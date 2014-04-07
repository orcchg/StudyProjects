#include <iostream>
#include <stdio.h>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;

typedef union
{
    long long i;
    double d;    
} t_double2long;

void print_bin(double number)
{
    int size = sizeof(double) * 8;
    t_double2long dl;
    dl.d = number;
    long long mask = 1LL << (size - 1);
    while(size--)
    {
        printf("%d", dl.i & mask ? 1 : 0);
        dl.i = dl.i << 1;
    }
}

int main() {
	double number;
	cin >> number;
	print_bin(number);
	_getch();
	return 0;
}