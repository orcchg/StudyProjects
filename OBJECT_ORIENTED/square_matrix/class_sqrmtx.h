#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

#ifndef OBJECT_ORIENTED_SQUARE_MATRIX_H

#define OBJECT_ORIENTED_SQUARE_MATRIX_H

template <typename T = int, int dim = 2>
class SquareMatrix
{
	private:
		int dimension;
		T** pArray;
	
	public:
		SquareMatrix();
		SquareMatrix(const T number);
		SquareMatrix(T** eArr, int N);
		SquareMatrix(const SquareMatrix & Obj);
		SquareMatrix(const SquareMatrix & Obj, int k, int l);
		SquareMatrix(T (*f)(int i, int j) );
		~SquareMatrix();
		
		const SquareMatrix operator + (const SquareMatrix & rhs);
		const SquareMatrix operator - (const SquareMatrix & rhs);
		const SquareMatrix operator * (const SquareMatrix & rhs);
		const SquareMatrix operator * (const T number);
		
		SquareMatrix operator =  (const SquareMatrix & rhs);
		
		SquareMatrix & operator += (const SquareMatrix & rhs);
		SquareMatrix & operator -= (const SquareMatrix & rhs);
		SquareMatrix & operator *= (const SquareMatrix & rhs);
		
		bool 		 operator == (const SquareMatrix & rhs) const;
		bool 		 operator != (const SquareMatrix & rhs) const;
		
		T			 operator () (int i, int j) const;
		
		T Trace() const;
		T Determinant() const;
		
		SquareMatrix Transpose() const;
		SquareMatrix Inverse() const;
		
		void Print() const;
		
		//-----------------------------------------------------------------------------
		class xDimDiscrepancy {
			public:
				xDimDiscrepancy() {
					cout << "Dimensions of operands are incompatible!\n";
				}
				~xDimDiscrepancy() {}
		};
		//-----------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::SquareMatrix()
{
	dimension = dim;
	
	pArray = new T*[dimension];
	for(int i = 0; i < dimension; ++i) {
		pArray[i] = new T[dimension];
	}
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::SquareMatrix(const T number)
{
	dimension = dim;
	
	pArray = new T*[dimension];
	for(int i = 0; i < dimension; ++i) {
		pArray[i] = new T[dimension];
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			pArray[i][j] = number;
		}
	}
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::~SquareMatrix()
{
	for(int i = 0; i < dimension; ++i) {
		delete pArray[i];
	}
	delete [] pArray;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::SquareMatrix(T** eArr, int N)
{
	dimension = dim;
	
	if (dimension != N) {
		throw xDimDiscrepancy();
	}
	
	pArray = new T*[dimension];
	for(int i = 0; i < dimension; ++i) {
		pArray[i] = new T[dimension];
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			pArray[i][j] = eArr[i][j];
		}
	}
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::SquareMatrix(const SquareMatrix & Obj)
{
	dimension = Obj.dimension;
	
	pArray = new T*[dimension];
	for(int i = 0; i < dimension; ++i) {
		pArray[i] = new T[dimension];
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			pArray[i][j] = Obj.pArray[i][j];
		}
	}
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::SquareMatrix(const SquareMatrix & Obj, int k, int l)
{
	dimension = Obj.dimension - 1;
	
	pArray = new T*[dimension];
	for(int i = 0; i < dimension; ++i) {
		pArray[i] = new T[dimension];
	}
	
	for(int i = 0; i < dimension; ++i) {
		if (i < k) {
			for(int j = 0; j < dimension; ++j) {
				if (j < l) {
					pArray[i][j] = Obj.pArray[i][j];
				} else {
					pArray[i][j] = Obj.pArray[i][j+1];
				}
			}
		} else {
			for(int j = 0; j < dimension; ++j) {
				if (j < l) {
					pArray[i][j] = Obj.pArray[i+1][j];
				} else {
					pArray[i][j] = Obj.pArray[i+1][j+1];
				}
			}
		}
	}			
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim>::SquareMatrix(T (*f)(int i, int j)) 
{
	dimension = dim;
	
	pArray = new T*[dimension];
	for(int i = 0; i < dimension; ++i) {
		pArray[i] = new T[dimension];
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			pArray[i][j] = f(i, j);
		}
	}
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
const SquareMatrix<T,dim> SquareMatrix<T,dim>::operator + (const SquareMatrix & rhs)
{
	SquareMatrix<T,dim> temp;
	
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			temp.pArray[i][j] = this->pArray[i][j] + rhs.pArray[i][j];
		}
	}
	
	return temp;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
const SquareMatrix<T,dim> SquareMatrix<T,dim>::operator - (const SquareMatrix & rhs)
{
	SquareMatrix<T,dim> temp;
	
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			temp.pArray[i][j] = this->pArray[i][j] - rhs.pArray[i][j];
		}
	}
	
	return temp;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
const SquareMatrix<T,dim> SquareMatrix<T,dim>::operator * (const SquareMatrix & rhs)
{
	SquareMatrix<T,dim> temp(0.0);
	
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}
	
	for(int j = 0; j < dimension; ++j) {
		for(int i = 0; i < dimension; ++i) {
		
			for(int k = 0; k < dimension; ++k) {
				temp.pArray[i][j] += this->pArray[k][j] * rhs.pArray[i][k];
			}
			
		}
	}
	
	return temp;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
const SquareMatrix<T,dim> SquareMatrix<T,dim>::operator * (const T number)
{
	SquareMatrix<T,dim> temp(*this);
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			temp.pArray[i][j] *= number;
		}
	}
	
