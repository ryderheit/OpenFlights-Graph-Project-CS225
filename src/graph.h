#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>

using std::vector;
using std::string;
using std::map;
using std::list;


struct Vertex {
  int ID;
  string code;
  list<Edge>* edges_;
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
  
