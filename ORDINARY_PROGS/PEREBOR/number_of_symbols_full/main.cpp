#include <conio.h>
#include <stdio.h>
	
#define MAXLIM 1000 // INPUT STRING MAX LENGTH	
#define MAXCHAR 256 // ANY ASCII CHAR
	
int main()
{
	int c;
	int i = 0, p = 0;
	int count[MAXLIM];
	char s[MAXLIM];
	
	for(int j = 0; j < MAXCHAR; ++j)
	{
		count[j] = 0;
	}
	
	while((c=getchar())!=EOF) 
	{
		s[i]=c;
		count[(int)c] += 1;
		i++;
	}	
	
	while(p < MAXCHAR) 
	{
		if (count[p]) 
		{
			printf("%d:  %c ->%d\n",p,(char)p,count[p]);
		}
		++p;
	}
	
	_getch();
	return 0;
}