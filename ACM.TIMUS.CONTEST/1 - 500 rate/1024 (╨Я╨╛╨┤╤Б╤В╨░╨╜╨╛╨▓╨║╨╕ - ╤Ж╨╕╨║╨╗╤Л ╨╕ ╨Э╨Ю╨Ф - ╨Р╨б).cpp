#include <stdio.h>
int gcd(int x, int y)
{
    int temp;
    if (x < y)
    {
        temp = x;
        x = y;
        y = temp;
    }
    while (y > 0)
    {
        temp = x%y;
        x = y;
        y = temp;
    }
    return x;
}
int n, p[1001], k2, k;
int main()
{
    int i, t;
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    t = p[1];
    while (t != 1)
    {
        k++;
        t = p[t];
    }
    k++;
    for (i = 2; i <= n; i++)
    {
        t = p[i];
        k2 = 0;
        while (t != i)
        {
            k2++;
            t = p[t];
        }
        k2++;
        k = k/gcd(k, k2)*k2;
    }
    printf("%d", k);
    return 0;
}