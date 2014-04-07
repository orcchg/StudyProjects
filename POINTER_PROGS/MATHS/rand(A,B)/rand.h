#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "inverse.h"

const int LIM = RAND_MAX;

char* Rand(int N, int A, int B)
{
	char* str = new char[100];
	int R[N];
	char* ch = new char();
	
	for(int i = 0; i < N; i++) {
		R[i] = B*(double)rand()/LIM; //[0..B];
		if( R[i] < A) {
			R[i] += A;
		}
	}
	
	for(int i = 0; i < N; i++) {
		sprintf(ch,"%d",R[i]);
		str = strcat(str,ch);
		str = strcat(str," ");
	}
	
	delete ch;
	
	str = inverse(str,strlen(str));
	
/*	for(int i = 0; i < N; i++) {
		printf("%d  ",R[i]);
	}*/
	
	return ++str;
}