#pragma once

#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <list>

using std::string;
using std::list;
using std::unordered_map;
using std::vector;


class Graph {
public:
  Graph(const string& airports_file, const string& routes_file);

  auto insertEdge(int src, int dest, int weight) -> void;
  auto insertVertex(int ID, string code) -> void;
  
  // Getters and setters
  auto getNumEdges() const -> int;
  auto getNumVertices() const -> int;

private:
struct Edge {
  int src;
  int dest;
  int weight;
};

struct Vertex {
  int ID;
  string code;
  list<Edge> adjList_;
};

  std::unordered_map<std::string, Vertex> map_;
  // Number of vertices, edges
  int n = 0, m = 0;

  auto readAirports(std::istream& airports) -> void;
  auto readRoutes(std::istream& routes) -> void;
};
  
