#include "graph.h"


auto Graph::readAirports(std::istream& airports) -> void {
  std::string line;

  // Needed?
  std::getline(airports, line);
  
  while (std::getline(airports, line)) {
    std::stringstream lineStream(line);
    std::string cell;
    vector<int> data;
    while(std::getline(lineStream, cell, ',')) {
      //std::cout << "lineStream:" << lineStream << std::endl;
      std::cout << "cell:" << cell << std::endl;
      std::stringstream entry(cell);
      int entry_int = 0;
      entry >> entry_int;
      std::cout << "entry_int:" << entry_int << std::endl;
      data.push_back(entry_int);
    }
  }
}


auto Graph::readRoutes(std::istream& routes) -> void {
#if 0
  while (!EOF) {
    readline();
    Edge* route = new Edge;
    route->src = datafromfile;
    route->dest = datafromfile;
    route->weight = findweight();
    adjList_[src].second.adjacent.push_back(route);
    adjList_[dest].second.adjacent.push_back(route);
  }
#endif
}
    
auto Graph::insertEdge(int src, int dest, int weight) -> void {}
auto Graph::insertVertex(int ID, string code) -> void {}

Graph::Graph(const string& airports_file, const string& routes_file) {
  std::ifstream airports(airports_file);
  std::ifstream routes(routes_file);
  readAirports(airports);
#if 0
  if (airports.is_open() /*&& routes.is_open()*/) {
    readAirports(airports);
    //readRoutes(routes);

    airports.close(); routes.close();
  }
  else 

    printf("File not found, try again");
#endif
}

auto Graph::getNumEdges() const -> int {
  return m;
}

auto Graph::getNumVertices() const -> int {
  return n;
}
