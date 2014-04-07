#include <iostream>
#include "struct.h"
using std::cout;
using std::endl;

void Out(member* pA, int n){

	for(int i = 0; i < n; ++i)
		cout << "(" << pA[i].key << " : " << pA[i].info << ")\n";
		
	cout << endl;
}