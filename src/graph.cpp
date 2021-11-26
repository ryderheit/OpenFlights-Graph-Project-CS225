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
#include <cmath>


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

auto toRad(double& deg) -> double{
  double one_deg = (M_PI)/180;
  return one_deg * deg;
}

auto getDist(Airport src, Airport dst) -> double{
  auto lat1 = toRad(src.lat);
  auto lon1 = toRad(src.lon);
  auto lat2 = toRad(dst.lat);
  auto lon2 = toRad(dst.lon);

  auto dlat = lat2 - lat1;
  auto dlon = lon2 - lon1;

  auto ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlon / 2), 2);
  ans = 2 * asin(sqrt(ans));

  double R = 6371;
  ans = ans * R;

  return ans;
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
    auto const lat = 5;
    auto const lon = 6;

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
        route.routes++;
        duplicate = true;
      }
    }
    if(!duplicate){
      airports_[pos->second].adjList.emplace_back(dst,0, 1);// std::rand() % 100);
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



auto Graph::floydWarshallwDistPaths() -> void{
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
      float route_weight = 1 / float(route.routes);

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


auto Graph::floydWarshallwRoutePaths() -> void{
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
      float route_weight = 1 / float(route.routes);

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
Route::Route() noexcept : dst{}, weight{}, routes{} {}
Route::Route(
  std::string dst_, std::uint32_t weight_, std::uint32_t routes_) noexcept : dst{std::move(dst_)}, weight{weight_}, routes{routes_} {}

// Empty constructor, copy constructor
Airport::Airport() noexcept : id{}, iata{}, icao{}, adjList{}, lat{}, lon{} {}
Airport::Airport(
  std::uint32_t id_, std::string iata_, std::string icao_, std::vector<Route> adjList_) noexcept
  : id{id_}, iata{std::move(iata_)}, icao{std::move(icao_)}, adjList{std::move(adjList_)} {}
