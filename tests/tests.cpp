#include <vector>
#include <iostream>

#include "../catch/catch.hpp"
#include "../src/graph.hpp"

using std::string;
using std::cout;
using std::endl;


TEST_CASE("test catch", "[weight=1]") {
    int new_int = 35;
    REQUIRE( new_int == 35 );
    REQUIRE( 2 + 3 == 5 );
}

TEST_CASE("test dummy airport trivial", "[weight=5]") {
    auto const airports = "tests/dummy_airports_trivial.txt";
    auto const routes = "tests/dummy_routes_trivial.txt";
    Graph g = Graph(airports, routes);

    cout << "\033[1;34m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    cout << "\033[1;34m        Expected output: \033[0m\n" << endl;
    cout << "\033[1;34m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    cout << "Starting BFS" << endl;
    cout << endl;
    cout << "Total distinct routes in file: " << 2 << endl;
    cout << "Unexplored edges: " << 0 << endl;
    cout << "Discovery edges: " << 1 << endl;
    cout << "Cross edges: " << 1 << endl;
    cout << "Total distinct routes found in BFS: " << 2 << endl;
    cout << endl;

    cout << "\033[1;36m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    cout << "\033[1;36m        Actual output: \033[0m\n" << endl;
    cout << "\033[1;36m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    g.BFS();
    cout << "\033[1;32mEnd of BFS test\033[0m\n" << endl;
}

TEST_CASE("test dummy airport small", "[weight=5]") {
    auto const airports = "tests/dummy_airports_trivial.txt";
    auto const routes = "tests/dummy_routes_small.txt";
    Graph g = Graph(airports, routes);

    cout << "\033[1;34m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    cout << "\033[1;34m        Expected output: \033[0m\n" << endl;
    cout << "\033[1;34m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    cout << "Starting BFS" << endl;
    cout << endl;
    cout << "Total distinct routes in file: " << 6 << endl;
    cout << "Unexplored edges: " << 0 << endl;
    cout << "Discovery edges: " << 2 << endl;
    cout << "Cross edges: " << 4 << endl;
    cout << "Total distinct routes found in BFS: " << 6 << endl;
    cout << endl;

    cout << "\033[1;36m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    cout << "\033[1;36m        Actual output: \033[0m\n" << endl;
    cout << "\033[1;36m-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[0m\n" << endl;
    g.BFS();
    cout << "\033[1;32mEnd of BFS test\033[0m\n" << endl;
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
