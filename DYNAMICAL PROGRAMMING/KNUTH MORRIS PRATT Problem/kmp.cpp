#include <string>
#include <vector>
#include <iostream>
using namespace std;
 
int KMP(const string& S, int begin, const string& pattern){
  vector<int> pf (pattern.length());
  pf[0] = 0;
  for (int k = 0, i = 1; i < pattern.length(); ++i){
    while(k > 0 && pattern[i] != pattern[k]) {
      k = pf[k - 1];
    }

    if (pattern[i] == pattern[k]) {
      k++;
    }
      pf[i] = k;
    }
  for (int k = 0, i = begin; i < S.length(); ++i){
    while ((k > 0) && (pattern[k] != S[i])) {
      k = pf[k - 1];
    }

    if (pattern[k] == S[i]) {
      k++;
    }
    if (k == pattern.length())
      return (i - pattern.length() + 1);//либо продолжаем поиск следующих вхождений
    }

  return -1;
}

int main() {
  string text, pattern;
  cin >> text;
  cin >> pattern;
  cout << text << " " << pattern << endl;
  cout << KMP(text, 0, pattern);
  return 0;
}
