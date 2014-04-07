#include <iostream>
using namespace std;

double sum(double a, double b) {
  return a + b;
}

double sub(double a, double b) {
  return a - b;
}

double mul(double a, double b) {
  return a * b;
}

double div(double a, double b) {
  if (b == 0) {
    throw;
  }
  return a / b;
}

typedef double (*F)(double, double);

double calc(int index, double a, double b, F* array) {
  return array[index](a, b);
}

int main() {
  F array[] = {sum, sub, mul, div};
  cout << calc(0, 5, 5, array) << endl;
  cout << calc(1, 7, 2, array) << endl;
  cout << calc(2, 5, 5, array) << endl;
  cout << calc(3, 8, 3, array) << endl;
  return 0;
}
