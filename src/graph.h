#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <unordered_map>

using std::vector;
using std::string;
using std::list;





class Graph {
public:
  Graph(string& const airports_file, string& const routes_file);
  auto insertEdge(int src, int dest, int weight) -> void;
  auto insertVertex(int ID, string code) -> void;
  
  // Getters and setters
  auto getEdges() const -> int;
  auto getVertices() const -> int;

private:

struct Vertex {
  int ID;
  string code;
  list<Edge> adjList_;
};

struct Edge {
  int src;
  int dest;
  int weight;
};

  std::unordered_map<int, Vertex> map_;
  // Number of vertices, edges
  int n = 0, m = 0;
};
  
