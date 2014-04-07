#pragma comment(linker, "/STACK:16777216")

#include <iostream>
#include <conio.h>
using namespace std;

//--------------------------------------------------------------------------------
const int nmax=110;

struct queue {

	int num;
	int info;
};

void del_Q(queue vec[],int nmax){ //сделать очередь пустой

	for (int i=0;i<nmax;i++){ 
			vec[i].num=0;
			vec[i].info=0;
	}
}

int emp_o_not(queue vec[],int nmax){ //очередь пуста/непуста

	int k=0;
	
	for (int i=0;i<nmax;i++)
		if (vec[i].info==0) k=1;
		
	return k;
}

void add(queue vec[],int nmax,int p){ //добавить элемент в очередь

	struct queue vec1[120];

	for (int i=1;i<nmax;i++)
		vec1[i].info=vec[i-1].info;

	vec1[0].info=p;
	vec[0].num=0;

	for (int i=0;i<nmax;i++){ 
		vec[i].info=vec1[i].info;
		vec[i].num=i;
	}
}

int take_el(queue vec[],int nmax){

	int k=1;
	int inf = 0;
	
	for(int i=0; i<nmax; i++){
		if(vec[i].num!=0 && i!=0)
			k++;
	}

	inf = vec[--k].info;
	vec[k].info=0;
	vec[k].num=0;
	
	return inf;
}
//--------------------------------------------------------------------------------



int main()
{
	int N;
	
	cin >> N;
	
	int** pA = new int*[N];
	
	queue** Array = new queue*[N];
	
	for(int i = 0; i < N; ++i)
	{
		pA[i] = new int[N];
		Array[i] = new queue[N];
		del_Q(Array[i], N);
	}
	

//---------------------------------------------------------------------------------		
	
	
	for(int j = 0; j < N; ++j)
	{
		for(int i = 0; i < N; ++i)
		{
			cin >> pA[j][i];
			add(Array[j], N, pA[j][i]);
		}
	}
	

//---------------------------------------------------------------------------------	
//------------------- POP FROM (0,0) TILL LAST REVERSE DIAGONAL -------------------	


	for(int i = 0; i < N; ++i)
	{
		for(int j = i; j >= 0; --j)
		{
			cout << take_el(Array[j], N) << " ";
		}
	}

	
//---------------------------------------------------------------------------------	
//------------------- POP THE REST ELEMENTS IN REVERSE ORDER -------------------	


	for(int i = 0; i < N - 1; ++i)
	{
		for(int j = N - 1; j >= i + 1; --j)
		{
			cout << take_el(Array[j], N) << " ";
		}
	}

//---------------------------------------------------------------------------------	


//	_getch();
	return 0;
}