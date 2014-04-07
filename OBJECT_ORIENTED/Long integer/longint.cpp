#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cmath>
using std::ostream;
using std::string;
using std::stack;
using std::vector;
using std::pair;

template <int BASE>
class LongInt {
public:
  LongInt() {}
  explicit LongInt(long long integer);
  LongInt(const vector<int>& vec);
  explicit LongInt(const string& str); 
  
  typedef std::vector<int>::iterator iterator;
  typedef std::vector<int>::const_iterator const_iterator;
  
  iterator begin() {
    return digits.begin();
  }
  
  const_iterator begin() const {
    return digits.begin();
  }
  
  iterator end() {
    return digits.end();
  }
  
  const_iterator end() const {
    return digits.end();
  }

  LongInt& operator += (const LongInt& rhs);
  LongInt& operator -= (const LongInt& rhs);
  LongInt& operator *= (const LongInt& rhs);
  LongInt& operator /= (const LongInt& rhs);
  LongInt& operator %= (const LongInt& rhs);
  
  LongInt& operator += (long long value);
  LongInt& operator -= (long long value);
  LongInt& operator *= (long long value);
  LongInt& operator /= (long long value);
  LongInt& operator %= (long long value);
 
  const LongInt operator + (const LongInt& rhs);
  const LongInt operator - (const LongInt& rhs);
  const LongInt operator * (const LongInt& rhs);
  const LongInt operator / (const LongInt& rhs);
  const LongInt operator % (const LongInt& rhs);
  
  const LongInt operator + (long long value);
  const LongInt operator - (long long value);
  const LongInt operator * (long long value);
  const LongInt operator / (long long value);
  const LongInt operator % (long long value);
  
  const LongInt operator << (long long number);
  const LongInt operator >> (long long number);
  
  bool operator < (const LongInt& rhs) const;
  bool operator > (const LongInt& rhs) const;
  bool operator <= (const LongInt& rhs) const;
  bool operator >= (const LongInt& rhs) const;
  bool operator == (const LongInt& rhs) const;
  bool operator != (const LongInt& rhs) const;
  
  bool operator < (long long value) const;
  bool operator > (long long value) const;
  bool operator <= (long long value) const;
  bool operator >= (long long value) const;
  bool operator == (long long value) const;
  bool operator != (long long value) const;
  
  const LongInt power(long long pow) const;
  const LongInt power(const LongInt& pow) const;
  const LongInt operator , (const LongInt& rhs) const;
  
  //---------------------------------------------
  friend ostream& operator << (ostream& out, const LongInt& rhs) {
    vector<int> buffer;
    for (const_iterator it = rhs.begin(); it != rhs.end(); ++it) {
      buffer.push_back(*it);
    }
    std::reverse(buffer.begin(), buffer.end());
    if (rhs.sign) {
      out << '-';
    }
    if (BASE == 8) {
      out << '0';
    }
    for (vector<int>::iterator itb = buffer.begin(); 
         itb != buffer.end(); 
         ++itb
        ) {
      out << *itb;
    }
    return out;
  }
  
  //---------------------------------------------
  inline long long getsize() const {
    return digits.size();
  }
  
  //-------------------------------------------------------
  LongInt& operator = (const LongInt& rhs) {
    LongInt temp(rhs);
    std::swap(digits, temp.digits);
    std::swap(sign, temp.sign);
    return *this;
  }
  
  //-------------------------------------------------------
  class DivisionByZeroException {
    public:
      DivisionByZeroException() {
        std::cerr << "Division by Zero!\n";
      }
  };

private:
  LongInt Add(const LongInt& lhs, const LongInt& rhs) const;
  LongInt Sub(const LongInt& lhs, const LongInt& rhs) const;
  pair<LongInt, LongInt> Div(const LongInt& lhs, const LongInt& rhs) const;
  
