#include <algorithm>
#include <complex>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::reverse;
using std::swap;
using std::max;
using std::complex;

const string LITERALS = "AGTC";

//-----------------------------------------------------------------------------
void input(string* first_string, string* second_string) {
  getline(cin, *first_string);
  getline(cin, *second_string);
}

int findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    );

int output(const string& first_string, const string& second_string) {
  return findPositionOfMostMatches(first_string, second_string);
}

int naive_findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    );

int outputNaive(const string& first_string, const string& second_string) {
  return naive_findPositionOfMostMatches(first_string, second_string);
}

int stupid_findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    );

int outputStupid(const string& first_string, const string& second_string) {
  return stupid_findPositionOfMostMatches(first_string, second_string);
}

//---------------------------------------------------------
void generateInput(
    int first_length,
    int second_length,
    string* first_string,
    string* second_string
    ) {
  if (first_length < second_length) {
    cerr << "Invalid string lengths!" << endl;
    throw;
  }
  for (int i = 0; i < first_length; ++i) {
    int char_index = rand() % LITERALS.size();
    first_string->push_back(LITERALS[char_index]);
  }
  for (int j = 0; j < second_length; ++j) {
    int char_index = rand() % LITERALS.size();
    second_string->push_back(LITERALS[char_index]);
  }
}

//-----------------------------------------------------------------------------
//! Prepare binary polynomial from source string with literal replaced with 1
vector<int> binarizeStringByLiteral(char literal, const string& source) {
  vector<int> binarized_string;
  for (int char_index = 0; char_index < source.length(); ++char_index) {
    if (source[char_index] == literal) {
      binarized_string.push_back(1);
    } else {
      binarized_string.push_back(0);
    }
  }
  return binarized_string;
}

//! Fast Fourier Transform (FFT) implementation
const double PI = 3.14159265;
typedef complex<double> base;

void calculateFFT(bool is_inverted_args, vector<base>* polynomial) { 
  if (polynomial->size() == 1) {
    return;
  }
  vector<base> even_subpolynomial(polynomial->size() / 2);
  vector<base> odd_subpolynomial(polynomial->size() / 2);
  for (int monom_index = 0, sub_index = 0;
      monom_index < polynomial->size();
      monom_index += 2, ++sub_index
      ) {
    even_subpolynomial[sub_index] = polynomial->at(monom_index);
    odd_subpolynomial[sub_index] = polynomial->at(monom_index + 1);
  }
  calculateFFT(is_inverted_args, &even_subpolynomial);
  calculateFFT(is_inverted_args, &odd_subpolynomial);

  double angle_arg = 2 * PI / polynomial->size() * (is_inverted_args ? -1 : 1);
  base current_value_of_minus_one_nth_sqrt(1);
  base next_value_of_minus_one_nth_sqrt(cos(angle_arg), sin(angle_arg));
  for (int index = 0; index < polynomial->size() / 2; ++index) {
    polynomial->at(index) = even_subpolynomial[index] + 
        current_value_of_minus_one_nth_sqrt * odd_subpolynomial[index];
    polynomial->at(index + polynomial->size() / 2) = even_subpolynomial[index] - 
        current_value_of_minus_one_nth_sqrt * odd_subpolynomial[index];
    if (is_inverted_args) {
      polynomial->at(index) /= 2;
      polynomial->at(index + polynomial->size() / 2) /= 2;
    }
    current_value_of_minus_one_nth_sqrt *= next_value_of_minus_one_nth_sqrt;
  }
}

template <typename T>
void multiplyWithFFT(
    const vector<T>& first_polynomial,
    const vector<T>& second_polynomial,
    vector<T>* fft_result
    ) {
  vector<base> fourier_frist_polynomial(first_polynomial.begin(), first_polynomial.end());
  vector<base> fourier_second_polynomial(second_polynomial.begin(), second_polynomial.end());
  int max_power = 1;
  while (max_power < max(first_polynomial.size(), second_polynomial.size())) {
    max_power <<= 1;
  }
  max_power <<= 1;
  fourier_frist_polynomial.resize(max_power);
  fourier_second_polynomial.resize(max_power);

  calculateFFT(false, &fourier_frist_polynomial);
  calculateFFT(false, &fourier_second_polynomial);

  for (int index = 0; index < max_power; ++index) {
    fourier_frist_polynomial[index] *= fourier_second_polynomial[index];
  }
  calculateFFT(true, &fourier_frist_polynomial);

  fft_result->resize(max_power);
  for (int index = 0; index < max_power; ++index) {
    fft_result->at(index) = 
        static_cast<T>(fourier_frist_polynomial[index].real() + 0.5);
  }
}

//---------------------------------------------------------
template <typename T>
void multiplyNaive(
    const vector<T>& first_polynomial,
    const vector<T>& second_polynomial,
    vector<T>* result
    ) {
  result->resize(first_polynomial.size() + second_polynomial.size() - 1);
  if (first_polynomial.size() > second_polynomial.size()) {
    for (int first_index = 0; first_index < first_polynomial.size(); ++first_index) {
      for (int second_index = 0; second_index < second_polynomial.size(); ++second_index) {
        result->at(first_index + second_index) = first_polynomial[first_index] * second_polynomial[second_index];
      }
    }
  } else {
    for (int second_index = 0; second_index < second_polynomial.size(); ++second_index) {
      for (int first_index = 0; first_index < first_polynomial.size(); ++first_index) {
        result->at(first_index + second_index) = first_polynomial[first_index] * second_polynomial[second_index];
      }
    }
  }
}

