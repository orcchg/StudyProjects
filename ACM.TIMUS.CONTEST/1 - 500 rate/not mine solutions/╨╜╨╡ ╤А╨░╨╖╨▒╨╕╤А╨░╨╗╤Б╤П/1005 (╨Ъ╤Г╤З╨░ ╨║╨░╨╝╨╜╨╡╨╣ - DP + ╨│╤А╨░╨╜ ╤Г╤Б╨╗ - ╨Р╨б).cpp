#include<iostream>
#include<stdlib.h>
using namespace std;
int main(void)
{
    int input,weight,temp,i;
    long int sum=0;
    cin>>input;
    if(input<1 && input>21)
        exit(0);
    int ary[20];
    for(i=0;i<input;i++)
    {
        cin>>weight;
        if(weight>=1 && weight<=100000)
        {
            ary[i]=weight;
            sum+=weight;
        }
    }
    for(i=0;i<input-1;i++)
    {
        for(int j=0;j<input-i-1;j++)
        {
            if(ary[j]>ary[j+1])
            {
                temp=ary[j];
                ary[j]=ary[j+1];
                ary[j+1]=temp;
            }
        }
    }
    int x=input-1;
    if(x==0)
    {
        cout<<ary[x];
        exit(0);
    }
    long int k1,k2,middle;
    middle=sum/2;
    k2=ary[x];
    k1=ary[x-1];
    int r=0;
    int bol=0;
    for(i=input-3;i>=r;)
    {
        if((k1+k2)<=middle)
        {
            k2=k1+k2;
            k1=ary[i];
            i--;
        }
        else if(k1<k2)
        {
            if(bol==0)
            {
            k1+=ary[r];
            r++;
            bol=1;
            }
            else
            {
                k1+=ary[i];
                bol=0;
                i--;
            }
        }
        else 
        {
            if(bol==0)
            {
            k2+=ary[r];
            r++;
            bol=1;
            }
            else
            {
                k2+=ary[i];
                bol=0;
                i--;
            }
        }
    }
    if(k2>k1)
        cout<<k2-k1;
    else
        cout<<k1-k2;
    return 0;
}