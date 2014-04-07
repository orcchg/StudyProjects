#include <conio.h>
#include <cstdio>
#include "mergesort.h"

int Inv_Num(int* pA,int n){

	int y=0;
	int* lhs = new int[n];
	
	lhs = Merge_Sort(pA,n,y);
	
	delete [] lhs;
	return y;
}

int main(){
	
	int n,k=0,inv;
	printf("Enter n: ");
	scanf("%d",&n);
	
	int* ptr = new int[n];
	printf("\nEnter A[i], i from 1 to %d\n",n);
	
	while(k<n){
		printf("Enter A[%d",k+1);
		printf("]: ");
		scanf("%d",&ptr[k]);
		k++;
		printf("\n");
	}
	
	inv = Inv_Num(ptr,n);
	
	printf("\nNumber of inversions: %d",inv);
	delete [] ptr;
	_getch();
}