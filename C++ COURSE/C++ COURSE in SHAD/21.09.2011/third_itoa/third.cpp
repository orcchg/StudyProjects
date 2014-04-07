#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using std::cin;
using std::cout;
using std::endl;

const int MAX = 1000;

void reverse(char s[], int length){
	int TEMP, i, j, k = 0;
	for(i = 0, j = length - 1; i < j; i++, j--){
		TEMP = s[i];
		s[i] = s[j];
		s[j] = TEMP;
	}
	while(k <= length - 1){
		cout << s[k];
		k++;
	}
}

void itoa(int N){

	char s[MAX];
	int i,SIGN;
	
	if ((SIGN = N) < 0) {
		N =- N; 
	}
	
	i = 0;
	do {
		s[i++] = N % 10 + '0';
	} while ((N /= 10) > 0);
	
	if (SIGN < 0) {
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s, i);
}



int main() {

	int i = 0;
	char c;
	char s[MAX];
	
	while((c = getchar()) >= '0' || c <= '9' && i <= MAX && c != EOF && c != '\n') {
		s[i] = c;
		i++;
	}
	itoa(atoi(s));
	
	_getch();
	return 0;
}