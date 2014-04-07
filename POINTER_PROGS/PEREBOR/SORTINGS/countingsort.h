void CountingSort (int *a, int n, int min, int max)
{
  int i, j, c;
  int *b;
  
  assert(n > 0);
  assert(min <= max);
  
  b = (int *)calloc(max - min + 1, sizeof(int));
  
  assert(b != NULL);
  
  for (i = 0; i <= n - 1; ++i)
  {   
	++b[a[i] - min];
  }
  
  for (j = min; j <= max; ++j)
  {
    c = b[j - min];
    while (c > 0)
    {
      *a = j; ++a; --c;
    }
  }
  
  free(b);
}