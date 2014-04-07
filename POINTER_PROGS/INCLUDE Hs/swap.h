void swap(int* pA, int* pB){

	int temp;
	
	temp=*pA;
	*pA=*pB;
	*pB=temp;
	
}

void swap(int& rA, int& rB){

	int temp;
	
	temp=rA;
	rA=rB;
	rB=temp;

}

void swap(char** pA, char** pB){

	char* temp;
	
	temp=*pA;
	*pA=*pB;
	*pB=temp;
	
}