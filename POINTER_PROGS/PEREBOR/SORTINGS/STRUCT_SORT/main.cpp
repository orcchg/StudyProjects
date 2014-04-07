#include "input.h"
#include "menu.h"
#include "out.h"
#include "random_array.h"
#include "copy_array.h"

#include "bubble_sort_str.h"
#include "insertion_sort_str.h"
#include "selection_sort_str.h"
#include "merge_sort_str.h"
#include "quick_sort_str.h"
#include "heap_sort_str.h"

#include "bubble_sort_str_D.h"
#include "insertion_sort_str_D.h"
#include "selection_sort_str_D.h"
#include "merge_sort_str_D.h"
#include "quick_sort_str_D.h"
#include "heap_sort_str_D.h"

member* Generate_RA(int k, int lim, int* n);

int main()
{
	member* Array = new member[MAXLIM];
	int n;
	
	char type, ch;
	int order = 0;
	int menu = 0;
	int flag = 1;
	
	if (Input(Array, &n))
	{			
		while(1)
		{
//			Array = Generate_RA(100000, 10000, 80000, &n);
			member* A = new member[n];
			Copy_Array(A, Array, n);
			
			menu = Menu(&type, &order);
			
			if (!menu)
			{
				break;
			}
			
			if (!order) // Ascending order
			{
				switch(menu)
				{
					case 1:
						Bubble_Sort(A, n);
						Out(A, n);
						break;
				
					case 2:
						Insertion_Sort(A, n);
						Out(A, n);
						break;
						
					case 7:
						Heap_Sort(A, 0, n-1);
						Out(A, n);
						break;
				
					case 3:
						A = Merge_Sort(A, n);
						Out(A, n);
						break;
				
					case 4:
						Quick_Sort(A, n);
						Out(A, n);
						break;
				
					case 5:
						Selection_Sort(A, n);
						Out(A, n);
						break;
						
					case 6:
						Out(A, n);
						break;
					
					default:
						break;
				}
			}
			else 	   // Descending order
			{
				switch(menu)
				{
					case 1:
						Bubble_Sort_D(A, n);
						Out(A, n);
						break;
					
					case 2:
						Insertion_Sort_D(A, n);
						Out(A, n);
						break;
						
					case 7:
						Heap_Sort_D(A, 0, n-1);
						Out(A, n);
						break;	
				
					case 3:
						A = Merge_Sort_D(A, n);
						Out(A, n);
						break;
					
					case 4:
						Quick_Sort_D(A, n);
						Out(A, n);
						break;
				
					case 5:
						Selection_Sort_D(A, n);
						Out(A, n);
						break;
						
					case 6:
						Out(A, n);
						break;	
					
					default:
						break;
				}
			}
			
			delete [] A;
		}
	}
	
	delete [] Array;
	
	return 0;
}