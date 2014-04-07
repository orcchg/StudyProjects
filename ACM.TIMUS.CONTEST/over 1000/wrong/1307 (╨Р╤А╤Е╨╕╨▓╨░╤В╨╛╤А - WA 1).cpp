#include <stdio.h>
#include <conio.h>
#include <cstring>

int main()
{
	char* s = new char[200002];
	int i = 0;
	
	while(!feof(stdin))
	{
		int c = getchar();
		if (c == 13)
		{
			s[i++] = (char)13;
		}
		else if (c == 10 || c == 13)
		{
			continue;
		}
		else
		{
			s[i++] = c;
		}
	}
	char ch = (char)39;
	
	printf("/*C*/\n");
	printf("#include<stdio.h>\n");
	printf("int main()\n");
	printf("{\nchar s[%d", (int)strlen(s));
	printf("] = \"%s", s);
	printf("\";\n");
	printf("\t\nfor(int i = 0; i < %d", (int)strlen(s));
	printf("; ++i)\n{\n\tif (s[i] == \'\\n\'");
	printf(")\n{\n\tprintf(\"\\n\");\n}\nelse\n{\n\tprintf(\"%cc",(char)37);
	printf("\", s[i]);\n}\n}");
	printf("\nreturn 0;\n}");
		
//	_getch();
	return 0;
}