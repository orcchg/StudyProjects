#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

int n, k, a[100001], nr[101];
char s[4];

int cmp (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}


int main() {

    long i = 0;
    scanf("%ld", &n);
    for (i = 1; i <= n; ++i) {
        scanf("%ld", &a[i - 1]);
    }
    scanf("%s", s);
    scanf("%ld", &k);
    qsort(a, n, sizeof(int), cmp);
    for (i = 1; i <= k; ++i) {
        scanf("%ld", &nr[i]);
 //       printf("%ld\n", a[nr - 1]);
    }
	
	for (i = 1; i <= k; ++i)
	{
		printf("%ld\n", a[nr[i] - 1]);
	}
//	_getch();
    return 0;
}