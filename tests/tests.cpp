#include <vector>

#include "../catch/catch.hpp"
#include "graph.hpp"

using std::string;

TEST_CASE("test catch", "[weight=1]") {
    int new_int = 35;
    REQUIRE( new_int == 35 );
    REQUIRE( 2 + 3 == 5 );
}

TEST_CASE("test dummy airport", "[weight=5]") {
    auto const airports = "tests/dummy_airports_trivial.txt";
    auto const routes = "tests/dummy_routes_trivial.txt";
    Graph g = Graph(airports, routes);
    g.BFS();
}

TEST_CASE("test path invalid airport", "[weight = 5]"){
    auto const airport = "data/small_airports.dat";
    auto const routes = "data/small_routes.dat";
    Graph g = Graph(airport, routes);

    g.floydWarshallwDistPaths();

    std::vector<Airport> path = g.pathReconstruction("SFO", "ABC");


    REQUIRE(path.size() == 0);

}

TEST_CASE("test path valid airport", "[weight = 5]"){
    auto const airport = "data/small_airports.dat";
    auto const routes = "data/small_routes.dat";
    Graph g = Graph(airport, routes);

    g.floydWarshallwDistPaths();

    auto path = g.pathReconstruction("SFO", "ORD");

}
