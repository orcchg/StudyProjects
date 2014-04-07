#include <iostream>
#include <vector>
#include <string>
#include <iterator>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

//template <typename Inp, typename Out>
//Out Split(const string& str, Inp firstDelim, Inp lastDelim, Out result) ;

void Split(const string& str, char delim, vector<string>* res) {
  string buffer;
  for (string::iterator it = str.begin(); it != str.end(); ++it) {
    if (*it != delim) {
      buffer.push_back(delim);
    } else {
      res.push_back(buffer);
      buffer.clear();
    }
}

int main() {
  string inp;
  cin >> inp;
  vector<string> res;
  Split(inp, 't', &res);
  copy_if(res.begin(), res.end(), ostream_iterator<string>(cout, ' ')); 

  return 0;
}
