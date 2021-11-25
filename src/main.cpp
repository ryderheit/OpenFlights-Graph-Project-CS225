#include <string>

#include "graph.hpp"

auto main() -> int {
  auto const airports_file = std::string{"data/airports.dat"};
  auto const routes_file = std::string{"data/routes.dat"};
  printf("badtime\n");
  auto graph = Graph{airports_file, routes_file};

  printf("funtime\n");
  auto const dists = graph.floydWarshallwPaths();

  auto route1 = graph.pathReconstruction("SFO", "ABC");
  auto route2 = graph.pathReconstruction("SFO", "ORD");
  auto route3 = graph.pathReconstruction("KSFO", "ORD");
  auto route4 = graph.pathReconstruction("VNO", "ROB");
  auto route5 = graph.pathReconstruction("CMI", "SXM");
  auto route6 = graph.pathReconstruction("GRU", "GEG");
  auto route7 = graph.pathReconstruction("GEG", "GRU");
  auto route8 = graph.pathReconstruction("CDG", "SZX");
  auto route9 = graph.pathReconstruction("OAK", "PEK");
  auto route0 = graph.pathReconstruction("HKD", "SFO");


  std::printf("Airports: %ld; Routes: %ld\n", graph.numAirports(), graph.numRoutes());
}
