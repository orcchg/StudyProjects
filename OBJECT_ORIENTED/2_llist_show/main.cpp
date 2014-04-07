#include <conio.h>
#include "class_dllist.hpp"

int main()
{
	mkey_t key;
	value_t value, out;
	int i=1,step1,step2;
		
	DLlist dlist;	

	dlist.insert(2,215);
	dlist.insert(7,100);
	dlist.insert(15,72);
	dlist.insert(3,56);
	dlist.insert(5,199);
	dlist.insert(4,0);
	dlist.insert(8,12);

	printf("%d\n",dlist.BlockCount);
	dlist.get_list_info();

	dlist.delete_first();
	dlist.delete_el(3);
	dlist.delete_el(5);
	dlist.delete_el(4);
	dlist.delete_el(11);
	
	printf("%d\n",dlist.BlockCount);
	dlist.get_list_info();
	
	printf("%d\n %d\n",dlist.find_el_rev(4,step1),dlist.find_el_dir(8,step2));
	printf("%d %d",step1,step2);
	
	_getch();
}