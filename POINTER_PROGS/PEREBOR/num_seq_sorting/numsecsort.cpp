#include <stdio.h>
#include <conio.h>

//------------------------------------------------
void Insertion_Sort(char* pA,int n){

	int i;
	char key;

	for(int j = 1; j < n; j++){
		key = pA[j];
		i = j - 1;
		
		while(i >= 0 && pA[i] > key){
			pA[i+1] = pA[i];
			i--;
			pA[i+1] = key;
		}
	}
}
//------------------------------------------------


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
		Insertion_Sort(pArr[i], Count[i]);
		for(int j = 0; j < Count[i]; ++j) {
			printf("%c", pArr[i][j]);
		}
		printf("\n");
	}
//------------------------------------------------	


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