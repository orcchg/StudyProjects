#include<iostream>
#include<conio.h>
using namespace std;

const int MAX=5000;
int iswas(char *, int);
int main()
{
        char line[MAX];
        int count;
        cout<<"Input the line: ";
        cin>>line;
        for(int i=0;line[i]!='\0';i++)
        {
            if(!iswas(line, i)) // проверка
            {
                       count=1;
                       cout<<line[i]<<" - ";
                for(int j=0;line[j]!='\0';j++)
                {
                    if(j==i)
                        continue;
                    if(line[j]==line[i])
                        count++;
                }
                cout<<count<<endl;
            }
        }
        getch();
 
        return 0;
}
int iswas(char * source, int nmbr)
{
        for(int i=0;i<nmbr;i++)
            if(source[i]==source[nmbr])
                return 1;
        return 0;
}