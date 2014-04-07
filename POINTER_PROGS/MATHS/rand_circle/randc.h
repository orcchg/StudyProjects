#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>

#define SQR(x) x*x

const int LIM = RAND_MAX;

char* Randc(double Rad, double A, double B)
{
	char* str = new char[100];
	double X,Y;
	int signX,signY,rndX,rndY;
	char* chX = new char();
	char* chY = new char();
	
	if ((rndX = rand()) >= LIM/2) signX = 1;
		else signX = -1;
	if ((rndY = rand()) >= LIM/2) signY = 1;
		else signY = -1;
		
	X = signX*Rad*(double)rand()/LIM;
	Y = signY*sqrt(SQR(Rad) - SQR(X))*(double)rand()/LIM;
	
		sprintf(chX,"%lf",X+A);
		sprintf(chY,"%10lf",Y+B);
		str = strcat(str,"(");
		str = strcat(str,chX);
		str = strcat(str,"  ");
		str = strcat(str,chY);
		str = strcat(str,")");
	
	delete [] chX;
	delete [] chY;
	
	return str;
}