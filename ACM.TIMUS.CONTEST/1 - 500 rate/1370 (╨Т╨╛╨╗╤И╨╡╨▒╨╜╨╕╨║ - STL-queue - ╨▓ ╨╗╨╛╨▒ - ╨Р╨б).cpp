#include <stdio.h>
#include <conio.h>
#include <queue>
using namespace std;

int main()
{

	int N, M;
	
	scanf("%d%d", &N, &M);
	
	queue<int> q;
	
	int* P = new int[N];
	for(int i = 0; i < N; ++i)
	{
		scanf("%d", &P[i]);
		q.push(P[i]);
	}
	
	delete [] P;
	
	int temp;
	for(int i = 1; i <= M; ++i)
	{
		temp = q.front();
		q.pop();
		q.push(temp);
	}
	
	for(int i = 0; i < 10; ++i)
	{
		printf("%d", q.front());
		q.pop();
	}
	
//	_getch();
	return 0;
}