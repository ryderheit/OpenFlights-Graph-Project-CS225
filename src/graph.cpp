#include <cstdio>
#include <exception>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <iterator>
#include <cmath>


#include "graph.hpp"

using std::string;
using std::vector;

auto Graph::stringSplit(string const& str) -> vector<string> {
  // Read string into a stream to read
  std::stringstream sstream{str};
  auto res = vector<string>{};

  // Read each bit into the vector
  for (auto tmp = string{}; std::getline(sstream, tmp, ','); res.push_back(tmp))
    ;

  return res;
}

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

  float R = 6371;
  ans = ans * R;

  return ans;
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
    auto const lat = std::stod(row[6]);
    auto const lon = std::stod(row[7]);

    // Place the route vector into the airports adj list
    airports_.emplace_back(open_id, id, iata, icao, std::vector<Route>{}, lat, lon);
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

    // Find the pos of the edge beginning
    auto const pos = name_map_.find(src);
    if (pos == name_map_.end()) // src not in name_map_
      continue;
    std::size_t src_pos = pos->second;

    auto const pos2 = name_map_.find(dst);
    if (pos2 == name_map_.end()) // src not in name_map_
      continue;
    std::size_t dest_pos = pos2->second;

    // Using the pos found, add the route to the relevant adjList
    bool duplicate = false;
    for(auto& route: airports_[pos->second].adjList){ // loop through each route from the src airport
      if(route.dst == dst){ // multiple edges
        route.routes++;
        duplicate = true;
      }
    }
    if(!duplicate){
      airports_[src_pos].adjList.emplace_back(src_pos, dest_pos, dst, getDist(airports_[src_pos], airports_[dest_pos]), 1);// std::rand() % 100);
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
  next_ = vector<vector<std::size_t>>(numAirports_, vector<std::size_t>(numAirports_, -1));
}

// Getters
auto Graph::numAirports() const noexcept -> std::size_t { return airports_.size(); }
auto Graph::numRoutes() const noexcept -> std::size_t { return numRoutes_; }

// Empty constructor, copy constructor
Route::Route() noexcept : dst{}, weight{} {}
Route::Route(
  std::size_t src_pos_,
  std::size_t dest_pos_,
  string dst_,
  float weight_,
  std::size_t routes_
) noexcept : 
  src_pos{src_pos_},
  dest_pos{dest_pos_},
  dst{std::move(dst_)},
  weight{weight_},
  routes{routes_} {}

// Empty constructor, copy constructor
Airport::Airport() noexcept : open_id{}, id{}, iata{}, icao{}, adjList{}, lat{}, lon{} {}
Airport::Airport(
  std::string open_id_,
  std::size_t id_,
  std::string iata_,
  std::string icao_,
  std::vector<Route> adjList_,
  float lat_,
  float lon_
) noexcept
  : open_id{open_id_},
    id{id_},
    iata{std::move(iata_)},
    icao{std::move(icao_)},
    adjList{std::move(adjList_)},
    lat{lat_},
    lon{lon_} {}
