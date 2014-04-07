#include <conio.h>
#include "getword.h"
#include "tree.h"

#define MAXWORD 100

int main(){

	int temp;
	int STRCOUNT=0;
	struct tnode *root;
    char word[MAXWORD];
	
	do {
		while((temp=getword(word,MAXWORD))!=EOF){
			if(temp != '\n'){
				root = add(root, word, STRCOUNT);
			} else 	
				printf("else-state\n");
				STRCOUNT++;
		}		
	} while (STRCOUNT < MAXLINE);
	
	Print(root);
	_getch();
	return 0;
}