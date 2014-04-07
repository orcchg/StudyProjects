#include <vector>
#include <algorithm>
#include <iostream>
#include <new>
#include <iomanip>
using namespace std;

//-----------------------------------------------------------------------------
template <typename T>
class Vector {
public:
  typedef T value_type;
  typedef T* pointer_type;
  typedef T& reference_type;
  
  Vector();  // done
  Vector(size_t sz);  // done
  Vector(size_t sz, const reference_type item);  // done
  Vector(const Vector& vec);  // done
  ~Vector() throw();  // done
  
  Vector& operator= (Vector<T> rhs);  // done
  
  reference_type at(size_t index);  // done
  reference_type at(size_t index) const;  // done
  reference_type operator[] (size_t index);  // done
  reference_type operator[] (size_t index) const;  // done
  
  void clear() throw();
  bool empty() const;  // done
  
  bool operator== (const Vector& rhs) const;  // done
  bool operator!= (const Vector& rhs) const;  // done
  bool operator< (const Vector& rhs) const;
  bool operator<= (const Vector& rhs) const;
  bool operator> (const Vector& rhs) const;
  bool operator>= (const Vector& rhs) const;
  
  void push_back(const reference_type item);  // done
  void push_back(const value_type item);  // done
  void pop_back();  // done
  
  inline size_t capacity() const;  // done
  inline size_t size() const;  // done
  
  void reserve(size_t sz);
  void resize(size_t sz);
  
  void swap(const Vector<T>* lhs, const Vector<T>* rhs);
  // ??? shrink_to_fit(???) ???;
  
  class Iterator {
  
  };
  
  typedef Iterator iterator;
  
  iterator begin();
  iterator end();
  iterator front() const;
  iterator back() const;
  
  iterator insert(iterator it, const reference_type item);
  iterator erase(iterator it);

private:
  pointer_type m_data;
  pointer_type m_size;
  pointer_type m_capacity;
  
  void destroy() throw();  // releases yet occupied memory and destroys yet constructed objects
  static const size_t reserve_factor = 256;
};

//-----------------------------------------------------------------------------
template <typename T>
void Vector<T>::destroy() throw() {
  // destroy all existing objects
  for (pointer_type data = m_data; data != m_size; ++data) {
    data->~T();
  }
  
  // release raw memory
  operator delete(m_data);
  m_capacity = m_size = m_data;
}

//-----------------------------------------------------------------------------
template <typename T>
Vector<T>::Vector() {
  {  // reserve raw memory
    size_t capacity_size = reserve_factor * sizeof(T);
    m_data = static_cast<pointer_type>(operator new(capacity_size));
    m_size = m_data;
    m_capacity = capacity_size + m_data;
  }
}

template <typename T>
Vector<T>::Vector(size_t sz) {
  {  // reserve raw memory
    size_t capacity_size = (sz + reserve_factor) * sizeof(T);
    m_data = static_cast<pointer_type>(operator new(capacity_size));
    m_size = m_data;
    m_capacity = capacity_size + m_data;
  }
  
  // construct objects in raw memory
  while (m_size != m_data + sz) {
    try {
      new (m_size) T();
    } catch (...) {
      destroy();
      throw;
    }
    ++m_size;
  }
}

template <typename T>
Vector<T>::Vector(size_t sz, const reference_type item) {
  {  // reserve raw memory
    size_t capacity_size = (sz + reserve_factor) * sizeof(T);
    m_data = static_cast<pointer_type>(operator new(capacity_size));
    m_size = m_data;
    m_capacity = capacity_size + m_data;
  }
  
  // construct objects in raw memory
  while (m_size != m_data + sz) {
    try {
      new (m_size) T(item);
    } catch (...) {
      destroy();
      throw;
    }
    ++m_size;
  }
}

template <typename T>
Vector<T>::Vector(const Vector& rhs) {
  // reserve raw memory
  m_data = static_cast<pointer_type>(operator new(rhs.m_capacity - rhs.m_data));
  m_size = m_data;
  m_capacity = rhs.m_capacity;
  
  // construct objects in raw memory
  size_t index = 0;
  while (m_size != m_data + rhs.size()) {
    try {
      new (m_size) T(*(rhs.m_data + index));
    } catch (...) {
      destroy();
      throw;
    }
    ++m_size;
    ++index;
  }
}

template <typename T>
Vector<T>::~Vector() throw() {
  destroy();
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> rhs) {
  std::swap(m_data, rhs.m_data);
  std::swap(m_size, rhs.m_size);
  std::swap(m_capacity, rhs.m_capacity);
  return *this;
}

//-----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::reference_type Vector<T>::at(size_t index) {
  if (index < 0 || index >= this->size()) {
    throw;
  }
  return *(m_data + index);
}

template <typename T>
typename Vector<T>::reference_type Vector<T>::at(size_t index) const {
  if (index < 0 || index >= this->size()) {
    throw;
  }
  return *(m_data + index);
}

template <typename T>
typename Vector<T>::reference_type Vector<T>::operator[] (size_t index) {
  return *(m_data + index);
}

template <typename T>
typename Vector<T>::reference_type Vector<T>::operator[] (size_t index) const {
  return *(m_data + index);
}

//-----------------------------------------------------------------------------
template <typename T>
void Vector<T>::clear() throw() {
  destroy();
}

