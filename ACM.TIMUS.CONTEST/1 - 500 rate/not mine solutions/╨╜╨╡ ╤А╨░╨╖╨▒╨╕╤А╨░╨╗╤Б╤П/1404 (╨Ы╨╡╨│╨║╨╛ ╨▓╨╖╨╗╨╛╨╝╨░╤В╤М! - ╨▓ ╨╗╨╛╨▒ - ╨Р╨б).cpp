#include<iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

int main()
{
    int step1[100];
    int step3[100];
    char step4[100];
    
    int i, temp;
    
    gets(step4);
    for(i=0;i<strlen(step4);i++)
        step3[i]=static_cast<int>(step4[i])-'a';
        
    step3[0]=step3[0]+26;
    for(i=1;i<strlen(step4);i++)
    {
        while(step3[i]<step3[i-1])
            step3[i]=step3[i]+26;
    }
    
    temp=5;
    for(i=0;i<strlen(step4);i++)
    {
        step1[i]=(step3[i]-temp)%26;
        temp=step3[i];
    }
    for(i=0;i<strlen(step4);i++)
    {
        cout<<static_cast<char>(step1[i]+'a');
    }
    cout<<endl;
    return 0;
}