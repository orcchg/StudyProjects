#include <iostream>
#include <cmath>
using namespace std;

const double EPSILON = 1.e-7;

double solve(double a, double b, double (*fptr)(double)) {
  if (fptr(a) * fptr(b) > 0) {
    throw;
  }
  double x;
  while (a < b) {
    x = a + (b - a) / 2.0;
    double f = fptr(x);
    cout << a << " " << b << " " << x << " " << f << endl;
    if (fabs(f) <= EPSILON) {
      return x;
    }
    if (fptr(a) * fptr(x) <= 0) {
      b = x;
      continue;
    }
    if (fptr(x) * fptr(b) <= 0) {
      a = x;
      continue;
    }
  }
}

int main() {
  cout << solve(0, 3.1415, atan) << endl;
  return 0;
}
