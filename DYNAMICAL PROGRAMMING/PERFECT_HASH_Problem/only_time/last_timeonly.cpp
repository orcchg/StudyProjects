#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stdio.h>
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::copy;
using std::ostream_iterator;

const int PRIME_NUMBER = 2000000011;

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
 
    inline PairHashParams RollHashParameters() const;
    inline int GetHashValue(PairHashParams pair, int key, unsigned size) const;
};

inline PairHashParams CFixedSet::RollHashParameters() const {
  PairHashParams a_and_b;
  a_and_b.a_residue = ((double)rand() / RAND_MAX * (PRIME_NUMBER - 2) + 1);
  a_and_b.b_residue = ((double)rand() / RAND_MAX * (PRIME_NUMBER - 1));
  return a_and_b;
}

inline int CFixedSet::GetHashValue(PairHashParams pair, int key, unsigned size) const {
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
  vector<int> primary_hash_values_array;
  do {
    hash_bucket_counter.assign(numbers.size(), 0);
    primary_hash_values_array.assign(numbers.size(), 0);
    m_primary_hash_parameters = RollHashParameters();
    for (int numbers_index = 0; 
         numbers_index < numbers.size(); 
         ++numbers_index) {
      int hash_value = GetHashValue(
          m_primary_hash_parameters, 
          numbers[numbers_index],
          m_secondary_hash_tables_array.size());
      primary_hash_values_array[numbers_index] = hash_value;
      hash_bucket_counter[hash_value] += 1;
    }
    max_list_length = *std::max_element(
        hash_bucket_counter.begin(),
        hash_bucket_counter.end());
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
 
  bool repeat_while_loop = false;
  bool first_time_looping = true;
  vector<int> collision_buckets(numbers.size(), 0);
  do {
    int buckets_index = 0;
    while (buckets_index < numbers.size()) {
      if (hash_bucket_counter[buckets_index] > 1) {
        if (repeat_while_loop) {
          if (collision_buckets[buckets_index] == 1) {
            m_secondary_hash_parameters_array[buckets_index] = RollHashParameters();
            collision_buckets[buckets_index] = 0;
          }
        } else {
          m_secondary_hash_parameters_array[buckets_index] = RollHashParameters();
        }
      }
      if (m_secondary_hash_tables_array[buckets_index].size() > 1) {
        m_secondary_hash_tables_array[buckets_index].assign(
            m_secondary_hash_tables_array[buckets_index].size(), -PRIME_NUMBER);
        filter[buckets_index].assign(filter[buckets_index].size(), 0);
      }
      ++buckets_index;
    }
    if (repeat_while_loop) {
      repeat_while_loop = false;
      first_time_looping = false;
    }
    for (int numbers_index = 0; numbers_index < numbers.size(); ++numbers_index) {
      int j_index = primary_hash_values_array[numbers_index];
      if (!first_time_looping && m_secondary_hash_tables_array[j_index].size() <= 1) {
        continue;
      }
      int last_key_value = GetHashValue(
          m_secondary_hash_parameters_array[j_index],
          numbers[numbers_index],
          m_secondary_hash_tables_array[j_index].size());
      m_secondary_hash_tables_array[j_index].at(last_key_value) = numbers[numbers_index];
      filter[j_index].at(last_key_value) += 1;
      if (filter[j_index].at(last_key_value) > 1) {
        repeat_while_loop = true;
        collision_buckets[j_index] = 1;
      }
    }
  } while (repeat_while_loop);
}

bool CFixedSet::Contains(int number) const {
  int j_index = GetHashValue(
      m_primary_hash_parameters,
      number,
      m_secondary_hash_tables_array.size());

  int last_key_value = GetHashValue(
    m_secondary_hash_parameters_array[j_index],
    number,
    m_secondary_hash_tables_array[j_index].size());
 
  return (number == m_secondary_hash_tables_array[j_index].at(last_key_value));
}

//-----------------------------------------------------------------------------
void input(
    vector<int>* element_array,
    vector<int>* query_array) {
  int fixedset_size; 
  scanf("%d", &fixedset_size);
  element_array->resize(fixedset_size );
  for (int i = 0; i < fixedset_size; ++i) {
    scanf("%d", &element_array->at(i));
  }
	
	//
  CFixedSet Fixed_set;
  Fixed_set.Initialize(*element_array);
	//
	
  int number_of_query;
  scanf("%d", &number_of_query);
  query_array->resize(number_of_query);
  for (int i = 0; i < number_of_query; ++i) {
    scanf("%d", &query_array->at(i));
  }
	
	//
  for (int i = 0; i < number_of_query; ++i) {
    if (Fixed_set.Contains(query_array->at(i))) { 
			 printf("Yes\n");
    } else {
			 printf("No\n");
    }			
  }
	//
	
}

//-----------------------------------------------------------------------------
int main() {
  srand(239);
  vector<int> numbers;
  vector<int> queries;
  long long clock_count = 0;
  long long clock_initialize = 0;
  input(&numbers, &queries);
  clock_count = clock();
/*  CFixedSet Fixed_set;
  Fixed_set.Initialize(numbers);
  clock_initialize = clock() - clock_count;
  for (int i = 0; i < queries.size(); ++i) {
    if (Fixed_set.Contains(queries[i])) { 
			 printf("Yes\n");
    } else {
			 printf("No\n");
    }			
  }*/
  cout << "FULL: " << (double)(clock()) / CLOCKS_PER_SEC << 
  "  ONLY INITIALIZE: " << (double)clock_initialize / CLOCKS_PER_SEC <<
  " OUTPUT: " << (double)(clock() - clock_count - clock_initialize) / CLOCKS_PER_SEC 
  << "  ONLY INPUT: " << (double)clock_count / CLOCKS_PER_SEC << '\n';
  return 0;
}
