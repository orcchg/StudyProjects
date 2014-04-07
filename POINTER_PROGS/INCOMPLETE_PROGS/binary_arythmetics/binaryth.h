#include <cstring>

char* sum(char* A, char* B)
{
	int k = 0;
	int len_A = strlen(A);
	int len_B = strlen(B);
	int len_M = ((len_A >= len_B) ? len_A : len_B);
	int len_m = ((len_A >= len_B) ? len_B : len_A);
	char* C = new char[len_M];
	char* D = new char[len_M];
	char* E = new char[len_M+1];
	
	char* AA = new char[len_M];
	char* BB = new char[len_m];
	
	//Split on Lesser and Higher Numbers//
	if(len_M == len_A) {
		for(int i = 0; i < len_M; i++) {
			AA[i] = A[i];
		}
		for(int i = 0; i < len_m; i++) {
			BB[i] = B[i];
		}
	} else if (len_M == len_B) {
		for(int i = 0; i < len_M; i++) {
			AA[i] = B[i];
		}
		for(int i = 0; i < len_m; i++) {
			BB[i] = A[i];
		}
	}
	
	//SHIFT of lesser Number//
	for(int i = 0; i < (len_M - len_m); i++) {
		C[i] = 0;
	}
	for(int i = (len_M - len_m); i < len_M; i++) {
		C[i] = BB[i];
	}
	
	//Pre-SUM//
	for(int i = 0; i < len_M; i++) {
		D[i] = C[i] + AA[i];
	}
	
	delete [] C;
	delete [] AA;
	delete [] BB;
	
	//Morphling//
while(k != len_M) {	
	for(int i = (len_M - 1); i > 0; i--) {
		if(D[i] == '2') {
			D[i] = '0';
			D[i] = D[i-1] + 1 + '0';
		} else if (D[i] == '3') {
			D[i] = '1';
		}
	}
	k++;
}

for(int i = 0; i < len_M; i++) {
	E[i+1] = D[i];
}

if(D[1] == '2' && D[0] == '1') {
	E[2] = '0';
	E[1] = '0';
	E[0] = '1';
} else if (D[1] == '3' && D[0] == '1') {
	E[2] = '1';
	E[1] = '0';
	E[0] = '1';
}

delete [] D;

	return E;
}
	