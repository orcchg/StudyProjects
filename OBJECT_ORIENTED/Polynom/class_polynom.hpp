#include <stdio.h>
#include <vector>
using std::vector;

#ifndef OBJECT_ORIENTED_CLASS_POLYNOM_H

#define OBJECT_ORIENTED_CLASS_POLYNOM_H

template <typename T = int>
class Polynom
{
	public:
		Polynom(int power);
		Polynom(const Polynom & Obj);
		Polynom(const vector<T> vec);
		~Polynom();
		
		/* Polynom rhs */
		const Polynom operator + (const Polynom & rhs) const;  // Done
		const Polynom operator - (const Polynom & rhs) const;	 // Done 
		const Polynom operator * (const Polynom & rhs) const;
		const Polynom operator / (const Polynom & rhs) const;
		const Polynom operator % (const Polynom & rhs) const;
		
		/* Scalar rhs */
		const Polynom operator + (const T& rhs) const;  // Done
		const Polynom operator - (const T& rhs) const;  // Done
		const Polynom operator * (const T& rhs) const;  // Done
		const Polynom operator / (const T& rhs) const;  // Done
		const Polynom operator % (const T& rhs) const;  // Done
		
		Polynom operator = (const Polynom & rhs);  // Done
		
		/* Polynom rhs */
		Polynom & operator += (const Polynom & rhs);  // Done
		Polynom & operator -= (const Polynom & rhs);  // Done
		Polynom & operator *= (const Polynom & rhs);
		Polynom & operator /= (const Polynom & rhs);
		Polynom & operator %= (const Polynom & rhs);
		
		/* Scalar rhs */
		Polynom operator += (const T& rhs);  // Done
		Polynom operator -= (const T& rhs);  // Done
		Polynom operator *= (const T& rhs);  // Done
		Polynom operator /= (const T& rhs);  // Done
		Polynom operator %= (const T& rhs);  // Done
		
		/* Bool operators */
		bool			operator == (const Polynom & rhs) const;  // Done
		bool 			operator != (const Polynom & rhs) const;  // Done
		bool			operator <  (const Polynom & rhs) const;
		bool			operator >  (const Polynom & rhs) const;
		bool 			operator <= (const Polynom & rhs) const;
		bool 			operator >= (const Polynom & rhs) const;
		
		/* Braces operations */
		T				operator () (const T& number) const;  // Done
		T				operator [] (int index) const;	// Done
		
		/* Maths operations */
		int GetPower() const;	 // Done
		const Polynom Derivative() const;  // Done
		const Polynom operator , (const Polynom & rhs) const;
		
		/* Other */
		void Print() const;  // Done
		
		//-------------------------------------------------------------------------
		class ArrayOutOfBoundsException
		{
			public:
				ArrayOutOfBoundsException() 
				{ printf("Index out of bounds!\n"); }
				~ArrayOutOfBoundsException()
				{}
		};	
		//-------------------------------------------------------------------------

	private:
		int m_power;
		vector<T> coeff;
};
/*****************************************************************************/

