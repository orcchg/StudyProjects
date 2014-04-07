#include <math.h>
#include <stdio.h>
#include "HOD.h"

#ifndef OBJECT_ORIENTED_CLASS_RATIONAL_H

#define OBJECT_ORIENTED_CLASS_RATIONAL_H

class Rational
{
	private:
		int numerator;
		int denominator;
		Rational & reduce();
		
	public:
		Rational() {}
		Rational(int num, int den);
		Rational(const Rational & Obj);
		~Rational() {}

/*	FURTHER METHODS CHANGES LEFT-OPERAND (for further consideration)
 *
		Rational & operator +	(const Rational & rhs);	
		Rational & operator -	(const Rational & rhs);	
		Rational & operator *	(const Rational & rhs);
		Rational & operator /	(const Rational & rhs);
*/	

		const Rational operator +	(const Rational & rhs);	
		const Rational operator -	(const Rational & rhs);	
		const Rational operator *	(const Rational & rhs);
		const Rational operator /	(const Rational & rhs);

//		Rational & operator -	(); // Warning! This method changes initial left operand!
		const Rational operator - ();
		
		Rational operator = 	(const Rational & rhs);
		
		bool 	 operator == 	(const Rational & rhs);
		bool 	 operator != 	(const Rational & rhs);
		bool	 operator <		(const Rational & rhs);
		bool	 operator >		(const Rational & rhs);
		bool	 operator <=	(const Rational & rhs);
		bool	 operator >=	(const Rational & rhs);
		
		void Show() const;
		
		//--------------------------------------------------------------------
		class xZeroDenom {
			public: 
				xZeroDenom() {
					printf("Unable to create rational with 0-denominator!\n");
				}
				~xZeroDenom() {}
		};
		//--------------------------------------------------------------------
		
