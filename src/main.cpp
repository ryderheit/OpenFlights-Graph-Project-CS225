#include <string>

#include "graph.hpp"

auto main() -> int {
  auto const airports_file = std::string{"data/airports.dat"};
  auto const routes_file = std::string{"data/routes.dat"};
  auto const graph = Graph{airports_file, routes_file};

  auto const dists = graph.floydWarshall();
  std::printf("Airports: %ld; Routes: %ld\n", graph.numAirports(), graph.numRoutes());
}
