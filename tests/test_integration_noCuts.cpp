
// Catch setup with supplied main()
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>
#include <vector>
// Header for interface we want to test
#include "tricktrack/CellularAutomaton.h"
#include "tricktrack/HitDoublets.h"
#include "tricktrack/SpacePoint.h"

using Hit = tricktrack::SpacePoint<size_t>;
using namespace tricktrack;

void findTripletsForTest(const TrackingRegion& region,
                         std::vector<Hit>
                             barrel0,
                         std::vector<Hit>
                             barrel1,
                         std::vector<Hit>
                             barrel2,
                         std::vector<CACell::CAntuplet>& foundTracklets) {

  std::vector<HitDoublets*> doublets;
  auto doublet1 = new HitDoublets(barrel0, barrel1);
  auto doublet2 = new HitDoublets(barrel1, barrel2);
  doublets.push_back(doublet1);
  doublets.push_back(doublet2);

  for (const auto& p0 : barrel0) {
    for (const auto& p1 : barrel1) {
      doublets[0]->add(p0.identifier(), p1.identifier());
    }
  }
  for (const auto& p1 : barrel1) {
    for (const auto& p2 : barrel2) {
      doublets[1]->add(p1.identifier(), p2.identifier());
    }
  }

  auto l1 = CALayer("innerLayer", 10);
  auto l2 = CALayer("middleLayer", 10);
  auto l3 = CALayer("outerLayer", 10);

  auto lp1 = CALayerPair(0, 1);
  auto lp2 = CALayerPair(1, 2);
  l1.theOuterLayers.push_back(1);
  l2.theInnerLayers.push_back(0);
  l2.theOuterLayers.push_back(2);
  l3.theInnerLayers.push_back(1);
  l1.theOuterLayerPairs.push_back(0);
  l2.theInnerLayerPairs.push_back(0);
  l2.theOuterLayerPairs.push_back(1);
  l3.theInnerLayerPairs.push_back(1);

  auto g = CAGraph();
  g.theLayers.push_back(l1);
  g.theLayers.push_back(l2);
  g.theLayers.push_back(l3);
  g.theLayerPairs.push_back(lp1);
  g.theLayerPairs.push_back(lp2);
  g.theRootLayers.push_back(0);

  auto automaton = new CellularAutomaton(g);
  automaton->createAndConnectCells(doublets, region, 1, 1000, 1000);
  automaton->evolve(3);
  automaton->findNtuplets(foundTracklets, 3);
}

TEST_CASE("Integration test without track filtering", "[integration]") {

  const TrackingRegion myRegion(10, 0, 0, 1000);

  SECTION("One hit per layer") {
    std::vector<Hit> inner_hits;
    inner_hits.push_back(Hit(0, 1, 0, 0));
    std::vector<Hit> middle_hits;
    middle_hits.push_back(Hit(0, 2, 0, 0));
    std::vector<Hit> outer_hits;
    outer_hits.push_back(Hit(0, 3, 0, 0));

    std::vector<CACell::CAntuplet> foundTracklets;
    findTripletsForTest(myRegion, inner_hits, middle_hits, outer_hits, foundTracklets);
    REQUIRE(foundTracklets.size() == 1);
  }

  SECTION("Two hits per layer, orthogonal tracks") {
    std::vector<Hit> inner_hits;
    inner_hits.push_back(Hit(0, 1, 0, 0));
    inner_hits.push_back(Hit(1, 0, 0, 1));
    std::vector<Hit> middle_hits;
    middle_hits.push_back(Hit(0, 2, 0, 0));
    middle_hits.push_back(Hit(2, 0, 0, 1));
    std::vector<Hit> outer_hits;
    outer_hits.push_back(Hit(0, 3, 0, 0));
    outer_hits.push_back(Hit(3, 0, 0, 1));

    std::vector<CACell::CAntuplet> foundTracklets;
    findTripletsForTest(myRegion, inner_hits, middle_hits, outer_hits, foundTracklets);
    REQUIRE(foundTracklets.size() == 2);
  }

  SECTION("Two hits per layer, very close tracks") {
    std::vector<Hit> inner_hits;
    inner_hits.push_back(Hit(0, 1, 0, 0));
    inner_hits.push_back(Hit(0, 1.001, 0, 1));
    std::vector<Hit> middle_hits;
    middle_hits.push_back(Hit(0, 2, 0, 0));
    middle_hits.push_back(Hit(0, 2.002, 0, 1));
    std::vector<Hit> outer_hits;
    outer_hits.push_back(Hit(0, 3, 0, 0));
    outer_hits.push_back(Hit(0, 3.003, 0, 1));

    std::vector<CACell::CAntuplet> foundTracklets;
    findTripletsForTest(myRegion, inner_hits, middle_hits, outer_hits, foundTracklets);
    REQUIRE(foundTracklets.size() == 8);
  }
}
