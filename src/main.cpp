#include <iostream>
#include <string>
#include <string.h>

#include "graph.hpp"

auto main(int argc, char** argv) -> int {
  // using namespace std::string_literals;

  std::string afile = "data/small_airports.dat";
  std::string rfile = "data/small_routes.dat";


  // Cli Args for QOL
  auto routecount = 0;
  std::string src = "", dst = "";
  std::string distf = "", pathf = "";
  bool read = false;
  bool cent = false;
  //printf("%d", argc);
  for (int arg=1; arg<argc;arg++) {
    if (!strcmp(argv[arg], "-h") || !strcmp(argv[arg], "--help")) {
      printf("Usage: \n");
      printf("[-routes | num routes to test]\n");
      printf("[-read | dist filename | next filename] [-write | dist filename | next filename]\n");
      printf("[-src | source for single test] [-dst | destination for single test]\n");
      printf("[-l]: use large dataset.\n");
      printf("[-c]: calculate centrality.\n");
      printf("Leave empty for graph construction.\n");
      return 0;
    }
    if (!strcmp(argv[arg], "-routes")) {
      arg++;
      routecount = atoi(argv[arg]);
    }
    if (!strcmp(argv[arg], "-src")) {
      arg++;
      src = (argv[arg]);
    }
    if (!strcmp(argv[arg], "-dst")) {
      arg++;
      dst = (argv[arg]);
    }
    if (!strcmp(argv[arg], "-l")) {
      afile = "data/airports.dat";
      rfile = "data/routes.dat";
    }
    if (!strcmp(argv[arg], "-read")) {
      arg++;
      distf = argv[arg];
      arg++;
      pathf = argv[arg];
      read = true;
    }
    if (!strcmp(argv[arg], "-write")) {
      arg++;
      distf = argv[arg];
      arg++;
      pathf = argv[arg];
    }
    if (!strcmp(argv[arg], "-c")) {
      cent = true;
    }
  }
  auto const airports_file = std::string{afile};
  auto const routes_file = std::string{rfile};

  auto graph = Graph{airports_file, routes_file};
  graph.BFS();

  //auto const dists = graph.floydWarshallwPaths();

  //routecount = 5;

  if (read) {
    graph.readFW(distf, pathf);
  }
  else {
    graph.floydWarshallwDistPaths();
  }

  if (!read && !distf.empty() && !pathf.empty()) {
    graph.writeFW(distf, pathf);
  }

  if (!src.empty() && !dst.empty()) {
    graph.pathReconstruction(src, dst);
  }

  if (routecount) {
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

  if (cent) {
    graph.generateCentrality();
    auto minmax = graph.minmax();
    printf("The most central airport is %s\n", minmax.second.c_str());
    printf("The least central airport is %s\n", minmax.first.c_str());
  }
}
