#include <cstdio>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <limits>

#include "graph.hpp"

using std::string;
using std::vector;

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
    auto const open_id = std::stoul(row[0]);
    auto const id = numAirports_;numAirports_++;
    // Read and strip quotes from places 4, 5 (IATA/ICAO)
    auto const iata = row[4].substr(1, row[4].size() - 2);
    auto const icao = row[5].substr(1, row[5].size() - 2);

    // Place the route vector into the airports adj list
    airports_.emplace_back(id, iata, icao, std::vector<Route>{});
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
    auto const& src = row[2];
    auto const& dst = row[4];

    // Find the pos of the edge beginning
    auto const pos = name_map_.find(src);
    if (pos == name_map_.end())
      continue;

    // Using the pos found add the route to the relevant ajdlist
    bool duplicate = false;
    for(auto& route: airports_[pos->second].adjList){
      if(route.dst == dst){
        route.weight++;
        duplicate = true;
      }
    }
    if(!duplicate){
      airports_[pos->second].adjList.emplace_back(dst, 1);// std::rand() % 100);
      ++numRoutes_;
    }
  }
}

Graph::Graph(string const& airports_file, string const& routes_file) : numRoutes_{}, numAirports_{} {
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
}


//Our Own Algorithms
auto Graph::floydWarshall() const -> vector<vector<float>>{
  /** Setup of the Algoithm **/
  //set up the 2D vector of airports to infinity (represented by -1)
  auto inf = std::numeric_limits<float>::infinity();
  vector<vector<float>> dist(numAirports_, vector<float>(numAirports_, inf));
  for(auto airport: airports_){
    //go through each airport (to fill out dist)
    auto src_index = airport.id;
    //set distance to itself as 0 (free to move to itself)
    dist[src_index][src_index] = 0;
    for(auto route: airport.adjList){
      auto pos = name_map_.find(route.dst);
      auto dst_index = pos->second;
      float route_weight = 1 / float(route.weight);

      std::cout << src_index << " " << dst_index << std::endl;
      dist[src_index][dst_index] = route_weight;
    }
  }



  /** The Meat of the Algoithm **/
  //nested loop through all vertices 3 times
  for(auto k = 0; k < numAirports_; k++){
    for(auto i = 0; i < numAirports_; i++){
      for(auto j = 0; j < numAirports_; j++){
        if(dist[i][j] > dist[i][k] + dist[k][j]){dist[i][j] = dist[i][k] + dist[k][j];}
      }
    }
  }

  return dist;
}

// Getters
auto Graph::numAirports() const noexcept -> std::size_t { return airports_.size(); }
auto Graph::numRoutes() const noexcept -> std::size_t { return numRoutes_; }

// Empty constructor, copy constructor
Route::Route() noexcept : dst{}, weight{} {}
Route::Route(
  std::string dst_, std::uint32_t weight_) noexcept : dst{std::move(dst_)}, weight{weight_} {}

// Empty constructor, copy constructor
Airport::Airport() noexcept : id{}, iata{}, icao{}, adjList{} {}
Airport::Airport(
  std::uint32_t id_, std::string iata_, std::string icao_, std::vector<Route> adjList_) noexcept
  : id{id_}, iata{std::move(iata_)}, icao{std::move(icao_)}, adjList{std::move(adjList_)} {}
