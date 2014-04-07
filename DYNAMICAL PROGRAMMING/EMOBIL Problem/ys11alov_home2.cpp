#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::vector;
using std::set;
using std::pair;
using std::sqrt;
using std::atan2;
using std::abs;
using std::min;
using std::numeric_limits;
using std::make_pair;

const double PI = 3.1415926535897;
const double radianDegreeFactor = 180.0 / PI;

//-----------------------------------------------------------------------------
struct City {
  int city_coordinate_x;
  int city_coordinate_y;
};

//-----------------------------------------------
struct road {
  int destination; 
  double angle;
  double length;

  road(int destination, double angle, double length)
  : destination(destination)
  , angle(angle)
  , length(length)
  {}
};

//-----------------------------------------------
//! Arc on circle road at city cluster
struct arcOfCircleRoad {
  int destination;
  double weight;

  arcOfCircleRoad(int destination, double weight)
  : destination(destination)
  , weight(weight)
  {}
};

//-----------------------------------------------
typedef vector<vector<road> > graph_of_cities;

struct Laplandia {
  double coefficient;
  graph_of_cities roads;
};

//-----------------------------------------------
double calculateTurnValue(
    double source_angle, 
    double destination_angle, 
    double coefficient
    ) {
  double turn_value = abs(destination_angle - source_angle);
  return coefficient * min(turn_value, 360.0 - turn_value);
}

//-----------------------------------------------------------------------------
void inputCities(int number_of_cities, vector<City>* cities) {
  cities->resize(number_of_cities);
  for (int city_index = 0; city_index < number_of_cities; ++city_index) {
    cin >> cities->at(city_index).city_coordinate_x;
    cin >> cities->at(city_index).city_coordinate_y;
  }
}

//-----------------------------------------------
void inputRoads(
    int number_of_roads, 
    const vector<City>& cities, 
    graph_of_cities* roads
    ) {
  roads->resize(cities.size());

  for (int road_index = 0; road_index < number_of_roads; ++road_index) {
    int source_city, destination_city;
    cin >> source_city >> destination_city;

    double road_difference_x = 
        cities[destination_city - 1].city_coordinate_x - 
            cities[source_city - 1].city_coordinate_x;

    double road_difference_y = 
        cities[destination_city - 1].city_coordinate_y - 
            cities[source_city - 1].city_coordinate_y;

    double length_of_road = 
        sqrt(
            road_difference_x * road_difference_x + 
                road_difference_y * road_difference_y
        );

    double road_angle_vs_horizon = 
        radianDegreeFactor * atan2(road_difference_y, road_difference_x);

    roads->at(source_city - 1).push_back(
        road(destination_city - 1, road_angle_vs_horizon, length_of_road)
        );
  }
}

//-----------------------------------------------
void input(int& start_city, int& finish_city, Laplandia* laplandia) {
  int number_of_cities;
  int number_of_roads;

  cin >> number_of_cities >> number_of_roads;
  cin >> start_city >> finish_city;

  double angle_coefficinet;
  cin >> angle_coefficinet;
  laplandia->coefficient = angle_coefficinet;

  vector<City> cities;
  inputCities(number_of_cities, &cities);
  inputRoads(number_of_roads, cities, &laplandia->roads);
}

//-----------------------------------------------
void output(double least_path_length) {
  if (least_path_length != numeric_limits<double>::max()) {
    cout << fixed << least_path_length;
  } else {
    cout << -1;
  }
  cout << endl;
}


//-----------------------------------------------------------------------------
typedef vector<arcOfCircleRoad> cirlceCityCluster;  // circle road and subcitites
typedef cirlceCityCluster::const_iterator iterator;
typedef vector<cirlceCityCluster> modifiedGraph;  // weighted graph of subcities

struct modifiedGraphStruct {
  modifiedGraph graph;
  int initial_city;
  int final_city;
};

