//Stack

#include <stdio.h>
#include <conio.h>
#include "stack.h"

int main(){

	struct stack vec[nmax] ;
	int p,k,d;
	char ch;
	int t;

	printf("Stack release based on vector\n");

	del_S(vec,nmax) ;
	k=emp_o_not(vec,nmax);
	if (k==1) printf("Stack is empty\n");

	printf("How many elements push?: ");
	scanf("%i",&t);
	for(int i=0;i<t;i++){
		printf("Enter the element: ");
		scanf("%i",&k);
		vec[i].info=k;
		vec[i].num=i;
	}

	for (int i=0;i<t;i++)
		printf("%i ",vec[i].info);
		
	printf("\n");
	printf("How many elements push?: ");
	scanf("%i",&d);
	
	printf("Enter the elements: ");
	for(int i=0;i<d;i++){
		scanf("%i",&p);
		push(vec,nmax,p) ;
	}
	
	t=t+d;
	for (int i=0;i<t;i++)
		printf("%i ",vec[i].info);
		
	printf("\nHow many elements delete?: ");
	scanf("%i",&d);
	
	printf("\n Delete processing... ");
	for(int i=0;i<d;i++)
		pop(vec,t);	
//	t=t-d;
	
	printf("\nPrint stack processing.....\n");
		for (int i=0;i<t;i++)
		printf("%i ",vec[i].info);
		
_getch();
}