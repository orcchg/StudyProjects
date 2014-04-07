#include <conio.h>
#include <stdio.h>

//--------------------------------------------------
struct pair
{
	int val;
	int key;
};
//--------------------------------------------------

//--------------------------------------------------
void Bubble_Sort(pair* pA,int n){

	int x=0, v = 0;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n-i; j++){
			
			if(pA[j-1].key < pA[j].key){
				x = pA[j-1].key;
				v = pA[j-1].val;
				pA[j-1].key = pA[j].key;
				pA[j-1].val = pA[j].val;
				pA[j].key = x;
				pA[j].val = v;
			}
		}
	}
}
//--------------------------------------------------


//--------------------------------------------------
int main()
{
	int N;
	
	scanf("%d", &N);
	
	pair* Pair = new pair[N];
	
	for(int i = 0; i < N; ++i)
	{
		scanf("%d%d", &Pair[i].val, &Pair[i].key);
	}
	
	Bubble_Sort(Pair, N);
	
	for(int i = 0; i < N; ++i)
	{
		printf("%d %d\n", Pair[i].val, Pair[i].key);
	}
	
//	_getch();
	return 0;
}