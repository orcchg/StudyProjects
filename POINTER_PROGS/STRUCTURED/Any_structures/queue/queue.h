const int nmax=10;

struct queue {

	int num;
	int info;
};

void del_Q(queue vec[],int nmax);
int emp_o_not(queue vec[],int nmax);
void add(queue vec[],int nmax,int p);
void take_el(queue vec[],int nmax);

void del_Q(queue vec[],int nmax){ //сделать очередь пустой

	for (int i=0;i<nmax;i++){ 
			vec[i].num=0;
			vec[i].info=0;
	}
}

int emp_o_not(queue vec[],int nmax){ //очередь пуста/непуста

	int k=0;
	
	for (int i=0;i<nmax;i++)
		if (vec[i].info==0) k=1;
		
	return k;
}

void add(queue vec[],int nmax,int p){ //добавить элемент в очередь

	struct queue vec1[20];

	for (int i=1;i<nmax;i++)
		vec1[i].info=vec[i-1].info;

	vec1[0].info=p;
	vec[0].num=0;

	for (int i=0;i<nmax;i++){ 
		vec[i].info=vec1[i].info;
		vec[i].num=i;
	}
}

void take_el(queue vec[],int nmax){

	int k=1;
	
	for(int i=0; i<nmax; i++){
		if(vec[i].num!=0 && i!=0)
			k++;
	}

	vec[--k].info=0;
	vec[k].num=0;
}