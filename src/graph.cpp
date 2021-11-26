#include <cstdio>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iterator>
#include <queue>

#include "graph.hpp"

using std::string;
using std::vector;
using std::unordered_map;
using std::queue;

auto stringSplit(string const& str) -> vector<string> {
  // Read string into a stream to read
  std::stringstream sstream{str};
  auto res = vector<string>{};

  // Read each bit into the vector
  for (auto tmp = string{}; std::getline(sstream, tmp, ','); res.push_back(tmp))
    ;

  return res;
}

auto Graph::readAirports(std::istream& airports) -> void {
  // For each line in the airports file
  for (auto line = string{}; std::getline(airports, line);) {
    // Split the string into the vector
    auto const row = stringSplit(line);
    // String to literal
    auto const open_id = row[0];
    auto const id = numAirports_;numAirports_++;
    // Read and strip quotes from places 4, 5 (IATA/ICAO)
    auto const iata = row[4].substr(1, row[4].size() - 2);
    auto const icao = row[5].substr(1, row[5].size() - 2);

    // Place the route vector into the airports adj list
    airports_.emplace_back(open_id, id, iata, icao, std::vector<Route>{});
    auto const pos = airports_.size() - 1;
    // Insert into the map
    name_map_.insert({iata, pos});
    name_map_.insert({icao, pos});
  }
}

auto Graph::readRoutes(std::istream& routes) -> void {
  // Read each line in the routes file
  for (auto line = string{}; std::getline(routes, line);) {
    // Read in the relevant bits
    auto const row = stringSplit(line);
    auto const& src = row[2]; // IATA or ICAO
    auto const& dst = row[4]; // IATA or ICAO
    auto const& dest_open_id = row[5]; // openflights ID
    auto const& src_open_id = row[3]; // openflights ID

    // Find the pos of the edge beginning
    auto const pos = name_map_.find(src);
    if (pos == name_map_.end()) // src not in name_map_
      continue;

    // Using the pos found, add the route to the relevant adjList
    bool duplicate = false;
    for(auto& route: airports_[pos->second].adjList){ // loop through each route from the src airport
      if(route.dst == dst){ // multiple edges
        route.weight++;
        duplicate = true;
      }
    }
    if(!duplicate){
      auto & list = airports_[pos->second].adjList;
      list.emplace_back(src_open_id, dest_open_id, dst, 1);// std::rand() % 100);
      edge_list_[src_open_id] = list;
      ++numRoutes_;
    }
  }
}

Graph::Graph(string const& airports_file, string const& routes_file) : numRoutes_{},
numAirports_{} {


  // Attempt to open each file and throw if failure
  std::ifstream airports{airports_file};
  if (!airports.is_open())
    throw std::invalid_argument{"Unable to open airports file"};

  std::ifstream routes{routes_file};
  if (!routes.is_open())
    throw std::invalid_argument{"Unable to open routes file"};

  // Call the CSV readers
  readAirports(airports);
  readRoutes(routes);

  auto inf = std::numeric_limits<float>::infinity();
  dist_ = vector<vector<float>>(numAirports_, vector<float>(numAirports_, inf));
  //this next_ vector will be used to reconstruct paths
  next_ = vector<vector<std::uint32_t>>(numAirports_, vector<std::uint32_t>(numAirports_, -1));
}


//Our Own Algorithms
auto Graph::floydWarshall() -> void{
  /** Setup of the Algoithm **/
  //set up the 2D vector of airports to infinity (represented by -1)

  for(auto airport: airports_){
    //go through each airport (to fill out dist_)
    auto src_index = airport.id;
    //set dist_ance to itself as 0 (free to move to itself)
    dist_[src_index][src_index] = 0;
    for(auto& route: airport.adjList){
      auto pos = name_map_.find(route.dst);
      if(pos == name_map_.end()){continue;}
      auto dst_index = pos->second;
      float route_weight = 1 / float(route.weight);

      dist_[src_index][dst_index] = route_weight;
    }
  }

    printf("Floyd Warshall's Progress:\n");

  /** The Meat of the Algoithm **/
  //nested loop through all vertices 3 times
  for(auto k = 0; k < numAirports_; k++){
    for(auto i = 0; i < numAirports_; i++){
      for(auto j = 0; j < numAirports_; j++){
        if(dist_[i][j] > dist_[i][k] + dist_[k][j]){dist_[i][j] = dist_[i][k] + dist_[k][j];}
      }
    }

    std::cout << "\r";
    std::cout << k << "/" << numAirports_ << std::flush;
  }
  printf("\r%lu/%lu",numAirports_, numAirports_);
  printf("\n\n");
}





