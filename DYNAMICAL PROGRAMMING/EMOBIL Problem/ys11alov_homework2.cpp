#include <iterator>
#include <vector>
#include <list>
#include <cstdio>
#include <cmath>
using std::iterator;
using std::vector;
using std::list;

const double PI = 3.1415926536;

struct City {
  int coordinate_x;
  int coordinate_y;
};

double calculateRoadLength(const City& first, const City& second) {
  return sqrt(pow(first.coordinate_x - second.coordinate_x, 2) + 
              pow(first.coordinate_y - second.coordinate_y, 2));
}

//-----------------------------------------------------------------------------
void input(
    vector<City>* city_places, 
    vector<list<int> >* graph_of_cities,
    double& angle_coeff
    ) {
  int number_of_cities, number_of_roads, start_city, finish_city;
  scanf(
    "%d %d %d %d %lf", 
    &number_of_cities, 
    &number_of_roads,
    &start_city,
    &finish_city,
    &angle_coeff
    );
  city_places->resize(number_of_cities);
  for (size_t city_index = 0; city_index < number_of_cities; ++city_index) {
    scanf(
        "\n%d %d", 
        &city_places->at(city_index).coordinate_x,
        &city_places->at(city_index).coordinate_y
        );
  }
  graph_of_cities->resize(number_of_cities);
  for (size_t road_index = 0; road_index < number_of_roads; ++road_index) {
    int from_city, destination_city;
    scanf("\n%d %d", &from_city, &destination_city);
    graph_of_cities->at(from_city - 1).push_back(destination_city);
  }
}

void outputTest(const vector<City>& city_places, const vector<list<int> >& graph_of_cities) {
  for (size_t city_index = 0; city_index < city_places.size(); ++city_index) {
    printf("[%d]:  %d %d\n", city_index + 1, city_places[city_index].coordinate_x, city_places[city_index].coordinate_y);
  }
  for (size_t city_index = 0; city_index < graph_of_cities.size(); ++city_index) {
    printf("\n[%d]:  ", city_index + 1);
    for (size_t road_index = 0; road_index < graph_of_cities[city_index].size(); ++road_index) {
      int counter = 0;
      list<int>::const_iterator it = graph_of_cities[city_index].begin();
      while (counter < road_index) {
        ++it;
        ++counter;
      }
      printf("%d ", *it);
    }
  }
}

void output(int destination_index, const vector<double>& least_paths) {
  return least_paths[destination_index];
}

//-----------------------------------------------------------------------------
void transformCityGraph(
    double angle_coeff, 
    const vector<list<int> >& graph_of_cities, 
    vector<list<int> >* transformed_city_graph
    ) {
  
}

void calculateDijkstraLeastPath(
    int source_index, 
    const vector<list<int> >& graph, 
    vector<double>* least_paths 
    ) {

}

//-----------------------------------------------------------------------------
int main() {
  vector<City> city_places;
  vector<list<int> > graph_of_cities;
  double angle_coeff;
  input(&city_places, &graph_of_cities, angle_coeff);
  outputTest(city_places, graph_of_cities);
  return 0;
}
