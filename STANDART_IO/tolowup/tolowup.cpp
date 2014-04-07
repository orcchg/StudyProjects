#include <conio.h>
#include <cstdio>
#include <ctype.h>

int main(int argc, char** argv){
	
	int c,ch;
	char* pS = argv[1];
	
	ch=*pS;
	{
		switch(ch){
		case 'L':
			while((c=getchar())!=EOF)
				putchar(tolower(c));
			break;
		
		case 'U':
			while((c=getchar())!=EOF)
				putchar(toupper(c));
			break;
		
		default:
			printf("Error!");
			break;
		}
	}
	
	_getch();
}