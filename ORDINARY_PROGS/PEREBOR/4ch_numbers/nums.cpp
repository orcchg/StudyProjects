#include <conio.h>
#include <stdio.h>

int main()
{
	int NUM=1000;
	int N=0,s[4],SUM=0;
	
	printf("Enter 0<N<37: ");
	scanf("%d",&N);
	fflush(stdin);
	
	for(int i=0; i<9000; i++) {
		s[0] = NUM / 1000;
		s[1] = (NUM - 1000*s[0]) / 100;
		s[2] = (NUM - 1000*s[0] - 100*s[1]) / 10;
		s[3] = NUM - 1000*s[0] - 100*s[1] - 10*s[2];
		SUM = s[0]+s[1]+s[2]+s[3];
//		printf("%d\n",SUM);
//		printf("%d%d%d%d\n",s[0],s[1],s[2],s[3]);
		if(SUM == N)
			printf("%d%d%d%d\n",s[0],s[1],s[2],s[3]);
		NUM += 1;
		s[0] = 0;
		s[1] = 0;
		s[2] = 0;
		s[3] = 0;
	}
	
	_getch();
}