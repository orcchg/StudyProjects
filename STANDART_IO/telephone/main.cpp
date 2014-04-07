#include <stdio.h>
#include <conio.h>
#include <cstring>
#include "phone.h"

int main() {
   char name[1000];
   person_t *base;
   int n, i, phone;
   
   printf("Enter N: ");
   scanf("%d", &n);
   printf("\n");
   base = (person_t*)malloc(n * sizeof(person_t));

   /* Считываем телефонную базу */
   printf("Enter Name and Number: \n");
   for (i = 0 ; i < n ; i++) {
	   printf("Name and Number %d: \n",i+1);
       scanf("%s%d", name, &phone);
       base[i].name = (char*)malloc(strlen(name) * sizeof(char));
       strcpy(base[i].name, name);
       base[i].phone = phone;
   }
 
   qsort(base, n, sizeof(person_t), namecmp);
   /* Напечатаем в алфавитном порядке */
   printf("\nAlphabet order: \n");
   for(i = 0 ; i < n ; i++) {
       printf("%20s %d\n", base[i].name, base[i].phone);
   }
    
 
   qsort(base, n, sizeof(person_t), phonecmp);
   /* Напечатаем в порядке возрастания номеров*/
   printf("\nNumber order: \n");
   for (i = 0 ; i < n ; i++) {
       printf("%20s %d\n", base[i].name, base[i].phone);
   }
 
   /* Освобождаем выделенную память */
 
   for (i = 0 ; i < n ; i++) {
       free(base[i].name);
   }
   free(base);
 
   _getch();
   return 0;
 
}