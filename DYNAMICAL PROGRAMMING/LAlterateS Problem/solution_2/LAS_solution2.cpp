#include <iostream>
#include <vector>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

//-----------------------------------------------------------------------------
void Input(vector<int>* sequence) {
	int length;
	
	cin >> length;
  sequence->resize(length);
	
  for (int i = 0; i < length; ++i) {
    cin >> sequence->at(i);
  }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Output(const vector<int>& sequence) {
	for (int i = 0; i < sequence.size(); ++i) {
    cout << sequence[i] << ' ';
  }
  cout << endl;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Unique(const vector<int>& sequence) {
	vector<int> result;
	result.push_back(sequence[0]);
	
	for (int j = 1; j < sequence.size(); ++j) {
		if (sequence[j] == sequence[j - 1]) {
			continue;
		}
		result.push_back(sequence[j]);
	}
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Find_Nodes(const vector<int>& sequence) {
	vector<int> result;
	result.push_back(sequence[0]);
	
	for (int i = 1; i + 1 < sequence.size(); ++i) {
		if ((sequence[i] > sequence[i - 1] && sequence[i] > sequence[i + 1]) ||
				(sequence[i] < sequence[i - 1] && sequence[i] < sequence[i + 1]) ) {
			result.push_back(sequence[i]);
		}
	}
	result.push_back(sequence.back());
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Build_LAS(const vector<int>& sequence, const vector<int>& nodes) {
	vector<int> result;
	result.push_back(sequence[0]);
	
	int j_node = 0;
	int prev = 0;
	if (nodes[1] >= nodes[0])	{  // Type I
		while(j_node + 2 <= nodes.size()) {
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] > result.back() &&
						sequence[i] <= nodes[j_node + 1] &&
						sequence[i] > nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
			
			if (j_node + 2 >= nodes.size() ||
					prev == nodes.size()) {
				break;
			}
				
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] < nodes[j_node] &&
						sequence[i] >= nodes[j_node + 1] &&
						sequence[i] < result.back() &&
						sequence[i] < nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
		}
		
		if (nodes[j_node] < nodes.back()) {  // increasing tail
//			cout << "Increasing tail type I" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//				cout << "CYCLE inc tail type I" << endl;
				if (sequence[i] > nodes[j_node] &&
						sequence[i] > result.back() &&
						sequence[i] <= nodes.back()) {
//						cout << "GOT inc tail type I" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		} else { // decreasing tail
//			cout << "Decreasing tail type I" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//			cout << "CYCLE dec tail type I" << endl;
				if (sequence[i] < nodes[j_node] &&
						sequence[i] < result.back() &&
						sequence[i] >= nodes.back()) {
//						cout << "GOT dec tail type I" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		}
//---------------------------------------------------------			
	} else {  									 // Type 2
		while(j_node + 2 <= nodes.size()) {
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] < result.back() &&
						sequence[i] >= nodes[j_node + 1] &&
						sequence[i] < nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
			
			if (j_node + 2 >= nodes.size() ||
					prev == nodes.size()) {
				break;
			}
				
			for (int i = prev; i < sequence.size(); ++i) {
				if (sequence[i] > nodes[j_node] &&
						sequence[i] <= nodes[j_node + 1] &&
						sequence[i] > result.back() &&
						sequence[i] > nodes[j_node + 2]) {
					result.push_back(sequence[i]);
					++j_node;
					prev = i;
					break;
				}
			}
		}
		
		if (nodes[j_node] < nodes.back()) {  // increasing tail
//			cout << "Increasing tail type II" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//			cout << "CYCLE inc tail type II" << endl;
				if (sequence[i] > nodes[j_node] &&
						sequence[i] > result.back() &&
						sequence[i] <= nodes.back()) {
//						cout << "GOT inc tail type II" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		} else { // decreasing tail
//			cout << "Decreasing tail type II" << endl;
			for (int i = prev; i < sequence.size(); ++i) {
//			cout << "CYCLE dec tail type II" << endl;
				if (sequence[i] < nodes[j_node] &&
						sequence[i] < result.back() &&
						sequence[i] >= nodes.back()) {
//						cout << "GOT dec tail type II" << endl;
					result.push_back(sequence[i]);
					break;
				}
			}
		}
	}
	
	return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
vector<int> Find_LAS(const vector<int>& sequence) {
  vector<int> result;
	
	vector<int> unique;
  unique = Unique(sequence);
	
	vector<int> nodes;
	nodes = Find_Nodes(unique);
//	cout << nodes.back() << endl;
//	Output(nodes);
	
	result = Build_LAS(unique, nodes);
	
  return result;
}
//-----------------------------------------------------------------------------

/*****************************************************************************/
int main()
{
	vector<int> sequence;
	Input(&sequence);
	vector<int> result_LAS;
	result_LAS = Find_LAS(sequence);
	Output(result_LAS);
	
	_getch();
	return 0;
}
/*****************************************************************************/