#include <cstdio>
#include <conio.h>

int main(){

	double sum,v;
	
	sum=0;
	while(scanf("%lf", &v) == 1)
		printf("\t%.2f\n",sum+=v);
		
	_getch();
}