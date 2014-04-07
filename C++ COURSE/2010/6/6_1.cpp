#include <algorithm>
#include <iostream>
#include <ostream>
using std::swap;
using std::cout;
using std::endl;
using std::ostream;

template <int P>
class Modular {
public:
  Modular();
  explicit Modular(long long value);

  const Modular operator + (const Modular& rhs) const;
  const Modular operator - (const Modular& rhs) const;
  const Modular operator * (const Modular& rhs) const;
  const Modular operator / (const Modular& rhs) const;
  const Modular operator % (const Modular& rhs) const;

  Modular& operator += (const Modular& rhs);
  Modular& operator -= (const Modular& rhs);
  Modular& operator *= (const Modular& rhs);
  Modular& operator /= (const Modular& rhs);
  Modular& operator %= (const Modular& rhs);
  
  operator long long ();
  friend ostream& operator << (ostream& out, const Modular& rhs) {
    out << rhs.m_value;
    return out;
  }

private:
  int m_value;
};

template <int P>
Modular<P>::Modular() : m_value(0) 
{
}

template <int P>
Modular<P>::Modular(long long value) : m_value(value % P) 
{
}

template <int P>
const Modular<P> Modular<P>::operator + (const Modular<P>& rhs) const {
  Modular<P> temp(*this);
  temp += rhs;
  return temp;
}

template <int P>
const Modular<P> Modular<P>::operator - (const Modular<P>& rhs) const {
  Modular<P> temp(*this);
  temp -= rhs;
  return temp;
}

template <int P>
const Modular<P> Modular<P>::operator * (const Modular<P>& rhs) const {
  Modular<P> temp(*this);
  temp *= rhs;
  return temp;
}

template <int P>
const Modular<P> Modular<P>::operator / (const Modular<P>& rhs) const {
  Modular<P> temp(*this);
  temp /= rhs;
  return temp;
}

template <int P>
const Modular<P> Modular<P>::operator % (const Modular<P>& rhs) const {
  Modular<P> temp(*this);
  temp %= rhs;
  return temp;
}

template <int P>
Modular<P>& Modular<P>::operator += (const Modular<P>& rhs) {
  m_value = (m_value + rhs.m_value) % P;
  return *this;
}

template <int P>
Modular<P>& Modular<P>::operator -= (const Modular<P>& rhs) {
  m_value = (m_value - rhs.m_value) % P;
  return *this;
}

template <int P>
Modular<P>& Modular<P>::operator *= (const Modular<P>& rhs) {
  m_value = (m_value * rhs.m_value) % P;
  return *this;
}

template <int P>
Modular<P>& Modular<P>::operator /= (const Modular<P>& rhs) {
  m_value = (m_value / rhs.m_value) % P;
  return *this;
}

template <int P>
Modular<P>& Modular<P>::operator %= (const Modular<P>& rhs) {
  m_value = (m_value % rhs.m_value) % P;
  return *this;
}

template <int P>
Modular<P>::operator long long () {
  return m_value;
}

int main() {
  Modular<50> m(112);
  Modular<50> n = m;
  Modular<50> k;
  k = n;
  cout << n << " " << m << " " << k << endl;
  m = k + n;
  k += n;
  cout << n << " " << m << " " << k << endl;
  m /= n;
  n *= n;
  k *= n;
  k *= m;
  cout << n << " " << m << " " << k << endl;
  m = k * n - k + n / k;
  long long l = static_cast<long long>(n) + 1234567;
  cout << n << " " << m << " " << k << " " << l << endl;
  return 0;
}
