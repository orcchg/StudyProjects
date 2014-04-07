#include <vector>
#include <stdio.h>
using namespace std;

void linear_interpolation(
    const vector<double>& old_grid,
    const vector<double>& old_data,
    const vector<double>& new_grid,
    vector<double>* new_data
    ) {
  new_data->resize(new_grid.size());
  for (size_t i = 1; i < old_grid.size(); ++i) {
    double A = (old_data(i) - old_data(i - 1)) / (old_grid(i) - old_grid(i - 1));
    double B = (old_data(i - 1) * old_grid(i) - old_data(i) * old_grid(i - 1)) / (old_grid(i) - old_grid(i - 1));
    while (j < new_grid.size() && new_grid(j) >= old_grid(i - 1) && new_grid(j) <= old_grid(i)) {
      new_data->at(j) = A * new_grid(j) + B;
      ++j;
    }
  }
}

int main() {
  vector<double> old_grid, old_data, new_grid, new_data;
  FILE* file;
  file.open("kabs_NEW.dat");
  
  file.close();
  linear_interpolation(old_grid, old_data, new_grid, &new_data);
  return 0;
}