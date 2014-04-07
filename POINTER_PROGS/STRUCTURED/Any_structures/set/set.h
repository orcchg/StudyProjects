#include <stdio.h>
#include <malloc.h>

struct set {
  int *set;
  int n;
  int allocated_n;
};

typedef struct set  set_t;

set_t* set_new();

// add element to set
int set_insert(set_t *s, int a);

// check if a exists in set
int set_include(set_t *s, int a);

// clear set
int set_clear(set_t *s);

int cmp_int(const void *a, const void *b) {
  const int *aa = (const int *)a;
  const int *bb = (const int *)b;
  return *aa - *bb; 
}

set_t* set_new() {
  set_t *s = (set_t*)malloc(sizeof(set_t));
  s->allocated_n = 1000;
  s->set = (int *)malloc(s->allocated_n * sizeof(int));
  s->n = 0; 
  return s;
}

int set_clear(set_t *s) {
  s->n = 0;
  s->set = (int *)realloc(s->set, (s->allocated_n = 1000) * sizeof(int));
  return 1;
}

int set_delete(set_t *s) {
  free(s->set);
  free(s);
  return 1;
}

int set_insert(set_t *s, int a) {
  if (set_include(s, a)) return 1;
  if ( s->n >= s->allocated_n ) {
    s->set = (int *)realloc(s->set, (s->allocated_n *= 2) * sizeof(int));
  }
  s->set[s->n++] = a;
  qsort(s->set, s->n, sizeof(s->set[0]), cmp_int);
  return 1;
}

int set_include(set_t *s, int a) {
  int l = 0;
  int r = s->n;
  if (s->n == 0) return 0; // строчка, которая изначально была пропущена, но тесты выявили этот bug
  while ( r - l > 1 ) {
    int c = (l + r) / 2;
    if ( a < s->set[c] ) {
      r = c;
    } else {
      l = c;
    }
  }
  return s->set[l] == a;  
}

int assert(int cnd, char *msg) {
  if (!cnd) {
    printf("FAIL: %s\n", msg);    
  }
}