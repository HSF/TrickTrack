// Catch setup with supplied main()
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>
#include <vector>
// Header for interface we want to test
#include "tricktrack/HitDoublets.h"
#include "tricktrack/SpacePoint.h"

using Hit = tricktrack::SpacePoint<size_t>;
using namespace tricktrack;

TEST_CASE("Hit Point Behavior", "[interface]") {

  // check test hit class
  auto p = Hit(1, 2, 3, 0);
  // check getters
  double l_x = 1;
  double l_y = 2;
  double l_z = 3;
  REQUIRE(p.x() == l_x);
  REQUIRE(p.y() == l_y);
  REQUIRE(p.z() == l_z);
  REQUIRE(p.rho() - std::sqrt(l_x * l_x + l_y + l_y) < 1e-12);
  REQUIRE(p.phi() - std::atan2(l_y, l_x) < 1e-12);

  // check test doublet ctors and getters
  std::vector<Hit> inner_hits;
  inner_hits.push_back(Hit(-3, -2, -1, 100));
  inner_hits.push_back(Hit(1, 1, 1, 101));
  std::vector<Hit> outer_hits;
  outer_hits.push_back(Hit(-30, -20, -10, 200));
  outer_hits.push_back(Hit(10, 10, 10, 201));

  HitDoublets doublets(inner_hits, outer_hits);
  doublets.add(0, 0);
  doublets.add(1, 1);

  REQUIRE(doublets.size() == 2);
  REQUIRE(doublets.innerHitId(0) == 0);
  REQUIRE(doublets.innerHitId(1) == 1);
  REQUIRE(doublets.outerHitId(0) == 0);
  REQUIRE(doublets.outerHitId(1) == 1);
}
