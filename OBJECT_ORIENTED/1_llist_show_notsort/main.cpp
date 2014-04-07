#include <conio.h>
#include "class_ollist_notsort.hpp"

int main()
{
	mkey_tns key;
	value_tns value, out;
	int i=1;
		
	OLlist_NotSort nsList;
	
	nsList.add_val_to_first(2,215);
	nsList.add_val_to_last(7,100);
	nsList.add_val_to_first(15,72);
	nsList.add_val_to_last(3,56);
	nsList.add_val_to_first(5,199);
	nsList.add_val_to_last(4,0);
	nsList.add_val_to_last(6,315);
	nsList.insert_any_pos(17,81,6);
	nsList.insert_any_pos(8,209,2);
	
	printf("%d\n",nsList.BlockCount);
	nsList.get_list_info();

	nsList.delete_first();
	nsList.delete_el(3);
	nsList.delete_el(5);
	nsList.delete_el(4);
	nsList.delete_el(11);
	
	printf("%d\n",nsList.BlockCount);
	nsList.get_list_info();
	
	out = nsList.find_el(6);
	printf("%d\n",out);
	out = nsList.find_el(21);
	printf("%d\n",out);
	
	_getch();
}