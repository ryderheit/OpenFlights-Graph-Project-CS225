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