  //---------------------------------------------
  bool greater_equal(const vector<int>& lhs, const vector<int>& rhs) const {
    if (lhs == rhs) {
      return true;
    }
    if (lhs.size() > rhs.size()) {
      return true;
    } else if (lhs.size() < rhs.size()) {
      return false;
    } else if (lhs.size() == rhs.size()) {
      for (vector<int>::const_reverse_iterator it = lhs.rbegin(), 
           itr = rhs.rbegin(); 
           it != lhs.rend(); 
           ++it, ++itr
          ) {
        if (*it > *itr) {
          return true;
        } else if (*it < *itr) {
          return false;
        } else if (*it == *itr) {
          continue;
        }
      }
      return true;
    }
  } 
  
  //---------------------------------------------
  bool is_zero(const LongInt& rhs) const {
    if (rhs.digits.empty()) {
      return true;
    }
    for (size_t i = 0; i != rhs.getsize(); ++i) {
      if (rhs.digits[i] != 0) {
        return false;
      }
    }
    return true;
  }
  
  //---------------------------------------------
  void delete_zeroes(LongInt& rhs) const {
    for (vector<int>::const_reverse_iterator it = rhs.digits.rbegin();
         it != rhs.digits.rend() - 1;
         ++it
        ) {
      if (*it == 0) {
        rhs.digits.pop_back();
      } else {
        break;
      }
    }
  }
  
  //---------------------------------------------
  int getbase() const {
    return BASE;
  }

  //---------------------------------------------
  vector<int> digits;
  bool sign;  // 0 - plus, 1 - minus
};

//-----------------------------------------------------------------------------
template <int BASE>
LongInt<BASE>::LongInt(const vector<int>& vec) {
  digits = vec;
  std::reverse(digits.begin(), digits.end());
  sign = 0;
}

template <int BASE>
LongInt<BASE>::LongInt(long long integer) {
  if (integer == 0) {
    digits.push_back(0);
    sign = 0;
    return;
  }
  
  if (integer > 0) {
    sign = false;
  } else if (integer < 0) {
    sign = true;
    integer *= -1;
  }

  long long temp = integer, power = -1;
  while (temp) {
    temp /= BASE;
    ++power;
  }

  for (size_t i = 0; i <= power; ++i) {
    digits.push_back(integer / pow(BASE, power - i));
    integer -= pow(BASE, power - i) * digits.back();
  }
  std::reverse(digits.begin(), digits.end());
}

template <int BASE>
LongInt<BASE>::LongInt(const string& str) {
  int shift = 0;
  if (*str.begin() == '-') {
    sign = 1;
    shift = 1;
  } else {
    sign = 0;
  }
  for (string::const_iterator it = str.begin() + shift; it != str.end(); ++it) {
    digits.push_back(*it - '0');
  }
  std::reverse(digits.begin(), digits.end());
}

//-----------------------------------------------------------------------------
template <int BASE>
LongInt<BASE> LongInt<BASE>::Add(const LongInt& lhs, const LongInt& rhs) const {
  LongInt<BASE> result;
  result.digits.resize(std::max(lhs.getsize(), rhs.getsize()));
  bool carry = false;
  
  LongInt<BASE> left(lhs);
  LongInt<BASE> right(rhs);
  if (lhs.getsize() >= rhs.getsize()) {
    right.digits.resize(lhs.getsize());
  } else {
    left.digits.resize(rhs.getsize());
  }
    
  for (size_t i = 0, temp = 0; i != std::max(lhs.getsize(), rhs.getsize()); ++i) {
    temp = left.digits[i] + right.digits[i] + (carry ? 1 : 0);
    carry = (temp >= BASE);
    result.digits[i] = (carry ? temp - BASE : temp);
  }
  if (carry) {
    result.digits.push_back(1);
  }
  return result;
}

template <int BASE>
LongInt<BASE> LongInt<BASE>::Sub(const LongInt& lhs, const LongInt& rhs) const {
  LongInt<BASE> result;
  bool borrow = false;
  int temp = 0;
  
  LongInt<BASE> left(lhs);
  LongInt<BASE> right(rhs);
  if (lhs.getsize() >= rhs.getsize()) {
    right.digits.resize(lhs.getsize());
  } else {
    left.digits.resize(rhs.getsize());
  }
  
  for (size_t i = 0; i != std::max(lhs.getsize(), rhs.getsize()); ++i) {
    temp = left.digits[i] - right.digits[i] - (borrow ? 1 : 0);
    borrow = (temp < 0);
    result.digits.push_back(borrow ? temp + BASE : temp);
  }
  return result;
}