auto Graph::floydWarshallwPaths() -> void{
  /** Setup of the Algoithm **/
  //set up the 2D vector of airports to infinity (represented by -1)

  //this next_ vector will be used to reconstruct paths

  for(auto airport: airports_){
    //go through each airport (to fill out dist_)
    auto src_index = airport.id;
    //set dist_ance to itself as 0 (free to move to itself)
    dist_[src_index][src_index] = 0;
    next_[src_index][src_index] = airport.id;
    for(auto& route: airport.adjList){
      auto pos = name_map_.find(route.dst);
      if(pos == name_map_.end()){continue;}
      auto dst_index = pos->second;
      float route_weight = 1 / float(route.weight);

      dist_[src_index][dst_index] = route_weight;
      next_[src_index][dst_index] = dst_index;
    }
  }

  printf("Floyd Warshall's Progress:\n");

  /** The Meat of the Algoithm **/
  //nested loop through all vertices 3 times
  for(auto k = 0; k < numAirports_; k++){
    for(auto i = 0; i < numAirports_; i++){
      for(auto j = 0; j < numAirports_; j++){
        if(dist_[i][j] > dist_[i][k] + dist_[k][j]){
          dist_[i][j] = dist_[i][k] + dist_[k][j];
          next_[i][j] = next_[i][k];
        }
      }
    }
    std::cout << "\r";
    std::cout << k << "/" << numAirports_ << std::flush;
  }
  printf("\r%lu/%lu",numAirports_, numAirports_);
  printf("\n\n");
}



auto Graph::pathHelper(std::string src, std::string dst) -> vector<Airport>{
  vector<Airport> path;

  if(name_map_.find(src) == name_map_.end()){
    printf("Invalid Source Airport Code\n");
    return path;
  }

  else if(name_map_.find(dst) == name_map_.end()){
    printf("Invalid Destination Airport Code\n");
    return path;
  }
  else {
    auto src_id = name_map_.find(src)->second;
    auto dst_id = name_map_.find(dst)->second;


    Airport null_airport;

    path.push_back(airports_[src_id]);


    while(src_id != dst_id){
      src_id = next_[src_id][dst_id];
      path.push_back(airports_[src_id]);
    }

    return path;
  }
}

auto Graph::BFS() -> void {
  std::cout << "Starting BFS" << std::endl;
  std::cout << std::endl;

  unordered_map<string,bool> exploredNodes; // openflights IDs -> whether explored
  unordered_map<string,int> edgeStates; // Route -> state of route

  for (auto & airport : airports_) {
    exploredNodes[airport.open_id] = false; // Mark each node (airport) as unexplored
    for (Route & route : airport.adjList) {
      auto const & src_dest = route.src_open_id + "," + route.dest_open_id;
      edgeStates[src_dest] = 0; // Give each edge (route) a state of 0 (unexplored)
    }
  }

  for (auto const & airport : airports_) {
    if (!exploredNodes[airport.open_id]) {
      BFSHelper(airport.open_id, exploredNodes, edgeStates);
    }
  }

  uint32_t undiscovered = 0;
  uint32_t discovery = 0;
  uint32_t cross = 0;

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

auto Graph::BFSHelper(const string open_id, unordered_map<string,bool>& exploredNodes,
      unordered_map<string,int>& edgeStates) -> void {
  queue<string> q; // queue of openflights IDs
  exploredNodes[open_id] = true;
  q.push(open_id);

  while (!q.empty()) {
    string & front_id = q.front();
    q.pop();
    for (Route & route : edge_list_[front_id]) {
      const string & src_id = route.src_open_id;
      const string & dest_id = route.dest_open_id;
      const string & src_dest = src_id + "," + dest_id;
      if (!exploredNodes[dest_id]) { // destination is not explored
        exploredNodes[dest_id] = true;
        edgeStates[src_dest] = 1; // mark as discovery edge
        q.push(dest_id);
      } else if (!edgeStates[src_dest]) { // destination is explored but edge is not
        edgeStates[src_dest] = 2; // mark as cross edge
      }
    }
  }
}

auto Graph::pathReconstruction(std::string src, std::string dst) -> vector<Airport>{
  std::cout << "src: " << src << "  dst: " << dst << std::endl;

  vector<Airport> path = pathHelper(src, dst);

  for(auto airport = path.begin(); airport < path.end(); airport++){
    if(airport == path.begin()){
      std::cout << airport->iata;
    } else {
      std::cout << "->" << airport->iata;
    }
  }
  std::cout << std::endl;
  std::cout << std::endl;
  return path;
}



// Getters
auto Graph::numAirports() const noexcept -> std::size_t { return airports_.size(); }
auto Graph::numRoutes() const noexcept -> std::size_t { return numRoutes_; }

// Empty constructor, copy constructor
Route::Route() noexcept : src_open_id{}, dest_open_id{}, dst{}, weight{} {}
Route::Route(
  string src_open_id_,
  string dest_open_id_,
  string dst_,
  std::uint32_t weight_
) noexcept : 
  src_open_id{src_open_id_}, dest_open_id{dest_open_id_}, dst{std::move(dst_)}, weight{weight_} {}

// Empty constructor, copy constructor
Airport::Airport() noexcept : open_id{}, id{}, iata{}, icao{}, adjList{} {}
Airport::Airport(
  std::string open_id_,
  std::uint32_t id_,
  std::string iata_,
  std::string icao_,
  std::vector<Route> adjList_
) noexcept
  : open_id{open_id_},
    id{id_},
    iata{std::move(iata_)},
    icao{std::move(icao_)},
    adjList{std::move(adjList_)} {}
