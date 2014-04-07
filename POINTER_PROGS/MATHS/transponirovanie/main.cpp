#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int SIZE = 12;

int main()
{
	char c;

do {
    int **mas;
    int i, j, k = 0, Tr = 0;
    
    mas = new int*[SIZE];
    if (!*mas) cout << "All err!";

    for( int k = 0; k < SIZE; k++)
        if (! (mas[k] = new int[SIZE]) )
            cout << "Allocation error!";

    int num = 1;
    for ( i = 0; i < SIZE; i++)
        for ( j = 0; j < SIZE; j++)
            mas[i][j] = 100*(double)rand()/RAND_MAX; //num++;
	
	//PRINT NON-TRANSFORMATED MATRIX//
	printf("INITIAL MATRIX\n\n\n");
	for ( i = 0; i < SIZE; i++) {
        for (j = 0 ; j < SIZE ; j++)
        {
            printf("%d ",mas[i][j]);
			if(i == j) {
				Tr += mas[i][j];
			}
        }
		printf("\n\n");
	}

    int count = 0;
    for ( i = 0; i < SIZE; i++)
        for (j = i + 1 ; j < SIZE ; j++)
        {
            k = mas[i][j];
            mas[i][j] = mas[j][i];
            mas[j][i] = k;
            count++;
        }
		
	printf("\n\nTRANSPONED MATRIX\n\n\n");	
	for ( i = 0; i < SIZE; i++) {
        for (j = 0 ; j < SIZE ; j++)
        {
            printf("%d ",mas[i][j]);
        }
		printf("\n\n");
	}
	
	printf("\nTrace = %d\n",Tr);
	
	delete [] mas;
	
} while((c=getchar())!=EOF);	
	
    return 0;
}