#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "universal_stack.h"
using std::cout;
using std::string;
using std::vector;

int main() {
  try {
    UStack<int> intStack;
    UStack<double> dblStack;
    intStack.push(42);
    intStack.push(7);
    dblStack.push(7.7);
    dblStack = intStack;
    cout << dblStack.top() << '\n';
    dblStack.pop();
    cout << dblStack.top() << '\n';
    dblStack.pop();
    cout << dblStack.top() << '\n';
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  UStack<int, vector> vStack;
  vStack.push(42);
  vStack.push(7);
  cout << vStack.top() << std::endl;
  vStack.pop();
  return 0;
}