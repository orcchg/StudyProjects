#include <iostream>
#include <conio.h>
#include <stdio.h>
using namespace std;

int main()
{
    __int64 n=1;
    double h=1.0;
    double s=0;
    __int64 N; 
	double M;
    double k=0;
    double d1;
    __int64 d;
	
    cin>>N;cin>>M;
	
    if(M>N)
    {
	  cout<<N;
      return 0;
    }

    k=N / M - 1;
    for( ; ; n++)
    {
        s=s + h / (2 * n + 1);
        if (s > k)
            break;
    }
	
    d1=( ((k - s) * (2 * n + 1) + 1) * M + n * M );
	
    d=(__int64)(d1);
	
    if(d1-d>0)
        d=d+1;
		
        cout<<d;
        return 0;

}