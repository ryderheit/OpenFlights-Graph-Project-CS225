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
  int centSize = -1;
  std::string src = "", dst = "";
  std::string distf = "", pathf = "";
  std::string region = "", country = "";
  std::string airline = "";
  bool read = false;
  bool query = false;
  //printf("%d", argc);
  for (int arg=1; arg<argc;arg++) {
    if (!strcmp(argv[arg], "-h") || !strcmp(argv[arg], "--help")) {
      printf("Usage: \n");
      printf("[-routes | num routes to test]\n");
      printf("[-read | dist filename | next filename]\n[-write | dist filename | next filename]\n");
      printf("[-region | region name]\n[-country | country name]\n");
      printf("[-airline | airline abbreviation (see airlines.dat)]\n");
      printf("[-src | source for single test] [-dst | destination for single test]\n");
      printf("[-c | optional: minimum outgoing routes, default 0]: calculate centrality.\n");
      printf("[-l]: use large dataset.\n");
      printf("[-q]: query the graph.\n");
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
      arg++;
      try {
        centSize = std::stoi(argv[arg]);
      }
      catch (...) {
        arg--;
        centSize = 0;
      }
    }
    if (!strcmp(argv[arg], "-region")) {
      arg++;
      region = argv[arg];
    }
    if (!strcmp(argv[arg], "-country")) {
      arg++;
      country = argv[arg];
    }
    if (!strcmp(argv[arg], "-airline")) {
      arg++;
      airline = argv[arg];
    }
    if (!strcmp(argv[arg], "-q")) {
      query = true;
    }
  }
  auto const airports_file = std::string{afile};
  auto const routes_file = std::string{rfile};

  Graph graph;
  if (!region.empty()) {
    graph = Graph(airports_file, routes_file, region, false, airline);
    printf("Looking for Airports in %s\n", region.c_str());
  }
  else if (!country.empty()) {
    graph = Graph(airports_file, routes_file, country, true, airline);
    printf("Looking for Airports in %s\n", country.c_str());
  }
  else {
    graph = Graph(airports_file, routes_file, airline);
    printf("Looking for routes flown by %s\n", airline.c_str());
  }
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

  if (centSize >= 0) {
    graph.generateCentrality(centSize);
    auto minmax = graph.minmax();
    printf("The most central airport is %s\n", minmax.second.c_str());
    printf("The least central airport is %s\n", minmax.first.c_str());
  }

  centSize = 0;

  while (query) {
    printf("Enter the abbreviation for the airport you'd like to know more about:\n");
    std::string airport;
    std::cin >> airport;
    if (airport == "q") break;
    graph.query(airport);
    printf("Type 'q' to quit. ");
  }
}
