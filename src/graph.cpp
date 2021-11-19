#include "graph.hpp"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>

using std::unordered_map;
using std::string;
using std::vector;
using std::list;


[[nodiscard]] auto stringSplit(string const& str) -> vector<string> {
  // Open stringstream for mutation
  auto sstream = std::stringstream{str};
  auto tmp = string{};
  auto res = vector<string>{};

  // Delimit string by commas into pieces of vector
  while (std::getline(sstream, tmp, ','))
    res.push_back(tmp);

  // Return split string in vector
  return res;
}

auto Graph::insertVertex(int id, string const& iata, string const& icao) -> void {
  // Construct vertex
  auto const vertex = Vertex{id, iata, icao, {}};

  // Add map entries for IATA/ICAO
  map_[iata] = vertex;
  map_[icao] = vertex;

  // If empty don't add a vertex
  if (iata != "" || icao != "")
    ++vertexCount_;
}

auto Graph::insertEdge(string const& src, string const& dst, int weight) -> void {
  // Emplace constructs an edge with forwarded args, adds to list at corrosponding map location
  map_[src].adjList.emplace_front(src, dst, weight);
  ++edgeCount_;
}

auto Graph::readAirports(std::istream& airports) -> void {
  auto line = string{};

  // Continue grabbing lines until EOF, splitting data into relevant pieces
  while (std::getline(airports, line)) {
    auto const row = stringSplit(line);
    auto const id = std::stoi(row[0]);
    auto const iata = row[4].substr(1, row[4].size() - 2);
    auto const icao = row[5].substr(1, row[5].size() - 2);

    insertVertex(id, iata, icao);
  }
}

auto Graph::readRoutes(std::istream& routes) -> void {
  string line;

  // Continue grabbing lines until EOF, splitting data into relevant pieces
  while (std::getline(routes, line)) {
    std::stringstream linestream(line);
    vector<std::string> column;
    string cell;

    while (std::getline(linestream, cell, ','))
      column.push_back(cell);

    auto const& src = column[2];
    auto const& dst = column[4];
    insertEdge(src, dst, rand() % 100);
  }
}

Graph::Graph(string const& airports_file, string const& routes_file) {
  // Open streams using input filenames
  auto airports = std::ifstream{airports_file};
  auto routes = std::ifstream{routes_file};

  // If failed to open
  if (!airports.is_open() || !routes.is_open())
    std::puts("One or more input files were not found, try again.");

  readAirports(airports);
  readRoutes(routes);
  // Clean map
  map_.erase("");
}

auto Graph::edgeCount() const -> int { return edgeCount_; }

auto Graph::vertexCount() const -> int { return vertexCount_; }
