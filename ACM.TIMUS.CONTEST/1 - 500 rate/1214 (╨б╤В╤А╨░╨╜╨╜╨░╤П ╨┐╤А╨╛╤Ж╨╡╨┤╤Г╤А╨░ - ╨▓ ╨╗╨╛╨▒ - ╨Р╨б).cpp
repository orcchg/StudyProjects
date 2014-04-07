#include <stdio.h>
#include <conio.h>

/*//------------------------------------
#include <math.h>
void P(__int64& x, __int64& y)
{
  int i, j;
  if (x>0 && y>0)
  {
    for (i = 1; i <= x+y; i++)
    {
      y = x*x+y;
      x = x*x+y;
      y = sqrt(x+(y/fabs(y))*(-fabs(y)));
      for (j = 1; j <= 2*y; j++)
        x = x-y;
    }
  }
}
//------------------------------------*/

int main()
{
	__int64 x, y;

	scanf("%I64d%I64d", &x, &y);
	
	if (x < 0 || y < 0)
	{
		printf("%I64d %I64d\n", x , y);
		return 0;
	}
	
	if (x*y % 2 == 1)
	{
		printf("%I64d %I64d\n", x , y);
		return 0;
	}
	
	if (x % 2 == 0)
	{
		if (y % 2 == 0)
		{
			printf("%I64d %I64d\n", x , y);
			return 0;
		}
		else
		{
			printf("%I64d %I64d\n", y , x);
			return 0;
		}
	}
	
	if (y % 2 == 0)
	{
		printf("%I64d %I64d\n", y , x);
		return 0;
	}	
	
//	_getch();
	return 0;
}