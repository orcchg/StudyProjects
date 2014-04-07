#include <stdio.h>

void fill_rectangle(int w, int h);

int main()
{
	int w, h;
	scanf("%d", &w);
	scanf("%d", &h);
	fill_rectangle(w,h);
	return 0;
}
