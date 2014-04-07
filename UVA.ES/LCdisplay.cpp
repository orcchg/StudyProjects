#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cmath>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::pair;
using std::make_pair;
using std::string;
using std::pow;
using std::reverse;

void input(vector<pair<int, int> >* species) {
  int size = 1, number = 1;
  while (size != 0 && number != 0) {
    cin >> size >> number;
    species->push_back(make_pair(size, number));
  }
  species->pop_back();
}

string itoa(int number, int BASE = 10) {
  int temp = number;
  int power = 0;
  while (temp) {
    temp /= BASE;
    ++power;
    // cout << temp << " " << power << endl;
  }
  string alphanumeric = "";
  while (power) {
    int rest = pow(BASE, power - 1);
    int digit = number / rest;
    // cout << rest << " " << number << " " << digit << endl;
    alphanumeric += '0' + digit;
    number -= rest * digit;
    --power;
  }
  return alphanumeric;
}

void output(const vector<pair<int, int> >& species) {

}

int main() {
  vector<pair<int, int> > species;
  input(&species);
  output(species);
  return 0;
}
