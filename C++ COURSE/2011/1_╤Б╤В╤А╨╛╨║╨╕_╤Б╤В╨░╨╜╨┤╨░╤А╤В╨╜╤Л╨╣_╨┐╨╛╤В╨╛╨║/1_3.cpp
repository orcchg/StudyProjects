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

vector<string> findContext(const string& text, const string& word) {
  map<string, vector<pair<int, int> > > dict;
  makeIndex(text, &dict);
  int number_of_lines = 1, last_place = 0;
  // calculate upper text limits
  string::const_iterator strit = text.end() - 1;
  while (*strit != '\n') {
    ++last_place;
  }
  for (string::const_iterator it = text.begin(); it != text.end(); ++it) {
    if (*it == '\n') {
      ++number_of_lines;
    }
  }
  vector<pair<int, int> > wordplace = dict[word];
  vector<string> answer;
  for (int word_index = 0; word_index < wordplace.size(); ++word_index) {
    int number_of_spaces = 0, current_line = wordplace[word_index].first, current_place = wordplace[word_index].second;
    string left_context, right_context;
    while (number_of_spaces < 4) {
      if (current_line != 1 && current_place != 0) {
        left_context += text[current_place];
        --current_place;
      } else {
        break;
      }
    }
    reverse(left_context.begin(), left_context.end());
    while (number_of_spaces < 4) {
      if (current_line != number_of_lines && current_place != last_place) {
        right_context += text[current_place + word.length()];
        ++current_place;
      } else {
        break;
      }
    }
    answer.push_back(left_context + word + right_context);
  }
  return answer;
}

int main(int argc, char** argv) {
  char* filename = argv[1];
  char* word_c = argv[2];
  string text, word(word_c);
  input(filename, &text);
  vector<string> context_array = findContext(text, word);
  copy(context_array.begin(), context_array.end(), ostream_iterator<string>(cout, "\n"));
  return 0;
}
  