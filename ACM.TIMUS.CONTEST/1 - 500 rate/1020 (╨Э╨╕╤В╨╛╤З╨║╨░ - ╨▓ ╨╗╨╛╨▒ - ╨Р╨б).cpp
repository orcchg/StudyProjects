#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdio.h>
using std::cout;
using std::cin;
using std::endl;

const double pie = 3.1415926535;

struct point
{
	double x;
	double y;
	double fi;
};

double dist(point A, point B)
{
	return sqrt( (A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) );
}

int main()
{

	int N;
	double R;
	double len = 0.0, fie = 0.0, psi = 0.0;
	
	cin >> N >> R;
	
	point* P = new point[N];
	
	for(int i = 0; i < N; ++i)
	{
		cin >> P[i].x >> P[i].y;
	}
//------------------------------------------------------------------------------------------	
	

//------------------------------------------------------------------------------------------		
	for(int i = 1; i < N - 1; ++i)
	{
		fie = atan( (P[i].y - P[i-1].y)/(P[i].x - P[i-1].x) );
/*		if (fie > pie) 
		{
			fie = pie - fie;
		}
*/		
		psi = atan( (P[i+1].y - P[i].y)/(P[i+1].x - P[i].x) );
/*		if (psi > pie)
		{
			psi = pie - psi;
		}
*/		
		P[i].fi = fabs(fie) + fabs(psi);
//		cout << i << " " << fie << " " << psi << " " << P[i].fi << endl;
	}
//------------------------------------------------------------------------------------------		
	
	
//------------------------------------------------------------------------------------------		
	fie = atan( (P[0].y - P[N-1].y)/(P[0].x - P[N-1].x) );
/*	if (fie > pie) 
	{
		fie = pie - fie;
	}
*/	
	psi = atan( (P[1].y - P[0].y)/(P[1].x - P[0].x) );
/*	if (psi > pie)
	{
		psi = pie - psi;
	}
*/	
	P[0].fi = fabs(fie) + fabs(psi);
	
//	cout << fie << " " << psi << " " << P[0].fi << endl;
//------------------------------------------------------------------------------------------		
	
	
//------------------------------------------------------------------------------------------	
	fie = atan( (P[N-1].y - P[N-2].y)/(P[N-1].x - P[N-2].x) );
/*	if (fie > pie) 
	{
		fie = pie - fie;
	}
*/	
	psi = atan( (P[0].y - P[N-1].y)/(P[0].x - P[N-1].x) );
/*	if (psi > pie)
	{
		psi = pie - psi;
	}
*/	
	P[N-1].fi = fabs(fie) + fabs(psi);
	
//	cout << fie << " " << psi << " " << P[N-1].fi << endl;
//------------------------------------------------------------------------------------------	

	
	for(int i = 0; i < N-1; ++i)
	{
		len += dist(P[i],P[i+1]);
//		len += P[i+1].fi*R;
//		cout << i << " " << len << endl;
	}
	
	len += dist(P[N-1],P[0]);
//	len += P[0].fi*R;
	len += 2*pie*R;
	
	printf("%.2lf", len);
	
//	_getch();
	return 0;
}