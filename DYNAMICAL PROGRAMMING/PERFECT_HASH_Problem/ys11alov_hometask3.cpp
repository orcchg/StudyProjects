#include <vector>
#include <algorithm>
#include <cstdlib>
#include <stdio.h>
using std::vector;

const int PRIME_NUMBER = 2000000011;
const int EMPTY_CELL = -2000000011;
const int LINEAR_MEMORY_COEFFICIENT = 5;
enum answer {NO = 0, YES = 1};

//-----------------------------------------------------------------------------
struct PairHashParams {
  long long a_residue;
  long long b_residue;

  PairHashParams():a_residue(0), b_residue(0) 
  {}
};

//-----------------------------------------------------------------------------
class CFixedSet {
  public:
    void initialize(const vector<int>& numbers);
    bool contains(int number) const;
 
  private:
    int m_primary_table_size;
    PairHashParams m_primary_hash_parameters;
    vector<PairHashParams> m_secondary_hash_parameters_array;
    vector<vector<int> > m_secondary_hash_tables_array;
 
    void makePrimaryHashing(
        const vector<int>& numbers,
        PairHashParams* primary_hash_parameters,
        vector<vector<int> >* key_buckets
        );

    void makeSecondaryHashing(
        const vector<vector<int> >& key_buckets,
        vector<PairHashParams>* secondary_hash_parameters_array,
        vector<vector<int> >* secondary_hash_tables_array
        );

    void placeNumbersToSquaredSizeTableNoCollisions(
        const vector<int>& numbers,
        PairHashParams* hash_parameters,
        vector<int>* hash_table
        );

    inline PairHashParams rollHashParameters() const;
    inline int getHashValue(PairHashParams pair, int key, unsigned size) const;
};

//---------------------------------------------------------
inline PairHashParams CFixedSet::rollHashParameters() const {
  PairHashParams a_and_b;
  a_and_b.a_residue = (static_cast<double>(rand()) / 
      RAND_MAX * (PRIME_NUMBER - 2) + 1);
  a_and_b.b_residue = (static_cast<double>(rand()) / 
      RAND_MAX * (PRIME_NUMBER - 1));
  return a_and_b;
}

//---------------------------------------------------------
inline int CFixedSet::getHashValue(
    PairHashParams pair, 
    int key, 
    unsigned size) const {
    long long auxiliary_term = pair.a_residue * key + pair.b_residue;
    if (auxiliary_term >= 0) {
      return (auxiliary_term % PRIME_NUMBER) % size;
    } else {
      // Because (-N) mod M == - (N mod M) in C/C++
      return (auxiliary_term % PRIME_NUMBER + PRIME_NUMBER) % size;
    }
}

//---------------------------------------------------------
void CFixedSet::initialize(const vector<int>& numbers) {
  vector<vector<int> > key_buckets;
  vector<vector<int> > lengths_of_chains_of_2nd_hash;

  m_primary_table_size = numbers.size();

  makePrimaryHashing(
      numbers,
      &m_primary_hash_parameters,
      &key_buckets
      );

  makeSecondaryHashing(
      key_buckets,
      &m_secondary_hash_parameters_array,
      &m_secondary_hash_tables_array
      );
}

//---------------------------------------------------------
void CFixedSet::makePrimaryHashing(
    const vector<int>& numbers,
    PairHashParams* m_primary_hash_parameters,
    vector<vector<int> >* key_buckets
    ) {
  vector<int> lengths_of_chains;
  long long sum_of_squares_of_list_lengths = 0;
  do {
    key_buckets->clear();
    key_buckets->resize(numbers.size());
    lengths_of_chains.assign(numbers.size(), 0);
    *m_primary_hash_parameters = rollHashParameters();
    for (int numbers_index = 0; 
         numbers_index < numbers.size(); 
         ++numbers_index) {
      int hash_value = getHashValue(
          *m_primary_hash_parameters, 
          numbers[numbers_index],
          numbers.size()
          );
      key_buckets->at(hash_value).push_back(
          numbers[numbers_index]
          );
      lengths_of_chains[hash_value] += 1;
    }
    for (int bucket_index = 0; 
         bucket_index < numbers.size(); 
         ++bucket_index) {
      sum_of_squares_of_list_lengths += static_cast<long long>(
          lengths_of_chains[bucket_index]) *
              lengths_of_chains[bucket_index];
    }
  } while (sum_of_squares_of_list_lengths > 
           LINEAR_MEMORY_COEFFICIENT * numbers.size()
          );
}

