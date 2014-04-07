#include <iostream>
using namespace std;

int main()
{
	int S = 0,n;

    cin>>n;
    if(n==0)S=1;
    if(n>0)S=(n+1)*n/2;
    if(n<0)
    {
        n=n*(-1)+2;    S=(3-n)*n/2;
    }
    cout<<S<<endl;
    return 0;
}