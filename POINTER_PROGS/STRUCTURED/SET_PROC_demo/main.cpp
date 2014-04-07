#include <conio.h>
#include <stdio.h>
#include "support.h"
#include "set_cross_union_uniq.h"

ULONG simple_dividor(ULONG,ULONG []);
ULONG set_cross(ULONG,ULONG,ULONG [],ULONG [],ULONG []);
ULONG set_union(ULONG,ULONG,ULONG [],ULONG [],ULONG []);
ULONG* set_uniq(ULONG,ULONG [],ULONG&);
ULONG* set_differ(ULONG,ULONG,ULONG [],ULONG[],ULONG&);
ULONG set_minimum(ULONG [],ULONG);

int main()
{
	ULONG a,b,c,L_a,L_b,L_c,L_ab,L_bc,L_abc,L_q=0,L_aq=0,L_r=0,L_bcq=0,min;
	ULONG A[50],B[50],C[50];
	ULONG AB[50], ABC[50], BCcr[50];
	ULONG* Q = new ULONG[50];
	ULONG* AQ = new ULONG[50];
	ULONG* R = new ULONG[50];
	ULONG* BCq = new ULONG[50];
	ULONG NOK = 1;
	
	printf("Enter a b c : ");
	scanf("%d %d %d",&a,&b,&c);
	printf("\n");
	fflush(stdin);
	
	printf("\nA: \n");
	L_a = simple_dividor(a,A);
	printf("%d\n",L_a);
	for(int i = 0; i < L_a; i++) {
		printf("%d ",A[i]);
	}
	
	printf("\nB: \n");
	L_b = simple_dividor(b,B);
	printf("%d\n",L_b);
	for(int i = 0; i < L_b; i++) {
		printf("%d ",B[i]);
	}
	
	printf("\nC: \n");
	L_c = simple_dividor(c,C);
	printf("%d\n",L_c);
	for(int i = 0; i < L_c; i++) {
		printf("%d ",C[i]);
	}
	
/*	printf("\nAB: \n");
	L_ab = set_cross(L_a,L_b,A,B,AB);
	printf("%d\n",L_ab);
	for(int i = 0; i < L_ab; i++) {
		printf("%d ",AB[i]);
	}
	
	printf("\nABC: \n");
	L_abc = set_cross(L_ab,L_c,AB,C,ABC);
	printf("%d\n",L_abc);
	for(int i = 0; i < L_abc; i++) {
		printf("%d ",ABC[i]);
	}
*/	
	printf("\nAB: \n");
	L_ab = set_union(L_a,L_b,A,B,AB);
	printf("%d\n",L_ab);
	for(int i = 0; i < L_ab; i++) {
		printf("%d ",AB[i]);
	}
	
	printf("\nABC: \n");
	L_abc = set_union(L_ab,L_c,AB,C,ABC);
	printf("%d\n",L_abc);
	for(int i = 0; i < L_abc; i++) {
		printf("%d ",ABC[i]);
	}
	
	printf("\nQ: \n");
	Q = set_uniq(L_abc,ABC,L_q);
	printf("%d\n",L_q);
	for(int i = 0; i < L_q; i++) {
		printf("%d ",Q[i]);
	}
	
	printf("\nAQ: \n");
	AQ = set_uniq(L_a,A,L_aq);
	printf("%d\n",L_aq);
	for(int i = 0; i < L_aq; i++) {
		printf("%d ",AQ[i]);
	}
	
	printf("\nR: \n");
	R = set_differ(L_q,L_aq,Q,AQ,L_r);
	printf("%d\n",L_r);
	for(int i = 0; i < L_r; i++) {
		printf("%d ",R[i]);
	}
	
	printf("\nBC cross: \n");
	L_bc = set_cross(L_b,L_c,B,C,BCcr);
	printf("%d\n",L_bc);
	for(int i = 0; i < L_bc; i++) {
		printf("%d ",BCcr[i]);
	}
	
	printf("\nBC Q: \n");
	BCq = set_uniq(L_bc,BCcr,L_bcq);
	printf("%d\n",L_bcq);
	for(int i = 0; i < L_bcq; i++) {
		printf("%d ",BCq[i]);
	}
	
	_getch();
}