#include <conio.h>
#include <cstdlib>
#include <iostream>
using namespace std;

void BubbleSort(int count, int* pArr) 
{ 
 int trash = 0; 
 for (int i = 0; i < count; i++)
  for (int j=0; j < count-i-1; j++) 
   if (pArr[j] > pArr[j+1])
    {
     trash = pArr[j]; 
     pArr[j] = pArr[j+1];
     pArr[j+1] = trash;
    }
}


//Функция вывода результатов:

void Out(int count, int* pArr) 
{
 for (int i = 0; i < count; i++) 
 cout << pArr[i] <<" ";
 cout << endl; 
}


//Использование:

int main()
{
 int Count;
 int Arr[100]; 
 cout << " Enter length of array: "; cin >> Count;
 for (int n = 0; n < Count; n++) Arr[n] = rand();
 Out(Count, Arr); 
 BubbleSort(Count, Arr); 
 Out(Count, Arr); 
 _getch();
 return 0;
}