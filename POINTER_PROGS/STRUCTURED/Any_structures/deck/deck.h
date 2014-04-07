const int nmax=10;

struct stack {

	int num;
	int info;
};

void del_S(stack vec[],int nmax);
int emp_o_not(stack vec[],int nmax);
void push(stack vec[],int nmax,int p);
void pop(stack vec[],int nmax);
void add(stack vec[],int nmax,int p);
void take_el(stack vec[],int nmax);
void take_el_head(stack vec[],int nmax,int it);

void del_S(stack vec[],int nmax){

	for(int i=0; i<nmax; i++){
		vec[i].num=0;
		vec[i].info=0;
	}
}

int emp_o_not(stack vec[],int nmax){

	int k=0;
	
	for(int i=0; i<nmax; i++)
		if(vec[i].info==0) k=1;
		
	return k;
}

void push(stack vec[],int nmax,int p){

	struct stack vec1[20];
	int k=1;
	
	for(int i=0; i<nmax; i++){
		vec1[i].info=vec[i].info;
		
		if(vec[i].num!=0 && i!=0)
			k++;
	}
	
	vec1[k].info=p;
	vec[k].num=k;
	
	for(int i=0; i<nmax; i++){
		vec[i].info=vec1[i].info;
	}
}

void pop(stack vec[],int nmax){

	int k=1;
	
	for(int i=0; i<nmax; i++){
		if(vec[i].num!=0 && i!=0)
			k++;
	}
	
	vec[--k].info=0;
	vec[k].num=0;
}

void add(stack vec[],int nmax,int p){

	struct stack vec1[20];

	for (int i=1;i<nmax;i++)
		vec1[i].info=vec[i-1].info;

	vec1[0].info=p;
	vec[0].num=0;

	for (int i=0;i<nmax;i++){ 
		vec[i].info=vec1[i].info;
		vec[i].num=i;
	}
}

void take_el(stack vec[],int nmax){

	int k=1;
	
	for(int i=0; i<nmax; i++){
		if(vec[i].num!=0 && i!=0)
			k++;
	}

	vec[--k].info=0;
	vec[k].num=0;
}

void take_el_head(stack vec[],int nmax,int it){

	vec[it].info=0;
	vec[it].num=0;
}