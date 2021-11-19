#include "graph.hpp"

auto main() -> int {
  using namespace std::string_literals;
  auto const airports_file = "data/small_airports.dat"s;
  auto const routes_file = "data/small_routes.dat"s;
  auto graph = Graph{airports_file, routes_file};

  return 1;
}
