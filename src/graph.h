#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <map>

using std::vector;
using std::string;
using std::map;


struct Vertex {
  string code;
  vector<Edge*> adjacent;
};

struct Edge {
  int src, dest, weight;
};


class Graph {
public:
  Graph() : edges_{}, adjList_{}, {};
  Graph(string airports, string routes);
  ~Graph();
private:
  map<int, Vertex*> adjList_;
};
  
