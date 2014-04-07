#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

//-----------------------------------------------------------------------------
struct Cube {
  int a_size;
  int b_size;
  int c_size;
};

//-----------------------------------------------------------------------------
void Input(vector<Cube>* Cubes) {
  int number_of_cubes;
  cin >> number_of_cubes;
  Cubes->resize(number_of_cubes);
  for (int i = 0; i < Cubes->size(); ++i) {
    cin >> Cubes->at(i).a_size >> Cubes->at(i).b_size >> Cubes->at(i).c_size;
  }
}

//-----------------------------------------------------------------------------
bool is_include(const vector<Cube>& Cubes, int index_first, int index_second) {
  return ( (Cubes[index_first].a_size < Cubes[index_second].a_size) && 
           (Cubes[index_first].b_size < Cubes[index_second].b_size) && 
           (Cubes[index_first].c_size < Cubes[index_second].c_size) );
}

//-----------------------------------------------------------------------------
int find_max_subseq_len(const vector<Cube>& Cubes, 
    const vector<int>& max_len_sequence,
    int L_border, 
    int R_border) {
  
  int max_length = 0;
  for (int j = L_border; j < R_border; ++j) {
    if (is_include(Cubes, j, R_border)) {
      if (max_len_sequence[j] > max_length) {
        max_length = max_len_sequence[j];
      }
    }
  }
  return max_length;
}

//-----------------------------------------------------------------------------
int Answer(const vector<Cube>& Cubes) {
  vector<int> max_len_sequence;
  max_len_sequence.resize(Cubes.size(), 0);
  max_len_sequence[0] = 1;
  
  for (int i = 1; i < Cubes.size(); ++i) {
    max_len_sequence[i] = find_max_subseq_len(Cubes, max_len_sequence, 0, i) + 1;
  }
  int ans = max_len_sequence[0];
  for (int i = 1; i < Cubes.size(); ++i) {
    if (max_len_sequence[i] > ans) {
      ans = max_len_sequence[i];
    }
  }
  return ans;
}

/*****************************************************************************/
int main()
{
  vector<Cube> Cubes;
  Input(&Cubes);
  cout << Answer(Cubes);
  return 0;
}

/** Created by
  * Alov Maksim,
	*	CS. 09/2011
	*/