template <typename T>
bool Vector<T>::empty() const {
  return m_data == m_size;
}

//-----------------------------------------------------------------------------
template <typename T>
bool Vector<T>::operator== (const Vector& rhs) const {
  if (size() != rhs.size()) {
    return false;
  }
  size_t index = 0;
  for (pointer_type data = m_data; data != m_size; ++data, ++index) {
    if (*data != *(rhs.m_data + index)) {
      return false;
    }
  }
  return true;
}

template <typename T>
bool Vector<T>::operator!= (const Vector& rhs) const {
  return !(*this == rhs);
}

template <typename T>
bool Vector<T>::operator< (const Vector& rhs) const {
  size_t minimal = this->size() < rhs.size() ? this->size() : rhs.size();
  for (size_t index = 0; index < minimal; ++index) {
    if (this->at(index) < rhs.at(index)) {
      return true;
    }
  }
  ///
}

template <typename T>
bool Vector<T>::operator<= (const Vector& rhs) const {

}

template <typename T>
bool Vector<T>::operator> (const Vector& rhs) const {

}

template <typename T>
bool Vector<T>::operator>= (const Vector& rhs) const {

}

//-----------------------------------------------------------------------------
template <typename T>
void Vector<T>::push_back(const reference_type item) {
  new (m_size) T(item);
  ++m_size;
}

template <typename T>
void Vector<T>::push_back(const value_type item) {
  new (m_size) T(item);
  ++m_size;
}

template <typename T>
void Vector<T>::pop_back() {
  if (m_size == m_data) {
    throw;  // empty vector
  }
  --m_size;
  m_size->~T();
}

//-----------------------------------------------------------------------------
template <typename T>
inline size_t Vector<T>::capacity() const {
  return m_capacity - m_data;
}

template <typename T>
inline size_t Vector<T>::size() const {
  return m_size - m_data;
}

//-----------------------------------------------------------------------------
template <typename T>
void Vector<T>::reserve(size_t sz) {

}

template <typename T>
void Vector<T>::resize(size_t sz) {

}

//-----------------------------------------------------------------------------
template <typename T>
void Vector<T>::swap(const Vector<T>* lhs, const Vector<T>* rhs) {

}

// ??? Vector<T>::shrink_to_fit(???) ???;
  
//-----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::iterator Vector<T>::begin() {

}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() {

}

template <typename T>
typename Vector<T>::iterator Vector<T>::front() const {

}

template <typename T>
typename Vector<T>::iterator Vector<T>::back() const {

}

//-----------------------------------------------------------------------------
template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator it, const reference_type item) {

}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator it) {

}

//-----------------------------------------------------------------------------
int main() {
  Vector<int> v;
  cout << v.size() << " " << v.capacity() << " " << boolalpha << v.empty() << endl;
  v.push_back(1);
  cout << v.size() << " " << v.capacity() << " " << boolalpha << v.empty() << endl;
  v.push_back(2);
  cout << v.size() << " " << v.capacity() << " " << boolalpha << v.empty() << endl;
  v.push_back(3);
  cout << v.size() << " " << v.capacity() << " " << boolalpha << v.empty() << endl;
  cout << v[0] << " " << v[1] << " " << v[2] << endl;
  cout << v.at(0) << " " << v.at(1) << " " << v.at(2) << endl;
  v[0] = 4;
  v.at(2) = 5;
  cout << v[0] << " " << v.at(2) << endl;

  Vector<int> w = v;
  Vector<int> x;
  x = v;
  cout << boolalpha << (x == v) << " " << boolalpha << " " << (w == x) << endl;
  v.clear();
  cout << v.size() << " " << v.capacity() << " " << boolalpha << v.empty() << endl;
  cout << w.size() << " " << w.capacity() << " " << boolalpha << w.empty() << endl;
  cout << x.size() << " " << x.capacity() << " " << boolalpha << x.empty() << endl;
  cout << w[0] << " " << w[1] << " " << w[2] << endl;
  cout << x.at(0) << " " << x.at(1) << " " << x.at(2) << endl;
  x.push_back(10);
  w.pop_back();
  cout << w.size() << " " << w.capacity() << " " << boolalpha << w.empty() << endl;
  cout << x.size() << " " << x.capacity() << " " << boolalpha << x.empty() << endl;
  cout << boolalpha << (x != v) << " " << boolalpha << " " << (w == x) << endl;
  cout << x.at(0) << " " << x.at(1) << " " << x[2] << " " << x[3] << endl;
  cout << w.at(0) << " " << w[1] << endl;
  /*try {
    cout << w.at(2);
  } catch (...) {
    cout << "Out of range" << endl;
  }
  try {
    cout << x.at(4);
  } catch (...) {
    cout << "Out of range" << endl;
  }*/
  w.pop_back();
  cout << w.size() << " " << w.capacity() << " " << boolalpha << w.empty() << endl;
  w.pop_back();
  cout << w.size() << " " << w.capacity() << " " << boolalpha << w.empty() << endl;
  /*try {
    w.pop_back();
  } catch (...) {
    cout << "Cannot pop back!" << endl;
  }*/
  w.push_back(555);
  cout << w[0] << endl;
  //w.clear();
  //cout << w.size() << " " << w.capacity() << " " << boolalpha << w.empty() << endl;
  return 0;
}
