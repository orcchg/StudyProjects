#include <conio.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "stack_add.h"

#define MAXLEN 1000

/* {'(','[','{','<',')',']','}','>'}
 * b10 = '(' = 1
 * b20 = '[' = 2
 * b30 = '{' = 3
 * b40 = '<' = 4
 * b11 = ')' = 5
 * b21 = ']' = 6
 * b31 = '}' = 7
 * b41 = '>' = 8
 */
int Get_Open(bra bracket){
	
	switch(bracket){
		case b11: //')' = 5 ; '(' = 1
			return 1;
		case b21: //']' = 6 ; '[' = 2
			return 2;
		case b31: //'}' = 7 ; '{' = 3
			return 3;
		case b41: //'>' = 8 ; '<' = 4
			return 4;
		default:
			return -1;
	}
}

int Bra_to_Int(bra bracket){
	
	switch(bracket){
		case nil:
			return 0;
		case b10: //'('
			return 1;
		case b20: //'['	
			return 2;
		case b30: //'{'
			return 3;
		case b40: //'<'
			return 4;
		case b11: //')'
			return 5;
		case b21: //']'
			return 6;
		case b31: //'}'
			return 7;
		case b41: //'>'
			return 8;
		default:
			return -1;
	}		
}			

bra Char_to_Bra(char ch){

	bra bracket = nil;
	
	switch(ch){
		case '(':
			return b10;
		case '[':	
			return b20;
		case '{':
			return b30;
		case '<':
			return b40;
		case ')':
			return b11;
		case ']':
			return b21;
		case '}':
			return b31;
		case '>':
			return b41;
		default:
			return nil;
	}		
}			

int Parse(char* s,int len){

	int i,Res=0;
	bra el;
	int elI=0;
	stack vec[nmax];
	
	del_S(vec,nmax);
	printf("Stack Empty?: %d\n",empty(vec));
	printf("Stack Full?: %d\n",full(vec,nmax));
	
	for(i = 0; i < len; i++){
		if(s[i] == '(' || s[i] == '[' || s[i] == '{' || s[i] == '<'){ //open bracket
			push(vec,nmax,Char_to_Bra(s[i]));
			std::cout <<" push "<< i <<" "<<Res<< std::endl;
		} else if(s[i] == ')' || s[i] == ']' || s[i] == '}' || s[i] == '>'){ //close bracket
			el = pop(vec,nmax);
			elI = Bra_to_Int(el);
			std::cout <<" pop "<< i <<" "<<Res<< std::endl;
			if(elI != Get_Open(Char_to_Bra(s[i]))){
				Res = i;
			}
		}
	}
	
	if(Res == 0)
		if(!empty(vec))
			Res = 1;
	
	std::cout<<Res<<std::endl;
	return Res;
}

int main(){

	char brch;
	int Res,i=0;
	
	char s[MAXLEN];
	
	while((brch=getchar())!='\n' && brch!=EOF){
		s[i++] = brch;
	}
	
	Res = Parse(s,i);
	if(Res == 0) printf("Success!\n");
	else printf("Failure!\n");

	_getch();	
	return 0;
}
			