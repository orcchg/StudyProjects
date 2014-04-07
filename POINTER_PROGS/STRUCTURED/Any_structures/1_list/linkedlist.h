/*
Usage:
  ADD   
  DEL 
  FIND 
  PRINT 
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef int mkey_t;  // ��� �����
typedef int value_t; // ��� ��������

struct li {
   mkey_t key;
   value_t value;
   struct li* next;
};

struct list {
   struct li *first;
   int size;
};

struct list *new_list(void) {
   struct list *res = (struct list*) malloc(sizeof(struct list));
   res->first = NULL;
   res->size = 0;
   return res;
}

struct li* new_list_item(void) {
    struct li *res = (struct li*) malloc(sizeof(struct li));
    res->next = 0;
    return res;
}

void delete_items(struct li* it) {
   if ( it ) {
      if ( it->next ) {
         delete_items(it->next);
      }
      free( it );
   }
}

void delete_list(struct list *l) {
   if ( l ) {
      delete_items( l->first );
      free ( l ); 
   }
}

/* ��������� ������� (key, value) � ������ ������ l
 * ���������� 1, ���� ������� �������� ������� (������ ��� ������� ���� ������� ��������)
 */
int insert_item( struct list *l, mkey_t key, value_t value ) {
   struct li *it = new_list_item();
   if ( it == NULL ) return 0;
   it->key = key;
   it->value = value;
   it->next = l->first;
   l->first = it;
   l->size++;
   return 1;
}

/* ��������� �������� (key, value) � ������ ������ l ������ � ��� ������,
 * ���� ������ l �� �������� �������� � ������ key.
 * ���������� 1, ���� ������� �������� ������� (������ ��� ������� ���� ������� ��������)
 * ��� �������� �������� value.
 */
int insert_item_uniq( struct list *l, mkey_t key, value_t value ) {
   if ( l ) {
      struct li *it;
      for ( it = l->first; it != NULL; it = it->next ) {
         if (it->key == key) {
            it->value = value;
            return 1;
         }
      }
      return insert_item(l, key, value);
   
   } else {
      return 0;
   }
}

/* ������� ������� (key, *). 
 * ���������� 1, ���� ������� � ��������� ������ ��� ������ � ������ l.
 */
int delete_item( struct list *l, mkey_t key ) {
   struct li *it, *prev_it = 0;
   for (  it = l->first; it != NULL; prev_it = it, it = it->next ) {
      if ( it->key == key ) {
         if ( prev_it != 0 ) 
            prev_it->next = it->next;
         else
            l->first = it->next;
         free( it );
         l->size--;
         return 1;
      }
   }
   return 0;
}

/* ������ ������� ���������� �������� �������� �� ������
*/
/*
int delete_item2( struct list *l, mkey_t key ) {
   struct li **it = &(l->first);
   for ( ; (*it) != NULL; it = &( (*it)->next) ) {
      if ( (*it)->key == key ) {
         struct li *tmp = *it;
         *it = (*it)->next ;
         free( tmp );
         return 1;
      }
   }
   return 0;
}
*/

/*
 *
 */
void print_list ( struct list *l ) {
   struct li *it;
   printf( "Size=%d\n", l->size );
   for ( it = l->first; it != NULL; it = it->next ) {
      printf("(%d,%d) -> ", it->key, it->value);   
   }
   printf( "NULL\n" );
}

int find_item( struct list *l, mkey_t key, value_t *value) {
   struct li *it;
   for ( it = l->first; it != NULL; it = it->next ) {
      if ( it->key == key ) {
         *value = it->value;
         return 1;
      }
   }
   return 0;
}