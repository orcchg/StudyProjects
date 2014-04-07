#include <cstdlib>
#include <stdio.h>
#include <math.h>

typedef double elem_t;

class Matrix {
			  int N; //number of columns
			  int M; //number of strings
			  elem_t** ptr; //pointer to 2D-array
			   
	public:
			/* Default Constructor: */
			Matrix();
			
			/* Constructor with params: */
			Matrix(int cols, int str) {
				N = cols;
				M = str;
				
				/* Space allocation for matrix: */
				ptr = new elem_t*[N];
				for(int k = 0; k < N; ++k)
					ptr[k] = new elem_t[M];
				
				/* Zero initialization: */
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < M; ++j) {
						ptr[i][j] = 0;
					}
				}	
			}
			
			/* Copy - Constructor: */
			Matrix(const Matrix& Obj) {
				N = Obj.N;
				M = Obj.M;
				
				/* Space allocation for matrix: */
				ptr = new elem_t*[N];
				for(int k = 0; k < N; ++k)
					ptr[k] = new elem_t[M];
				
				/* Copy initialization */
				for (int i = 0; i < N; ++i) {
					for (int j = 0; j < M; ++j) {
						ptr[i][j] = Obj.ptr[i][j];
					}
				}
			}
			
			/* Destructor (Garbage collection): */
			~Matrix() {
				for(int k = 0; k < N; ++k)
					delete [] ptr[k];
				delete [] ptr;
			}
			
			/* Methods: */
			void Fill(elem_t** pArr);	
			void Print() const;
			void Print(double) const; //To show double-values
			Matrix* Mirror(); //This method changes initial Matrix!
			Matrix Transpose() const;
			Matrix Inverse() const;
			
			/* Operations: */
			Matrix* operator=(const Matrix& rhs);
			Matrix operator+(const Matrix& rhs) const;
			Matrix operator-(const Matrix& rhs) const;
			Matrix operator*(const Matrix& rhs) const;
			Matrix operator*(elem_t rhs) const;
			
			/* Functions: */
			elem_t Determinant() const;
			elem_t Trace() const;
};

/********** METHODS **********/

void Matrix::Fill(elem_t** pArr) {

	for (int j = 0; j < M; ++j) {
		for (int i = 0; i < N; ++i) {
			ptr[i][j] = pArr[i][j];
		}
	}
}


void Matrix::Print() const {

	for (int j = 0; j < M; ++j) {
		for (int i = 0 ; i < N ; ++i) {
			printf("%d ",ptr[i][j]);
		}
		printf("\n\n");
	}
}


void Matrix::Print(double db) const {

	for (int j = 0; j < M; ++j) {
		for (int i = 0 ; i < N ; ++i) {
			printf("%.3lf ",(double)ptr[i][j]);
		}
		printf("\n\n");
	}
}


Matrix* Matrix::Mirror() {

	Matrix temp(this->N, this->M);
	
	for (int j = 0; j < M; ++j) {
        for (int i = 0 ; i < N ; ++i)
        {
            temp.ptr[i][j] = this->ptr[N-i-1][M-j-1];
        }
	}	
	
	for (int j = 0; j < M; ++j) {
        for (int i = 0 ; i < N ; ++i) {
            this->ptr[i][j] = temp.ptr[i][j];
        }
	}
	
	return this;
	
}


Matrix Matrix::Transpose() const {

	Matrix temp(this->M, this->N);
	
	for (int j = 0; j < M; ++j) {
        for (int i = 0 ; i < N ; ++i) {
            temp.ptr[j][i] = this->ptr[i][j];
        }
	}
	return temp;
	
}


Matrix Matrix::Inverse() const {

	Matrix temp(this->N, this->M);
	Matrix err(0,0);

	if(N != M) {
		printf("Non-square Matrix! Return 0!\n");
		return err;
		
	} else {
		elem_t det = this->Determinant();
		
		if (det == 0) {
			printf("Confluent Matrix! Det = 0!\n");
			return err;
		} else {	
		
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < M; ++j) {
			
				Matrix Minor(N-1,M-1);
				
				/* Initialization of Minor(j,i): */
				for(int k = 0; k < N-1; ++k) {
					if(k < j) {
						for(int l = 0; l < M-1; ++l) {
							if(l < i) {
								Minor.ptr[k][l] = ptr[i-1][j-1]; // i = 1 , j = 1
							} else {
								Minor.ptr[k][l] = ptr[i+1][j-1]; // i = 0 , j = 1
							}
						}
					} else {
						for(int l = 0; l < M-1; ++l) {
							if(l < i) {
								Minor.ptr[k][l] = ptr[i-1][j+1]; // i = 1 , j = 0
							} else {
								Minor.ptr[k][l] = ptr[i+1][j+1]; // i = 0 , j = 0
							}
						}
					}
				}
				temp.ptr[i][j] = pow(-1,i+j)*(double)Minor.Determinant()/det;
			}
		}
		}
		
	}
	return temp;
	
}


