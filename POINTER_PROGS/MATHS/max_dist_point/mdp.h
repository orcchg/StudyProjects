#include <math.h>
#include <stdio.h>

double SQR(double);
//double MIN(int, double [], int&, int&);
//double MAX(int, double [], int&, int&);

double MDP(double* X, double* Y, int N/*, int& rAm, int& rBm*/, int& rAM, int& rBM)
{
	int S = 0;
	double min,max;
	
	S=N*(N-1)/2;
	
	double* R = new double[S];
	
	R[0] = sqrt( SQR(X[1] - X[0]) + SQR(Y[1] - Y[0]) );
	max = R[0];
	
	for(int j = 0; j < N; j++) {
		for(int i = j + 2; i < N; i++) {
			R[j+i-1] = sqrt( SQR(X[i] - X[j]) + SQR(Y[i] - Y[j]) );
			if (R[j+i-1] > max) {
				rAM = j + 1;
				rBM = i + 1;
				max = R[j+i-1];
			}
		}
	}
	
//	min = MIN(S,R,rAm,rBm,N);
//	max = MAX(S,R,rAM,rBM,N);
	
	return max;
}
	
double SQR(double x)
{
	return x*x;
}

/*double MIN(int len, double R[], int& rAm, int& rBm, int N)
{
	int j = 0;
	double min = R[0];
	
	for(int i = 1; i < len; i++) {
		if (min > R[i]) {
			min = R[i];
			j++;
		}
	}
	
	rAm = j / (N - 1 - ju);
    rBm = j % (N - 1 - ju);	
	
	return min;
}
	
double MAX(int len, double R[], int& rAM, int& rBM, int N)
{
	int j = 0;
	double max = R[0];
	
	for(int i = 1; i < len; i++) {
		if (max < R[i]) {
			max = R[i];
			j++;
		}
	}
	
	return max;
}*/