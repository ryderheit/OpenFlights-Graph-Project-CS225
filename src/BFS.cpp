#include <queue>
#include <iostream>
#include <unordered_map>
#include <cmath>

#include "graph.hpp"

using std::queue;
using std::unordered_map;
using std::string;

auto Graph::toRad(const float deg) const-> float{
  float one_deg = (M_PI)/180;
  return one_deg * deg;
}

auto Graph::getDist(const Airport & src, const Airport & dst) const -> float {
  auto lat1 = toRad(src.lat);
  auto lon1 = toRad(src.lon);
  auto lat2 = toRad(dst.lat);
  auto lon2 = toRad(dst.lon);

  auto dlat = lat2 - lat1;
  auto dlon = lon2 - lon1;

  auto ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
  ans = 2 * acos(1 - 2 * ans);

  // float R = 6371;
  // ans = ans * R;

  return ans;
}


auto Graph::BFS() -> void {
  std::cout << "Starting BFS" << std::endl;
  std::cout << std::endl;

  unordered_map<unsigned,bool> exploredNodes; // our own airport IDs -> whether explored
  unordered_map<string,int> edgeStates; // "{src_pos},{dest_pos}" -> state of route

  for (auto & airport : airports_) {
    exploredNodes[airport.id] = false; // Mark each node (airport) as unexplored
    for (Route & route : airport.adjList) {
      auto const & src_dest = std::to_string(route.src_pos) + "," + std::to_string(route.dest_pos);
      edgeStates[src_dest] = 0; // Give each edge (route) a state of 0 (unexplored)
    }
  }

  for (auto const & airport : airports_) {
    if (!exploredNodes[airport.id]) {
      BFSHelper(airport.id, exploredNodes, edgeStates);
    }
  }

  size_t undiscovered = 0;
  size_t discovery = 0;
  size_t cross = 0;

  std::cout << "Total distinct routes in file: " << numRoutes_ << std::endl;
  for (auto it = edgeStates.begin(); it != edgeStates.end(); ++it) {
    if (it->second == 0) {
      undiscovered++;
    } else if (it->second == 1) {
      discovery++;
    } else if (it->second == 2) {
      cross++;
    }
  }
  std::cout << "Unexplored edges: " << undiscovered << std::endl;
  std::cout << "Discovery edges: " << discovery << std::endl;
  std::cout << "Cross edges: " << cross << std::endl;
  std::cout << "Total distinct routes found in BFS: " << undiscovered + discovery + cross << std::endl;
  std::cout << std::endl;
}

/**
 * @param index the index of the airport in airports_
 * @param exploredNodes map of id -> whether the node has been explored
 * @param edgeStates map of edge as string -> state of the edge
 */
auto Graph::BFSHelper(const unsigned index, unordered_map<unsigned,bool>& exploredNodes,
      unordered_map<string,int>& edgeStates) -> void {
  queue<unsigned> q; // queue of our own IDs
  exploredNodes[index] = true;
  q.push(index);

  while (!q.empty()) {
    unsigned & front_idx = q.front();
    q.pop();

    const Airport & airport = airports_[front_idx];
    for (const Route & route : airport.adjList) {
      const string & src_dest = std::to_string(route.src_pos) + "," + std::to_string(route.dest_pos);
      if (!exploredNodes[route.dest_pos]) { // destination is not explored
        exploredNodes[route.dest_pos] = true;
        edgeStates[src_dest] = 1; // mark as discovery edge
        q.push(route.dest_pos);
      } else if (!edgeStates[src_dest]) { // destination is explored but edge is not
        edgeStates[src_dest] = 2; // mark as cross edge
      }
    }
  }
}