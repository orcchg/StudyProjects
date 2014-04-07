#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <map>
using namespace std;

void calcNGramms(const string& str, size_t n, map<string, size_t>* const result) {
  for (int position = 0; position < str.length() - n + 1; ++position) {
    string n_gramm;
    for (int index = 0; index < n; ++index) {
      n_gramm += str[position + index];
    }
    if (result->find(n_gramm) != result->end()) {
      ++result->operator[](n_gramm);
    } else {
      result->operator[](n_gramm) = 1;
    }
  }
}

void output(const map<string, size_t>& dict) {
  for (map<string, size_t>::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    cout << "[ " << it->first << " ]  " << it->second << endl; 
  }
}

int main(int argc, char** argv) {
  char* text = argv[1];
  string str(text);
  map<string, size_t> dict;
  calcNGramms(str, 5, &dict);
  output(dict);
  return 0;
}
