#include <conio.h>
#include <stdio.h>
#include <iostream>

double power_1(double,int);
double power_2(double,int);
double power_3(double,int);

int main(){

	int n;
	double x;
	
	printf("Enter x and n: ");
	while(scanf("%lf %d",&x ,&n) == 2){
	
			printf("\n%lf",power_1(x,n));

			printf("\n%lf",power_2(x,n));

			printf("\n%lf",power_3(x,n));
	}
}

double power_1(double x, int n){

   if(n == 0) return 1;
   if(n < 0) return power_1 ( 1 / x, -n);
   return x * power_1(x, n - 1);
}

double power_2(double x, int n){

	if(n == 0) return 1;
	if(n < 0) return power_2(1/x, -n);
	if(n % 2) return x * power_2(x,n-1);
	return power_2(x*x,n/2);
}

double power_3(double x, int n){

	int k=n,count1=0,count2=0;
	double b=1.0;

while(k!=0){	
	if(k % 2 == 0){
		x*=x;
		k/=2;
	} else {
		b*=x;
		k--;
	}
}
	
	return b;
}