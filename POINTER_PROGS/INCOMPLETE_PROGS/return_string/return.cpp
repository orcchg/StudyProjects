#include <conio.h>
#include <iostream>
#include <stdio.h>
using namespace std;

char *string_uppercase(char* string){ 

   char *starting_address = string; // адрес string[0]; 
   while (*string)

   { 
      if ((*string >= 'a') && (*string <= 'z')) *string = *string - 'a' + 'A'; 
      string++; 
   } 
   return(starting_address); 
}

int main(){

	char* ptr = string_uppercase("LeArN lANguAGe!");
	printf("%s\n",++ptr);
	_getch();
}