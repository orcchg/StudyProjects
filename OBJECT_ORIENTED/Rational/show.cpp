#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "class_rational.hpp"

int main()
{
	try {
		Rational A(3, 5);
		Rational B(4, 7);
		Rational C(1, 2);
		Rational D(1, 3);
		Rational E(1, 6);
	
		Rational K(0, 1);
	
	K = E + D;
	K.Show();
//	E.Show();
	
	K = C - D;
	K.Show();
//	C.Show();
	
	K = A * B;
	K.Show();
//	A.Show();
	
	K = C / B;
	K.Show();
//	C.Show();

	B.Show();
	K = -B;
	K.Show();
	B.Show();


//------------------------------------------------------

		Rational F(17, 34);
		Rational G(9, 15);

	if (F == C) {
		cout << "F = C" << endl;
	} else {
		cout << "F != C Wrong!" << endl;
	}
	
	if (G != C) {
		cout << "G != C" << endl;
	} else {
		cout << "G == C Wrong!" << endl;
	}
	
	if (G == A) {
		cout << "G = A" << endl;
	} else {
		cout << "G != A Wrong!" << endl;
	}
	
	if (C > D) {
		cout << "C > D" << endl;
	} else {
		cout << "C <= D Wrong!" << endl;
	}
	
	if (E < D) {
		cout << "E < D" << endl;
	} else {
		cout << "E >= D Wrong!" << endl;
	}
	
	if (F >= C) {
		cout << "F >= C" << endl;
	} else {
		cout << "F < C Wrong!" << endl;
	}
	
	if (A <= G) {
		cout << "A <= G" << endl;
	} else {
		cout << "A > G Wrong!" << endl;
	}
	
//		Rational I(1, 0);
//		Rational J(0, 0);
		Rational L(0, 15);
//		I.Show();
//		J.Show();
		L.Show();
		
		K.Show();
		K = L - K;
		K.Show();
//		K = K / L;
		K.Show();
		
		} catch (const Rational::xZeroDenom & e) {}
		  catch (const Rational::xDivByZero & ex) {}
	
	cin.ignore();
	return 0;
}