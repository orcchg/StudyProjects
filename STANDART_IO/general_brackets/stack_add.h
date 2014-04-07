#define VOID -1

const int nmax = 10;

/* {'(','[','{','<',')',']','}','>'}
 * b10 = '(' = 1
 * b20 = '[' = 2
 * b30 = '{' = 3
 * b40 = '<' = 4
 * b11 = ')' = 5
 * b21 = ']' = 6
 * b31 = '}' = 7
 * b41 = '>' = 8
 */
enum bra {nil,b10,b11,b20,b21,b30,b31,b40,b41};

struct stack {

	int num;
	bra info;
};

void del_S(stack vec[],int nmax);
int emp_o_not(stack vec[],int nmax);
void push(stack vec[],int nmax,int p);
bra pop(stack vec[],int nmax);
bool empty(stack vec[]);
bool full(stack vec[],int nmax);

void del_S(stack vec[],int nmax){

	for(int i=0; i<nmax; i++){
		vec[i].num=VOID;
		vec[i].info=nil;
	}
}

int emp_o_not(stack vec[],int nmax){

	int k=0;
	
	for(int i=0; i<nmax; i++)
		if(vec[i].info==nil) k=1;
		
	return k;
}

void push(stack vec[],int nmax,bra p){

	struct stack vec1[20];
	int k=0;

if(!full(vec,nmax))
	{//
	for(int i=0; i<nmax; i++){
		vec1[i].info=vec[i].info;
		
		if(vec[i].num!=VOID)
			k++;
	}
	
	vec1[k].info=p;
	vec[k].num=k;
	
	for(int i=0; i<nmax; i++){
		vec[i].info=vec1[i].info;
	}
	
	} else ; //
}

bra pop(stack vec[],int nmax){

	int k=0;
	bra el;
	
if(!empty(vec))
	{//	
	for(int i=0; i<nmax; i++){
		if(vec[i].num!=VOID)
			k++;
	}
	
	el = vec[k-1].info;
	vec[--k].info=nil;
	vec[k].num=VOID;
	
	return el;
	
	} return nil; //
}

bool empty(stack vec[]){

	if(vec[0].num == VOID) return true;
	return false;
}

bool full(stack vec[],int nmax){

	if(vec[nmax-1].num != VOID) return true;
	return false;
}