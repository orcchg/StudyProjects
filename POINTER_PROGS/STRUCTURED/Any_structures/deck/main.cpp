//Deck

#include <stdio.h>
#include <conio.h>
#include <iostream>
#include "deck.h"

void service_add(int d,int p, stack vec[],int nmax);
void service_push(int d,int p, stack vec[],int nmax);

int main(){

	struct stack vec[nmax] ;
	int p,k,d;
	char ch;
	int t;

	printf("Deck release based on vector\n");

	del_S(vec,nmax) ;
	k=emp_o_not(vec,nmax);
	if (k==1) printf("Deck is empty\n");

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
	
	printf("\nINPUT: Choose Head 'H' or Tail 'T' to add new elements: ");
LABEL:  std::cin >> ch;
		switch(ch){
			case 'H':
				service_add(d,p,vec,nmax);
			break;
			
			case 'T':
				service_push(d,p,vec,nmax);
			break;
			
			default:
				printf("Wrong command! Try again: ");
				std::cin.clear();
				goto LABEL;
		}
		
	t=t+d;
	for (int i=0;i<t;i++)
		printf("%i ",vec[i].info);
		
	printf("\nHow many elements delete?: ");
	scanf("%i",&d);	
		
	printf("\nDELETE: Choose Head 'H' or Tail 'T' to delete elements: ");	
LABEL1:  std::cin >> ch;
		 switch(ch){
			case 'H':	
				printf("\n Delete processing... ");
				for(int i=0;i<d;i++)
					take_el_head(vec,t,i);	
			break;
			
			case 'T':
				printf("\n Delete processing... ");
				for(int i=0;i<d;i++)
					pop(vec,t);	//or take_el(vec,t);
			break;
			
			default:
				printf("Wrong command! Try again: ");
				std::cin.clear();
				goto LABEL1;
		}
				
//	t=t-d;			
	printf("\nPrint deck processing.....\n");
		for (int i=0;i<t;i++)
		printf("%i ",vec[i].info);
		
_getch();
}

void service_add(int d,int p, stack vec[],int nmax){

	printf("Enter the elements: ");
	
		for(int i=0;i<d;i++){
			scanf("%i",&p);
			add(vec,nmax,p) ;
		}
}

void service_push(int d,int p, stack vec[],int nmax){

	printf("Enter the elements: ");
		for(int i=0;i<d;i++){
			scanf("%i",&p);
			push(vec,nmax,p) ;
		}
}