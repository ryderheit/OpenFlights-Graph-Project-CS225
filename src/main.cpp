#include "graph.h"

int main() {
  const std::string& airports_file = "/data/small_airports.dat";
  const std::string& routes_file = "/data/small_routes.dat";

  Graph* graph = new Graph(airports_file, routes_file);
  delete graph;
  return 0;
}
