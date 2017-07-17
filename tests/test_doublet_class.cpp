// Catch setup with supplied main()
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Header for interface we want to test
#include "tricktrack/SpacePoint.h"

using Hit = tricktrack::SpacePoint<size_t>;

TEST_CASE("Hit Point Behavior", "[interface]") {

  auto p = tricktrack::SpacePoint<int>(1, 2, 3, 99);
  // check getters
  double l_x = 1;
  double l_y = 2;
  double l_z = 3;
  REQUIRE(p.x() == l_x);
  REQUIRE(p.y() == l_y);
  REQUIRE(p.z() == l_z);
  REQUIRE(p.rho() - std::sqrt(l_x * l_x + l_y + l_y) < 1e-12);
  REQUIRE(p.phi() - std::atan2(l_y, l_x) < 1e-12);
}
