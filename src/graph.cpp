#include "graph.h"


auto setupmap(string airports) {
  fopen(airports);
  while (!EOF) {
    readline();
    auto vertex = new Vertex;
    vertex->code = string;
    vertex->adjacent = vector<Edge*>;
    adjList_.insert(std::make_pair(id, vertex));
  }
}

auto fillmap(string routes) {
  fopen(routes);
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
    

Graph::Graph(string airports, string routes) {
  setupmap(airporsts);
  fillmap(routes);
}