/* Constructors */
//-----------------------------------------------------------------------------
template <typename T>
Polynom<T>::Polynom(int power) 
{
	m_power = power - 1;
	coeff.resize(power);
	coeff.clear();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T>::Polynom(const Polynom & Obj) 
{
	m_power = Obj.m_power;
	coeff.resize(Obj.m_power + 1);
	coeff.clear();
	for (int i = 0; i <= Obj.m_power; ++i) {
		coeff[i] = Obj.coeff[i];
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T>::Polynom(const vector<T> vec)
{
	m_power = vec.size() - 1;
	coeff.resize(vec.size());
	for (int i = 0; i < vec.size(); ++i) {
		coeff[i] = vec[i];
	}
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T>::~Polynom()
{
	m_power = 0;
	coeff.clear();
	coeff.resize(0);
}
/*****************************************************************************/

/* Polynom rhs */
//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator + (const Polynom & rhs) const
{	
	int max_power = (this->m_power > rhs.m_power) ? this->m_power : rhs.m_power;
	
	Polynom<T> temp(max_power + 1);
	if (max_power == this->m_power) {
		for (int index = 0; index <= rhs.m_power; ++index) {
			temp.coeff[index] = this->coeff[index] + rhs.coeff[index];
		}
		for (int index = rhs.m_power + 1; index <= max_power; ++index) {
			temp.coeff[index] = this->coeff[index];
		}
	} else {
		for (int index = 0; index <= this->m_power; ++index) {
			temp.coeff[index] = this->coeff[index] + rhs.coeff[index];
		}
		for (int index = this->m_power + 1; index <= max_power; ++index) {
			temp.coeff[index] = rhs.coeff[index];
		}
	}
	
	return temp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator - (const Polynom & rhs) const
{
	int max_power = (this->m_power > rhs.m_power) ? this->m_power : rhs.m_power;
	
	Polynom<T> temp(max_power + 1);
	if (max_power == this->m_power) {
		for (int index = 0; index <= rhs.m_power; ++index) {
			temp.coeff[index] = this->coeff[index] - rhs.coeff[index];
		}
		for (int index = rhs.m_power + 1; index <= max_power; ++index) {
			temp.coeff[index] = this->coeff[index];
		}
	} else {
		for (int index = 0; index <= this->m_power; ++index) {
			temp.coeff[index] = this->coeff[index] - rhs.coeff[index];
		}
		for (int index = this->m_power + 1; index <= max_power; ++index) {
			temp.coeff[index] = -rhs.coeff[index];
		}
	}
	
	return temp;
}
/*****************************************************************************/

/* Scalar rhs */
//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator + (const T& rhs) const
{
	Polynom<T> temp(*this);
	temp.coeff[0] += rhs;
	
	return temp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator - (const T& rhs) const
{
	Polynom<T> temp(*this);
	temp.coeff[0] -= rhs;
	
	return temp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator * (const T& rhs) const
{
	Polynom<T> temp(*this);
	for (int index = 0; index <= temp.m_power; ++index) {
		temp.coeff[index] *= rhs;
	}
	
	return temp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator / (const T& rhs) const
{
	Polynom<T> temp(*this);
	for (int index = 0; index <= temp.m_power; ++index) {
		temp.coeff[index] /= rhs;
	}
	
	return temp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::operator % (const T& rhs) const
{
	Polynom<T> temp(*this);
	for (int index = 0; index <= temp.m_power; ++index) {
		temp.coeff[index] %= rhs;
	}
	
	return temp;
}
/*****************************************************************************/

/*****************************************************************************/
template <typename T>
Polynom<T> Polynom<T>::operator = (const Polynom & rhs) 
{
	this->m_power = rhs.m_power;
	this->coeff.resize(rhs.m_power + 1);
	
	for (int index = 0; index <= rhs.m_power; ++index) {
		this->coeff[index] = rhs.coeff[index];
	}
	
	return *this;
}
/*****************************************************************************/

/* Polynom rhs */
//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> & Polynom<T>::operator += (const Polynom & rhs)
{
	int max_power = (this->m_power > rhs.m_power) ? this->m_power : rhs.m_power;
	
	if (max_power == this->m_power) {
		for (int index = 0; index <= rhs.m_power; ++index) {
			this->coeff[index] += rhs.coeff[index];
		}
	} else {
		this->coeff.resize(rhs.m_power + 1);
		for (int index = 0; index <= this->m_power; ++index) {
			this->coeff[index] += rhs.coeff[index];
		}
		for (int index = this->m_power; index <= rhs.m_power; ++index) {
			this->coeff[index] = rhs.coeff[index];
		}
		this->m_power = max_power;
	}
	
	return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> & Polynom<T>::operator -= (const Polynom & rhs)
{
	int max_power = (this->m_power > rhs.m_power) ? this->m_power : rhs.m_power;
	
	if (max_power == this->m_power) {
		for (int index = 0; index <= rhs.m_power; ++index) {
			this->coeff[index] -= rhs.coeff[index];
		}
	} else {
		this->coeff.resize(rhs.m_power + 1);
		for (int index = 0; index <= this->m_power; ++index) {
			this->coeff[index] -= rhs.coeff[index];
		}
		for (int index = this->m_power; index <= rhs.m_power; ++index) {
			this->coeff[index] = -rhs.coeff[index];
		}
		this->m_power = max_power;
	}
	
	return *this;
}
//-----------------------------------------------------------------------------

/*****************************************************************************/

/* Scalar rhs */
//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> Polynom<T>::operator += (const T& rhs)
{
	this->coeff[0] += rhs;
	return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> Polynom<T>::operator -= (const T& rhs)
{
	this->coeff[0] -= rhs;
	return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> Polynom<T>::operator *= (const T& rhs)
{
	for (int index = 0; index <= m_power; ++index) {
		this->coeff[index] *= rhs;
	}
	
	return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> Polynom<T>::operator /= (const T& rhs)
{
	for (int index = 0; index <= m_power; ++index) {
		this->coeff[index] /= rhs;
	}
	
	return *this;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
Polynom<T> Polynom<T>::operator %= (const T& rhs)
{
	for (int index = 0; index <= m_power; ++index) {
		this->coeff[index] %= rhs;
	}
	
	return *this;
}
/*****************************************************************************/

/* Bool operators */
//-----------------------------------------------------------------------------
template <typename T>
bool Polynom<T>::operator == (const Polynom & rhs) const
{
	if (m_power == rhs.m_power) {
		for (int index = 0; index <= m_power; ++index) {
			if (coeff[index] != rhs.coeff[index]) {
				return false;
			}
		}
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
bool Polynom<T>::operator != (const Polynom & rhs) const
{
	if (m_power == rhs.m_power) {
		for (int index = 0; index <= m_power; ++index) {
			if (coeff[index] != rhs.coeff[index]) {
				return true;
			}
		}
		return false;
	}
	return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/

/* Braces operations */
//-----------------------------------------------------------------------------
template <typename T>
T Polynom<T>::operator () (const T& number) const
{
	T result = coeff[m_power];
	int k = 0;
	
	while (k < m_power) {
		++k;
		result = result * number + coeff[m_power - k];
	}
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
T Polynom<T>::operator [] (int index) const
{
	if (index >= 0 && index <= m_power) {
		return coeff[index];
	} else {
		throw ArrayOutOfBoundsException();
	}
}
/*****************************************************************************/

/* Maths operations */
//-----------------------------------------------------------------------------
template <typename T>
int Polynom<T>::GetPower() const
{
	return m_power;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template <typename T>
const Polynom<T> Polynom<T>::Derivative() const
{
	Polynom<T> temp(*this);
	temp.m_power = this->m_power - 1;
	
	for (int index = 0; index <= temp.m_power; ++index) {
		temp.coeff[index] = this->coeff[index + 1] * (index + 1);
	}
	
	return temp;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/*****************************************************************************/

/* Other */ 
//-----------------------------------------------------------------------------
template <typename T>
void Polynom<T>::Print() const
{
	printf("POWER: %d;\t", this->m_power);
	for (int index = 0; index <= this->m_power; ++index) {
		printf("%.3lf ", static_cast<double>(this->coeff[index]));
	}
printf("\n");
}
//-----------------------------------------------------------------------------

#endif
