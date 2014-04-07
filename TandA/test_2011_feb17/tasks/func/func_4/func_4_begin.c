#include <stdio.h>

void draw_rectangle(int w, int h, char c);

int main()
{
	int w, h, c;
	scanf("%d", &w);
	scanf("%d", &h);
	getchar();
	c = getchar();
	draw_rectangle(w,h, c);
	return 0;
}
