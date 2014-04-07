#include <conio.h>
#include <stdio.h>
#include "class_queue.hpp"

int main()
{
	Queue vec(3);
	int el,out,i=1,n;
	
	printf("Enter int elements: ");
	while(!feof(stdin)){
		printf("%d: ",i++);
		scanf("%d",&el);
		vec.enqueue(el);
		printf("\n");
	}
	i = 0;
	
	printf("Enter n to dequeue: ");
	scanf("%d",&n);
	printf("\n");
	
	while(i < n){
		out = vec.dequeue();
		printf("%d ",out);
		i++;
	}
	
	_getch();
}