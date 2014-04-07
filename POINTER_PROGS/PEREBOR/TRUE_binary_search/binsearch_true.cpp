#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

void Input(vector<int>* sequence) {
  int N;
  cin >> N;
	sequence->resize(N);
	for (int i = 0; i < N; ++i) {
	  cin >> sequence->at(i);
	}
}

void Output(int answer) {
  cout << answer << endl;
}

void Output_seq(const vector<int>& seq) {
  for (int i = 0; i < seq.size(); ++i) {
	  cout << seq[i] << ' ';
	}
	cout << endl;
}

int Binary_Search(const vector<int>& a, int x) {
    size_t first = 0; /* Первый элемент в массиве */
    size_t last = a.size();    /* Элемент в массиве, СЛЕДУЮЩИЙ ЗА последним */
                                        /* Если просматриваемый участок непустой, first<last */
    size_t mid; 
 
    if (a.size() == 0)
    {
         /* массив пуст */
				 return -1;
    } 
    else if (a[0] > x)
    {
         /* не найдено; если вам надо вставить его со сдвигом - то в позицию 0    */
				 return -1;
    } 
    else if (a[a.size() - 1] < x)
    {
         /* не найдено; если вам надо вставить его со сдвигом - то в позицию n    */
				 return -1;
    }
 
    while (first < last)
    {
        /* ВНИМАНИЕ! В отличие от более простого (first+last)/2, этот код стоек к переполнениям.    */
        mid = first + (last - first) / 2;
 
        if (x <= a[mid])
        {
            last = mid;
        }
        else
        {
            first = mid + 1;
        }
    }
 
    /* Если проверка n==0 в начале опущена - значит, тут раскомментировать!    */
    if (/*a.size()!=0 &&*/ a[last] == x)
    {
        /* Искомый элемент найден. last - искомый индекс */
				return last;
    } else
    {
        /* Искомый элемент не найден. Но если вам вдруг надо его вставить со сдвигом, то его место - last.    */
				return -1;
    }
}

int main() {
  int lambda;
	vector<int> sequence;
	Input(&sequence);
	cin >> lambda;
	sort(sequence.begin(), sequence.end());
	Output_seq(sequence);
	Output(Binary_Search(sequence, lambda));
	Output(sequence[Binary_Search(sequence, lambda)]);
	_getch();
	return 0;
}