#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "inverse.h"

const int LIM = RAND_MAX;

void swap(int&, int&);

char* Trans(int N,int base)
{
	char* str = new char[N*base];
	int R[N],temp=0;
	char* ch = new char();
	
	for(int i = 1; i <= N; i++) {
		R[i-1] = i;
	}
	
	for(int i = 0; i < N; i++) {
		temp = N*(double)rand()/LIM;
		if (temp < 1) {
			temp += 1;
		}
		swap(R[i],R[temp-1]);
	}
	
	for(int i = 0; i < N; i++) {
		sprintf(ch,"%d",R[i]);
		str = strcat(str,ch);
		str = strcat(str," ");
	}
	
	delete [] ch;
	
/*	for(int i = 0; i < N; i++) {
		printf("%d  ",R[i]);
	}*/
	
	return ++str;
}

void swap(int& rA, int& rB) {

	int temp = rA;
	rA = rB;
	rB = temp;
}