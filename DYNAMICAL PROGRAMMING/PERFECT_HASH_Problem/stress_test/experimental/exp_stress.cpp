#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::binary_search;
using std::sort;

enum answer {NO = 0, YES = 1};
const int PRIME_NUMBER = 1000001011;

//-----------------------------------------------------------------------------
void input(
    vector<int>* element_array,
    vector<int>* query_array) {
  int fixedset_size; 
  cin >> fixedset_size;
  element_array->resize(fixedset_size);
  for (int i = 0; i < fixedset_size; ++i) {
    cin >> element_array->at(i);
  }
  int number_of_query;
  cin >> number_of_query;
  query_array->resize(number_of_query);
  for (int i = 0; i < number_of_query; ++i) {
    cin >> query_array->at(i);
  }
}

//-----------------------------------------------------------------------------
void output(const vector<answer>& answer_array) {
  for (int i = 0; i < answer_array.size(); ++i) {
    switch (answer_array[i]) {
      case NO:
        cout << "No";
        break;
      case YES:
        cout << "Yes";
        break;
      default:
        break;
    }
    cout << endl;
  }
}

//-----------------------------------------------------------------------------
struct PairHashParams {
  long long a_residue;
  long long b_residue;
 
  PairHashParams():a_residue(0), b_residue(0) 
	{};
  ~PairHashParams() 
  {};
};

//-----------------------------------------------------------------------------
class CFixedSet {
  public:
    CFixedSet() {};
    ~CFixedSet() {
      m_secondary_hash_parameters_array.clear();
      m_secondary_hash_tables_array.clear();
    };
    void Initialize(const vector<int>& numbers);
    bool Contains(int number) const;
 
  private:
    PairHashParams m_primary_hash_parameters;
    vector<PairHashParams> m_secondary_hash_parameters_array;
    vector<vector<int> > m_secondary_hash_tables_array;
 
    PairHashParams RollHashParameters(/*unsigned seed*/) const;
    int GetHashValue(PairHashParams pair, int key, unsigned size) const;
};

PairHashParams CFixedSet::RollHashParameters(/*unsigned seed*/) const {
  PairHashParams a_and_b;
//  srand(seed);
  a_and_b.a_residue = /*static_cast<long long>*/((double)rand() / RAND_MAX * (PRIME_NUMBER - 2) + 1);
  //cout << "A: " <<  a_and_b.a_residue;
  a_and_b.b_residue = /*static_cast<long long>*/((double)rand() / RAND_MAX * (PRIME_NUMBER - 1));
  //cout << "  B: " <<  a_and_b.b_residue << endl;
  return a_and_b;
}

int CFixedSet::GetHashValue(PairHashParams pair, int key, unsigned size) const {
  return ((
       static_cast<long long>(fabs(pair.a_residue * key +
       pair.b_residue)) 
       % PRIME_NUMBER) 
       % size);
}

