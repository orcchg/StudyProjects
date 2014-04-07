#include <stdlib.h>

typedef struct person {
   char *name;
   int phone;
} person_t;
 
int namecmp(const void* a, const void* b);
int phonecmp(const void* a, const void* b);

int namecmp(const void* a, const void* b) {
    person_t *pa = (person_t*)a;
    person_t *pb = (person_t*)b;
    return strcmp(pa->name, pb->name);
}
int phonecmp(const void* a, const void* b) {
    person_t *pa = (person_t*)a;
    person_t *pb = (person_t*)b;
    return pa->phone - pb->phone;
}