#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <iostream>
using std::cin;

const double pi = 3.1415926535;
const double g = 10.0;
const double eps = 0.000001;

int main()
{
	int V; // start velocity
	int A; // degrees
	double a; // radians 
	double K; // coeff;
	
	double S = 0.0; // distance - ?
	
	cin >> V >> A >> K;
	
	if (A == 90)
	{
		S = 0.0;
		printf("%.2lf", S);
	
//		_getch();
		return 0;
	}
	
	a = (double)A/180.0*pi;
	double koeff = 2.0*sin(a)*cos(a) / g;
	double v = (double)V;
	
	S = v * koeff * v;
	
	double way = S / K;
	
	while(way > eps)
	{
		S += way;
		way /= K;	
	}
	
	printf("%.2lf", S);
	
//	_getch();
	return 0;
}