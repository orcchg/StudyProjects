#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <cstring>

using namespace std;
 
const int N = 250;      // phi(1000) порядка 1.e209
 
typedef unsigned char byte;
 
void add(byte a[N], byte b[N], byte c[N])
{
        byte    over = 0;
 
        for( int i = N - 1; i >= 0; i--)
        {
                c[i] = a[i] + b[i] + over;
 
                if( c[i] >= 10 )
                {
                        over = c[i] / 10;
                        c[i] = c[i] % 10;
                }
                else
                {
                        over = 0;
                }
        }
}
 
void phib(int n)
{
		int i = 0;
		
        byte fib0[N];
        byte fib1[N];
        byte fib2[N];
 
        for( int j = 0; j < N; j++)
        {
                fib0[j] = 0;
                fib1[j] = 0;
                fib2[j] = 0;
    }
 
        fib0[N - 1] = 1;
        fib1[N - 1] = 1;
 
        for( i = 2; i < n; i++ )
        {
                add( fib0, fib1, fib2 );
 
                memmove( fib0, fib1, sizeof(byte)*N );
                memmove( fib1, fib2, sizeof(byte)*N );
        }
 
        i = 0;
        while( fib2[i] == 0 ) i++;
        
        for( ; i < N; i++)
        {
                cout << setw(1) << char('0' + fib2[i]);
        }
        cout << endl;
}