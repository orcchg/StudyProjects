#include <conio.h>
#include <stdio.h>

#include "class_sqrmtx.hpp"

//---------------------------------------------------------------
int f_i(int i, int j);
double f_d(int i, int j);
//---------------------------------------------------------------


int main()
{
	int num = 1;
	
	int** eArr = new int*[2];
	for(int i = 0; i < 2; ++i) {
		eArr[i] = new int[2];
	}	
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			eArr[i][j] = num++;
		}
	}
	
	
	num = 1;
	
	double** dArr = new double*[2];
	for(int i = 0; i < 2; ++i) {
		dArr[i] = new double[2];
	}	
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			dArr[i][j] = num++;
		}
	}
	
	
	int** Em = new int*[2];
	for(int i = 0; i < 2; ++i) {
		Em[i] = new int[2];
	}
	for(int i = 0; i < 2; ++i) {
		for(int j = 0; j < 2; ++j) {
			if (j == i) {
				Em[i][j] = 1;
			} else {
				Em[i][j] = 0;
			}
		}
	}
	
	
	int** Em3 = new int*[3];
	for(int i = 0; i < 3; ++i) {
		Em3[i] = new int[3];
	}
	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3; ++j) {
			if (j == i) {
				Em3[i][j] = 1;
			} else {
				Em3[i][j] = 0;
			}
		}
	}
	//-----------------------------------------------------------------
try {	
	SquareMatrix<> A; // 2x2 with thrash
	SquareMatrix<double,3> B(55.555);
	SquareMatrix<> C(eArr, 2);
	SquareMatrix<> O2(1);
	SquareMatrix<int,3> O3(1);
	SquareMatrix<> E2(Em, 2);
	SquareMatrix<int,3> E3(Em3, 3); 
	
/*	A.Print();
	B.Print();
	C.Print();
	O2.Print();
	O3.Print();
	E2.Print();
	E3.Print();
*/	
	double b = B(1,2);
	printf("%lf\n", b);
	//-----------------------------------------------------------------
	
	SquareMatrix<> CE = C * E2;
	C.Print();
	E2.Print();
	CE.Print();
	
	SquareMatrix<double,3> BB(1.1);
	BB *= B;
	BB -= BB;
	BB += B;
	BB.Print();
	printf("%lf\n", BB(2,0));
	
	SquareMatrix<int,4> R1(2);
	SquareMatrix<int,4> R2(3);
	R1 = R2;
	R1.Print();
	
	SquareMatrix<double> I1(5);
	SquareMatrix<double> I2(2.5);
	I1 = I1 * 2;
	I1.Print();
	
	SquareMatrix<double,5> F1(&f_d);
	SquareMatrix<> F2(&f_i);
	F1.Print();
	F2.Print();
	
	printf("%d %d\n", C.Trace(), C.Determinant());
	printf("%d %d\n", F2.Trace(), F2.Determinant());
	
	SquareMatrix<> CT = C.Transpose();
	CT.Print();
	
	CT = CT.Inverse();
	CT.Print();
	
	SquareMatrix<double,2> Cdbl(dArr, 2);
	SquareMatrix<double> CTdbl = Cdbl.Transpose();
	CTdbl = CTdbl.Inverse();
	CTdbl.Print();
	
	//-----------------------------------------------------------------
} catch (const SquareMatrix<>::xDimDiscrepancy & e) {}	
	
	_getch();
	return 0;
}
//---------------------------------------------------------------


//---------------------------------------------------------------
int f_i(int i, int j) 
{
	return (i + 1) * (j - 3);
}
//---------------------------------------------------------------

//---------------------------------------------------------------
double f_d(int i, int j)
{
	return (i - 1.5) * (j + 1.5);
}
//---------------------------------------------------------------