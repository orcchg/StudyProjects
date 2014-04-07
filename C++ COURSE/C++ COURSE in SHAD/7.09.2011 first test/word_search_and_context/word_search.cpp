#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

const bool YES = 1;
const bool NO = 0;

//--------------------------------------------------------------------------------------------
bool is_present(const string & buffer, const string & sample, vector<unsigned>* positions) {

	unsigned n = buffer.length();
	unsigned m = sample.length();
	unsigned index = 0;
	bool result = false;
	
	for(size_t i = 0; i <= n - m + 1; ++i) {
		unsigned j = 0;
		while(j <= m && sample[j] == buffer[i + j - 1]) {
			++j;
		}
		if (j == m + 1) {
			positions->at(index) = i;
			result = true;
			++index;
		}
	}
	return result;
}			
//--------------------------------------------------------------------------------------------

struct word_index {
	size_t char_i;
	size_t word_i;
	
	word_index() :
		char_i(0),
		word_i(0)
	{}
};


/********************************************************************************************/
int main()
{
	ifstream fin("test.txt");
	if (!fin) {
		cout << "Unable to open file!\n";
		return 1;
	}
	
	string buffer;
	char c;
	
	fin >> buffer;
		
	string word;	
	cout << "Enter sample word: ";
	cin >> word;
	cin.ignore();
	
	vector<size_t> positions;
	positions.clear();
	
	vector<string> words;
	words.clear();
	
	vector<size_t> word_pos;
	word_pos.clear();
	
	word_index wordCount;
	
	if (buffer, word, &positions) {
		bool IN_WORD = NO;
		while(fin.get(c)) {
			++wordCount.char_i;
			if (c == ' ' || c == '\t' || c == '\n') {
				IN_WORD = NO;
			} else if (IN_WORD == NO) {
				word_pos[wordCount.word_i] = wordCount.char_i;
				++wordCount.word_i;
				IN_WORD = YES;
			} else if (IN_WORD == YES) {
				words[wordCount.word_i] += c;
			}
		}
		for(size_t index = 0; index < positions.size(); ++index) {
		
			unsigned min = fabs(positions[index] - word_pos[0]);
			size_t index_close = 0;
			for(size_t j = 1; j < word_pos.size(); ++j) {
				if ( fabs(positions[index] - word_pos[j]) < min) {
					min = fabs(positions[index] - word_pos[j]);
					index_close = j;
				}
			}
					
			for(int word_ind = -3; word_ind <= 3; ++word_ind) {
				if (index_close + word_ind >= 0) {
					cout << words[index_close + word_ind] << " ";
				} else {
					continue;
				}
			}
			cout << endl;
		}
	}
					
	fin.close();
	cin.ignore();
	return 0;
}
/********************************************************************************************/