#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <utility>
using std::pair;
using std::cout;
using std::endl;
using std::cin;
using std::make_pair;
using std::max_element;
using std::max;
using std::min;
using std::vector;

void input(vector<pair<int, int> >* borders) {
  int number_of_lines;
  cin >> number_of_lines;
  cin.ignore();
  while (number_of_lines) {
    int first, second;
    cin >> first >> second;
    borders->push_back(make_pair(first, second));
    --number_of_lines;
  }
}

void output(const vector<pair<int, int> >& borders, const vector<int>& answer) {
  for (size_t i = 0; i < borders.size(); ++i) {
    cout << borders[i].first << " " << borders[i].second << " " << answer[i] << endl;
  }
}

int calculateCycleLength(int number) {
  int cycle_length = 1;
  while (number != 1) {
    if (number % 2 == 0) {
      number /= 2;
    } else {
      number *= 3;
      number += 1;
    }
    ++cycle_length;
  }
  return cycle_length;
}

int calculateMaxCylceLengthBetweenTwoNumbers(int first, int second) {
  vector<int> cycle_lengths;
  int right_border = max(first, second);
  int left_border = min(first, second);
  for (int number = left_border; number <= right_border; ++number) {
    cycle_lengths.push_back(calculateCycleLength(number));
  }
  return *max_element(cycle_lengths.begin(), cycle_lengths.end());
}

vector<int> processSolution(const vector<pair<int, int> >& borders) {
  vector<int> max_cycle_lengths;
  for (vector<pair<int, int> >::const_iterator it = borders.begin(); it != borders.end(); ++it) {
    max_cycle_lengths.push_back(calculateMaxCylceLengthBetweenTwoNumbers(it->first, it->second));
  }
  return max_cycle_lengths;
}

int main() {
  vector<pair<int, int> > borders;
  input(&borders);
  vector<int> answer = processSolution(borders);
  output(borders, answer);
  return 0;
}
