#include<iostream>
using namespace std;
int main()
{
    int flag[3] = {0};
    int b,r,y;
    cin>>b>>r>>y;
    int n,i,j,k;
    char str[3][10];
    cin>>n;
    i=0;
    while(i<n)
        cin>>str[i++];
    for(i=0;i<n;i++)
    {
        if(str[i][0]=='B'||str[i][0]=='b')
            flag[0]=1;
        if(str[i][0]=='R'||str[i][0]=='r')
            flag[1]=1;
        if(str[i][0]=='Y'||str[i][0]=='y')
            flag[2]=1;
    }
    int sum=1;
    if(flag[0]==1)
        sum*=b;
    if(flag[1]==1)
        sum*=r;
    if(flag[2]==1)
        sum*=y;
    cout<<sum<<endl;
    return 0;
}