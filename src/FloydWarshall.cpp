#include <cstdio>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

using std::string;
using std::vector;

#include "graph.hpp"

auto Graph::floydWarshall() -> void{
  /** Setup of the Algoithm **/
  //set up the 2D vector of airports to infinity (represented by -1)

  for(auto airport: airports_){
    //go through each airport (to fill out dist_)
    auto src_index = airport.id;
    //set dist_ance to itself as 0 (free to move to itself)
    dist_[src_index][src_index] = 0;
    for(auto& route: airport.adjList){
      auto dst_index = route.dest_pos;
      float route_weight = 1 / route.weight;

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
      auto dst_index = route.dest_pos;

      dist_[src_index][dst_index] = route.weight;
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
      auto dst_index = route.dest_pos;
      float route_weight = 1 / (float)(route.routes);

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



auto Graph::pathHelper(std::string & src, std::string & dst) -> vector<Airport>{
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

void Graph::writeFW(const string & dist, const string & next) const {
  std::ofstream file{dist};
  for (auto v : dist_) {
    for (auto w : v) {
      string s = std::to_string(w);
      file.write(s.c_str(), s.size());
      file.put(',');
    }
    file.put('\n');
  }
  file.close();
  file.open(next);
  for (auto v : next_) {
    for (auto w : v) {
      string s = std::to_string(w);
      file.write(s.c_str(), s.size());
      file.put(',');
    }
    file.put('\n');
  }
  file.close();
}

void Graph::readFW(const string & dist, const string & next) {
  std::ifstream file{dist};
  if (!file.is_open()) {
    printf("Bad File\n\n");
    return;
  }
  string line;
  std::size_t i = 0, j = 0;
  printf("Dist Progress:\n");
  while (getline(file, line)) {
    auto v = stringSplit(line);
    for (string s : v) {
      if (s.size()) {
        dist_[i][j] = std::stof(s);
      }
      ++j;
    }
    j = 0;
    std::cout << "\r";
    std::cout << i << "/" << numAirports_ << std::flush;
    ++i;
  }
  file.close();
  file.open(next);
  i = j = 0;
  printf("\r%lu/%lu\n\nNext Progress:\n", numAirports_, numAirports_);
  while (getline(file, line)) {
    if (!line.size()) break;
    auto v = stringSplit(line);
    for (string s : v) {
      if (s.size()) {
        next_[i][j] = std::stoul(s);
      }
      ++j;
    }
    j = 0;
    std::cout << "\r";
    std::cout << i << "/" << numAirports_ << std::flush;
    ++i;
  }
    printf("\r%lu/%lu\n\n", numAirports_, numAirports_);
}