#include <conio.h>
#include <stdio.h>
#include <math.h>

const double pi = 3.1415926535897932384626433832795;
const double g = 9.81; // m/sec^2

int main()
{
	int L, H, W; //cm, cm, ob/min
	
	scanf("%d%d%d", &L, &H, &W);
	
	if ((double)L/200.0 > (double)H/100.0)
	{
		printf("butter\n");
		return 0;
	}
	
	double t = sqrt(2.0*fabs((double)H/100.0 - (double)L/200.0)/g);
	double w = (double)W*t/60.0;
	double p = 0;
	double* q = &p;
	
	double u = modf(w, q);
	
//	printf("%lf\n", w);
	
	if ( (u<=1.0/4.0) || (u>3.0/4.0) )
	{
		printf("butter\n");
		return 0;
	}
	else if ( u>1.0/4.0 && u<=3.0/4.0)
	{
		printf("bread\n");
		return 0;
	}
	printf("butter\n");
//	_getch();
/*	double w = W/60.0; // ob/sec
	double t = 1.0/w; // time for one rotation in sec
	double t2 = t/2.0; // time for one half-rotation in sec
	
	double h = 0.5*g*t*t; // track of CM for one rotation in cm
	double h2 = 0.5*g*t2*t2; // track of CM for one half-rotation in cm
	
	double T = sqrt(2.0 * (H - 0.5*L)/ g); // full time of CM falling
	
	int n = 0;
	double way = 0;
	
	while(way < H)
	{
		++n;
		way = 0.5*g*pow(n*t, 2);
	}
	--n; // number of rotations
	
	way = 0.5*g*pow(n*t, 2); // full way of CM during n rotations
	
	double defect = H - way; // residual way w/o full rotation
	
	double t_last = T - n * t; // residual time to trace residual way
	double alpha = t_last * w; // number of fractional rotations
	
	if ( (alpha <= 0.25) || (alpha >= 0.75) )
	{
		printf("butter\n");
	}
	else
	{
		printf("bread\n");
	}*/
	
	return 0;
}