/******************************/

/********** OPERATIONS **********/

Matrix* Matrix::operator=(const Matrix& rhs)
{
	if((this->N != rhs.N) || (this->M != rhs.M)) {
			printf("Not relevant dimensions of RHS! Operation ABORT!\n");
		return this;
		
	} else {
		for(int j = 0; j < M; ++j) {
			for(int i = 0; i < N; ++i) {
				this->ptr[i][j] = rhs.ptr[i][j];
			}
		}
	}
	return this;
	
}


Matrix Matrix::operator+(const Matrix& rhs) const
{
	Matrix temp(N,M);

	if((N != rhs.N) || (M != rhs.M)) {
		Matrix err(0,0);
		printf("Not relevant dimensions of RHS! Return NULL-Matrix!\n");
		return err;
		
	} else {	
		for(int j = 0; j < M; ++j) {
			for(int i = 0; i < N; ++i) {
				temp.ptr[i][j] = ptr[i][j] + rhs.ptr[i][j];
			}
		}
		
	}
	return temp;
	
}


Matrix Matrix::operator-(const Matrix& rhs) const
{
	Matrix temp(N,M);

	if((N != rhs.N) || (M != rhs.M)) {
		Matrix err(0,0);
		printf("Not relevant dimensions of RHS! Return NULL-Matrix!\n");
		return err;
		
	} else {			
		for(int j = 0; j < M; ++j) {
			for(int i = 0; i < N; ++i) {
				temp.ptr[i][j] = ptr[i][j] - rhs.ptr[i][j];
			}
		}
		
	}
	return temp;
	
}


Matrix Matrix::operator*(const Matrix& rhs) const
{
	int tN = rhs.N;
	int tM = M;
	Matrix temp(tN,tM);
	
	if(N != rhs.M) {
		Matrix err(0,0);
		printf("Not relevant dimension M of RHS! Return NULL-Matrix!\n");
		return err;
		
	} else {
		
		for(int k = 0; k < tM; ++k) {
			for(int l = 0; l < tN; ++l) {
				
				for(int i = 0; i < N; ++i) {
					temp.ptr[l][k] += ptr[i][k] * rhs.ptr[l][i];
				}

			}
		}
		
	}	
	return temp;
	
}

Matrix Matrix::operator*(elem_t rhs) const
{
	Matrix temp(N,M);
	
	for (int j = 0; j < M; ++j) {
		for(int i = 0; i < N; ++i) {
			temp.ptr[i][j] = (this->ptr[i][j])*rhs;
		}
	}
	return temp;
	
}
/********************************/	

/********** FUNCTIONS ***********/

elem_t Matrix::Determinant() const 
{
	elem_t det = 0;

	if(N != M) {
		printf("Non-square Matrix! Return 0!\n");
		return 0;
	
	} else if (N == 1) {
		return ptr[0][0];
	
	} else {
		int l = 0;
		
		for(int k = 0; k < N; ++k) {
			
			Matrix Minor(N-1,N-1); 
			
			/* Initialization of Minor(k,l): */
			for(int i = 0; i < N-1; ++i) {
				if (i < k) {
					for(int j = 0; j < N-1; ++j) {
						if(j < l) {
							Minor.ptr[i][j] = this->ptr[i][j];
						} else {
							Minor.ptr[i][j] = this->ptr[i][j+1];
						}
					}
				} else {
					for(int j = 0; j < N-1; ++j) {
						if(j < l) {
							Minor.ptr[i][j] = this->ptr[i+1][j];
						} else {
							Minor.ptr[i][j] = this->ptr[i+1][j+1];
						}
					}
				}
			}
			det += pow(-1,k)*ptr[k][l]*Minor.Determinant();
		}
	}
	return det;
	
}


elem_t Matrix::Trace() const 
{
	elem_t Tr = 0;

	if(N != M) {
		printf("Non-square Matrix! Return 0!\n");
		return 0;
		
	} else {
		for(int i = 0; i < N; ++i) {
			Tr += ptr[i][i];
		}
	}
	return Tr;
	
}

/********************************/