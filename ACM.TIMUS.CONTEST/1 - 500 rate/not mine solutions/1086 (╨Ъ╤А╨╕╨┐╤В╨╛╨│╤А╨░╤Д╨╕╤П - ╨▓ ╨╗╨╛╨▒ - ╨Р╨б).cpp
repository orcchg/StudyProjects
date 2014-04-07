#include <stdio.h>
#include <math.h>

int p[15003],ind=5;

bool is_prime(int n){
int i=3,l=(int)sqrt((double)n)+1;
while(i<l){
if(n%i==0)
return 0;
i+=2;
}
return 1;
}

void init(){
int i;
for(i=11;ind<15002;i+=2){
if(is_prime(i)){
p[ind]=i;
ind++;
}
}
}

int main()
{
p[1]=2;p[2]=3;p[3]=5;p[4]=7;
int n,i,k;
init();
scanf("%d",&n);
for(i=1;i<=n;i++){
scanf("%d",&k);
printf("%d\n",p[k]);
}
return 0;
}