#include <cstdlib>

char* Generate_Rand(int n){

	int key=0,val=0,i=0;
	char* s = new char[n];
	
	while(i<n){
		val = rand();
		if(val > RAND_MAX/2)
			key = 1;
		else
			key = 0;
			
		switch(key){
			case 0:
				s[i++]='(';
				break;
			case 1:
				s[i++]=')';
				break;
		}
	}
	
	return s;
}