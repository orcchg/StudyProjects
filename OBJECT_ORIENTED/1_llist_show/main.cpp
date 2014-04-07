#include <conio.h>
#include "class_ollist.hpp"

int main()
{
	mkey_t key;
	value_t value, out;
	int i=1;
		
	OLlist list;	
		
/*	printf("Enter key and value: ");
	while(!feof(stdin)){
		printf("%d: ",i++);
		scanf("%d %d",&key,&value);
		fflush(stdin);
		list.insert(key,value);
		printf("\n");
	}*/
	list.insert(2,215);
	list.insert(7,100);
	list.insert(15,72);
	list.insert(3,56);
	list.insert(5,199);
	list.insert(4,0);
	list.insert(8,12);
	
	printf("%d\n",list.BlockCount);
	list.get_list_info();
	
/*	fflush(stdin);
	
	printf("Enter key to delete: ");
	while(!feof(stdin)){
		printf("%d: ",i++);
		scanf("%d",&key);
		fflush(stdin);
		out = list.delete_el(key);
		printf("Deleted: %d\n",out);
	}		*/

	list.delete_first();
	list.delete_el(3);
	list.delete_el(5);
	list.delete_el(4);
	list.delete_el(11);
	
	printf("%d\n",list.BlockCount);
	list.get_list_info();
	
	printf("%d\n %d\n",list.find_el(7),list.find_el(11));
	
	_getch();
}