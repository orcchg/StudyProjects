#include <conio.h>
#include <cstdio>
#include "class_deck.hpp"

int main()
{
	Deck vec(3);	
	int el,out,i=1,n,N;
	
	printf("Enter int elements to Tail; Ctrl+Z to stop: ");
	while(!feof(stdin)){
		printf("%d: ",i++);
		scanf("%d",&el);
		vec.add_tail(el);
		printf("\n");
	}
	N = i-2;
	i = 1;
	out = vec.take_tail(); //POP Ctrl+Z
	
	ungetc(EOF,stdin);
	printf("Number of els add to Head == Number of els add to Tail! N: %d\n",N);
	printf("Enter int elements to Head: \n");
	while(i<=N){
		printf("%d: ",i++);
		scanf("%d",&el);
		vec.add_head(el);
		printf("\n");
	}
	i = 0;
	
	printf("Enter n to take: ");
	scanf("%d",&n);
	
	printf("\nFrom Tail: \n");
	while(i < n){
		out = vec.take_tail();
		printf("%d ",out);
		i++;
	}	
	i = 0;
	
	printf("\nFrom Head: \n");
	while(i < n){
		out = vec.take_head();
		printf("%d ",out);
		i++;
	}
	
	_getch();
}