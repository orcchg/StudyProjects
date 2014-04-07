#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> allstrings(const string& alphabet, int length) {
  vector<string> result;
  if (length == 0) {
    return result;
  }
  for (int char_index = 0; char_index < alphabet.length(); ++char_index) {
    string temp;
    temp.push_back(alphabet[char_index]);
    result.push_back(temp);
  }
  if (length == 1) {
    return result;
  }
  result.clear();
  for (int i = 0; i < alphabet.length(); ++i) {
    string temp;
    temp.push_back(alphabet[i]);
    for (int j = 0; j < alphabet.length(); ++j) {
      temp.push_back(alphabet[j]);
      result.push_back(temp);
      temp = "";
      temp.push_back(alphabet[i]);
    }
  }
  if (length == 2) {
    return result;
  }
  vector<string> old_result = result;
  for (int len = 2; len < length; ++len) {
    result.clear();
    for (int i = 0; i < alphabet.length(); ++i) {
      string temp;
      temp.push_back(alphabet[i]);
      for (int j = 0; j < old_result.size(); ++j) {
        temp += old_result[j];
        result.push_back(temp);
        temp = "";
        temp.push_back(alphabet[i]);
      }
    }
    old_result = result;
  }
  return result;
}

int main() {
  int length, alphabet_size;
  cin >> length >> alphabet_size;
  string alphabet;
  for (int i = 0; i < alphabet_size; ++i) {
    char ch = 'a' + i;
    alphabet.push_back(ch);
  }
  vector<string> allstr = allstrings(alphabet, length);
  for (int i = 0; i < allstr.size(); ++i) {
    cout << allstr[i] << endl;
  }
  return 0;
}
