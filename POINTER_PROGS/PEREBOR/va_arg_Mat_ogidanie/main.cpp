#include <conio.h>
#include <stdio.h>
#include <stdarg.h>

double avg(int n, ...);

int main()
{
	double x;
	
	printf("Keep inputting double numbers: 0 - to exit\n\n");
	while(1)
	{
		scanf("%lf",&x);
		if (x == 0)
		{
			break;
		}
		////////

	_getch();
	return 0;
}

double avg(int n, ...)
{
	va_list ap;
	double res = .0L;
	
	va_start(ap, n);
	
	for(int i = 0; i < n; ++i)
	{
		res += va_arg(ap, double);
	}
	
	va_end(ap);
	
	if (n > 0)
	{
		return res/n;
	}
	else
	{
		printf("\nArgument error!");
		exit(0);
	}
}
	