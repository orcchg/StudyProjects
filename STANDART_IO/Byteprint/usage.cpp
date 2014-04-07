#include <conio.h>
#include "intBitPrint.h"

#define PRINT_CODE(expr) {printf("\nThe code of "#expr" is\n"); intBitPrint(expr);}
#define PRINT_EXPI(expr) printf("The value of "#expr" is %d\n")

int main(){
	
	PRINT_CODE(4);
	PRINT_CODE(-4);
	PRINT_CODE(~4);
	PRINT_EXPI(~4);
	PRINT_CODE(!4);
	PRINT_EXPI(!4);
	
	_getch();
}