//-----------------------------------------------
void modifyGraph(
    int laplandia_initial_city, 
    int laplandia_final_city, 
    const Laplandia& laplandia, 
    modifiedGraphStruct* result
    ) {
  vector<vector<int> > old_graph_of_cities(laplandia.roads.size());
  vector<pair<int, int> > new_graph_of_cities;
  vector<int> initial_cities, final_cities;

  for (int city_index = 0; 
      city_index < laplandia.roads.size(); 
      ++city_index
      ) {
    for (int road_index = 0; 
        road_index < laplandia.roads[city_index].size(); 
        ++road_index
        ) {
      old_graph_of_cities[city_index].push_back(result->graph.size());
      if (city_index == laplandia_initial_city) {
        initial_cities.push_back(result->graph.size());
      }
      result->graph.push_back(cirlceCityCluster());
      new_graph_of_cities.push_back(make_pair(city_index, road_index));
      result->graph.back().push_back(
          arcOfCircleRoad(result->graph.size(),
              laplandia.roads[city_index][road_index].length)
      );
      if (laplandia.roads[city_index][road_index].destination == 
          laplandia_final_city
          ) {
        final_cities.push_back(result->graph.size());
      }
      result->graph.push_back(cirlceCityCluster());
    }
  }

  for (int new_city_index = 0; 
      new_city_index < result->graph.size(); 
      new_city_index += 2
      ) {
    int city_index = new_graph_of_cities[new_city_index / 2].first;
    int road_index = new_graph_of_cities[new_city_index / 2].second;
    double current_angle = laplandia.roads[city_index][road_index].angle;
    int old_destination = laplandia.roads[city_index][road_index].destination;
    for (int road_index = 0; 
        road_index < laplandia.roads[old_destination].size(); 
        ++road_index
        ) {
      double next_angle = 
          laplandia.roads[old_destination][road_index].angle;
      int new_arc_destination = 
          old_graph_of_cities[old_destination][road_index];
      double arc_weight = 
          calculateTurnValue(current_angle, next_angle, laplandia.coefficient);
      result->graph[new_city_index + 1].push_back(
          arcOfCircleRoad(new_arc_destination, arc_weight)
      );
    }
  }

  result->graph.push_back(cirlceCityCluster());
  result->initial_city = result->graph.size() - 1;
  for (vector<int>::const_iterator initial_city = initial_cities.begin();
      initial_city != initial_cities.end();
      ++initial_city
      ) {
    result->graph.back().push_back(arcOfCircleRoad(*initial_city, 0));
  }

  result->graph.push_back(cirlceCityCluster());
  result->final_city = result->graph.size() - 1;
  for (vector<int>::const_iterator final_city = final_cities.begin();
      final_city != final_cities.end();
      ++final_city
      ) {
    result->graph[*final_city].push_back(
        arcOfCircleRoad(result->final_city, 0)
    );
  }
}

//-----------------------------------------------------------------------------
//! Dijkstra least path calculation
double calculateLeastPath(
    const modifiedGraph& graph, 
    int initial_city, 
    int final_city
    ) {
  vector<double> distances(graph.size(), numeric_limits<double>::max());
  vector<bool> is_city_visited(graph.size(), false); 
  set<pair<double, int> > greynode_queue;

  distances[initial_city] = 0;
  greynode_queue.insert(make_pair(0.0, initial_city));

  while (!greynode_queue.empty()) {
    const int current_city = greynode_queue.begin()->second;
    greynode_queue.erase(greynode_queue.begin());

    if (is_city_visited[current_city]) {
      continue;
    }
    const cirlceCityCluster& current_cluster = graph[current_city];
    is_city_visited[current_city] = true;

    for (iterator arcOfCircleRoad = current_cluster.begin(); 
        arcOfCircleRoad != current_cluster.end(); 
        ++arcOfCircleRoad
        ) {
      int next_cluster = arcOfCircleRoad->destination;
      if (distances[next_cluster] > distances[current_city] + 
          arcOfCircleRoad->weight
          ) {
        distances[next_cluster] = 
            distances[current_city] + arcOfCircleRoad->weight;
        greynode_queue.insert(
            make_pair(distances[next_cluster], next_cluster)
        );
      }
    }
  }
  return distances[final_city];
}

double findLeastPath(
    int start_city, 
    int finish_city, 
    const Laplandia& laplandia
    ) {
  modifiedGraphStruct graph_of_city_clusters;
  modifyGraph(start_city, finish_city, laplandia, &graph_of_city_clusters);
  return calculateLeastPath(
      graph_of_city_clusters.graph,
      graph_of_city_clusters.initial_city,
      graph_of_city_clusters.final_city
      );
}

//-----------------------------------------------------------------------------
int main() {
  int start_city, finish_city;
  Laplandia laplandia;
  input(start_city, finish_city, &laplandia);
  double least_path_length = 
      findLeastPath(start_city - 1, finish_city - 1, laplandia);
  output(least_path_length);
  return 0;
}
