#include <cstdio>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>

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
    auto const id = std::stoul(row[0]);
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
    airports_[pos->second].adjList.emplace_back(dst, std::rand() % 100);
    ++numRoutes_;
  }
}

Graph::Graph(string const& airports_file, string const& routes_file) : numRoutes_{} {
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
