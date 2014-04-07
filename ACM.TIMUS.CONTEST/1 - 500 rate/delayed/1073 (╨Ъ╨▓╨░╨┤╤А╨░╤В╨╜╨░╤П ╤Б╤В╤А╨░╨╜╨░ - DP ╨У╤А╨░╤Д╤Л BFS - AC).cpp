/* USE GRAPHS - DP; BFS method
 *
 * Every number from 1 to N is the vertex of graph; 
 *
 * Let image graph where every number is vertex, then we can add edge from a to b 
 * if a+SQ=b (where SQ - some square). Now you can see graph, there maximum 60000 
 * vertex and maximum ~ 60000*300 = 18 000 000 edges, out task is find way from 0 
 * to given number. BFS will done this in O(N+M)
 */
 
#include <iostream>
#include <cmath>
using namespace std;

int data[60001];

int main()
{
    int n;
    cin>>n;
	
    data[1]=1;
    data[2]=2;
	
    for (int i=3;i<=n;++i) 
	{
        int min=data[i-1]+1;
		
        for (int j=2;j<=245;++j) 
		{
            if (i>=j*j) 
			{
               if (min>data[i-j*j]+1) 
			   {
					min=data[i-j*j]+1;
			   }
            }
            else break;
        }
        data[i]=min;
    }
    cout<<data[n];
	
    return 0;
}