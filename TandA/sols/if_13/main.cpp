#include <conio.h>
#include <stdio.h>
#include <string.h>

//Rome numbers 1..100
/* I - 1
 * V - 5
 * X - 10
 * L - 50
 * C - 100
 * D - 500
 * M - 1000
 */
 
int main()
{
	int N;
	char ch[5] = {'I','V','X','L','C'};
	char* v = new char[10];
	char* s = new char[10];
	scanf("%d",&N);
	
	switch(N) {
		case 1:
		case 2:
		case 3: 
			for(int i = 1, i <=N; ++i) {
				sprintf(v,"%c",ch[0]);
				s = strcat(s,v);
			}
			break;
		case 4:
			sprintf(v,"%c%c",ch[0],ch[1]);
			s = strcat(s,v);
			break;
		case 5:
			sprintf(v,"%c",ch[1]);
			s = strcat(s,v);
			break;
		case 6:
		case 7:
		case 8:
			sprintf(v,"%c",ch[1]);
			s = strcat(s,v);
			for(int i = 1; i <= N-5; ++i) {
				sprintf(v,"%c",ch[0]);
				s = strcat(s,v);
			}
			break;
		case 9:
			sprintf(v,"%c%c",ch[0],ch[2]);
			s = strcat(s,v);
			break;
		case 10:
			sprintf(v,"%c",ch[2]);
			s = strcat(s,v);
			break;
		case 11:
		case 12:
		case 13:
			sprintf(v,"%c",ch[2]);
			s = strcat(s,v);
			for(int i = 1; i <= N-10; ++i) {
				sprintf(v,"%c",ch[0]);
				s = strcat(s,v);
			}
			break;
		case 
			
	}

	
	_getch();
	return 0;
}