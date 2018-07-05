#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <exception>
#include <iostream>
#include <vector>

#include "tricktrack/FKDTree.h"
#include "tricktrack/TTPoint.h"

using namespace tricktrack;


TEST_CASE("FKDTree with TTPoint", "[integration]") {

  TTPoint p(0, 1, 2, 3,4);
  p.print();
  try {
    FKDTree<TTPoint, double, 4> tree;
    float minX = 0.2;
    float minY = 0.1;
    float minZ = 0.1;
    float minT = 0.4;
    float maxX = 0.7;
    float maxY = 0.9;
    float maxZ = 0.3;
    float maxT = 0.9;

    unsigned int numberOfPointsInTheBox = 1000;
    unsigned int numberOfPointsOutsideTheBox = 5000;
    std::vector<TTPoint> points;
    std::vector<unsigned int> result;

    TTPoint minPoint(minX, minY, minZ, minT,0);
    TTPoint maxPoint(maxX, maxY, maxZ, maxT,0);
    unsigned int id = 0;

    for (unsigned int i = 0; i < numberOfPointsInTheBox; ++i) {
      float x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxX - minX)));

      float y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxY - minY)));
      float z = minZ + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxZ - minZ)));
      float t = minT + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxT - minT)));

      points.emplace_back(x, y, z,t, id);
      id++;
    }

    for (unsigned int i = 0; i < numberOfPointsOutsideTheBox; ++i) {
      float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
      float y;
      if (x <= maxX && x >= minX)
        y = maxY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(1.f - maxY)));
      float z = minZ + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxZ - minZ)));
      float t = minT + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxT - minT)));

      points.emplace_back(x, y, z, t, id);
      id++;
    }
    tree.build(points);
    tree.search(minPoint, maxPoint, result);
    REQUIRE((unsigned int)tree.size() == numberOfPointsInTheBox + numberOfPointsOutsideTheBox);
    REQUIRE((unsigned int)result.size() == numberOfPointsInTheBox);

  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    REQUIRE(false);
  }
}
