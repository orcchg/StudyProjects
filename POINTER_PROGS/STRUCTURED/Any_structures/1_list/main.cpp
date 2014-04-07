#include <conio.h>
#include "linkedlist.h"

int main()
{
   char cmd[1024];
   struct list *l = new_list();
   
   while (1) 
   {
      fgets( cmd, sizeof(cmd), stdin );
	  
    if ( strncmp( cmd, "ADD", 3 ) == 0 ) 
	{
         mkey_t key;
         value_t value;
		 
         if( sscanf(cmd + 3, "%d%d", &key, &value) == 2 ) 
		 {
            insert_item_uniq(l, key, value );
         } 
		 else 
		 {
            printf("Bad arguments: %s\n", cmd+3);
            printf("Usage: ADD <key> <value>\n");
         }
    } 
	else if ( strncmp( cmd, "DEL", 3 ) == 0 ) 
	  {
         mkey_t key;
         sscanf(cmd + 3, "%d", &key );
         delete_item( l, key );
      } 
	  else if ( strncmp( cmd, "PRINT", 5) == 0 ) 
	  {
         print_list( l );
      } 
	  else if ( strncmp( cmd, "FIND", 4) == 0 ) 
	  {
         mkey_t key;
         value_t value;
         sscanf( cmd + 4, "%d", &key );
		 
         if ( find_item( l, key, &value ) ) 
		 {
            printf("Value = %d\n", value);   
         } 
		 else 
		 {
            printf("Not found\n");
         }
      }
   }
   
   _getch();
   return 0;
}