		//--------------------------------------------------------------------
		class xDivByZero {
			public: 
				xDivByZero() {
					printf("Division by zero rational!\n");
				}
				~xDivByZero() {}
		};
		//--------------------------------------------------------------------
};
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
Rational::Rational(int num, int den) : 
						numerator(num),
						denominator(den)
{
	if (denominator == 0) {
		throw xZeroDenom();
	}
	if (numerator >= 0 && denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	} else if (numerator < 0 && denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
Rational::Rational(const Rational & Obj)
{
	numerator = Obj.numerator;
	denominator = Obj.denominator;
}
//-------------------------------------------------------------------------------

/*******************************************************************************/
Rational & Rational::reduce()
{
	int gcd = HOD(numerator, denominator);
	numerator /= gcd;
	denominator /= gcd;
	
	return *this;
}
/*******************************************************************************/

/*     FURTHER METHODS CHANGES LEFT-OPERAND (for further consideration)
//-------------------------------------------------------------------------------
Rational & Rational::operator + (const Rational & rhs)
{
	numerator = numerator * rhs.denominator + denominator * rhs.numerator;
	denominator = denominator * rhs.denominator;
	
	*this = this->reduce();
	return *this;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
Rational & Rational::operator - (const Rational & rhs)
{
	numerator = numerator * rhs.denominator - denominator * rhs.numerator;
	denominator = denominator * rhs.denominator;
	
	if (numerator < 0) {
		numerator *= -1;
		*this = this->reduce();	
		numerator *= -1;
	} else {
		*this = this->reduce();	
	}
	return *this;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
Rational & Rational::operator * (const Rational & rhs)
{
	numerator *= rhs.numerator;
	denominator *= rhs.denominator;
	
	if (numerator < 0) {
		numerator *= -1;
		*this = this->reduce();	
		numerator *= -1;
	} else {
		*this = this->reduce();	
	}
	return *this;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
Rational & Rational::operator / (const Rational & rhs)
{
	numerator *= rhs.denominator;
	denominator *= rhs.numerator;
	
	if (denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}
	
	if (numerator < 0) {
		numerator *= -1;
		*this = this->reduce();	
		numerator *= -1;
	} else {
		*this = this->reduce();	
	}
	return *this;
}
//-------------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------
const Rational Rational::operator + (const Rational & rhs)
{
	Rational temp;
	
	temp.numerator = numerator * rhs.denominator + denominator * rhs.numerator;
	temp.denominator = denominator * rhs.denominator;
	
	if (temp.numerator < 0) {
		temp.numerator *= -1;
		temp = temp.reduce();	
		temp.numerator *= -1;
	} else {
		temp = temp.reduce();	
	}
	return temp;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
const Rational Rational::operator - (const Rational & rhs)
{
	Rational temp;

	temp.numerator = numerator * rhs.denominator - denominator * rhs.numerator;
	temp.denominator = denominator * rhs.denominator;
	
	if (temp.numerator < 0) {
		temp.numerator *= -1;
		temp = temp.reduce();	
		temp.numerator *= -1;
	} else {
		temp = temp.reduce();	
	}
	return temp;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
const Rational Rational::operator * (const Rational & rhs)
{
	Rational temp;
	
	temp.numerator = numerator * rhs.numerator;
	temp.denominator = denominator * rhs.denominator;
	
	if (temp.numerator < 0) {
		temp.numerator *= -1;
		temp = temp.reduce();	
		temp.numerator *= -1;
	} else {
		temp = temp.reduce();	
	}
	return temp;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
const Rational Rational::operator / (const Rational & rhs)
{
	Rational temp;
	
	temp.numerator = numerator * rhs.denominator;
	temp.denominator = denominator * rhs.numerator;
	
	if (temp.denominator == 0) {
		throw xDivByZero();
	}
	
	if (denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}
	
	if (temp.numerator < 0) {
		temp.numerator *= -1;
		temp = temp.reduce();	
		temp.numerator *= -1;
	} else {
		temp = temp.reduce();	
	}
	return temp;
}
//-------------------------------------------------------------------------------

/*
//-------------------------------------------------------------------------------
Rational & Rational::operator - ()
{
	numerator *= -1;
	return *this;
}
//-------------------------------------------------------------------------------
*/

//-------------------------------------------------------------------------------
const Rational Rational::operator - ()
{
	Rational temp(*this);
	
	temp.numerator *= -1;
	return temp;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
Rational Rational::operator = (const Rational & rhs)
{
	numerator = rhs.numerator;
	denominator = rhs.denominator;
	
	return *this;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool Rational::operator == (const Rational & rhs)
{
	Rational copy(*this);
	Rational rhs_copy(rhs);
	
	copy = copy.reduce();
	rhs_copy = rhs_copy.reduce();
	
	Rational temp = copy / rhs_copy;
	
	if ((temp.numerator - temp.denominator) == 0) return true;
	else return false;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool Rational::operator != (const Rational & rhs)
{
	Rational copy(*this);
	Rational rhs_copy(rhs);
	
	copy = copy.reduce();
	rhs_copy = rhs_copy.reduce();
	
	Rational temp = copy / rhs_copy;
	
	if ((temp.numerator - temp.denominator) == 0) return false;
	else return true;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool Rational::operator < (const Rational & rhs)
{
	Rational copy(*this);
	Rational rhs_copy(rhs);
	
	copy = copy.reduce();
	rhs_copy = rhs_copy.reduce();
	
	Rational temp = copy / rhs_copy;
	
	return (temp.denominator > temp.numerator);
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool Rational::operator > (const Rational & rhs)
{
	Rational copy(*this);
	Rational rhs_copy(rhs);
	
	copy = copy.reduce();
	rhs_copy = rhs_copy.reduce();
	
	Rational temp = copy / rhs_copy;
	
	return (temp.denominator < temp.numerator);
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool Rational::operator <= (const Rational & rhs)
{
	Rational copy(*this);
	Rational rhs_copy(rhs);
	
	copy = copy.reduce();
	rhs_copy = rhs_copy.reduce();
	
	Rational temp = copy / rhs_copy;
	
	return (temp.denominator >= temp.numerator);
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool Rational::operator >= (const Rational & rhs)
{
	Rational copy(*this);
	Rational rhs_copy(rhs);
	
	copy = copy.reduce();
	rhs_copy = rhs_copy.reduce();
	
	Rational temp = copy / rhs_copy;
	
	return (temp.denominator <= temp.numerator);
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void Rational::Show() const
{
	printf("%d/%d\n", numerator, denominator);
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------

#endif