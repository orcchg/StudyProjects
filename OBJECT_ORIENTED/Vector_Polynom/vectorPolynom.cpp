#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::vector;

template <typename T = int>
class Polynomial {
	public:
    Polynomial() : m_power(-1) {}  // Null Polynomials are empty and have power = -1
		Polynomial(const Polynomial & Obj);
		Polynomial(const vector<T>& vec);
		
		/* Polynomial rhs */
		const Polynomial operator + (const Polynomial & rhs) const; 
		const Polynomial operator - (const Polynomial & rhs) const;	  
		const Polynomial operator * (const Polynomial & rhs) const; 
		const Polynomial operator / (const Polynomial & rhs) const; 
		const Polynomial operator % (const Polynomial & rhs) const;	 
		
		Polynomial operator + () const;	 
		Polynomial operator - () const; 
		
		/* Scalar rhs */
		const Polynomial operator + (const T& rhs) const; 
		const Polynomial operator - (const T& rhs) const; 
		const Polynomial operator * (const T& rhs) const; 
		const Polynomial operator / (const T& rhs) const; 
		const Polynomial operator % (const T& rhs) const; 
		
		Polynomial& operator = (const Polynomial & rhs); 
		Polynomial& operator = (const T& rhs); 			 
		
		/* Polynomial rhs */
		Polynomial & operator += (const Polynomial & rhs); 
		Polynomial & operator -= (const Polynomial & rhs); 
		Polynomial & operator *= (const Polynomial & rhs);	 
		Polynomial & operator /= (const Polynomial & rhs);	 
		Polynomial & operator %= (const Polynomial & rhs);	 
		
		/* Scalar rhs */
		Polynomial & operator += (const T& rhs); 
		Polynomial & operator -= (const T& rhs); 
		Polynomial & operator *= (const T& rhs); 
		Polynomial & operator /= (const T& rhs); 
		Polynomial & operator %= (const T& rhs); 
		
		/* Bool operators */
		bool			operator == (const Polynomial & rhs) const; 
		bool 			operator != (const Polynomial & rhs) const; 
		
			/* Lexicographical compare */
			bool		  operator <  (const Polynomial & rhs) const;	 
			bool 			operator <= (const Polynomial & rhs) const;	 
			bool 			operator >  (const Polynomial & rhs) const;	 
			bool 			operator >= (const Polynomial & rhs) const;	 
		
		/* Braces operations */
		T 				operator () (const T& value);   		 
		const T 	operator () (const T& value) const; 
		T&				operator [] (size_t index);			  	 
		const T&  operator [] (size_t index) const;		 
		
		/* Maths operations */
		int GetPower() const;	 						 
		const Polynomial Derivative() const; 
		const Polynomial operator , (const Polynomial & rhs) const;	 
		
		/* Output */
		void Print() const;  // Show power and coefficients
		//-------------------------------------------------------------------------
		friend std::ostream& operator << (std::ostream& out, const Polynomial & Obj) {
		// Show formula
		  if (!Obj.coeff.empty()) {
				Polynomial<T> temp(Obj);
				if (temp.m_power >= 0) {
				  if (temp.coeff[0] != 0) {
						out << temp.coeff[0] << ' ';
					}
				}
				if (temp.m_power >= 1) {
					if (temp.coeff[1] > 0 && temp.coeff[1] != 1 && temp.coeff[0] != 0) {
						out << "+ " << temp.coeff[1] << "x ";
					} else if (temp.coeff[1] == 1  && temp.coeff[0] != 0) {
						out << "+ " << "x ";
					} else if (temp.coeff[1] < 0 && temp.coeff[1] != -1  && temp.coeff[0] != 0) {
						out << "- " << -temp.coeff[1] << "x ";
					} else if (temp.coeff[1] == -1  && temp.coeff[0] != 0) {
						out << "- x ";
					} else if (temp.coeff[1] > 0 && temp.coeff[1] != 1 && temp.coeff[0] == 0) {
						out << temp.coeff[1] << "x ";
					} else if (temp.coeff[1] == 1  && temp.coeff[0] == 0) {
						out << "x ";
					} else if (temp.coeff[1] < 0 && temp.coeff[1] != -1  && temp.coeff[0] == 0) {
						out << "- " << -temp.coeff[1] << "x ";
					} else if (temp.coeff[1] == -1  && temp.coeff[0] == 0) {
						out << "- x ";
					}
				}
				if (temp.m_power >= 2) {
					for (size_t i = 2; i < temp.coeff.size(); ++i) {
						if (temp.coeff[i] == 0) {
							continue;
						} else {
							if (temp.coeff[i] > 0 && temp.coeff[i] != 1) {
								out << "+ " << temp.coeff[i] << "x^" << i << " ";
							} else if (temp.coeff[i] < 0 && temp.coeff[i] != -1) {
								out << "- " << -temp.coeff[i] << "x^" << i << " ";
							} else if (temp.coeff[i] == 1) {
								out << "+ " << "x^" << i << " ";
							} else if (temp.coeff[i] == -1) {
								out << "- " << "x^" << i << " ";
							}
						}
					}
				} 
			} else {
				out << "NULL";
			}
			return out;
		}
		//-------------------------------------------------------------------------
		
