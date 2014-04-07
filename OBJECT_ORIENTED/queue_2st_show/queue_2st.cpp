#include <conio.h>
#include <cstdio>
#include "class_stack.hpp"

int main()
{
	Queue queue(3);
	int el,i=1,n,out;
	
	printf("Enter int elements; Ctrl+Z to stop: \n");
	while(!feof(stdin)){
		printf("%d: ",i++);
		scanf("%d",&el);
		queue.enqueue(el);
	}
	out = queue.s1.pop(); //POP Ctrl+Z
	i=0;
	
	printf("Enter n to pop: ");
	scanf("%d",&n);
	fflush(stdin);
	
	while(i<n){
		out = queue.dequeue();
		printf("%d ",out);
		i++;
	}
		
	_getch();
}