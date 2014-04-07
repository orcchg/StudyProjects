#include <iostream>
#include <conio.h>
#include <iomanip>
#include "solve.h"

double solve(double a, double b, double (*f)(double));
double func(double x);

int main()
{
	double a = 0, b = 10;
	double result = 0;
	
	result = solve(a, b, &func);
	
	std::cout << std::setprecision(10) << result;
	_getch();
	return 0;
}

double func(double x)
{
	return sin(x);
}