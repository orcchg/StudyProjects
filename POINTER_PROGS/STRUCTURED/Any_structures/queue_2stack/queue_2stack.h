#include "stack.h"

void add(stack vec[],int nmax,int p);
void take_el(stack vec[],int nmax);

void add(stack vec[],int nmax,int p){

	push(vec,nmax,p);
}

void take_el(stack vec[],stack vec2[],int nmax){

	int k=1;
	
	push(vec2,nmax,pop(vec,nmax));
	
	for(int i=0; i<nmax; i++){
		if(vec2[i].num!=0 && i!=0)
			k++;
	}
	
	vec2[--k].info=0;
	vec2[k].num=0;
}
