//Syntax: gennoalloc <seed> <start> <M> <number of segments> <possibility of good allocation> <precise>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define for if (0) ; else for

int n, m, prec, m0, start, p, q, a[100000], gr[100000], z[100000];

int rand32()
{
  return (rand()&65535)<<15|(rand()&32767);
}

void randperm(int n, int *p)
{
  for (int i=0;i<n;i++)
  {
    int t = rand32()%(1+i);
    p[i] = p[t];
    p[t] = i;
  }
}

int main(int argc, char** argv)
{
  unsigned temp;
  assert((argc==7)&&(sscanf(argv[1],"%u",&temp)==1)&&(sscanf(argv[2],"%d",&start)==1)
    &&(sscanf(argv[3],"%d",&m0)==1)&&(sscanf(argv[4],"%d",&p)==1)&&(sscanf(argv[5],"%d",&q)==1)
    &&(sscanf(argv[6],"%d",&prec)==1));
  srand(temp);

  m = 0;
  n = 0;
  randperm(p,z);
  for (int i=0;i<p;i++)
  {
    if (!i)
      gr[i] = start;
    else
    {
      if (prec)
        gr[i] = gr[i-1]+1+rand()%3;
      else
        gr[i] = gr[i-1]+1+!(rand()%10);
    }
    n += gr[i];
  }
  for (int i=0;i<p;i++)
    a[m++] = gr[z[i]];
  randperm(p>>1,z);
  for (int i=0;i<(p>>1);i++)
    a[m++] = -1-((z[i]<<1)+1);
  while (m<m0)
    if (prec)
    {
      if (rand()%q)
        a[m++] = start+p+(p/4)+10+rand()%16;
      else
        a[m++] = start+rand()%p; 
    }
    else
    {
      if (rand()%q)
        a[m++] = start+3*p+10+rand()%1234;
      else
        a[m++] = start+rand()%(3*p); 
    }

  printf("%d %d\n",n,m);
  for (int i=0;i<m;i++)
    printf("%d\n",a[i]);

  return 0;
}

