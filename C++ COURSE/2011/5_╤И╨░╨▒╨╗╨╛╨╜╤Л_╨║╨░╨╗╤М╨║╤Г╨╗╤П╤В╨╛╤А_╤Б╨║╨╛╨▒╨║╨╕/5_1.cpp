#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <ostream>
#include <vector>
#include <map>
#include <string>
#include <utility>
using namespace std;

class IOException {
public:
  IOException() {
    cerr << "IO exception invoked!" << endl;
  }
};

void input(const char* filename, string* text) {
  ifstream fin(filename);
  if (!fin) {
    throw IOException();
  }
  while (!fin.eof()) {
    *text += fin.get();
  }
  fin.close();
}

void output(const string& text) {
  cout << text << endl;
}

template <typename T>
void output(const vector<T>& array) {
  copy(array.begin(), array.end(), ostream_iterator<T>(cout, "\n"));
}

void output(const map<string, vector<pair<int, int> > >& dict) {
  for (map<string, vector<pair<int, int> > >::const_iterator it = dict.begin(); it != dict.end(); ++it) {
    cout << "[ " << it->first << " ]  ";
    for (vector<pair<int, int> >::const_iterator vit = it->second.begin(); vit != it->second.end(); ++vit) {
      cout << "(" << vit->first << "," << vit->second << ") ";
    }
    cout << endl;
  }
}

void splitTextOnLines(const string& text, vector<string>* lines) {
  string str;
  for (string::const_iterator it = text.begin(); it != text.end(); ++it) {
    if (*it != '\n') {
      str += *it;
    } else {
      lines->push_back(str);
      str.clear();
    }
  }
}

bool isAlpha(char ch) {
  if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
    return true;
  }
  return false;
}

void makeIndex(const vector<string>& lines, map<string, vector<pair<int, int> > >* const result) {
  int line_number = 1;
  for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it, ++line_number) {
    int position = 1;
    string word;
    for (string::const_iterator strit = it->begin(); strit != it->end(); ++strit, ++position) {
      if (!isAlpha(*strit)) {
        if (result->find(word) != result->end()) {
          result->operator[](word).push_back(make_pair(line_number, position - word.length()));
        } else {
          vector<pair<int, int> > new_pairs(1, make_pair(line_number, position - word.length()));
          result->operator[](word) = new_pairs;
        }		
        word.clear();
      } else {
        word += *strit;
      }
    }
  }
}

void makeIndex(const string& text, map<string, vector<pair<int, int> > >* const result) {
  vector<string> lines;
  splitTextOnLines(text, &lines);
  makeIndex(lines, result);
}

int main(int argc, char** argv) {
  char* filename = argv[1];
  string text;
  input(filename, &text);
  // output(text);
  // cout << "\n\n\n";
  vector<string> lines;
  splitTextOnLines(text, &lines);
  output<string>(lines);
  map<string, vector<pair<int, int> > > result;
  makeIndex(lines, &result);
  output(result);
  return 0;
}
  