template <int BASE>
pair<LongInt<BASE>, LongInt<BASE> > LongInt<BASE>::Div(const LongInt& lhs, const LongInt& rhs) const {
  if (rhs.digits.empty() || is_zero(rhs)) {
    throw DivisionByZeroException();
  }

  pair<LongInt<BASE>, LongInt<BASE> > answer;
  if (!greater_equal(lhs.digits, rhs.digits)) {
    answer.first = LongInt();
    answer.second = LongInt();
    answer.first.digits.push_back(0);
    answer.second.digits.push_back(0);
    return answer;  // Return Zero
  }

  if (lhs.digits == rhs.digits) {
    LongInt result;
    result.digits.clear();
    result.digits.push_back(1);
    result.sign = lhs.sign ^ rhs.sign;
    answer.first = result;
    answer.second = LongInt();
    answer.second.digits.push_back(0);
    return answer;
  }

  vector<int> temporary, quotient;
  vector<int>::const_reverse_iterator it = lhs.digits.rbegin();
  for (size_t i = 0; i < rhs.getsize(); ++i) {
    temporary.push_back(*it);
    ++it;
  }

  LongInt proxy(temporary);
  if (proxy < rhs) {
    temporary.push_back(*it);
  }

  LongInt temp(temporary);
  ++it;
  while (temp >= rhs) {
    long long quotient_digit = 0;
    while (greater_equal(temp.digits, rhs.digits)) {
      temp -= rhs;
      ++quotient_digit;
    }
    quotient.push_back(quotient_digit);
    while (temp < rhs && it < lhs.digits.rend()) {
      temp *= 10;
      temp += *it;
      ++it;
    }
  }
  answer.first = LongInt(quotient);  // quotient
  answer.first.sign = lhs.sign ^ rhs.sign;
  answer.second = temp;  // rest
  return answer;
}

