#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>
#include <climits>

class Route { // Edge
public:
  Route() noexcept;
  Route(
    std::size_t src_pos_,
    std::size_t dest_pos_,
    std::string dst_,
    float weight_,
    std::size_t routes_
  ) noexcept;

  std::size_t src_pos = UINT_MAX; // position of src in airports_
  std::size_t dest_pos = UINT_MAX; // position of dest in airports_
  std::string dst;
  float weight;
  std::size_t routes;
};

struct Airport { // Node
public:
  Airport() noexcept;
  Airport(
    std::string open_id_,
    std::size_t id_,
    std::string iata_,
    std::string icao_,
    std::vector<Route> adjList_,
    float lat,
    float lon
  ) noexcept;

  std::size_t id; // our own ID, used in name_map_
  std::string open_id;
  std::string iata;
  std::string icao;
  float lon;
  float lat;
  std::vector<Route> adjList;

  //Sets r to the edge in this airport which goes to dst. Slow.
  void to(const std::size_t dst, Route & r) const;
};

class Graph {
public:
  Graph(std::string const& airports_file, std::string const& routes_file);

  auto numAirports() const noexcept -> std::size_t;
  auto numRoutes() const noexcept -> std::size_t;

  //Shortest Path and Helpers
  auto floydWarshall() -> void;
  auto floydWarshallwDistPaths() -> void;
  auto floydWarshallwRoutePaths() -> void;
  auto pathReconstruction(std::string src, std::string dst) -> std::vector<Airport>;
  void writeFW(const std::string & dist, const std::string & next) const;
  void readFW(const std::string & dist, const std::string & next);

  // BFS algorithm
  auto BFS() -> void;

  //Betweeness
  //Creates btwn_. Run after FloydWarshall!!
  void generateCentrality();
  //Returns the minimally and maximally central airports in a pair
  std::pair<std::string, std::string> minmax() const;
  //Returns the centrality of a given airport
  float centrality(const std::string & src) const;

private:
  auto readAirports(std::istream& airports) -> void;
  auto readRoutes(std::istream& routes) -> void;

  auto toRad(const float deg) const-> float;
  auto getDist(const Airport & src, const Airport & dst) const -> float;

  auto pathHelper(std::string & src, std::string & dst) -> std::vector<std::size_t>;

  auto BFSHelper(const unsigned index, std::unordered_map<unsigned,bool>& exploredNodes,
      std::unordered_map<std::string,int>& edgeStates) -> void;

  std::vector<Airport> airports_;
  std::unordered_map<std::string, std::size_t> name_map_;

  std::vector<std::vector<float>> dist_;
  std::vector<std::vector<std::size_t>> next_;
  std::vector<float> btwn_ = {};

  std::size_t numRoutes_;
  std::size_t numAirports_;

  auto stringSplit(std::string const& str) -> std::vector<std::string>;
};
