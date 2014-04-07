#include <iostream>
#include <conio.h>
using namespace std;

//---------------------------------------
const int nmax=110;

struct stack {

	int num;
	int info;
};

void del_S(stack vec[],int nmax){

	for(int i=0; i<nmax; i++){
		vec[i].num=0;
		vec[i].info=0;
	}
}

int emp_o_not(stack vec[],int nmax){

	int k=0;
	
	for(int i=0; i<nmax; i++)
		if(vec[i].info==0) k=1;
		
	return k;
}

void push(stack vec[],int nmax,int p){

	struct stack vec1[120];
	int k=1;
	
	for(int i=0; i<nmax; i++){
		vec1[i].info=vec[i].info;
		
		if(vec[i].num!=0 && i!=0)
			k++;
	}
	
	vec1[k-1].info=p;
	vec[k].num=k;
	
	for(int i=0; i<nmax; i++){
		vec[i].info=vec1[i].info;
	}
}

int pop(stack vec[],int nmax){

	int k=1;
	int res = 0;
	
	for(int i=0; i<nmax; i++){
		if(vec[i].num!=0 && i!=0)
			k++;
	}
	
	res = vec[--k].info;
	vec[k].info=0;
	vec[k].num=0;
	
	
	return res;
}
//---------------------------------------

int main()
{
	int N;
	
	cin >> N;
	
	stack** Array = new stack*[N];
	for(int i = 0; i < N; ++i)
	{
		Array[i] = new stack[N];
		del_S(Array[i], N);
	}
	
	int t = 0;
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j <= i; ++j)
		{
			push(Array[j], N, ++t);
		}
	}
	
/*	if (N >= 2) 
	{
		for(int i = N - 1; i > 1; --i)
		{
			for(int j = 0; j < N - 1; ++j)
			{
				pop(Array[i], N);
			}
		}
	}*/
	
	for(int i = 0; i < N; ++i)
	{
		for(int j = 0; j < N; ++j)
		{
			cout << pop(Array[i], N) << " ";
		}
		cout << endl;
	}

	
	
/*	for(int i = 0; i < N; ++i)
	{
		push(Array[N-1], N, i+1);
	}
	
	for(int i = 0; i < N; ++i)
	{
		cout << pop(Array[N-1], N) << " ";
	}
*/	
	_getch();
	return 0;
}