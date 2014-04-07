# include <string.h>
# include <iostream>
using namespace std;

int main()
{
    char a[128][32];
    int N,i,j,k,h;
    cin>>N;
    if (0<=N && 100>=N)
    {
        for (i=0;i<N;i++)
            cin >>a[i];
        for (i=0;i<N;i++)
        {
            k=0;
            for (j=0;j<N;j++)
            {
                if (strcmp(a[i],a[j])==0)
                    k++;
            }
            if (k>=2)
            {
                h=0;
                for(j=0;j<i;j++)
                {
                    if(strcmp(a[i],a[j])!=0)
                        h++;
                }
                if (h==i)
                    cout<< a[i]<<endl;
            }
        }
    }
    return 0;
}