#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::min;
using std::cout;
using std::cin;

//-----------------------------------------------------------------------------
inline int calculateCommonPrefixLength(
    const string& source,
    int first_substing_position,
    int second_substring_position
    ) {
  int longest_common_prefix_length = 0;
  while (second_substring_position < source.length() && 
          source[first_substing_position] == 
              source[second_substring_position]
        ) {
    longest_common_prefix_length += 1;
    ++first_substing_position;
    ++second_substring_position;
  }
  return longest_common_prefix_length;
}

//-----------------------------------------------------------------------------
vector<int> calculateZFunction(const string& source) {
  vector<int> z_function_values(source.length());
  z_function_values[0] = source.length();
  for (int char_index = 1, left_border = 0, right_border = 0; 
      char_index < source.length(); 
      ++char_index
      ) {
    if (char_index <= right_border) {
      z_function_values[char_index] = 
          min(
              right_border - char_index + 1, 
              z_function_values[char_index - left_border]
              );
    }
    z_function_values[char_index] += 
        calculateCommonPrefixLength(
            source,
            z_function_values[char_index],
            z_function_values[char_index] + char_index
            );
    if (char_index + z_function_values[char_index] - 1 > right_border) {
      left_border = char_index;
      right_border = char_index + z_function_values[char_index] - 1;
    }
  }
  return z_function_values;
}

//-----------------------------------------------------------------------------
void input(string* source) {
  getline(cin, *source);
}

//-----------------------------------------------------------------------------
void output(const vector<int>& z_function_values) {
  for (size_t value_index = 0;
      value_index < z_function_values.size(); 
      ++value_index
      ) {
    cout << z_function_values[value_index] << ' ';
  }
}

//-----------------------------------------------------------------------------
int main() {
  string source;
  input(&source);
  vector<int> z_function_values = calculateZFunction(source);
  output(z_function_values);
  return 0;
}
