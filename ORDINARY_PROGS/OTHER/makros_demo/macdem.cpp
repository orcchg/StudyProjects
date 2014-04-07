#include <iostream>
#include <conio.h>
using namespace std;

#define MAX(A,B) ((A)>(B)?(A):(B))
#define SQUARE(X) X*X

#define SWAP(X,Y) {int TEMP=X; \
X=Y; Y=TEMP; }

int main() {

	int A,B,P,Q;
	
	cout << "Enter A: ";
	cin >> A;
	cout << endl;
	
	cout << "Enter B: ";
	cin >> B;
	cout << endl;
	
	cout << "MAX(A,B): " << MAX(A,B) << endl;
	
	cout << "Enter P: ";
	cin >> P;
	cout << endl;
	
	cout << "Enter Q: ";
	cin >> Q;
	cout << endl;
	
	cout << "MAX(A+P,B+Q): " << MAX(A+P,B+Q) << ((A+P)>(B+Q)?" A+P":" B+Q") << endl;
	cout << "sqr A: " << SQUARE(A) << endl;
	SWAP(A,B);
	cout << "SWAP A,B " << A << " " << B << endl;
	
	_getch();
}