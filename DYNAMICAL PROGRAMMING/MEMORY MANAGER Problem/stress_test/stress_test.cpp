#include <iostream>
#include <fstream>
#include <vector>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::vector;
using std::cout;

int main() {
  ifstream in_right("result_20.txt");
  ifstream in_mine("mine_20.txt");
	if (!in_right || !in_mine) {
	  cout << "UNABLE TO OPEN!\n";
	  return 1;
	}
	vector<char> right, mine;
	char ch;
	while (in_right >> ch) {
		right.push_back(ch);
	}
	char dh;
	while (in_mine >> dh) {
    mine.push_back(dh);
  }
  if (right != mine) {
    cout << "WRONG ANSWER!\n";
  } else {
    cout << "OK\n";
  }
	return 0;
}
