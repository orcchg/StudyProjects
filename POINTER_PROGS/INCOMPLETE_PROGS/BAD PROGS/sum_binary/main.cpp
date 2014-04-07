#include <conio.h>
#include <stdio.h>
#include "inverse.h"

int* Trace(long bin, int len);
long Bin_to_Int(int s[], int len);
long power(int a,int n);

int main(){

	long a,b,aa,bb;
	int alen=0,blen=0;
	
	printf("Enter binary numbers a & b: ");
	scanf("%ld %ld",&a,&b);
	printf("\n");
	
	while(aa){
		aa/=10;
		alen++;
	}
	while(bb){
		bb/=10;
		blen++;
	}
	alen--;
	blen--;
	printf("%d %d\n",alen,blen);
	
	printf("%ld %ld\n",Bin_to_Int(Trace(a,alen),alen),Bin_to_Int(Trace(b,blen),blen));
	
	_getch();
}

int* Trace(long bin, int len){

	char s[len];
	char* s1 = new char[len];
	int* v = new int[len];
	
	if(sprintf(s,"%ld",bin)!=1) return NULL;
	else { 
		 s1 = inverse(s,len);
			for(int i=0; i<len; i++){
				v[i] = s1[i];
			}
	}
	
	delete [] s1;
	return v;
}

long Bin_to_Int(int s[],int len){

	long sum=0;
	
	for(int i=0; i<len; i++)
		sum+=s[i]*power(2,i);
		
	return sum;
}

long power(int a,int n){

	int k=n,c=a,b=1;
	
	while(k){
		if(k % 2 == 0){
			c*=c;
			k/=2;
		} else {
			b*=c;
			k--;
		}
	}
	
	return b;
}