//---------------------------------------------------------
void CFixedSet::placeNumbersToSquaredSizeTableNoCollisions(
    const vector<int>& numbers,
    PairHashParams* hash_parameters,
    vector<int>* hash_table 
    ) {
  /* Reserve squared place */
  hash_table->resize(numbers.size() * numbers.size(), EMPTY_CELL);
  vector<int> lengths_of_chains(numbers.size() * numbers.size(), 0);

  // The loop places numbers through hash_table (squared size)
  // and excludes collisions in terms of making every length_of_chain
  // to be less or equal to 1 .
  bool has_collision_occured;
  do {
    has_collision_occured = false;
    *hash_parameters = rollHashParameters();
    hash_table->assign(hash_table->size(), EMPTY_CELL);
    lengths_of_chains.assign(
        lengths_of_chains.size(),
        0
        );
    for (int numbers_index = 0; 
         numbers_index < numbers.size(); 
         ++numbers_index) {
      int hash_value = getHashValue(
          *hash_parameters,
          numbers[numbers_index],
          hash_table->size()
          );
      hash_table->at(hash_value) = numbers[numbers_index];
      lengths_of_chains.at(hash_value) += 1;
      if (lengths_of_chains.at(hash_value) > 1) {
        has_collision_occured = true;
      }
    }
  } while (has_collision_occured);
}

//---------------------------------------------------------
void CFixedSet::makeSecondaryHashing(
    const vector<vector<int> >& key_buckets,
    vector<PairHashParams>* m_secondary_hash_parameters_array,
    vector<vector<int> >* m_secondary_hash_tables_array
    ) {
  m_secondary_hash_tables_array->resize(m_primary_table_size);
  m_secondary_hash_parameters_array->resize(m_primary_table_size);
  for (int bucket_index = 0;
       bucket_index < key_buckets.size();
       ++bucket_index) {
     if (key_buckets[bucket_index].size() != 0) {
      placeNumbersToSquaredSizeTableNoCollisions(
          key_buckets[bucket_index],
          &m_secondary_hash_parameters_array->at(bucket_index),
          &m_secondary_hash_tables_array->at(bucket_index)
          );
     }
  }
}

//---------------------------------------------------------
bool CFixedSet::contains(int number) const {
  int first_hash_index = getHashValue(
      m_primary_hash_parameters,
      number,
      m_primary_table_size
      );

  if (m_secondary_hash_tables_array[first_hash_index].size() == 0) {
    return false;
  }

  int second_hash_index = getHashValue(
      m_secondary_hash_parameters_array[first_hash_index],
      number,
      m_secondary_hash_tables_array[first_hash_index].size()
      );

  return (number == 
      m_secondary_hash_tables_array[first_hash_index].at(second_hash_index)
      );
}

//-----------------------------------------------------------------------------
void input(
    vector<int>* element_array,
    vector<int>* query_array
    ) {
  int fixedset_size; 
  scanf("%d", &fixedset_size);
  element_array->resize(fixedset_size );
  for (int i = 0; i < fixedset_size; ++i) {
    scanf("%d", &element_array->at(i));
  }
  int number_of_query;
  scanf("%d", &number_of_query);
  query_array->resize(number_of_query);
  for (int i = 0; i < number_of_query; ++i) {
    scanf("%d", &query_array->at(i));
  }
}

//-----------------------------------------------------------------------------
void output(const vector<answer>& answer_array) {
  for (int index = 0; index < answer_array.size(); ++index) {
    switch (answer_array[index]) {
      case NO:
        printf("No\n");
        break;
      case YES:
        printf("Yes\n");
        break;
      default:
        break;
    }
  }
}

//-----------------------------------------------------------------------------
int main() {
  srand(239);
  vector<int> numbers;
  vector<int> queries;
  input(&numbers, &queries);
  CFixedSet Fixed_set;
  Fixed_set.initialize(numbers);
  vector<answer> answer_array;
  for (int i = 0; i < queries.size(); ++i) {
    if (Fixed_set.contains(queries[i])) {
      answer_array.push_back(YES);
    } else {
      answer_array.push_back(NO);
    }
  }
  output(answer_array);
  return 0;
}