void CFixedSet::Initialize(const vector<int>& numbers) {
  m_secondary_hash_parameters_array.resize(numbers.size());
  m_secondary_hash_tables_array.resize(numbers.size());
 
  int max_list_length = 0;
  vector<int> hash_bucket_counter;
//  int seed = 0;
  do {
    hash_bucket_counter.assign(m_secondary_hash_tables_array.size(), 0);
    m_primary_hash_parameters = RollHashParameters(/*179 + seed * 112*/);
    for (int numbers_index = 0; 
         numbers_index < numbers.size(); 
         ++numbers_index) {
      int hash_value = GetHashValue(
          m_primary_hash_parameters, 
          numbers[numbers_index],
          m_secondary_hash_tables_array.size());
      hash_bucket_counter[hash_value] += 1;
      //cout << hash_value << " "; //
    }
    //cout << endl; //
    max_list_length = *std::max_element(
        hash_bucket_counter.begin(),
        hash_bucket_counter.end());
    //cout << "MLL: " << max_list_length << endl;
//    seed += 5;
  } while (max_list_length >= 10);
 
  vector<vector<int> > filter(m_secondary_hash_tables_array.size());
  for (int bucket_index = 0; 
       bucket_index < m_secondary_hash_tables_array.size(); 
       ++bucket_index) {
    if (hash_bucket_counter[bucket_index] != 0) {
      m_secondary_hash_tables_array[bucket_index].resize(
          hash_bucket_counter[bucket_index] * hash_bucket_counter[bucket_index],
          -PRIME_NUMBER);
    } else {
      m_secondary_hash_tables_array[bucket_index].resize(1, -PRIME_NUMBER);
    }
    filter[bucket_index].resize(
         hash_bucket_counter[bucket_index] * hash_bucket_counter[bucket_index],
         0);
  }
 
 // seed = 0;
  bool repeat_while_loop = false;
  vector<int> collision_buckets(numbers.size(), 0);
  do {
    int buckets_index = 0;
    while (buckets_index < numbers.size()) {
      if (hash_bucket_counter[buckets_index] > 1) {
        if (repeat_while_loop) {
          if (collision_buckets[buckets_index] == 1) {
            //cout << buckets_index << "  coll ";
            m_secondary_hash_parameters_array[buckets_index] = RollHashParameters(/*109 + seed * 113*/);
            collision_buckets[buckets_index] = 0;
          }
        } else {
          //cout << buckets_index << "  ";
          m_secondary_hash_parameters_array[buckets_index] = RollHashParameters(/*432 + seed * 16*/);
        }
    //    seed += 3;
      }
      m_secondary_hash_tables_array[buckets_index].assign(
          m_secondary_hash_tables_array[buckets_index].size(), -PRIME_NUMBER);
      filter[buckets_index].assign(filter[buckets_index].size(), 0);
      ++buckets_index;
    }
    if (repeat_while_loop) {
      repeat_while_loop = false;
    }
    for (int numbers_index = 0; numbers_index < numbers.size(); ++numbers_index) {
      int j_index = GetHashValue(
          m_primary_hash_parameters, 
          numbers[numbers_index],
          m_secondary_hash_tables_array.size());
      int last_key_value = GetHashValue(
          m_secondary_hash_parameters_array[j_index],
          numbers[numbers_index],
          m_secondary_hash_tables_array[j_index].size());
      m_secondary_hash_tables_array[j_index].at(last_key_value) = numbers[numbers_index];
      filter[j_index].at(last_key_value) += 1;
      /*cout << m_secondary_hash_tables_array[j_index].at(last_key_value) << " " 
			<< j_index << " " << m_secondary_hash_tables_array[j_index].size() << " " << last_key_value << " " 
			<< filter[j_index].at(last_key_value) << endl;*/
      if (filter[j_index].at(last_key_value) > 1) {
        repeat_while_loop = true;
        collision_buckets[j_index] = 1;
  //      seed += 1;
      }
    }
  //    cout << "PROCEED" << endl;
  } while (repeat_while_loop);
}

bool CFixedSet::Contains(int number) const {
  int j_index = GetHashValue(
      m_primary_hash_parameters,
      number,
      m_secondary_hash_tables_array.size());
//  cout << "CONTAINS: PRIMARY HASH Proceed" << endl;

  int last_key_value = GetHashValue(
    m_secondary_hash_parameters_array[j_index],
    number,
    m_secondary_hash_tables_array[j_index].size());
//  cout << "CONTAINS: SECONDARY HASH Proceed" << endl;
 
  return (number == m_secondary_hash_tables_array[j_index].at(last_key_value));
}

//-----------------------------------------------------------------------------
vector<answer> binarySearch(
    const vector<int>& numbers,
    const vector<int>& queries) {
  vector<int> numeros = numbers;
  sort(numeros.begin(), numeros.end());
  vector<answer> answer_array;
  for (int q = 0; q < queries.size(); ++q) {
    if (binary_search(numeros.begin(), numeros.end(), queries[q])) {
      answer_array.push_back(YES);
    } else {
      answer_array.push_back(NO);
    }
  }
  return answer_array;
}

