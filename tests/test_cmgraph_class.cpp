#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "tricktrack/CMGraph.h"
#include "tricktrack/CMGraphUtils.h"

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

TEST_CASE("CM Graph User construction", "[interface]") {

  std::vector<std::vector<std::string>> layerDescription { {{"b1","b2","b3", "b4"}, {"b1","b2","b3", "e1"}, {"e1", "e2", "e3", "e4"}, {"b1", "b2", "e1", "e2"}, {"b1", "e1", "e2", "e3"} }};
  auto g = createGraph(layerDescription);

  REQUIRE(g.theLayers[g.theRootLayers[0]] == "b1");

  REQUIRE(g.theLayers[g.theRootLayers[1]] == "e1");

  REQUIRE(g.theLayers[g.theLayers[0].theOuterLayers[0]] == "b2");

  REQUIRE(g.theLayers[g.theLayers[0].theOuterLayers[1]] == "e1");


}
