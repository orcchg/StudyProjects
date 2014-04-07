#include <stdio.h>
#include <conio.h>

int main()
{
	char** pArr = new char*[100];
	for(int i = 0; i < 100; ++i) {
		pArr[i] = new char[1000];
	}
	
	int index = 0;
	int* Count = new int[100];
	for(int i = 0; i < 100; ++i) {
		Count[i] = 0;
	}
//------------------------------------------------
	
	while(!feof(stdin) && index < 100) {
		int j = 0;
		int c;		
		while((c = getchar()) != '0' && c != EOF && j < 1000) {
			pArr[index][j++] = c;
		}
		fflush(stdin); // Remove '\n' from i-sequence
		Count[index] = j;
		++index;
	}
	
	for(int i = 0; i < index; ++i) {
		for(int j = 0; j < Count[i]; ++j) {
			printf("%c", pArr[i][j]);
		}
		printf("\n");
	}
		
//------------------------------------------------		

	delete [] Count;	
	
	for(int i = 0; i < 100; ++i) {
		delete pArr[i];
	}
	delete [] pArr;
//------------------------------------------------	

	_getch();
	return 0;
}