		/* Access iterator */	
		//-------------------------------------------------------------------------
		typedef typename vector<T>::iterator iterator;
		typedef typename vector<T>::const_iterator const_iterator;
		
		iterator begin() {
			return coeff.begin();
		}
		const_iterator begin() const {
			return coeff.begin();
		}
		iterator end() {
			return coeff.end();
		}
		const_iterator end() const {
			return coeff.end();
		}
		//-------------------------------------------------------------------------
		
		/* Exceptions */
		//-------------------------------------------------------------------------
		class ArrayOutOfBoundsException {
			public:
				ArrayOutOfBoundsException() { 
				  cerr << "Index out of bounds!\n"; 
				}
				~ArrayOutOfBoundsException()
				{}
		};	
		//-------------------------------------------------------------------------
		class DivisionByZeroException {
		  public:
				DivisionByZeroException() {
					cerr << "Division by Zero!\n";
				}
				~DivisionByZeroException()
				{}
		};
		//-------------------------------------------------------------------------
    
    /* Monom class */
    //-------------------------------------------------------------------------
    class Monom {
      public:
        explicit Monom() : lambda(1)
        {}
        ~Monom() {}

        Polynomial<T> operator ^ (int power) const {
          Polynomial<T> temp;
          temp.coeff.resize(power + 1, 0);
          temp.coeff[power] = lambda;
          temp.m_power = power;
          return temp;
        }

        const Monom operator * (T rhs) const {
          Monom temp(rhs);
          return temp;
        }
 
        T lambda;
      private:
        explicit Monom(T lam) : lambda(lam)
        {}
    };
 
    Polynomial(const Monom & monom) : m_power(1) {
      coeff.resize(2, 0);
      coeff[1] = monom.lambda;
    }
    //-------------------------------------------------------------------------

	private:
		int m_power;
		vector<T> coeff;
		
		inline Polynomial<T> multiply(const Polynomial & current, T lambda, int power) const {
			// Multiplies current Polynomial on lambda * x^power
			Polynomial<T> result;
			result = current * lambda;
			while (power--) {
			  result.coeff.insert(result.coeff.begin(), 0);
			}
			result.m_power = current.m_power + power;
			while (result.coeff.size() != 0 && result.coeff.back() == T()) {
				result.coeff.pop_back();
				--result.m_power;
			}
			return result;
		}
		
		Polynomial(int) : m_power(0) {  // Scalar Polynomial
		  coeff.push_back(1);
		}
};
/*****************************************************************************/

/* Constructors */
//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>::Polynomial(const Polynomial & Obj) {
  if (Obj.coeff.empty()) {
    m_power = -1;
    return;
  }
	m_power = Obj.m_power;
	coeff.resize(Obj.coeff.size());
	for (size_t i = 0; i < coeff.size(); ++i) {
		coeff[i] = Obj.coeff[i];
	}
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>::Polynomial(const vector<T>& vec) {
  if (vec.empty()) {
    m_power = -1;
    return;
  }
	m_power = vec.size() - 1;
	coeff.resize(vec.size());
	coeff = vec;
}

/*****************************************************************************/

