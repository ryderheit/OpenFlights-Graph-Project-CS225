#include "../catch/catch.hpp"

TEST_CASE("test catch", "[weight=1]") {
    int new_int = 35;
    REQUIRE( new_int == 35 );
    REQUIRE( 2 + 3 == 5 );
}