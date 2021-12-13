#include <iostream>
#include <string>
#include <string.h>

#include "graph.hpp"

auto main(int argc, char** argv) -> int {
  // using namespace std::string_literals;

  std::string afile = "data/airports.dat";
  std::string rfile = "data/routes.dat";


  // Cli Args for QOL
  int centSize = -1;
  std::string distf = "", pathf = "";
  std::string region = "", country = "";
  std::string airline = "";
  std::string centf = "";
  bool read = false;
  bool readc = false;
  bool query = false;
  bool routes = false;
  //printf("%d", argc);
  for (int arg=1; arg<argc;arg++) {
    if (!strcmp(argv[arg], "-h") || !strcmp(argv[arg], "--help")) {
      printf("Optional Flags:\n");
      printf("[-read | dist filename | next filename]: Read FW from provided files.\n[-write | dist filename | next filename]: Write FW to provided files.\n");
      printf("[-readc | filename]: Read Centrality from provided file.\n[-writec | filename]: Write Centrality to provided file.\n");
      printf("[-region | region name]: Do not use with -country!\n[-country | country name]: Do not use with -region!\n");
      printf("[-airline | airline abbreviation (see airlines.dat)]\n");
      printf("[-c | optional: minimum outgoing routes, default 0]: calculate centrality.\n");
      printf("[-routes]: query the graph for paths.\n");
      printf("[-s]: use small dataset.\n");
      printf("[-q]: query the graph for centrality.\n");
      printf("[-h]: help\n");
      return 0;
    }
    if (!strcmp(argv[arg], "-routes")) {
      routes = true;
    }
    if (!strcmp(argv[arg], "-s")) {
      afile = "data/small_airports.dat";
      rfile = "data/small_routes.dat";
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
    if (!strcmp(argv[arg], "-readc")) {
      arg++;
      readc = true;
      centf = argv[arg];
    }
    if (!strcmp(argv[arg], "-writec")) {
      arg++;
      readc = false;
      centf = argv[arg];
    }
  }
  auto const airports_file = std::string{afile};
  auto const routes_file = std::string{rfile};

  Graph graph;
  if (!region.empty()) {
    graph = Graph(airports_file, routes_file, region, false, airline);
    printf("Looking for Airports in %s\n", region.c_str());
    if (!airline.empty()) printf("Looking for routes flown by %s\n", airline.c_str());
  }
  else if (!country.empty()) {
    graph = Graph(airports_file, routes_file, country, true, airline);
    printf("Looking for Airports in %s\n", country.c_str());
    if (!airline.empty()) printf("Looking for routes flown by %s\n", airline.c_str());
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

  while (routes) {
    printf("Please input source and destination\n");
    std::string src = "", dst = "";
    printf("src: ");
    std::cin >> src;
    if (src == "q") break;
    printf("\ndst: ");
    std::cin >> dst;
    if (dst == "q") break;
    graph.pathReconstruction(src, dst);
    printf("Type 'q' to quit. ");
  }


  printf("Airports: %ld; Routes: %ld\n", graph.numAirports(), graph.numRoutes());

  if (centSize >= 0) {
    if (centf.size() && readc) {
      graph.readBC(centf);
    }
    else {
      graph.generateCentrality(centSize);
    }
    if (centf.size() && !readc) {
      graph.writeBC(centf);
    }
    auto minmax = graph.minmax();
    printf("The most central airport is %s\n", minmax.second.c_str());
    printf("The least central airport is %s\n", minmax.first.c_str());
  }

  while (query) {
    printf("Enter the abbreviation for the airport you'd like to know more about:\n");
    std::string airport;
    std::cin >> airport;
    if (airport == "q") break;
    graph.query(airport);
    printf("Type 'q' to quit. ");
  }
}
