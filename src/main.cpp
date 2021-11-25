#include <iostream>
#include <string>
#include <string.h>

#include "graph.hpp"

auto main(int argc, char** argv) -> int {
  // using namespace std::string_literals;

  auto const airports_file = std::string{"data/airports.dat"};
  auto const routes_file = std::string{"data/routes.dat"};

  // Cli Args for QOL
  auto routecount = 0;
  printf("%d", argc);
  for (int arg=1; arg<argc;arg++) {
    if (!strcmp(argv[arg], "-h") || !strcmp(argv[arg], "--help")) {
      printf("Usage: \n");
      printf("[-routes | num routes to test] \n");
      printf("[-src | source for single test] [-dst | destination for single test]\n");
      printf("leave empty for graph construction\n");
    }
    if (!strcmp(argv[arg], "-routes")) {
      arg++;
      routecount = atoi(argv[arg]);
    }
    if (!strcmp(argv[arg], "-src")) {
      arg++;
      std::string src = (argv[arg]);
    }
    if (!strcmp(argv[arg], "-dst")) {
      arg++;
      std::string src = (argv[arg]);
    }
  }

  auto graph = Graph{airports_file, routes_file};

  //auto const dists = graph.floydWarshallwPaths();

  routecount = 30;

  if (routecount) {
    graph.floydWarshallwPaths();
    for (auto i = 0; i < routecount; i++) {
      printf("Please input source and destination\n");
      std::string src = "", dst = "";
      printf("src: ");
      std::cin >> src;
      printf("\ndst: ");
      std::cin >> dst;
      printf("\n");
      graph.pathReconstruction(src, dst);
    }
  }

      

  printf("Airports: %ld; Routes: %ld\n", graph.numAirports(), graph.numRoutes());
}