//-----------------------------------------------------------------------------
template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator += (const LongInt& rhs) {
  LongInt temp(*this);
  LongInt temp_add = Add(temp, rhs);
  LongInt temp_sub_1 = Sub(temp, rhs);
  LongInt temp_sub_2 = Sub(rhs, temp);
 
  if (sign && rhs.sign) {
    std::swap(digits, temp_add.digits);
    sign = 1;
    delete_zeroes(*this);
    return *this;
  } 
  
  if (sign && !rhs.sign) { 
    if (greater_equal(digits, rhs.digits)) {
      std::swap(digits, temp_sub_1.digits);
      sign = 1;
      delete_zeroes(*this);
      return *this;
    } else {
      std::swap(digits, temp_sub_2.digits);
      sign = 0;
      delete_zeroes(*this);
      return *this;
    }
  } 
  
  if (!sign && rhs.sign) {
    if (greater_equal(digits, rhs.digits)) {
      std::swap(digits, temp_sub_1.digits);
      sign = 0;
      delete_zeroes(*this);
      return *this;
    } else {
      std::swap(digits, temp_sub_2.digits);
      sign = 1;
      delete_zeroes(*this);
      return *this;
    }
  }
  
  if (!sign && !rhs.sign) {
    std::swap(digits, temp_add.digits);
    sign = 0;
    delete_zeroes(*this);
    return *this;
  }
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator -= (const LongInt& rhs) {
  LongInt temp(*this);
  LongInt temp_add = Add(temp, rhs);
  LongInt temp_sub_1 = Sub(temp, rhs);
  LongInt temp_sub_2 = Sub(rhs, temp);
  
  if (sign && rhs.sign) {
    if (greater_equal(digits, rhs.digits)) {
      std::swap(digits, temp_sub_1.digits);
      sign = 1;
      delete_zeroes(*this);
      return *this;
    } else {
      std::swap(digits, temp_sub_2.digits);
      sign = 0;
      delete_zeroes(*this);
      return *this;
    }
  } 
  
  if (sign && !rhs.sign) { 
    std::swap(digits, temp_add.digits);
    sign = 1;
    delete_zeroes(*this);
    return *this;
  } 
  
  if (!sign && rhs.sign) {
    std::swap(digits, temp_add.digits);
    sign = 0;
    delete_zeroes(*this);
    return *this;
  }
  
  if (!sign && !rhs.sign) {
    if (greater_equal(digits, rhs.digits)) {
      std::swap(digits, temp_sub_1.digits);
      sign = 0;
      delete_zeroes(*this);
      return *this;
    } else {
      std::swap(digits, temp_sub_2.digits);
      sign = 1;
      delete_zeroes(*this);
      return *this;
    }
  }
}

//-----------------------------------------------
template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator *= (const LongInt& rhs) {
  LongInt result;
  result.digits.resize(getsize() + rhs.getsize());
  for (size_t i = 0; i != getsize(); ++i) {
    int carry = 0;
    for (size_t j = 0, digit = 0; j != rhs.getsize(); ++j) {
      digit = digits[i] * rhs.digits[j] + result.digits[i + j] + carry;
      carry = digit / BASE;
      result.digits[i + j] = digit - carry * BASE;
    }
    result.digits[i + rhs.getsize()] = carry;
  }
  result.sign = sign ^ rhs.sign;
  std::swap(digits, result.digits);
  std::swap(sign, result.sign);
  delete_zeroes(*this);
  return *this;
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator /= (const LongInt& rhs) {
  pair<LongInt<BASE>, LongInt<BASE> > result = Div(*this, rhs);
  std::swap(digits, result.first.digits);
  std::swap(sign, result.first.sign);
  delete_zeroes(*this);
  return *this;
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator %= (const LongInt& rhs) {
  pair<LongInt<BASE>, LongInt<BASE> > result = Div(*this, rhs);
  std::swap(digits, result.second.digits);
  std::swap(sign, result.second.sign);
  delete_zeroes(*this);
  return *this;
}

//-----------------------------------------------
template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator += (long long value) {
  LongInt temp(value);
  *this += temp;
  return *this;
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator -= (long long value) {
  LongInt temp(value);
  *this -= temp;
  return *this;
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator *= (long long value) {
  LongInt temp(value);
  *this *= temp;
  return *this;
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator /= (long long value) {
  LongInt temp(value);
  *this /= temp;
  return *this;
}

template <int BASE>
LongInt<BASE>& LongInt<BASE>::operator %= (long long value) {
  LongInt temp(value);
  *this %= temp;
  return *this;
}

//-----------------------------------------------------------------------------
template <int BASE> 
const LongInt<BASE> LongInt<BASE>::operator + (const LongInt& rhs) {
  LongInt result(*this);
  result += rhs;
  return result;
}

template <int BASE> 
const LongInt<BASE> LongInt<BASE>::operator - (const LongInt& rhs) {
  LongInt result(*this);
  result -= rhs;
  return result;
}

template <int BASE> 
const LongInt<BASE> LongInt<BASE>::operator * (const LongInt& rhs) {
  LongInt result(*this);
  result *= rhs;
  return result;
}

template <int BASE> 
const LongInt<BASE> LongInt<BASE>::operator / (const LongInt& rhs) {
  LongInt result(*this);
  result /= rhs;
  return result;
}

template <int BASE> 
const LongInt<BASE> LongInt<BASE>::operator % (const LongInt& rhs) {
  LongInt result(*this);
  result %= rhs;
  return result;
}

//-----------------------------------------------
template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator + (long long value) {
  LongInt result(*this), temp(value);
  result += temp;
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator - (long long value) {
  LongInt result(*this), temp(value);
  result -= temp;
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator * (long long value) {
  LongInt result(*this), temp(value);
  result *= temp;
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator / (long long value) {
  LongInt result(*this), temp(value);
  result /= temp;
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator % (long long value) {
  LongInt result(*this), temp(value);
  result %= temp;
  return result;
}

//-----------------------------------------------------------------------------
template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator << (long long number) {
  LongInt result(*this);
  while (number) {
    result *= 2;
    --number;
  }
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator >> (long long number) {
  LongInt result(*this);
  while (number) {
    result /= 2;
    --number;
  }
  return result;
}

//-----------------------------------------------------------------------------
template <int BASE>
bool LongInt<BASE>::operator < (const LongInt& rhs) const {
  if (!sign && !rhs.sign) {
    return !greater_equal(digits, rhs.digits);
  }
  
  if (sign && !rhs.sign) {
    return true;
  }
 
  if (!sign && rhs.sign) {
    return false;
  }
  
  if (sign && rhs.sign) {
    if (digits == rhs.digits) {
      return false;
    } else {
      return greater_equal(digits, rhs.digits);
    }
  }
}

template <int BASE>
bool LongInt<BASE>::operator > (const LongInt& rhs) const {
  return !(*this <= rhs);
}

template <int BASE>
bool LongInt<BASE>::operator <= (const LongInt& rhs) const {
  return (*this < rhs) || (*this == rhs);
}

template <int BASE>
bool LongInt<BASE>::operator >= (const LongInt& rhs) const {
  return !(*this < rhs);
}

template <int BASE>
bool LongInt<BASE>::operator == (const LongInt& rhs) const {
  return !(*this < rhs) && !(rhs < *this);
}

template <int BASE>
bool LongInt<BASE>::operator != (const LongInt& rhs) const {
  return !(*this == rhs);
}

//-----------------------------------------------
template <int BASE>
bool LongInt<BASE>::operator < (long long value) const {
  if (value == 0) {
    if (is_zero(*this)) {
      return false;
    }
    if (sign) {
      return true;
    } else {
      return false;
    }
  }
  LongInt<BASE> temp(value);
  return *this < temp;
}

template <int BASE>
bool LongInt<BASE>::operator > (long long value) const {
  if (value == 0) {
    if (is_zero(*this)) {
      return false;
    }
    if (sign) {
      return false;
    } else {
      return true;
    }
  }
  LongInt<BASE> temp(value);
  return *this > temp;
}

template <int BASE>
bool LongInt<BASE>::operator <= (long long value) const {
  if (value == 0) {
    if (is_zero(*this)) {
      return true;
    }
    if (sign) {
      return true;
    } else {
      return false;
    }
  }
  LongInt<BASE> temp(value);
  return *this <= temp;
}

template <int BASE>
bool LongInt<BASE>::operator >= (long long value) const {
  if (value == 0) {
    if (is_zero(*this)) {
      return true;
    }
    if (sign) {
      return false;
    } else {
      return true;
    }
  }
  LongInt<BASE> temp(value);
  return *this >= temp;
}

template <int BASE>
bool LongInt<BASE>::operator == (long long value) const {
  if (value == 0) {
    return is_zero(*this);
  }
  LongInt<BASE> temp(value);
  return *this == temp;
}

template <int BASE>
bool LongInt<BASE>::operator != (long long value) const {
  if (value == 0) {
    return !is_zero(*this);
  }
  LongInt<BASE> temp(value);
  return *this != temp;
}

//-----------------------------------------------------------------------------
template <int BASE>
const LongInt<BASE> LongInt<BASE>::power(long long pow) const {
  LongInt result;

  if (pow % 2 == 0) {
    result.sign = 0;
  } else {
    if (sign) {
      result.sign = 1;
    } else {
      result.sign = 0;
    }
  }

  result.digits.clear();
  result.digits.push_back(1);
  LongInt temp(*this);
  while (pow) {
    if (pow % 2 == 0) {
      pow /= 2;
      temp *= temp;
    } else {
      --pow;
      result *= temp;
    }
  }

  delete_zeroes(result);
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::power(const LongInt& power) const {
  LongInt result, pow(power);

  if (pow % 2 == 0) {
    result.sign = 0;
  } else {
    if (sign) {
      result.sign = 1;
    } else {
      result.sign = 0;
    }
  }

  result.digits.clear();
  result.digits.push_back(1);
  LongInt temp(*this);
  while (!is_zero(pow)) {
    if (pow % 2 == 0) {
      pow /= 2;
      temp *= temp;
    } else {
      pow = pow - 1;
      result *= temp;
    }
  }
 
  delete_zeroes(result);
  return result;
}

template <int BASE>
const LongInt<BASE> LongInt<BASE>::operator , (const LongInt& rhs) const {
  LongInt left(*this), right(rhs);
  left.sign = right.sign = 0;
  while (left != 0 && right != 0) {
    if (left >= right) {
      left %= right;
    } else {
      right %= left;
    }
  }
  if (left == 0) {
    delete_zeroes(right);
    right.sign = rhs.sign;
    return right;
  } 
  if (right == 0) {
    delete_zeroes(left);
    left.sign = sign;
    return left;
  }
}
  
//-----------------------------------------------------------------------------
template <int BASE, typename T>
class StackCalc {
  public:
    explicit StackCalc(const string& str) : operations(str) {
      proceed();
    }

    //-------------------------------------------------------
    class DivisionByZeroException {
      public:
        DivisionByZeroException() {
          std::cerr << "Division by Zero!\n";
        }
    };
  
  private:
    void proceed();	

    string operations;
    stack<T> stek;
    T first_value, second_value;
    vector<int> digits;
};

template <int BASE, typename T>
void StackCalc<BASE, T>::proceed() {
  for (string::iterator it = operations.begin(); it != operations.end(); ++it) {
    switch(*it) {
      case '+':
        first_value = stek.top();
        stek.pop();
        second_value = stek.top();
        stek.pop();
        stek.push(first_value + second_value);
        break;
      case '-':
        first_value = stek.top();
        stek.pop();
        second_value = stek.top();
        stek.pop();
        stek.push(first_value - second_value);
        break;
      case '*':
        first_value = stek.top();
        stek.pop();
        second_value = stek.top();
        stek.pop();
        stek.push(first_value * second_value);
        break;
      case '/':
        first_value = stek.top();
        stek.pop();
        second_value = stek.top();
        stek.pop();
        if (first_value == 0) {
          throw DivisionByZeroException();
        }
        stek.push(first_value / second_value);
        break;
      case '%':
        first_value = stek.top();
        stek.pop();
        second_value = stek.top();
        stek.pop();
        if (first_value == 0) {
          throw DivisionByZeroException();
        }
        stek.push(first_value % second_value);
        break;
      case '=':
        std::cout << "Current value is: " << stek.top() << std::endl;
        break;
      case ' ':
      case '\t':
      case '\n':
        if (*(it - 1) >= '0' && *(it - 1) <= '9') {
          stek.push(LongInt<BASE>(digits));
          digits.clear();
        }
        break;
      default:
        digits.push_back(*it - '0');
    }
  }
}

int main() {
  string _1, _2;
  std::getline(std::cin, _1);
  std::getline(std::cin, _2);
  LongInt<10> first(_1);
  LongInt<10> second(_2);
  std::cout << "1st: " << first << ' ' << first.getsize() << std::endl;
  std::cout << "2nd: " << second << ' ' << second.getsize() << std::endl;
  std::cout << "+ " << first + second << std::endl;
  std::cout << "- " << first - second << std::endl;
  std::cout << "* " << first * second << std::endl;
  try {
    std::cout << "/ " << first / second << std::endl;
    std::cout << "% " << first % second << std::endl;
  } catch (LongInt<10>::DivisionByZeroException e) {}
  LongInt<10> third(123450987654321);
  std::cout << "3rd: " << third << std::endl;
  std::cout << "pow " << first.power(152) << std::endl;
  std::cout << "HOD " << (first, second) << std::endl;

  LongInt<8> fourth(12345), fifth(-12);
  LongInt<2> fourth_2(12345), fifth_2(-1);
  std::cout << fourth << ' ' << fifth << std::endl;
  std::cout << fourth_2 << ' ' << fifth_2 << std::endl;
  std::cout << "POW " << first.power(second) << std::endl;

  std::cout << "Enter string (print '=' to get value): ";
  string str;
  std::getline(std::cin, str);
  StackCalc<10, LongInt<10> > sc(str);
  return 0;
}

