typedef double elem_t;

class Matrix {
			  int N; //number of columns
			  int M; //number of strings
			  elem_t** ptr; //pointer to 2D-array
			   
	public:
			/* Default Constructor: */
			Matrix();
			
			/* Constructor with params: */
			Matrix(int cols, int str);
			
			/* Copy - Constructor: */
			Matrix(const Matrix& Obj);
					
			/* Destructor (Garbage collection): */
			~Matrix();
			
			
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
/****************************************************************/