#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <array>
#include <exception>
#include <iostream>
#include <vector>

#include "tricktrack/FKDTree.h"

using namespace tricktrack;

TEST_CASE("FKDTree 2D", "[integration]") {
  TTPoint a(0, 1, 2, 3, 4);
  a.print();
  /*
  try {
    FKDTree<float, 2> tree;
    float minX = 0.2;
    float minY = 0.1;
    float maxX = 0.7;
    float maxY = 0.9;
    unsigned int numberOfPointsInTheBox = 1000;
    unsigned int numberOfPointsOutsideTheBox = 5000;
    std::vector<FKDPoint<float, 2>> points;
    std::vector<unsigned int> result;

    FKDPoint<float, 2> minPoint(minX, minY);
    FKDPoint<float, 2> maxPoint(maxX, maxY);
    unsigned int id = 0;

    for (unsigned int i = 0; i < numberOfPointsInTheBox; ++i) {
      float x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxX - minX)));

      float y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxY - minY)));

      points.emplace_back(x, y, id);
      id++;
    }

    for (unsigned int i = 0; i < numberOfPointsOutsideTheBox; ++i) {
      float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
      float y;
      if (x <= maxX && x >= minX)
        y = maxY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(1.f - maxY)));

      points.emplace_back(x, y, id);
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
  */
}

TEST_CASE("FKDTree 3D", "[integration]") {
  /*
  try {
    FKDTree<float, 3> tree;
    float minX = 0.2;
    float minY = 0.1;
    float minZ = 0.1;
    float maxX = 0.7;
    float maxY = 0.9;
    float maxZ = 0.3;

    unsigned int numberOfPointsInTheBox = 1000;
    unsigned int numberOfPointsOutsideTheBox = 5000;
    std::vector<FKDPoint<float, 3>> points;
    std::vector<unsigned int> result;

    FKDPoint<float, 3> minPoint(minX, minY, minZ);
    FKDPoint<float, 3> maxPoint(maxX, maxY, maxZ);
    unsigned int id = 0;

    for (unsigned int i = 0; i < numberOfPointsInTheBox; ++i) {
      float x = minX + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxX - minX)));

      float y = minY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxY - minY)));
      float z = minZ + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxZ - minZ)));

      points.emplace_back(x, y, z, id);
      id++;
    }

    for (unsigned int i = 0; i < numberOfPointsOutsideTheBox; ++i) {
      float x = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
      float y;
      if (x <= maxX && x >= minX)
        y = maxY + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(1.f - maxY)));
      float z = minZ + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / std::fabs(maxZ - minZ)));

      points.emplace_back(x, y, z, id);
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
  */
}
