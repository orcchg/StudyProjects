Index: task2.cpp
diff --git a/task2.cpp b/task2.cpp
index e69de29bb2d1d6434b8b29ae775ad8c2e48c5391..3f1ceef4ac228b3b80f6d03c010fd59f9ad649c1 100644
--- a/task2.cpp
+++ b/task2.cpp
@@ -0,0 +1,245 @@
+#include <iostream>
+#include <vector>
+#include <cmath>
+#include <set>
+#include <limits>
+#include <utility>
+#include <algorithm>
+
+using std::cin;
+using std::cout;
+using std::vector;
+using std::set;
+
+static const double PI = 3.14159265358;
+static const double radianDegreeFactor = 180 / PI;
+
+struct Road {
+    int destination; 
+    double angle;
+    double length;
+
+    Road(int destination_, double angle_, double length_)
+        : destination(destination_)
+        , angle(angle_)
+        , length(length_)
+    {}
+};
+
+typedef vector<Road> CityRoads;
+
+typedef vector<CityRoads> CountryMap;
+
+struct Country {
+    int start;
+    int stop;
+    CountryMap map;
+    double turnCost;
+};
+
+struct CityPoint {
+    int cityX;
+    int cityY;
+};
+
+vector<CityPoint> inputCities(int citiesCount)
+{
+    vector<CityPoint> cities(citiesCount);
+    for (int cityId = 0; cityId < citiesCount; ++cityId) {
+        cin >> cities[cityId].cityX;
+        cin >> cities[cityId].cityY;
+    }
+
+    return cities;
+}
+
+CountryMap inputRoads(int roadsCount, const vector<CityPoint>& cities)
+{
+    CountryMap countryMap(cities.size());
+
+    for (int roadId = 0; roadId < roadsCount; ++roadId) {
+        int fromCity;
+        int toCity;
+        cin >> fromCity >> toCity;
+
+        double roadX = cities[toCity - 1].cityX - cities[fromCity - 1].cityX;
+        double roadY = cities[toCity - 1].cityY - cities[fromCity - 1].cityY;
+
+        double roadLength = std::sqrt(roadX*roadX + roadY*roadY);
+        double roadAngle = radianDegreeFactor*std::atan2(roadY, roadX);
+        countryMap[fromCity - 1].push_back(Road(toCity - 1, roadAngle, roadLength));
+    }
+
+    return countryMap;
+}
+
+Country input()
+{
+    int citiesCount;
+    int roadsCount;
+    int startCity;
+    int stopCity;
+
+    cin >> citiesCount >> roadsCount;
+    cin >> startCity >> stopCity;
+
+    Country country;
+    country.start = startCity - 1;
+    country.stop  = stopCity - 1;
+    cin >> country.turnCost;
+
+    vector<CityPoint> cities = inputCities(citiesCount);
+
+    country.map = inputRoads(roadsCount, cities);
+
+    return country;
+}
+
+struct Arc  {
+    int destination;
+    double weight;
+
+    Arc (int destination_, double weight_)
+        : destination(destination_)
+        , weight(weight_)
+    {}
+};
+
+typedef vector<Arc> Node;
+typedef vector<Node> SimpleGraph;
+
+double findLightesRoute(const SimpleGraph& graph, int startNode, int stopNode)
+{
+    vector<double> distances(graph.size(), std::numeric_limits<double>::max());
+    vector<bool> nodeIsVisited(graph.size(), false);
+
+    typedef std::pair<double, int> QueuedNode;
+
+    typedef set<QueuedNode> Queue;
+   
+    Queue nodesQueue;
+
+    distances[startNode] = 0;
+    nodesQueue.insert(std::make_pair(0.0, startNode));
+
+    while (!nodesQueue.empty()) {
+        const int currentNodeId = nodesQueue.begin()->second;
+        nodesQueue.erase(nodesQueue.begin());
+
+        if (nodeIsVisited[currentNodeId]) {
+            continue;
+        }
+        const Node& currentNode = graph[currentNodeId];
+        nodeIsVisited[currentNodeId] = true;
+
+        for (Node::const_iterator arc = currentNode.begin(); arc != currentNode.end(); ++arc) {
+            int nextNode = arc->destination;
+            if (distances[nextNode] > distances[currentNodeId] + arc->weight) {
+                distances[nextNode] = distances[currentNodeId] + arc->weight;
+                nodesQueue.insert(std::make_pair(distances[nextNode], nextNode));
+            }
+        }
+    }
+
+    return distances[stopNode];
+}
+
+double getTurnCost(double fromAngle, double toAngle, double turnFactor)
+{
+    double turnAngle = std::abs(toAngle - fromAngle);
+    return turnFactor * std::min(turnAngle, 360 - turnAngle);
+}
+
+struct SimplifyGraphResult {
+    SimpleGraph graph;
+    int startNode;
+    int stopNode;
+};
+
+SimplifyGraphResult simpliphyCountryGraph(const Country& country)
+{
+    SimplifyGraphResult result;
+    vector<vector<int> > fromNodesMapping(country.map.size());
+    vector<std::pair<int, int> > reverseNodesMapping;
+    vector<int> startNodes;
+    vector<int> stopNodes;
+
+    for (int oldNodeId = 0; oldNodeId < country.map.size(); ++oldNodeId) {
+        for (int road = 0; road < country.map[oldNodeId].size(); ++road) {
+            fromNodesMapping[oldNodeId].push_back(result.graph.size());
+            if (oldNodeId == country.start) {
+                startNodes.push_back(result.graph.size());
+            }
+
+            result.graph.push_back(Node());
+            reverseNodesMapping.push_back(std::make_pair(oldNodeId, road));
+            result.graph.back().push_back(Arc(result.graph.size(),
+                                              country.map[oldNodeId][road].length));
+            if (country.map[oldNodeId][road].destination == country.stop) {
+                stopNodes.push_back(result.graph.size());
+            }
+            result.graph.push_back(Node());
+        }
+    }
+    for (int newNodeId = 0; newNodeId < result.graph.size(); newNodeId = newNodeId + 2) {
+        int oldNodeId = reverseNodesMapping[newNodeId/2].first;
+        int road = reverseNodesMapping[newNodeId/2].second;
+
+        double currentAngle = country.map[oldNodeId][road].angle;
+        int oldDestination = country.map[oldNodeId][road].destination;
+        for (int nextRoad = 0; nextRoad < country.map[oldDestination].size(); ++nextRoad) {
+            double nextAngle = country.map[oldDestination][nextRoad].angle;
+            int newArcDestination = fromNodesMapping[oldDestination][nextRoad];
+
+            double turnCost = getTurnCost(currentAngle, nextAngle, country.turnCost);
+            result.graph[newNodeId + 1].push_back(Arc(newArcDestination, turnCost));
+        }
+    }
+
+    result.graph.push_back(Node());
+    result.startNode = result.graph.size() - 1;
+    for (vector<int>::const_iterator startNode = startNodes.begin();
+         startNode != startNodes.end();
+         ++startNode)
+    {
+        result.graph.back().push_back(Arc(*startNode, 0));
+    }
+
+    result.graph.push_back(Node());
+    result.stopNode = result.graph.size() - 1;
+    for (vector<int>::const_iterator stopNode = stopNodes.begin();
+         stopNode != stopNodes.end();
+         ++stopNode)
+    {
+        result.graph[*stopNode].push_back(Arc(result.stopNode, 0));
+    }
+
+    return result;
+}
+
+double findLightestTracePower(const Country& country)
+{
+    const SimplifyGraphResult simplifyResult = simpliphyCountryGraph(country);
+    return findLightesRoute(simplifyResult.graph,
+                            simplifyResult.startNode,
+                            simplifyResult.stopNode);
+}
+
+void output(double power)
+{
+    if (power != std::numeric_limits<double>::max()) {
+        cout  << std::fixed << power;
+    } else {
+        cout << -1;
+    }
+    cout << std::endl;
+}
+
+int main(int argc, char* argv[])
+{
+    const Country inputMap = input();
+    const double power = findLightestTracePower(inputMap);
+    output(power);
+
+    return 0;
+}