#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tricktrack/CMGraph.h"

using namespace tricktrack;

TEST_CASE("CM Graph methods", "[interface]") {

  auto l1 = CMLayer("Layer1", 10);
  auto l2 = CMLayer("Layer2", 10);

  REQUIRE(!(l1 == "Layer2"));
  REQUIRE(l1.name() == "Layer1");

  auto lp1 = CMLayerPair(0, 1);
  auto lp2 = CMLayerPair(0, 1);

  REQUIRE(lp1 == lp2);

  auto g = CMGraph();
  g.theLayers = std::vector<CMLayer>{l1, l2};
}
