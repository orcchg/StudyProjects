#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;

void Q_S(vector<int>* sequence, int p, int r) {

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
		Q_S(sequence, p, j);
	}
	if (i < r) {
		Q_S(sequence, i, r);
	}
}

void Quick_Sort(vector<int>* pA, int n) {

	Q_S(pA, 0, n - 1);
}

int Partition(vector<int>* pA, int p, int r) {
  int x = pA->at(r);
	int i = p - 1;
	for (int j = p; j < r; ++j) {
	  if (pA->at(j) <= x) {
		  ++i;
		  std::swap(pA->at(i), pA->at(j));
		}
	}
	std::swap(pA->at(i + 1), pA->at(r));
	return i + 1;
}

/*void Q_S_Elim(vector<int>* sequence, int p, int r) {
  if (p < r) {
	  int q = Partition(sequence, p, r);
		Q_S_Elim(sequence, p, r - 1);
		Q_S_Elim(sequence, q + 1, r);
	}
} // PABOTAET !*/

void Q_S_Elim(vector<int>* sequence, int p, int r) {
  while (p < r) {
		int q = Partition(sequence, p, r);
	  Q_S_Elim(sequence, p, r - 1);
		p = q + 1;
		continue;
	}
}		

void Quick_Sort_Elim(vector<int>* pA, int n) {
  Q_S_Elim(pA, 0, n - 1);
}

void Output(const vector<int>& sequence) {
  for (int i = 0; i < sequence.size(); ++i) {
	  cout << sequence[i] << ' ';
	}
	cout << endl;
}

const int length = 100;
const int range = 10000;

int main() {
  srand(239);
//  while(true) {
	  int size = rand() % length + 1;
		vector<int> sequence;
		vector<int> sequence_eliminated;
		for (int i = 0; i < size; ++i) {
      sequence.push_back(static_cast<int>(2*(double)range/RAND_MAX*rand() - range));
    }
		sequence_eliminated.resize(size);
		sequence_eliminated = sequence;
		cout << "INIT: "; //
		Output(sequence_eliminated); // 
		Quick_Sort(&sequence, sequence.size());
		Quick_Sort_Elim(&sequence_eliminated, sequence_eliminated.size());
		if (sequence_eliminated != sequence) {
		  Output(sequence);
			Output(sequence_eliminated); //
//			break;
		} else {
		  cout << "OK" << endl;
			Output(sequence_eliminated); //
	  }
//	}
  _getch();
	return 0;
}