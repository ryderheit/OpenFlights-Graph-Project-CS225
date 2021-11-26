#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class Route { // Edge
public:
  Route() noexcept;
  Route(
    std::string src_open_id_,
    std::string dest_open_id_,
    std::string dst_,
    std::uint32_t weight_,
    std::uint32_t routes_
  ) noexcept;

  std::string src_open_id;
  std::string dest_open_id;
  std::string dst;
  std::uint32_t weight;
  std::uint32_t routes;
};

struct Airport { // Node
public:
  Airport() noexcept;
  Airport(
    std::string open_id_,
    std::uint32_t id_,
    std::string iata_,
    std::string icao_,
    std::vector<Route> adjList_
  ) noexcept;

  std::uint32_t id;
  std::string open_id;
  std::string iata;
  std::string icao;
  double lon;
  double lat;
  std::vector<Route> adjList;
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

  // BFS algorithm
  auto BFS() -> void;

private:
  auto readAirports(std::istream& airports) -> void;
  auto readRoutes(std::istream& routes) -> void;

  auto toRad(double& deg) -> double;
  auto getDist(Airport src, Airport dst) -> double;

  auto pathHelper(std::string src, std::string dst) -> std::vector<Airport>;

  auto BFSHelper(const std::string open_id, std::unordered_map<std::string,bool>& exploredNodes,
      std::unordered_map<std::string,int>& edgeStates) -> void;

  std::vector<Airport> airports_;
  std::unordered_map<std::string, std::size_t> name_map_;
  std::unordered_map<std::string, std::vector<Route>> edge_list_; // src openflights id -> routes

  std::vector<std::vector<float>> dist_;
  std::vector<std::vector<std::uint32_t>> next_;

  std::size_t numRoutes_;
  std::size_t numAirports_;
};
