//Syntax: genzebra <seed> <N> <number of segments> <number of subdivisions> <use many small buckets>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define for if (0) ; else for
#define MAGIC 10
#define MAGICS 137

int n, useb, m, p, q, a[100000], gr[100000], grz[100000];

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

void randsum(int n, int s, int *a)
{
  if (s<=0)
  {
    randperm(s-1,a);
    stable_sort(a,a+n-1);
  }
  else
  {
    if (useb&&(s>=30000000))
    {
      for (int i=0;i<n-1;i++)
      {
        a[i] = rand32()%MAGICS+(s/n)*i;
        if (a[i]<0)
          a[i] = 0;
        if (a[i]>=s-1)
          a[i] = s-2;
      }
      stable_sort(a,a+n);
      for (int i=1;i<n-1;i++)
        if (a[i]<=a[i-1])
        {
          a[i] = 1+a[i-1];
          assert(a[i]<s-1);
        }      
    }
    else
    {
      for (int i=0;i<n-1;i++)
        a[i] = rand32()%(s-1);
      stable_sort(a,a+n);
      for (int i=1;i<n-1;i++)
        if (a[i]<=a[i-1])
        {
          a[i] = 1+a[i-1];
          assert(a[i]<s-1);
        }
    }
  }
  a[n-1] = s-1-a[n-2];
  for (int i=n-2;i>=1;i--)
    a[i] -= a[i-1];
  a[0]++;
}

inline bool less(const int &a, const int &b)
{
  return (gr[a]>gr[b]);
}

void refill()
{
  static int perm[100000];
  randperm(p>>1,perm);
  fprintf(stderr,"refill: randperm\n");
  for (int i=0;i<(p>>1);i++)
    a[m++] = -1-grz[(i<<1)+1];
  for (int i=0;i<(p>>1);i++)
    perm[i] = (i<<1)+1;
  fprintf(stderr,"p = %d\n",p);
  stable_sort(perm,perm+(p>>1),less);
  fprintf(stderr,"refill: stable_sort\n");
  for (int i=0;i<(p>>1);i++)
  {
    grz[perm[i]] = m;
    a[m++] = gr[perm[i]];
  }
  fprintf(stderr,"refill\n");
}

void divide()
{
  static int perm[100000], s[100000][3], zz[100000][3], Gr[100000], Grz[100000], P;
  P = 0;
  randperm(p>>1,perm);
  for (int i=0;i<(p>>1);i++)
    if (gr[(i<<1)+1]>=MAGIC)
      randsum(3,gr[(i<<1)+1],s[i]);
  for (int i=0;i<(p>>1);i++)
    if (gr[(perm[i]<<1)+1]>=MAGIC)
    {
      a[m++] = -1-grz[(perm[i]<<1)+1];
      if (i==8850)
        i = i;
      if (!s[143][1]&&i<8852)
        i = i;
      if (perm[i]==143)
        fprintf(stderr,"! %d\n",i);        
      randsum(3,gr[(perm[i]<<1)+1],s[perm[i]]);
      for (int j=0;j<3;j++)
      {
        assert(s[perm[i]][j]);
        zz[perm[i]][j] = m;
        a[m++] = s[perm[i]][j];
      }
    }
  fprintf(stderr,"%d\n",s[1763>>1][2]);
  for (int i=0;i<p;i++)
    if ((i&1)&&(gr[i]>=MAGIC))
      for (int j=0;j<3;j++)
      {
        Gr[P] = s[i>>1][j];
        Grz[P] = zz[i>>1][j];
        if (!Gr[P])
          fprintf(stderr,"%d %d %d %d\n",P,i,j,s[i>>1][j]);
        assert(Gr[P]);
        P++;
      }
    else
    {
      Gr[P] = gr[i];
      Grz[P++] = grz[i];
      assert(gr[i]);
    }
  p = P;
  for (int i=0;i<p;i++)
  {
    gr[i] = Gr[i];
    grz[i] = Grz[i];
    assert(gr[i]);
  }
  fprintf(stderr,"set p to %d\n",p);
  fprintf(stderr,"divide\n");
}

int main(int argc, char** argv)
{
  unsigned temp;
  assert((argc==6)&&(sscanf(argv[1],"%u",&temp)==1)&&(sscanf(argv[2],"%d",&n)==1)
    &&(sscanf(argv[3],"%d",&p)==1)&&(sscanf(argv[4],"%d",&q)==1)&&(sscanf(argv[5],"%d",&useb)==1));
  srand(temp);

  m = 0;
  randsum(p,n,gr);
  fprintf(stderr,"first\n");
  for (int i=0;i<p;i++)
  {
    grz[i] = m;
    a[m++] = gr[i];
  }
  refill();

  while (q--)
  {
    divide();
    refill();
  }

  printf("%d %d\n",n,m);
  for (int i=0;i<m;i++)
    printf("%d\n",a[i]);

  return 0;
}