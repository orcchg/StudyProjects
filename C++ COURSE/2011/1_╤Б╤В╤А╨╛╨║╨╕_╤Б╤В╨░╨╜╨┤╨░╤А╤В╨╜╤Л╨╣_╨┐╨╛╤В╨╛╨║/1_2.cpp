#include <iostream>
#include <string>
#include <iterator>
#include <fstream>
#include <set>
using namespace std;

void input(const string& filename, string* text) {
  ifstream fin(filename.c_str());
  if (!fin) {
    cerr << "File " << filename << " not found!" << endl;
    throw;
  }

  char ch;
  while (!fin.eof()) {
    fin.get(ch);
    *text += ch;
  }
  fin.close();
}

bool is_space(char ch) {
  return (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\b');
}

bool is_point(char ch) {
  return (ch == '.' || ch == ',' || ch == ';' || ch == ':');
}

int countWords(const string& text) {
  int number_of_words = 0;
  int number_of_lines = 0;
  for (string::const_iterator it = text.begin(); it != text.end(); ++it) {
    if (is_space(*it)) {
      ++number_of_words;
    }
    if (*it == '\n') {
      ++number_of_lines;
    }
  }
  return number_of_words;
}

int countUniqueWords(const string& text) {
  set<string> set_of_words;
  string temp;
  for (string::const_iterator it = text.begin(); it != text.end(); ++it) {
    if (!is_space(*it) && !is_point(*it) && *it != '\n') {
      temp += *it;
    } else {
      set_of_words.insert(temp);
      temp = "";
    }
  }
  return set_of_words.size();
}

int main() {
  string text;
  input("text.txt", &text);
  cout << text << endl;
  cout << "WORDS COUNT: " << countWords(text) << endl;
  cout << "UNIQUE COUNT: " << countUniqueWords(text) << endl;
  return 0;
}
