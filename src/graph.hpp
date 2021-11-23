#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

class Route {
public:
  Route() noexcept;
  Route(std::string dst, std::uint32_t weight) noexcept;

  // TODO: OpenFlights ID
  std::string dst;
  std::uint32_t weight;
};

struct Airport {
public:
  Airport() noexcept;
  Airport(
    std::uint32_t id, std::string iata, std::string icao, std::vector<Route> adjList) noexcept;

  std::uint32_t id;
  std::string iata;
  std::string icao;
  std::vector<Route> adjList;
};

class Graph {
public:
  Graph(std::string const& airports_file, std::string const& routes_file);

  auto numAirports() const noexcept -> std::size_t;
  auto numRoutes() const noexcept -> std::size_t;

private:
  auto readAirports(std::istream& airports) -> void;
  auto readRoutes(std::istream& routes) -> void;

  std::vector<Airport> airports_;
  std::unordered_map<std::string, std::size_t> name_map_;

  std::size_t numRoutes_;
};

