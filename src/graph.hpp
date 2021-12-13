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

  std::string name() const;
};

class Graph {
public:
  Graph();
  Graph(std::string const& airports_file, std::string const& routes_file, std::string airline = "");
  //construct graph either by airport region (case 0) or country (case 1),
  //and airline. Empty string means no filtering
  Graph(std::string airports_file, std::string routes_file,
        std::string region, bool country, std::string airline = "");
  
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
  void generateCentrality(std::size_t minSize = 0);
  //Returns the minimally and maximally central airports in a pair
  std::pair<std::string, std::string> minmax() const;
  //Returns the centrality of a given airport
  float centrality(const std::string & src) const;
  //Prints out info about the airport
  void query(std::string q) const;
  //Prints airports with no routes
  void printIsolated() const;
  //Read and write centrality
  void writeBC(const std::string & filename) const;
  void readBC(const std::string & filename);

private:
  auto readAirports(std::istream& airports) -> void;
  void readAirportsbyRegion(std::istream & airports, std::string filter);
  void readAirportsbyCountry(std::istream & airports, std::string filter);
  auto readRoutes(std::istream& routes) -> void;
  void readRoutes(std::istream & routes, std::string filter);

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
