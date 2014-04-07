#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "bubblesort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
#include "selectionsort.h"
#include "out.h"
using namespace std;

#define eof -1
#define MAXLEN 1000

int main(){

	int j=0,key,size;
	int A[MAXLEN];
	char c,s[MAXLEN];
	bool exit=false;
	int* pA;
	
	LABEL: size = 0;
		   j = 0;
	
	cout << "Enter Size: ";
	cin >> size;
	cout << "\nEnter Array: ";
	
		do {
			cin >> A[j];
			j++;
		} while(j < size);
	
	Out(A,j);
	
	printf("Choose Sort: \nB - bubble\nI - insertion\nM - merge\nQ - quick\nS - selection\nA - input again\nZ - exit\n: ");
	
	for(;;){
		if((key = getchar())!='\n'){
		
		switch(key){
			case 'A':
				goto LABEL;
				break;
			case 'B':
				Bubble_Sort(A,j);
				Out(A,j);
				break;
			case 'I':
				Insertion_Sort(A,j);
				Out(A,j);
				break;
			case 'M':
				pA = Merge_Sort(A,j);
				Out(pA,j);
				break;
			case 'Q':
				Quick_Sort(A,j);
				Out(A,j);
				break;
			case 'S':
				Selection_Sort(A,j);
				Out(A,j);
				break;
			case 'Z':
				exit = true;
				break;
			default:
				printf("Error choise!\n");
				break;
			}
		}
		if(exit)
			break;
	}
}
				