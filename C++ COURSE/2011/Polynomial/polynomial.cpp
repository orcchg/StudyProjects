#include "polynomial.h"

template <typename T>
class Polynomial {
public:
  
  
  
private:
  deque<T> m_coeffs;
};

const Polynomial operator + (const Polynomial& lhs, const Polynomial& rhs);
const Polynomial operator - (const Polynomial& lhs, const Polynomial& rhs);
const Polynomial operator * (const Polynomial& lhs, const Polynomial& rhs);
const Polynomial operator / (const Polynomial& lhs, const Polynomial& rhs);
const Polynomial operator % (const Polynomial& lhs, const Polynomial& rhs);