//-----------------------------------------------------------------------------
//! Convenient class to store corresponding numbers of positions
template <typename T = int>
class sequence {
public:
  sequence() {}
  sequence(int size) {
    m_content.assign(size, T());
  }

  size_t size() const {
    return m_content.size();
  }

  void push_back(const T& item) {
    m_content.push_back(item);
  }

  sequence& operator += (const sequence& rhs) {
    for (int index = 0; index < m_content.size(); ++index) {
      m_content[index] += rhs.m_content[index];
    }
    return *this;
  }

  int find_leftmost_max() const {
    int leftmost_max_position = 0;
    T maximum = m_content[leftmost_max_position];
    for (int index = 0; index < m_content.size(); ++index) {
      if (m_content[index] > maximum) {
        maximum = m_content[index];
        leftmost_max_position = index;
      }
    }
    return leftmost_max_position;
  }

private:
  vector<T> m_content;
};

//---------------------------------------------------------
template <typename T>
sequence<T> findMatchesByProduct(
    int text_length,
    int number_of_possible_positions, 
    const vector<T>& product
    ) {
  sequence<T> match_place_numbers;
  for (int index = 0; index < number_of_possible_positions; ++index) {
    match_place_numbers.push_back(product[text_length - 1 - index]);
  }
  return match_place_numbers;
}

int findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    ) {
  int number_of_possible_positions = 
      first_string.length() - second_string.length() + 1;
  sequence<> literal_match_places(number_of_possible_positions);
  for (int literal_index = 0; 
      literal_index < LITERALS.length();
      ++literal_index
      ) {
    vector<int> first_polynomial = 
        binarizeStringByLiteral(LITERALS[literal_index], first_string);
    vector<int> second_polynomial = 
        binarizeStringByLiteral(LITERALS[literal_index], second_string);
    vector<int> product;
    reverse(first_polynomial.begin(), first_polynomial.end());
    multiplyWithFFT(first_polynomial, second_polynomial, &product);
    literal_match_places += 
        findMatchesByProduct(
            first_string.length(), 
            number_of_possible_positions, 
            product
            );
  }
  return literal_match_places.find_leftmost_max() + 1;
}

//---------------------------------------------------------
int naive_findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    ) {
  int number_of_possible_positions = 
      first_string.length() - second_string.length() + 1;
  sequence<> literal_match_places(number_of_possible_positions);
  for (int literal_index = 0; 
      literal_index < LITERALS.length();
      ++literal_index
      ) {
    vector<int> first_polynomial = 
        binarizeStringByLiteral(LITERALS[literal_index], first_string);
    vector<int> second_polynomial = 
        binarizeStringByLiteral(LITERALS[literal_index], second_string);
    vector<int> product;
    reverse(first_polynomial.begin(), first_polynomial.end());
    multiplyNaive(first_polynomial, second_polynomial, &product);
    literal_match_places += 
        findMatchesByProduct(
            first_string.length(), 
            number_of_possible_positions, 
            product
            );
  }
  return literal_match_places.find_leftmost_max() + 1;
}

//---------------------------------------------------------
//! Naive & slow solution
int stupid_findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    ) {
  int number_of_possible_positions = 
      first_string.length() - second_string.length() + 1;
  sequence<int> literal_match_places(number_of_possible_positions);
  for (int literal_index = 0; 
      literal_index < LITERALS.length();
      ++literal_index
      ) {
    // Complete pluck
    sequence<int> positions_numbers;
    for (int i = 0; i < number_of_possible_positions; ++i) {
      int sum = 0;
      for (int j = 0; j < second_string.length(); ++j) {
        if (first_string[i + j] == second_string[j]) {
          ++sum;
        }
      }
      positions_numbers.push_back(sum);
    }
    literal_match_places += positions_numbers;
  }
  return literal_match_places.find_leftmost_max() + 1;
}

//-----------------------------------------------------------------------------
const int LENGTH = 200000;

int main() {
  srand(789);
  while (true) {
    clock_t rest = 0;
    string first_string, second_string;
    int first_length = rand() % LENGTH + 1;
    int second_length = rand() % LENGTH + 1;
    if (first_length < second_length) {
      swap(first_length, second_length);
    }
    generateInput(first_length, second_length, &first_string, &second_string);
    cout << first_string.size() << " " << second_string.size() << "  ";
    rest = clock();
    clock_t time = 0;
    cout << static_cast<double>(rest) / CLOCKS_PER_SEC << " ";
    int answer = output(first_string, second_string);
    time = clock() - rest;
    //int naive_answer = outputNaive(first_string, second_string);
    clock_t slow_time = 0;
    int slow_answer = outputStupid(first_string, second_string);
    slow_time = clock() - rest - time;
    if (/*answer == naive_answer &&*/ answer == slow_answer) {
      cout << "OK";
    } else {
      cout << "WRONG ANSWER !!!\a";
    }
    cout << "  " << static_cast<double>(time) / CLOCKS_PER_SEC << " " << 
        static_cast<double>(slow_time) / CLOCKS_PER_SEC << "  " <<
        answer << " " << slow_answer /*<< " " << naive_answer*/ << "  ";
    if (static_cast<double>(time) / CLOCKS_PER_SEC > 15.0) {
      cout << "TIME LIMIT EXCEEDED !!!\a\a\a";
    }
    cout << endl;
  }
  return 0;
}
