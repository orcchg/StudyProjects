#include "class_polynom.hpp"
#include <iostream>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;

int main() 
{
	vector<int> vec_a;
	vector<int> vec_b;
	vector<double> vec_d;
	vec_a.resize(6);
	vec_b.resize(6);
	vec_d.resize(6);
	
	for (int i = 0; i < 6; ++i) {
		vec_a[i] = i + 1;
		vec_b[i] = 2*i - 1;
		vec_d[i] = 1.51*i - 0.29;
	}
	
	Polynom<int> A(vec_a);
	Polynom<int> B(vec_b);
	Polynom<> C(6);
	
	A.Print();
	B.Print();
	
	C = A;
	try {
		cout << C[0] << " " << C[4] << " " << C[5] << " " /*<< C[6]*/ << endl;
	} catch (Polynom<>::ArrayOutOfBoundsException e) {}
	cout << C(1) << " " << C(2) << " " << C(2.5) << endl; 
	
	Polynom<double> D(vec_d);
	D.Print();
	cout << D(2.5) << endl;
	
	C = B.Derivative();
	B.Print();
	C.Print();
	
	_getch();
	return 0;
}
	