/* Polynomial rhs */
//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator + (const Polynomial & rhs) const {	
	int max_size = (coeff.size() > rhs.coeff.size()) 
			? coeff.size() : rhs.coeff.size();
	if (max_size == coeff.size()) {
	  Polynomial<T> temp(*this);
		if (!rhs.coeff.empty()) {
		  for (int index = 0; index < rhs.coeff.size(); ++index) {
			  temp.coeff[index] += rhs.coeff[index];
		  }
		}
		return temp;
	} else if (max_size == rhs.coeff.size()) {
		Polynomial<T> temp(rhs);
		if (!coeff.empty()) {
			for (size_t index = 0; index < coeff.size(); ++index) {
				temp.coeff[index] += coeff[index];
			}
		}
		return temp;
	}
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator - (const Polynomial & rhs) const {	
	int max_size = (coeff.size() > rhs.coeff.size()) 
			? coeff.size() : rhs.coeff.size();
	if (max_size == coeff.size()) {
	  Polynomial<T> temp(*this);
		if (!rhs.coeff.empty()) {
		  for (int index = 0; index < rhs.coeff.size(); ++index) {
			  temp.coeff[index] -= rhs.coeff[index];
		  }
		}
		return temp;
	} else if (max_size == rhs.coeff.size()) {
		Polynomial<T> temp(rhs);
		if (!coeff.empty()) {
			for (size_t index = 0; index < coeff.size(); ++index) {
				temp.coeff[index] -= coeff[index];
			}
		}
		temp *= -1;
		return temp;
	}
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator * (const Polynomial & rhs) const {
  Polynomial<T> temp;
  if (!coeff.empty() && !rhs.coeff.empty()) { 
	  Polynomial<T> this_temp(*this);
		Polynomial<T> rhs_temp(rhs);
		temp.m_power = m_power + rhs.m_power;
		this_temp.coeff.resize(temp.m_power + 1, 0);
		rhs_temp.coeff.resize(temp.m_power + 1, 0);
		temp.coeff.resize(temp.m_power + 1, 0);
		for (size_t i = 0; i < temp.coeff.size(); ++i) {
		  for (size_t j = 0; j <= i; ++j) {
				temp.coeff[i] += this_temp.coeff[j] * rhs_temp.coeff[i - j]; 
			}
		}
	}
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator / (const Polynomial & rhs) const {
  if (!rhs.coeff.empty()) {
	  if (m_power < rhs.m_power) {
		  return Polynomial<T>();
		}
		Polynomial<T> temp;
		Polynomial<T> this_temp(*this);
		Polynomial<T> rhs_temp(rhs);
		int previous_power = m_power;
		temp.m_power = (m_power - rhs.m_power) >= 0 ? m_power - rhs.m_power : -1;
		while (rhs_temp.m_power <= this_temp.m_power) {
			T quotient = this_temp.coeff.back() / rhs_temp.coeff.back();
			if (quotient == T()) {
			  break;
			}
			temp.coeff.push_back(quotient);
			this_temp -= multiply(rhs_temp, quotient, this_temp.m_power - rhs_temp.m_power);
			if (previous_power - this_temp.m_power > 1 && this_temp.m_power >= 0) {  
				// Don't skip intermediate zeros!
			  for (int power_count = 0; 
				     power_count + 1 < previous_power - this_temp.m_power; 
						 ++power_count) {
					temp.coeff.push_back(T());
				}
			}
			previous_power = this_temp.m_power;
		}
		reverse(temp.coeff.begin(), temp.coeff.end());
		return temp;
	} else {
	  throw DivisionByZeroException();
	}
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator % (const Polynomial & rhs) const {
	if (!rhs.coeff.empty()) {
	  Polynomial<T> temp(*this);
		while (temp.m_power >= rhs.m_power) {
		  T quotient = temp.coeff.back() / rhs.coeff.back();
			if (quotient == T()) { 
			  break;
			}
			temp -= multiply(rhs, quotient, temp.m_power - rhs.m_power);
		}
		return temp;
	} else {
	  throw DivisionByZeroException();
	}
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T> Polynomial<T>::operator + () const {
  Polynomial<T> temp(*this);
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T> Polynomial<T>::operator - () const {
	Polynomial<T> temp(*this);
	temp *= -1;
	return temp;
}

/*****************************************************************************/

/* Scalar rhs */
//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator + (const T& rhs) const {
	Polynomial<T> temp(*this);
	if (coeff.empty() && rhs != 0) {
	  temp.m_power = 0;
		temp.coeff.resize(1);
	}
	temp.coeff[0] += rhs; 
	
	// Collapse null Polynomial
	if (temp.coeff.size() == 1 && temp.coeff[0] == T()) {
	  temp.coeff.clear();
		temp.m_power = -1;
	}
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator - (const T& rhs) const {
	Polynomial<T> temp(*this);
	if (coeff.empty() && rhs != 0) {
	  temp.m_power = 0;
		temp.coeff.resize(1);
	}
	temp.coeff[0] -= rhs; 
	
	// Collapse null Polynomial
	if (temp.coeff.size() == 1 && temp.coeff[0] == T()) {
	  temp.coeff.clear();
		temp.m_power = -1;
	}
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator * (const T& rhs) const {
	Polynomial<T> temp(*this);
	if (!coeff.empty() && rhs != 0) {
	  for (size_t index = 0; index < temp.coeff.size(); ++index) {
		  temp.coeff[index] *= rhs;
	  }	
	} else if (rhs == 0) {  // Collapse null Polynomial
	  temp.coeff.clear();
		temp.m_power = -1;
	}
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator / (const T& rhs) const {
	Polynomial<T> temp(*this);
	if (rhs != 0) {
		if (!coeff.empty()) {
			for (size_t index = 0; index < temp.coeff.size(); ++index) {
				temp.coeff[index] /= rhs;
			}
			// Collapse null Polynomial
			while (temp.m_power >= 0 && temp.coeff.back() == T()) { 
				temp.coeff.pop_back();
				--temp.m_power;
			}
		}
	} else {
		throw DivisionByZeroException();
	}
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator % (const T& rhs) const {
	Polynomial<T> temp(*this);
	if (rhs != 0) {
		if (!coeff.empty()) {
			for (size_t index = 0; index < temp.coeff.size(); ++index) {
				temp.coeff[index] %= rhs;
			}
			// Collapse null Polynomial
			while (temp.m_power >= 0 && temp.coeff.back() == T()) { 
				temp.coeff.pop_back();
				--temp.m_power;
			}
		}
	} else {
		throw DivisionByZeroException();
	}
	return temp;
}

/*****************************************************************************/

/*****************************************************************************/
template <typename T>
Polynomial<T>& Polynomial<T>::operator = (const Polynomial & rhs) {
  Polynomial<T> temp(rhs);
	std::swap(m_power, temp.m_power);
	std::swap(coeff, temp.coeff);
	return *this;
}

template <typename T>
Polynomial<T>& Polynomial<T>::operator = (const T& rhs) {
  Polynomial<T> temp;
	if (rhs != 0) {
		temp.m_power = 0;
	  temp.coeff.resize(1, rhs);
	}
	std::swap(m_power, temp.m_power);
	std::swap(coeff, temp.coeff);
	return *this;
}
/*****************************************************************************/

/* Polynomial rhs */
//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator += (const Polynomial & rhs) {
	Polynomial<T> temp(*this);
	*this = temp + rhs;
	// Collapse null Polynomial
	while (m_power >= 0 && coeff.back() == T()) { 
		coeff.pop_back();
		--m_power;
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator -= (const Polynomial & rhs) {
	Polynomial<T> temp(*this);
	*this = temp - rhs;
	// Collapse null Polynomial
	while (m_power >= 0 && coeff.back() == T()) { 
		coeff.pop_back();
		--m_power;
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator *= (const Polynomial & rhs) {
  Polynomial<T> temp(*this);
	*this = temp * rhs;
	// Collapse null Polynomial
	while (m_power >= 0 && coeff.back() == T()) { 
		coeff.pop_back();
		--m_power;
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator /= (const Polynomial & rhs) {
  Polynomial<T> temp(*this);
	*this = temp / rhs;
	// Collapse null Polynomial
	while (m_power >= 0 && coeff.back() == T()) { 
		coeff.pop_back();
		--m_power;
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator %= (const Polynomial & rhs) {
  Polynomial<T> temp(*this);
	*this = temp % rhs;
	// Collapse null Polynomial
	while (m_power >= 0 && coeff.back() == T()) { 
		coeff.pop_back();
		--m_power;
	}
	return *this;
}

/*****************************************************************************/

/* Scalar rhs */
//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator += (const T& rhs) {
  if (!coeff.empty()) {
		coeff[0] += rhs;
	  if (m_power == 0 && coeff.back() == T()) {  // Collapse null Polynomial
		  coeff.pop_back();
			m_power = -1;
		}
	} else if (rhs != 0) {
	  coeff.resize(1, rhs);
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator -= (const T& rhs) {
	if (!coeff.empty()) {
		coeff[0] -= rhs;
	  if (m_power == 0 && coeff.back() == T()) {  // Collapse null Polynomial
		  coeff.pop_back();
			m_power = -1;
		}
	} else if (rhs != 0) {
	  coeff.resize(1, -rhs);
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator *= (const T& rhs) {
	if (rhs != 0) {
		if (!coeff.empty()) {
			for (int index = 0; index < coeff.size(); ++index) {
				this->coeff[index] *= rhs;
			}
		}
	} else {  // Collapse null Polynomial
	  coeff.clear();
		m_power = -1;
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator /= (const T& rhs) {
  if (rhs != 0) {
		if (!coeff.empty()) {
			for (int index = 0; index < coeff.size(); ++index) {
				this->coeff[index] /= rhs;
			}
			// Collapse null Polynomial
			while (m_power >= 0 && coeff.back() == T()) { 
				coeff.pop_back();
				--m_power;
			}
		}
	} else {
		throw DivisionByZeroException();
	}
	return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
Polynomial<T>& Polynomial<T>::operator %= (const T& rhs) {
	if (rhs != 0) {
		if (!coeff.empty()) {
			for (int index = 0; index < coeff.size(); ++index) {
				this->coeff[index] %= rhs;
			}
			// Collapse null Polynomial
			while (m_power >= 0 && coeff.back() == T()) { 
				coeff.pop_back();
				--m_power;
			}
		}
	} else {
		throw DivisionByZeroException();
	}
	return *this;
}

/*****************************************************************************/

/* Bool operators */
//-----------------------------------------------------------------------------
template <typename T>
bool Polynomial<T>::operator == (const Polynomial & rhs) const {
	return (coeff == rhs.coeff);
}

//-----------------------------------------------------------------------------
template <typename T>
bool Polynomial<T>::operator != (const Polynomial & rhs) const {
	return (coeff != rhs.coeff);
}

/* Lexicographical compare */
//-----------------------------------------------------------------------------
template <typename T>
bool Polynomial<T>::operator < (const Polynomial & rhs) const {
  Polynomial<T> this_temp(*this);
	Polynomial<T> rhs_temp(rhs);
  reverse(this_temp.coeff.begin(), this_temp.coeff.end());
	reverse(rhs_temp.coeff.begin(), rhs_temp.coeff.end());
	return (this_temp.coeff < rhs_temp.coeff);
}

//-----------------------------------------------------------------------------
template <typename T>
bool Polynomial<T>::operator <= (const Polynomial & rhs) const {
  Polynomial<T> this_temp(*this);
	Polynomial<T> rhs_temp(rhs);
  reverse(this_temp.coeff.begin(), this_temp.coeff.end());
	reverse(rhs_temp.coeff.begin(), rhs_temp.coeff.end());
	return (this_temp.coeff <= rhs_temp.coeff);
}

//-----------------------------------------------------------------------------
template <typename T>
bool Polynomial<T>::operator > (const Polynomial & rhs) const {
  Polynomial<T> this_temp(*this);
	Polynomial<T> rhs_temp(rhs);
  reverse(this_temp.coeff.begin(), this_temp.coeff.end());
	reverse(rhs_temp.coeff.begin(), rhs_temp.coeff.end());
	return (this_temp.coeff > rhs_temp.coeff);
}

//-----------------------------------------------------------------------------
template <typename T>
bool Polynomial<T>::operator >= (const Polynomial & rhs) const {
  Polynomial<T> this_temp(*this);
	Polynomial<T> rhs_temp(rhs);
  reverse(this_temp.coeff.begin(), this_temp.coeff.end());
	reverse(rhs_temp.coeff.begin(), rhs_temp.coeff.end());
	return (this_temp.coeff >= rhs_temp.coeff);
}

/*****************************************************************************/

/* Braces operations */
//-----------------------------------------------------------------------------
template <typename T>
T Polynomial<T>::operator () (const T& value) {
	if (coeff.empty()) {
		return T();
	} else if (m_power == 0) {
	  return coeff.back();
	}
	T result = coeff[m_power];
	int k = 0;
	while (k < m_power) {
		++k;
		result = result * value + coeff[m_power - k];
	}
	return result;
}

//-----------------------------------------------------------------------------
template <typename T>
const T Polynomial<T>::operator () (const T& value) const {
	if (coeff.empty()) {
		return T();
	} else if (m_power == 0) {
	  return coeff.back();
	}
	T result = coeff[m_power];
	int k = 0;
	while (k < m_power) {
		++k;
		result = result * value + coeff[m_power - k];
	}
	return result;
}

//-----------------------------------------------------------------------------
template <typename T>
T& Polynomial<T>::operator [] (size_t index) {
	if (m_power >= 0 && index >= 0 && index <= m_power) {
		return coeff[index];
	} else {
		throw ArrayOutOfBoundsException();
	}
}

//-----------------------------------------------------------------------------
template <typename T>
const T& Polynomial<T>::operator [] (size_t index) const {
	if (m_power >= 0 && index >= 0 && index <= m_power) {
		return coeff[index];
	} else {
		throw ArrayOutOfBoundsException();
	}
}

/*****************************************************************************/

/* Maths operations */
//-----------------------------------------------------------------------------
template <typename T>
int Polynomial<T>::GetPower() const {
	return m_power;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::Derivative() const {
	Polynomial<T> temp(*this);
	temp.m_power = m_power - 1;
	if (temp.m_power >= 0) {
		for (size_t index = 0; index + 1 < coeff.size(); ++index) {
			temp.coeff[index] = coeff[index + 1] * (index + 1);
		}
		temp.coeff.pop_back();
	}
	return temp;
}

//-----------------------------------------------------------------------------
template <typename T>
const Polynomial<T> Polynomial<T>::operator , (const Polynomial & rhs) const {
	Polynomial<T> this_temp(*this);
	Polynomial<T> rhs_temp(rhs);
	if (m_power < 0 || rhs.m_power < 0) {
		// Cannot get gcd from one or both null Polynomials
		return Polynomial<T>();	 
  } else if (m_power == 0 || rhs.m_power == 0) {
		// Mutual prime Polynomials, return scalar '1'
		return Polynomial<T>(1);  
	}
	Polynomial<T> previous_this(this_temp);
	Polynomial<T> previous_rhs(rhs_temp);
	while (this_temp.m_power >= 0 && rhs_temp.m_power >= 0) {
	  if (this_temp.m_power >= rhs_temp.m_power) {
		  this_temp %= rhs_temp;
			if (this_temp.m_power >= 0) {
				this_temp /= this_temp.coeff.back();
			}
			if (previous_this == this_temp) {
			  return Polynomial<T>(1);
			}
			previous_this = this_temp;
		} else {
		  rhs_temp %= this_temp;
			if (rhs_temp.m_power >= 0) {
				rhs_temp /= rhs_temp.coeff.back();
			}
			if (previous_rhs == rhs_temp) {
			  return Polynomial<T>(1);
			}
			previous_rhs = rhs_temp;
		}
	}
	Polynomial<T> GCD;
	if (this_temp.m_power < 0) {
	  GCD = rhs_temp;
	} else if (rhs_temp.m_power < 0) {
	  GCD = this_temp;
	}
	return GCD;
}

/*****************************************************************************/

/* Output */ 
//-----------------------------------------------------------------------------
template <typename T>
void Polynomial<T>::Print() const {
	cout << "POWER: " << m_power << ' ';
  if (!coeff.empty()) {
	  for (size_t index = 0; index < coeff.size(); ++index) {
	  	cout << coeff[index] << ' ';
	  }
  }
  cout << '\n';
}

/*****************************************************************************/
int main() {
	vector<int> a;
	for (int i = 1; i < 5; ++i) {
	  a.push_back(i);
	}
	vector<int> b;
	for (int i = 0; i < 7; ++i) {
	  int value = 4 - i;
	  b.push_back(value);
	}
	Polynomial<int> A(a);
	Polynomial<int> B(b);
	cout << "A = " << A << '\n' << "B = " << B << '\n';
	Polynomial<int> C;
	cout << "NULL Polynomial: " << C << " Power: " << C.GetPower() << '\n';
	C = A + B;
	cout << "A + B = " << C << '\n';
	C = A - B;
	cout << "A - B = " << C << '\n';
	C = 0;
	cout << "C = 0 <=> C: " << C << '\n';
	C += A;
	cout << "C += A: " << C << '\n';
	C -= B;
	cout << "C -= B: " << C << '\n';
	C += 7;
	cout << "C += 7: " << C << '\n';
	C -= 4;
	cout << "C -= 4: " << C << '\n';
	C *= 5;
	cout << "C *= 5: " << C << '\n';
	C /= 5;
	cout << "C /= 5: " << C << '\n';
	C %= 3;
	cout << "C %= 3: " << C << '\n';
	C = A * 0;
	cout << "C = A * 0: " << C << '\n';
	try {
	  C = A / 0;
	} catch (Polynomial<>::DivisionByZeroException e) {
    cout << "C = A / 0: Div by Zero exception!\n";
  }
	C = A * B;
	cout << "C = A * B: " << C << '\n';
	
	cout << "\n\n NEW PolynomialS INCLUDED: \n";
	vector<int> d;
	d.push_back(1); d.push_back(2); d.push_back(2); d.push_back(1);
	vector<int> f;
	f.push_back(-2); f.push_back(-2); f.push_back(-1); f.push_back(1); f.push_back(1);
	vector<int> g;
	g.push_back(1); g.push_back(2); g.push_back(3); g.push_back(4); g.push_back(5); g.push_back(6);
	vector<int> h;
	h.push_back(-1); h.push_back(1); h.push_back(3); h.push_back(5); h.push_back(7); h.push_back(9);
	vector<int> k;
	k.push_back(-1); k.push_back(-1); k.push_back(1); k.push_back(1);
	vector<int> z;
	z.push_back(1); z.push_back(1);
	vector<int> l;
	l.push_back(-2); l.push_back(10); l.push_back(12); l.push_back(-5); l.push_back(1); l.push_back(2);
	vector<int> m;
	m.push_back(7); m.push_back(-2); m.push_back(0); m.push_back(1);
	vector<int> n;
	n.push_back(-8); n.push_back(-4); n.push_back(2); n.push_back(5); n.push_back(2); n.push_back(-4); n.push_back(1);
	vector<int> p;
	p.push_back(-4); p.push_back(-4); p.push_back(1); p.push_back(-1); p.push_back(-1); p.push_back(1);
	Polynomial<int> D(d);  cout << "D: " << D << '\n';
	Polynomial<int> F(f);  cout << "F: " << F << '\n';
	Polynomial<int> G(g);  cout << "G: " << G << '\n';
	Polynomial<int> H(h);  cout << "H: " << H << '\n';
	Polynomial<int> K(k);  cout << "K: " << K << '\n';
	Polynomial<int> Z(z);	cout << "Z: " << Z << '\n';
	Polynomial<int> L(l);  cout << "L: " << L << '\n';
	Polynomial<int> M(m);  cout << "M: " << M << '\n';
	Polynomial<int> N(n);  cout << "N: " << N << '\n';
	Polynomial<int> P(p);  cout << "P: " << P << '\n';
	
	cout << "\n\n START CALCULATIONS\n";
	C = (D, F);
	cout << "C = GCD(D, F): " << C << '\n';
	C = H / G;
	cout << "C = H / G: " << C << '\n';
	C = K / Z;
	cout << "C = K / Z: " << C << '\n';
	C = (L, M);
	cout << "MUTUAL PRIME: C = GCD(L, M): " << C << '\n';
	C = (P, N);
	cout << "Inverse order: C = GCD(P, N): " << C << '\n';
	C = F % D;
	cout << "C = F % D: " << C << '\n';
	C = N % P;
	cout << "C = N % P: " << C << '\n';
	C = P % (N % P);
	cout << "C = P % (N % P): " << C << '\n';
	C = 108;
	C %= P;
	cout << "108 % P: " << C << '\n';
	C = 108;
	C /= P;
	cout << "108 / P: " << C << '\n';
	C = P / 1;
	cout << "C = P / 1: " << C << '\n';
	C = P;
	C /= 7;
	cout << "C = P; C /= 7: " << C << '\n';
	C = P;
	C /= 4;
	cout << "C = P; C /= 4: " << C << '\n';
	C += Z;
	cout << "C = P; C /= 4; C += Z: " << '\n';
	C = P / 4 + 1;
	cout << "C = P / 4 + 1: " << C << '\n';
	C = P / 4 + 2;
	C += Z;
	cout << "C = P / 4 + 2; C += Z: " << C << '\n';
	C = P = N;
	cout << "C = P = N: " << C << '\n';
	cout << "Get Power of C: " << C.GetPower() << '\n';
	C = -F;
	cout << "C = -F: " << C << '\n';
	C *= L;
	cout << "C = -F; C *= L: " << C << '\n';
	cout << "C(3): " << C(3) << '\n';
	cout << "C(0): " << C(0) << "  C(-2): " << C(-2) << '\n';
	cout << "C\' - derivative: " << C.Derivative() << "  Power: " << C.Derivative().GetPower() << '\n';
	C = 16;
	cout << "C = 16 - scalar; C\': " << C.Derivative() << "  Power: " << C.Derivative().GetPower() << '\n';
	
	C = N;
	cout << "\n\n Iterator from C.begin to C.end\nC = N: " << C << '\n';
	for (Polynomial<int>::iterator it = C.begin(); it != C.end(); ++it) {
	  cout << *it << ' ';
	}
	
	cout << "\n\n Bool operations\nC = N\n";
	if (C == N) {
	  cout << "True: C == N\n";
	} else {
	  cout << "WRONG BOOL OPERATOR!\n";
	}
	if (C != L) {
	  cout << "True: C != L\n";
	} else {
	  cout << "WRONG BOOL OPERATOR!\n";
	}
	
	cout << "\n\n Get C[ index ]: \n";
	cout << "C[0]: " << C[0] << " C[3]: " << C[3] << '\n';
	try {
	  cout << C[11] << '\n';
	} catch (Polynomial<int>::ArrayOutOfBoundsException e) {
	  cout << "C[11] is out of bounds!\n";
	}
	
	cout << "\n\n SUPER Special Polynomials\n";
	vector<int> x;
	x.push_back(0); x.push_back(1);
	vector<int> y;
	y.push_back(1); y.push_back(2);
	Polynomial<int> X(x);	cout << "X: " << X << '\n';
	Polynomial<int> Y(y);  cout << "Y: " << Y << '\n';
	C = (X, Y);
	cout << "C = GCD(X, Y): " << C << '\n';
	C = (Y, X);
	cout << "C = GCD(Y, X): " << C << '\n';
	C = X / Y;
	cout << "C = X / Y: " << C << '\n';
	C = Y / X;
	cout << "C = Y / X: " << C << '\n';
	C = Y % X;
	cout << "C = Y % X: " << C << '\n';
	C = X % Y;
	cout << "C = X % Y: " << C << '\n';
	
	vector<int> q;
	q.push_back(0); q.push_back(1);
	vector<int> t;
	t.push_back(0); t.push_back(4);
	Polynomial<int> Q(q);  cout << "Q: " << Q << '\n';
	Polynomial<int> T(t);  cout << "T: " << T << '\n';
	C = (Q, T);
	cout << "C = GCD(Q, T): " << C << '\n';
	C = (T, Q);
	cout << "C = GCD(T, Q): " << C << '\n';
	
	cout << "\n\n Double examples\n";
	vector<double> d1;
	d1.push_back(1.5); d1.push_back(2.3); d1.push_back(-3.4);
	vector<double> d2;
	d2.push_back(-0.6); d2.push_back(1.8);
	Polynomial<double> D1(d1);  cout << "D1: " << D1 << '\n';
	Polynomial<double> D2(d2);  cout << "D2: " << D2 << '\n';
	Polynomial<double> Result;
	Result = D1 / D2;
	cout << "Result = D1 / D2: " << Result << '\n';
	
  cout << "\n\n Monom Demo\n";
  Polynomial<int>::Monom _x;
  Polynomial<int> f_x = (_x^1)*4 + (_x^3) + (_x^5) + _x;
  cout << "Polynomial from Monom: " << f_x << '\n';
  Polynomial<double>::Monom _y;
  Polynomial<double> f_y = (_y^2) + _y + (_y^7)*2.71 + 0.59 + _y*0.91;
  cout << "Polynomial from Monom: " << f_y << '\n';
 
	cout << "Thank You for attention!\n";
  _getch();
	return 0;
}
