#include <cstdio>

int main(){

	int c,a=0;
	
	do {
	c = getchar();
		if(c == '(')
			a++;
		else if (c == ')')
				if( --a < 0)
					break;
	} while (c != '\n');
	
	if( a == 0)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
