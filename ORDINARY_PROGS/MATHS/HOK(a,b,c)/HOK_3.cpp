#include <conio.h>
#include <stdio.h>

int Dijkstra(int,int);

int main()
{
	int a,b,c;
	int NOK1,NOK2;
	
	printf("Enter a b c : ");
	scanf("%d %d %d",&a,&b,&c);
	printf("\n");
	fflush(stdin);
	
	NOK1 = Dijkstra(a,b);
	NOK2 = Dijkstra(NOK1,c);
	
	printf("\n\nHOK(%d %d) = %d\n",a,b,NOK1);
	printf("\n\nHOK(%d %d %d) = %d\n",a,b,c,NOK2);
	
	_getch();
}
		
int Dijkstra(int a,int b)
{
	int m = a, n = b, u = b, v = a,z;
	
	while(m > 0 && n > 0) {
		if(m >= n) {
			m -= n;
			v += u;
		} else {
			n -= m;
			u += v;
		}
	}
	if(m == 0) {
		z = v;
	} else if (n == 0) {
		z = u;
	}
	
	return z/2;
}