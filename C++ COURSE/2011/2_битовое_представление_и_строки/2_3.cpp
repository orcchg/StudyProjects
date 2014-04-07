#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool compare(const string& first, const string& second) {
  if (first.length() < second.length()) {
    return true;
  } else if (first.length() > second.length()) {
    return false;
  }
  for (size_t i = 0; i < first.length(); ++i) {
    if (first[i] < second[i]) {
      return true;
    }
  }
  return false;
}

void input(vector<string>* array) {
  string str;
  while (getline(cin, str)) {
    array->push_back(str);
  }
}

int main() {
  vector<string> array;
  input(&array);
  sort(array.begin(), array.end(), compare);
  copy(array.begin(), array.end(), ostream_iterator<string>(cout, "\n"));
  return 0;
}
