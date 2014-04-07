//Queue on 2 stacks

#include <stdio.h>
#include <conio.h>
#include "queue_2stack.h"

int main(){

	struct stack vec[nmax] ;
	struct stack vec2[nmax] ;
	int p,k,d;
	char ch;
	int t;

	printf("Queue release based on vector\n");

	del_S(vec,nmax) ;
	del_S(vec2,nmax) ;
	k=emp_o_not(vec,nmax);
	if (k==1) printf("Queue is empty\n");

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
		add(vec,nmax,p) ;
	}
	
	t=t+d;
	for (int i=0;i<t;i++)
		printf("%i ",vec[i].info);
		
	printf("\nHow many elements delete?: ");
	scanf("%i",&d);
	
	printf("\n Delete processing... ");
	for(int i=0;i<d;i++)
		take_el(vec,vec2,t);	
	t=t-d;
	
	printf("\nPrint queue processing.....\n");
		for (int i=0;i<t;i++)
		printf("%i ",vec2[i].info);
		
_getch();
}