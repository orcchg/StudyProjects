#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::vector;

//--------------------------------------------------------------
void Q_S(vector<int>* sequence, int p, int r){

	int i,j,q,temp;
	
	i = p;
	j = r;
	q = (p+r)/2;
	
	do {
		while((sequence->at(i) < sequence->at(q)) && (i < r))
			i++;
		while((sequence->at(q) < sequence->at(j)) && (j > p))
			j--;
		
		if(i <= j){
			temp = sequence->at(i);
			sequence->at(i) = sequence->at(j);
			sequence->at(j) = temp;
			i++;
			j--;
		}
	} while (i <= j);
	
	if(p < j)
		Q_S(sequence, p, j);
	if(i < r)
		Q_S(sequence, i, r);
}

void Quick_Sort(vector<int>* sequence){

	Q_S(sequence, 0, sequence->size() - 1);
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void QuickSort(vector<int>* sequence, int p, int r) {
	int i = p;
	int j = r;
	int q = p + (r - p)/2;
	
	do {
		while (sequence->at(i) < sequence->at(q)) {
			++i;
		}
		while (sequence->at(q) < sequence->at(j)) {
			--j;
		}
		
		if (i <= j) {
			int temp = sequence->at(i);
			sequence->at(i) = sequence->at(j);
			sequence->at(j) = temp;
			++i;
			--j;
		}
	} while (i <= j);
	
	if (p < j) {
		QuickSort(sequence, p, j);
	}
	if (i < r) {
		QuickSort(sequence, i, r);
	}
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void QuickSort_virt(vector<int>* sequence, int p, int r) {

	int i = p;
	int j = r;
	int temp;
	int m = p + (r - p) / 2;
	int x = sequence->at(m);
	
	while (i <= j) {
		while (sequence->at(i) < x) {
			++i;
		}
		while (x < sequence->at(j)) {
			--j;
		}
		
		if (i <= j) {
			temp = sequence->at(i);
			sequence->at(i) = sequence->at(j);
			sequence->at(j) = temp;
			++i;
			--j;
		}
	}
	
	if (p < j) {
		QuickSort_virt(sequence, p, j);
	}
	if (i < r) {
		QuickSort_virt(sequence, i, r);
	}
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void ChooseMinimumSort(vector<int>* sequence) {

  for (int position = 0; position + 1 < sequence->size(); ++position) {
  
    int minimum = sequence->at(position);
    int index_of_minimum = position;
	
    for (int i = position + 1; i < sequence->size(); ++i) {
	
      if (sequence->at(i) < minimum) {
        minimum = sequence->at(i);
        index_of_minimum = i;
      }
    }
    swap(sequence->at(position), sequence->at(index_of_minimum));
	
  }
  
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void OutputSequence(const string& name, 
                    const vector<int>& sequence) {
  cout << name;
  for (int i = 0; i < sequence.size(); ++i) {
    cout << ' ' << sequence[i];
  }
  cout << endl;
}
//--------------------------------------------------------------


const int MAX_SEQUENCE_LENGTH = 4;
const int MAX_ELEMENT = 100;

//--------------------------------------------------------------
int main()
{
	srand(239);
	while(true)
	{
		int sequence_length = rand() % MAX_SEQUENCE_LENGTH + 1;
		vector<int> sequence;
		
		for (int i = 0; i < sequence_length; ++i) {
			sequence.push_back(rand() % MAX_ELEMENT + 1);
		}
		
		vector<int> sequence_copy_for_bubble_sort = sequence;
		QuickSort_virt(&sequence_copy_for_bubble_sort, 
		          0, sequence.size() - 1);
		
		vector<int> sequence_copy_for_minimum_sort = sequence;
		ChooseMinimumSort(&sequence_copy_for_minimum_sort);
		
		if (sequence_copy_for_bubble_sort != sequence_copy_for_minimum_sort) 
		{
			cout << "Wrong Answer!" << endl;
			OutputSequence("Test:", sequence);
			OutputSequence("Quick sort:", sequence_copy_for_bubble_sort);
			OutputSequence("Minimum sort:", sequence_copy_for_minimum_sort);
			break;
		} 
		else 
		{
			cout << "OK" << endl;
		}
	}
	
  cin.ignore();
  return 0;
}