#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <vector>
#include <iostream>

#include "tricktrack/FKDTree.h"

using namespace tricktrack;

TEST_CASE("CM Graph methods", "[interface]") {
  constexpr uint numLayers = 3;
  std::array<std::vector<FKDPoint<float, 3>>, numLayers> layerKDpointVectors;

  for (unsigned int layerCounter = 0; layerCounter < numLayers; ++layerCounter) {
    layerKDpointVectors[layerCounter].push_back(FKDPoint<float, 3>(layerCounter, layerCounter, layerCounter, layerKDpointVectors[layerCounter].size()));

  }

  // simple test: check that the search works correctly on the last layer
  auto points = layerKDpointVectors[numLayers - 1];
  points[0].print();
  points[1].print();
  FKDTree<float, 3> kdtree(points.size(), points);
  kdtree.build();
  // small search window, do not expect to find anything
  auto resultIds1 = kdtree.search_in_the_box(FKDPoint<float, 3>(0,0,0,0),
                                             FKDPoint<float, 3>(1,1,1,0));
  REQUIRE(resultIds1.size() == 0);

  // in this search window we should find the hit
  auto resultIds2 = kdtree.search_in_the_box(FKDPoint<float, 3>(0,0,0,0),
                                             FKDPoint<float, 3>(10,10,10,0));

  REQUIRE(resultIds2.size() == 1);
}
