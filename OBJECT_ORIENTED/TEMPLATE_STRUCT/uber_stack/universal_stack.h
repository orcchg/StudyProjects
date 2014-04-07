// An universal template stack with custom container and custom allocator;
// Allows an assignment between two stacks with different types of elements;

#ifndef UNIVERSAL_STACK_HPP

#define UNIVERSAL_STACK_HPP

#include <deque>
//#include <allocator>
#include <memory>
#include <stdexcept>

template <typename T, template <typename ELEM, typename std::allocator<ELEM> > class CONT = std::deque>
class UStack {
  private:
    CONT<T> elems;

  public:
    void push(const T&);
    void pop();
    T top() const;
    bool empty() const {
      return elems.empty();
    }

    template <typename T2, template <typename ELEM2, typename = std::allocator<ELEM2> > class CONT2>
    UStack<T, CONT>& operator = (const UStack<T2, CONT2>&);
};

template <typename T, template <typename, typename> class CONT>
void UStack<T, CONT>::push(const T& rhs) {
  elems.push_back(rhs);
}

template <typename T, template <typename, typename> class CONT>
void UStack<T, CONT>::pop() {
  if (elems.empty()) {
    throw std::out_of_range("Stack<>::pop(): empty stack");
  }
  elems.pop_back();
}

template <typename T, template <typename, typename> class CONT>
T UStack<T, CONT>::top() const {
  if (elems.empty()) {
      throw std::out_of_range("Stack<>::pop(): empty stack");
    }
  return elems.back();
}

template <typename T, template <typename, typename> class CONT>
template <typename T2, template <typename, typename> class CONT2>
UStack<T, CONT>& UStack<T, CONT>::operator = (const UStack<T2, CONT2>& rhs) {
  if ((void*)this == (void*)&rhs) {
    return *this;
  }
  UStack<T2> temp(rhs);
  elems.clear();
  while (!temp.empty()) {
    elems.push_front(temp.top());
    temp.pop();
  }
  return *this;
}

#endif