#include "set.h"

int main(int argc, char *argv[]) {
  int i;
  int *b;
  int n = 1000;

  set_t *s = set_new();

  if (argc > 1) {
    n = atoi(argv[1]);
  } 

  if (n <= 0) {
    n = 1000;
  }

  b = (int*)malloc(n * sizeof(int));

  for ( i = 0; i < n; i++) {
    b[i] = rand();
    set_insert(s, b[i]);
    assert( set_include(s, b[i]), "1" );
  }

  for ( i = 0; i < n; i++) {
    assert( set_include(s, b[i]), "2" );
  }

  set_clear(s);

  for ( i = 0; i < n; i++) {
    assert( !set_include(s, b[i]), "3" );
  }

  _getch();
  return 0;
}