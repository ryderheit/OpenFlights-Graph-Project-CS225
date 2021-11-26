#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class Route {
public:
  Route() noexcept;
  Route(std::string dst, std::uint32_t weight, std::uint32_t routes) noexcept;

  // TODO: OpenFlights ID
  std::string dst;
  std::uint32_t weight;
  std::uint32_t routes;
};

struct Airport {
public:
  Airport() noexcept;
  Airport(
    std::uint32_t id, std::string iata, std::string icao, std::vector<Route> adjList) noexcept;

  std::uint32_t id;
  std::uint32_t open_id;
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

private:
  auto readAirports(std::istream& airports) -> void;
  auto readRoutes(std::istream& routes) -> void;

  auto toRad(double& deg) -> double;
  auto getDist(Airport src, Airport dst) -> double;

  auto pathHelper(std::string src, std::string dst) -> std::vector<Airport>;

  std::vector<Airport> airports_;
  std::unordered_map<std::string, std::size_t> name_map_;

  std::vector<std::vector<float>> dist_;
  std::vector<std::vector<std::uint32_t>> next_;

  std::size_t numRoutes_;
  std::size_t numAirports_;
};
