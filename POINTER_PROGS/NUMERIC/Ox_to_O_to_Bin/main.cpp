#include <conio.h>
#include <stdio.h>
#include <iostream>
#include "B16toB10.h"
#include "B8toB10.h"
#include "B2toB10.h"
#include "B10toB16.h"
#include "B10toB8.h"
#include "B10toB2.h"

#include "B8toB16.h"
#include "B8toB2.h"
#include "B2toB16.h"
#include "B2toB8.h"
#include "B16toB8.h"
#include "B16toB2.h"

#define MAXLEN 100

int B16_to_B10(char*);
int B8_to_B10(char*);
int B2_to_B10(char*);
char* B10_to_B16(int);
char* B10_to_B8(int);
char* B10_to_B2(int);

char* B8_to_B16(char*);
char* B8_to_B2(char*);
char* B2_to_B16(char*);
char* B2_to_B8(char*);
char* B16_to_B8(char*);
char* B16_to_B2(char*);

int main()
{
	int N;
	char* N16 = new char[MAXLEN];
	char* N8 = new char[MAXLEN];
	char* N2 = new char[MAXLEN];
	char* NB10toB16 = 0;
	char* NB10toB8 = 0;
	char* NB10toB2 = 0;
	
	char* NB8toB16 = 0;
	char* NB8toB2 = 0;
	char* NB2toB16 = 0;
	char* NB2toB8 = 0;
	char* NB16toB8 = 0;
	char* NB16toB2 = 0;
	
	/************************************************/
	
	printf("Enter N16: ");
	scanf("%s",N16);
	printf("16->10: %d\n",B16_to_B10(N16));
	
	printf("Enter N8: ");
	scanf("%s",N8);
	printf("8->10: %d\n",B8_to_B10(N8));
	
	printf("Enter N2: ");
	scanf("%s",N2);
	printf("2->10: %d\n",B2_to_B10(N2));
	
	/************************************************/
	
	printf("Enter N: ");
	scanf("%d",&N);
	NB10toB16 = B10_to_B16(N);
	printf("10->16: %s\n",NB10toB16);
	delete NB10toB16;
	
	NB10toB8 = B10_to_B8(N);
	printf("10->8: %s\n",NB10toB8);
	delete NB10toB8;
	
	NB10toB2 = B10_to_B2(N);
	printf("10->2: %s\n",NB10toB2);
	delete NB10toB2;
	
	/************************************************/
	
	NB8toB16 = B8_to_B16(N8);
	printf("8->16: %s\n",NB8toB16);
	delete NB8toB16;
	
	NB8toB2 = B8_to_B2(N8);
	printf("8->2: %s\n",NB8toB2);
	delete NB8toB2;
	
	NB2toB16 = B2_to_B16(N2);
	printf("2->16: %s\n",NB2toB16);
	delete NB2toB16;
	
	NB2toB8 = B2_to_B8(N2);
	printf("2->8: %s\n",NB2toB8);
	delete NB2toB8;
	
	NB16toB8 = B16_to_B8(N16);
	printf("16->8: %s\n",NB16toB8);
	delete NB16toB8;
	
	NB16toB2 = B16_to_B2(N16);
	printf("16->2: %s\n",NB16toB2);
	delete NB16toB2;
	
	/************************************************/
	
	delete N16;
	delete N8;
	delete N2;
	
	_getch();
}