#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
int a[25001];
int cmp (const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
} 
int main () 
{
    int N,i;
    scanf("%d",&N);
    for(i=0;i<N;i++)
        scanf("%d",&a[i]);
    qsort(a,N,sizeof(int),cmp);
    for(i=N-1;i>-1;i--)
        printf("%d ",a[i]);
//	_getch();
	return 0;
}
