#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tricktrack/CAGraph.h"

using namespace tricktrack;

TEST_CASE("CA Graph methods", "[interface]") {

  auto l1 = CALayer("Layer1", 10);
  auto l2 = CALayer("Layer2", 10);

  REQUIRE(!(l1 == "Layer2"));
  REQUIRE(l1.name() == "Layer1");

  auto lp1 = CALayerPair(0, 1);
  auto lp2 = CALayerPair(0, 1);

  REQUIRE(lp1 == lp2);

  auto g = CAGraph();
  g.theLayers = std::vector<CALayer>{l1, l2};
}
