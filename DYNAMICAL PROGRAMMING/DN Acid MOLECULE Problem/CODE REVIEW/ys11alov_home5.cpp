#include <algorithm>
#include <complex>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::reverse;
using std::max;
using std::complex;

const int LITERALS_LENGTH = 4;
const char* LITERALS = "AGTC";

//-----------------------------------------------------------------------------
void input(string* first_string, string* second_string) {
  getline(cin, *first_string);
  getline(cin, *second_string);
}

int findPositionOfMostMatches(
    const string& first_string,
    const string& second_string
    );

void output(int position_of_most_matches) {
  cout << position_of_most_matches;
}

//-----------------------------------------------------------------------------
vector<int> binarizeStringByLiteral(const string& source, char literal) {
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

typedef complex<double> base;

void calculateFFT(vector<base>* polynomial, bool is_inverted_args) { 
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
  calculateFFT(&even_subpolynomial, is_inverted_args);
  calculateFFT(&odd_subpolynomial, is_inverted_args);

  double angle_arg = 2 * M_PI / polynomial->size() * (is_inverted_args ? -1 : 1);
  base current_omega(1);
  base next_omega(cos(angle_arg), sin(angle_arg));
  for (int index = 0; index < polynomial->size() / 2; ++index) {
    polynomial->at(index) = even_subpolynomial[index] + 
        current_omega * odd_subpolynomial[index];
    polynomial->at(index + polynomial->size() / 2) = even_subpolynomial[index] - 
        current_omega * odd_subpolynomial[index];
    if (is_inverted_args) {
      polynomial->at(index) /= 2;
      polynomial->at(index + polynomial->size() / 2) /= 2;
    }
    current_omega *= next_omega;
  }
}

template <typename T>
void multiplyWithFFT(
    const vector<T>& first_polynomial,
    const vector<T>& second_polynomial,
    vector<T>* fft_result
    ) {
  vector<base> fourier_first_polynomial(first_polynomial.begin(), first_polynomial.end());
  vector<base> fourier_second_polynomial(second_polynomial.begin(), second_polynomial.end());
  int max_power = 1;
  while (max_power < max(first_polynomial.size(), second_polynomial.size())) {
    max_power <<= 1;
  }
  max_power <<= 1;
  fourier_first_polynomial.resize(max_power);
  fourier_second_polynomial.resize(max_power);

  calculateFFT(&fourier_first_polynomial, false);
  calculateFFT(&fourier_second_polynomial, false);

  for (int index = 0; index < max_power; ++index) {
    fourier_first_polynomial[index] *= fourier_second_polynomial[index];
  }
  calculateFFT(&fourier_first_polynomial, true);

  fft_result->resize(max_power);
  for (int index = 0; index < max_power; ++index) {
    fft_result->at(index) = 
        static_cast<T>(fourier_first_polynomial[index].real() + 0.5);
  }
}

//-----------------------------------------------------------------------------
template <typename T = int>
class sequence {
public:
  sequence() {}
  explicit sequence(int size) {
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
    const vector<T>& product, 
    int text_length,
    int number_of_possible_positions
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
      literal_index < LITERALS_LENGTH;
      ++literal_index
      ) {
    vector<int> first_polynomial = 
        binarizeStringByLiteral(first_string, LITERALS[literal_index]);
    vector<int> second_polynomial = 
        binarizeStringByLiteral(second_string, LITERALS[literal_index]);
    vector<int> product;
    reverse(first_polynomial.begin(), first_polynomial.end());
    multiplyWithFFT(first_polynomial, second_polynomial, &product);
    literal_match_places += 
        findMatchesByProduct(
            product, 
            first_string.length(), 
            number_of_possible_positions
            );
  }
  return literal_match_places.find_leftmost_max() + 1;
}

//-----------------------------------------------------------------------------
int main() {
  string first_string, second_string;
  input(&first_string, &second_string);
  int answer = findPositionOfMostMatches(first_string, second_string);
  output(answer);
  return 0;
}