	return temp;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim> SquareMatrix<T,dim>::operator = (const SquareMatrix & rhs)
{
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}

	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			this->pArray[i][j] = rhs.pArray[i][j];
		}
	}
	
	return *this;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim> & SquareMatrix<T,dim>::operator += (const SquareMatrix & rhs)
{
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}

	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			this->pArray[i][j] = this->pArray[i][j] + rhs.pArray[i][j];
		}
	}
	
	return *this;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim> & SquareMatrix<T,dim>::operator -= (const SquareMatrix & rhs)
{
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			this->pArray[i][j] = this->pArray[i][j] - rhs.pArray[i][j];
		}
	}
	
	return *this;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim> & SquareMatrix<T,dim>::operator *= (const SquareMatrix & rhs)
{
	SquareMatrix<T,dim> temp(0.0);
	
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}
	
	for(int j = 0; j < dimension; ++j) {
		for(int i = 0; i < dimension; ++i) {
		
			for(int k = 0; k < dimension; ++k) {
				temp.pArray[i][j] += this->pArray[k][j] * rhs.pArray[i][k];
			}
			
		}
	}
	
	*this = temp;
	return *this;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
bool SquareMatrix<T,dim>::operator == (const SquareMatrix & rhs) const
{
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}

	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			if (this->pArray[i][j] != rhs.pArray[i][j]) {
				return false;
			}
		}
	}
	return true;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
bool SquareMatrix<T,dim>::operator != (const SquareMatrix & rhs) const
{
	if (dimension != rhs.dimension) {
		throw xDimDiscrepancy();
	}

	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			if (this->pArray[i][j] != rhs.pArray[i][j]) {
				return true;
			}
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
T SquareMatrix<T,dim>::operator () (int i, int j) const
{
	return pArray[i][j];
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
void SquareMatrix<T,dim>::Print() const
{
	for(int j = 0; j < dimension; ++j) {
		for(int i = 0; i < dimension; ++i) {
			cout << pArray[i][j] << " ";
		}
		cout << endl;
	}
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
T SquareMatrix<T,dim>::Trace() const
{
	T trace = 0.0;
	for(int i = 0; i < dimension; ++i) {
		trace += pArray[i][i];
	}
	return trace;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
T SquareMatrix<T,dim>::Determinant() const
{
	T det = 0.0;
	int j = 0;
	
	if (dimension == 1) {
		return pArray[0][0];
	}
	
	for(int i = 0; i < dimension; ++i) {
		SquareMatrix<T,dim> Minor(*this, i, j);
		det += pow(-1, i) * pArray[i][j] * Minor.Determinant();
	}
	return det;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim> SquareMatrix<T,dim>::Transpose() const
{
	SquareMatrix<T,dim> temp;
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			temp.pArray[i][j] = pArray[j][i];
		}
	}
	return temp;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
template <typename T, int dim>
SquareMatrix<T,dim> SquareMatrix<T,dim>::Inverse() const
{
	SquareMatrix<T,dim> temp(*this);
	
	T det = this->Determinant();
	
	if (det == 0.0) {
		cout << "Confluent Matrix!" << endl;
		return temp;
	}
	
	for(int i = 0; i < dimension; ++i) {
		for(int j = 0; j < dimension; ++j) {
			SquareMatrix<T,dim> Minor(*this, j, i);
			temp.pArray[i][j] = (double)pow(-1, i + j) * Minor.Determinant() / det;
		}
	}
	return temp;
}
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------

#endif
		