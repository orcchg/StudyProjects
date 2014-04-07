#include <conio.h>
#include <stdio.h>
#include "class_stack.hpp"

int main()
{
	Stack vec(3);
	int i;
	
	while(!feof(stdin)){
		int c = getchar();
		int x;
		int temp1,temp2,temp3;
		
		switch(c){
			case EOF: break;
			case '\n':
			case ' ': break;
			case '=': printf("Result = %d\n",vec.pop()); break;
			case 27: goto RESULT; //27 = '<-'; backspace
			case '+': vec.push(vec.pop() + vec.pop()); break;
			case '-': vec.push(-vec.pop() + vec.pop()); break;
			case '*': vec.push(vec.pop() * vec.pop()); break;
			case '/': temp1 = vec.pop();
					  temp2 = vec.pop();
					  temp3 = temp2/temp1;
					  vec.push(temp3);
					  break;
			default:
				ungetc(c, stdin);
				if(scanf("%d",&x)!=1) {
					fprintf(stderr, "Can't read integer!\n");
					return -1;
				} else {
					vec.push(x);
				}
				break;
		}
	}
	
	RESULT: i = 0;
			while(!vec.empty()) {
				printf("Stack[%d] = %d\n",i,vec.pop());
				i++;
			}
	_getch();
	return 0;
}	