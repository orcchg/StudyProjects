#include <conio.h>
#include <stdio.h>
#include "mdp.h"

double MDP(double* X, double* Y, int N/*, int& rAm, int& rBm*/, int& rAM, int& rBM);

int main()
{
	int N,rAM,rBM;
	printf("Enter N: ");
	scanf("%d",&N);
	printf("\n");
	fflush(stdin);
	double MAX;
	
	double* X = new double[N];
	double* Y = new double[N];
	
	printf("Enter Points X Y: \n");
	for(int i = 0; i < N; i++) {
		printf("Point %d: ",i+1);
		scanf("%lf %lf",&X[i],&Y[i]);
		printf("\n(%lf %lf)",X[i],Y[i]);
		fflush(stdin);
		printf("\n\n");
	}
	
	MAX = MDP(X,Y,N,rAM,rBM);
	
	printf("\n\n\n%d %d\n%.4lf\n",rAM,rBM,MAX);
	printf("(%.4lf %.4lf) ; (%.4lf %.4lf)",X[rAM-1],Y[rAM-1],X[rBM-1],Y[rBM-1]);
	_getch();
}