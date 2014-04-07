#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

int main()
{
	FILE* fp;
	fp = fopen("test.txt", "r");
	
	if (!fp)
	{
		printf("No existing file!\n");
		exit(1);
	}
	
	int c;
	char* str = new char[1000];
//	while(!feof(fp))
	{
//		c = getc(fp);
//		putc(c, stdout);

//		str = fgets(str, 1001, fp);
//		fputs(str, stdout);

	}
	fread(str, 1001, 1, fp);
	fprintf(stdout, "%s", str, 1001);
	
	fflush(fp);
	fclose(fp);
	
	_getch();
	return 0;
}