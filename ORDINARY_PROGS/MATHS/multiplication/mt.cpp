#include <stdio.h>
#include <conio.h>

int main()
{
    int i, j, n; 
    printf ("¬ведите n: ");
    scanf ("%d", &n);

    for (i = 1; i <= n ; i++) {
        for (j = n; j > -n ; j--) {
             printf ("%05d", i * j);
        }
        printf("\n");
    }
	_getch();
    return 0;
}