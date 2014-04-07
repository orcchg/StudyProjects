long C(long n, long k){

	if(n < k) return 0;
	if(k == 0) return 1;
	if(k == 1) return n;
	return C(n-1,k-1) + C(n-1,k);
}

#include <cmath>
#include <iostream>

void Graph_C(long n){

	double y;
	for(int i=0; i<n; i++){
		y = log10(C(i,i/2))/log10(2);
		for(int j=0; j<(int)y; j++)
			std::cout << 'X';
		std::cout << '\n';
	}
}
	