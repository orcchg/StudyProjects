#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "class_stack.hpp"
#include "power.h"

#define MAXLEN 1000
#define MAXLIM 100

int main()
{
	char* s1 = new char[MAXLEN];
	char* s2 = new char[MAXLEN];
	long set1[MAXLIM],set2[MAXLIM];
	int j=0,k=0,u1=0,u2=0;
	int count1=0,count2=0;
	
	Stack vec1(5),vec2(5);
	
	printf("Enter set 1; Ctrl+Z to stop: ");
	scanf("%s",s1);
	
	for(int i=0; s1[i]!=EOF; i++) u1++;
	fflush(stdin);
	
	printf("Enter set 2; Ctrl+Z to stop: ");
	scanf("%s",s2);

	for(int i=0; s2[i]!=EOF; i++) u2++;	
	fflush(stdin);
	
	printf("%d %d\n",u1,u2);
	
	for(int i=0; i<u1; i++) {
		if(s1[i] >= '0' && s1[i] <= '9') {
			vec1.push(s1[i]-'0');
			count1++;
		} else { 
			for(int q=0; q<count1; q++)
				set1[j++] += vec1.pop()*power(q,10);
		}
	}
	
	for(int i=0; i<u2; i++) {
		if(s2[i] >= '0' && s2[i] <= '9') {
			vec2.push(s2[i]-'0');
			count2++;
		} else { 
			for(int p=0; p<count2; p++)
				set2[k++] += vec2.pop()*power(p,10);
		}
	}
	
	for(int i=0; i<j; i++) {
		printf("%ld",set1[i]);
	}
	printf("\n");
	for(int i=0; i<k; i++) {
		printf("%ld",set2[i]);
	}
	
	_getch();
}