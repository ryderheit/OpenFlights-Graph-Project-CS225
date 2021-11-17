#include "graph.h"


auto readAirports(std::istream& airports) {
  while (!EOF) {
    readline();
    auto vertex = new Vertex;
    vertex->code = string;
    vertex->adjacent = vector<Edge*>;
    adjList_.insert(std::make_pair(id, vertex));
  }
}

auto readRoutes(std::istream& routes) {
  while (!EOF) {
    readline();
    Edge* route = new Edge;
    route->src = datafromfile;
    route->dest = datafromfile;
    route->weight = findweight();
    adjList_[src].second.adjacent.push_back(route);
    adjList_[dest].second.adjacent.push_back(route);
  }
}
    
auto Graph::insertEdge(int src, int dest, int weight) -> void {}
auto Graph::insertVertex(int ID, string code) -> void {}

Graph::Graph(string airports_file, string routes_file) {
  std::ifstream airports(airports_file);
  std::ifstream routes(routes_file);

  if (airports.is_open() && routes.is_open()) {
    fillNode(airports);
    fillEdge(routes);

    airports.close(); routes.close();
  } else 
    printf("File not found, try again");
}