//-----------------------------------------------------------------------------
template <typename T>
void printVector(const vector<T>& v) {
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i] << ' ';
  }
  cout << endl;
}

int countOnes(const vector<answer> va) {
  int counter = 0;
  for (int i = 0; i < va.size(); ++i) {
    if (va[i] == YES) {
      ++counter;
    }
  }
  return counter;
}

//-----------------------------------------------------------------------------
const int NUMBERS = 100000;
const int QUERIES = 1000000;
const int LIMIT = 10000 * NUMBERS;

//-----------------------------------------------------------------------------
int main() {
  long long it = 0;
  double clocks = 0.0;
  double clockverk = 0.0;
  double clock_binary = 0.0;
  double max_clock = 0.0;
  double max_clock_sum = 0.0;
	srand(239);
while (true) {
  vector<int> numbers(NUMBERS);
  vector<int> queries(QUERIES);
//  srand(39 + it);
  for (int nums = 0; nums < NUMBERS; ++nums) {
    numbers[nums] = 10000 * (nums + 1) + rand() % 9567 - LIMIT / 2;
  }
  for (int quer = 0; quer < QUERIES; ++quer) {
    queries[quer] = static_cast<int>((double)rand() / RAND_MAX * 2 * LIMIT - LIMIT);
  }
 /* for (int quer = 0; quer <= QUERIES / NUMBERS; ++quer) {
    queries.insert(queries.begin() + quer * NUMBERS, numbers.begin(), numbers.end()); 
  }*/
  queries.erase(queries.begin() + QUERIES, queries.end());
//  input(&numbers, &queries);
  CFixedSet Fixed_set;
//  printVector(numbers);
//  printVector(queries);
  Fixed_set.Initialize(numbers);
  vector<answer> answer_array_hash;
//  cout << "START CONTAINS" << endl;
  for (int i = 0; i < queries.size(); ++i) {
//  cout << "DONE " << i + 1 << " / " << queries.size() << endl;
    if (Fixed_set.Contains(queries[i])) {
      answer_array_hash.push_back(YES);
    } else {
      answer_array_hash.push_back(NO);
    }
  }
  if (max_clock < (double)clock() / CLOCKS_PER_SEC - clocks - clock_binary) {
    max_clock = (double)clock() / CLOCKS_PER_SEC - clocks - clock_binary;
  }
  clockverk = (double)clock() / CLOCKS_PER_SEC - clocks - clock_binary;
  clocks = (double)clock() / CLOCKS_PER_SEC;
  vector<answer> answer_array_binary;
  answer_array_binary = binarySearch(numbers, queries);
  clock_binary = (double)clock() / CLOCKS_PER_SEC - clocks;
  if (max_clock_sum < clockverk + clock_binary) {
    max_clock_sum = clockverk + clock_binary;
  }
  if (answer_array_hash != answer_array_binary) {
    cout << "WRONG ANSWER!" << endl;
    printVector(numbers);
    printVector(queries);
    cout << "HASH: " << endl;
    output(answer_array_hash);
    cout << "BINARY: " << endl;
    output(answer_array_binary);
    break;
  } else {
 //   printVector(numbers);
 //   printVector(queries);
 //   printVector(answer_array_hash);
    cout << countOnes(answer_array_hash) << " " << countOnes(answer_array_binary) << " " << 
    (double)countOnes(answer_array_hash) / QUERIES << "  ";
    cout << "OK  " << clockverk << " " << max_clock << "  BIN: " << clock_binary << 
    "  SUM: " << clockverk + clock_binary << "  MAX_SUM: " << max_clock_sum << endl;
//    it += /*static_cast<int>(rand() / RAND_MAX * 1000 + 15) + pow(-1, rand() % 19) * 12;*/ 17;
  }
}
//  output(answer_array);
  return 0;
}
