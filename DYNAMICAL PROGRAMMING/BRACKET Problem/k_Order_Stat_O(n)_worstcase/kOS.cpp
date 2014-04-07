#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;

//-----------------------------------------------------------------------------
void input(vector<int>* sequence, int* k_order_stat) {
  cout << "Enter k number of order statistic: ";
  cin >> *k_order_stat;
  cout << "Enter n sequence size: ";
  int length;
  cin >> length;
  sequence->resize(length);
  cout << "Enter vector: ";
  for (int i = 0; i < length; ++i) {
    cin >> sequence->at(i);
  }
}

//-----------------------------------------------------------------------------
void output(int k_order_stat) {
  cout << "Order stat k: " << k_order_stat << endl;
}

//-----------------------------------------------------------------------------
int sortAlgorithm(const vector<int>& sequence, int k_order_stat) {
  vector<int> temp_sequence = sequence;
  sort(temp_sequence.begin(), temp_sequence.end());
  return temp_sequence.at(k_order_stat);
}

//-----------------------------------------------------------------------------
vector<int> median_fifth(const vector<int>& sequence) {
  vector<vector<int> > sorted_fives;
  sorted_fives.resize(sequence.size() / 5 + 1);
  int j = 0;
  int size_div_five = sequence.size() - sequence.size() % 5;
  for (int i = 0; i < size_div_five; i+=5, ++j) {
    for (int k = 0; k < 5; ++k) {
      sorted_fives.at(j).push_back(sequence.at(i + k));
    }
    sort(sorted_fives.at(j).begin(), sorted_fives.at(j).end());
  }
  for (int i = size_div_five; i < sequence.size(); ++i) { 	
    sorted_fives.at(j).push_back(sequence.at(i));
  }
  sort(sorted_fives.at(j).begin(), sorted_fives.at(j).end());
  vector<int> result_medians;
  for (int i = 0; i < j; ++i) {
    result_medians.push_back(sorted_fives.at(i).at(sorted_fives.at(i).size() / 2));
  }
  return result_medians;
}

//-----------------------------------------------------------------------------
int findMedian(const vector<int>& medians) {
  if (medians.size() == 1) {
    return medians.back();
  }
  