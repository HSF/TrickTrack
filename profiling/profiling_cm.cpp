

#include <cmath>
#include <random>
#include <vector>
#include <cstdio>
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>
// Header for interface we want to test
#include "tricktrack/HitChainMaker.h"
#include "tricktrack/HitDoublets.h"
#include "tricktrack/SpacePoint.h"
#include "tricktrack/TripletFilter.h"

using namespace std::placeholders;
using Hit = tricktrack::SpacePoint<size_t>;
using namespace tricktrack;

template <typename Hit>
  bool customizedGeometricFilter(const CMCell<Hit>& theInnerCell, const CMCell<Hit>& theOuterCell) {
  return defaultGeometricFilter(theInnerCell,theOuterCell, 0.8, 0., 0., 0.002, 0.2, 0.8, 0.2 );

    }

void findTripletsForTest(const TrackingRegion& region,
                         std::vector<Hit>
                             barrel0,
                         std::vector<Hit>
                             barrel1,
                         std::vector<Hit>
                             barrel2,
                         std::vector<CMCell<Hit>::CMntuplet>& foundTracklets) {

  std::vector<HitDoublets<Hit>*> doublets;
  auto doublet1 = new HitDoublets<Hit>(barrel0, barrel1);
  auto doublet2 = new HitDoublets<Hit>(barrel1, barrel2);
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

  auto l1 = CMLayer("innerLayer", 10);
  auto l2 = CMLayer("middleLayer", 10);
  auto l3 = CMLayer("outerLayer", 10);

  auto lp1 = CMLayerPair(0, 1);
  auto lp2 = CMLayerPair(1, 2);
  l1.theOuterLayers.push_back(1);
  l2.theInnerLayers.push_back(0);
  l2.theOuterLayers.push_back(2);
  l3.theInnerLayers.push_back(1);
  l1.theOuterLayerPairs.push_back(0);
  l2.theInnerLayerPairs.push_back(0);
  l2.theOuterLayerPairs.push_back(1);
  l3.theInnerLayerPairs.push_back(1);

  auto g = CMGraph();
  g.theLayers.push_back(l1);
  g.theLayers.push_back(l2);
  g.theLayers.push_back(l3);
  g.theLayerPairs.push_back(lp1);
  g.theLayerPairs.push_back(lp2);
  g.theRootLayers.push_back(0);

  auto automaton = new HitChainMaker<Hit>(g);

    constexpr double rep = 1;
		std::clock_t startcputime = std::clock();
    for (int j = 0; j < rep; ++j) {

  TripletFilter<Hit> ff = std::bind(defaultGeometricFilter<Hit>, _1, _2, 1., 1.,1.,1.,1.,1.,1.);
  automaton->createAndConnectCells(doublets, ff);
  automaton->evolve(3);
  automaton->findNtuplets(foundTracklets, 3);
		double cpu_duration = (std::clock() - startcputime) / rep / (double)CLOCKS_PER_SEC;
    std::cout << foundTracklets.size() << "\t" << cpu_duration << "\t" << barrel0.size() << std::endl; 
     }
}


int main() {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0,M_PI);
    double r = 0;
    float phi = 0; 

    for (int numTracks = 1; numTracks < 60; numTracks ++) {

    std::vector<Hit> inner_hits;
    std::vector<Hit> middle_hits;
    std::vector<Hit> outer_hits;
    phi = distribution(generator);  
    for (int _n = 0; _n < numTracks; ++_n) {
    r = 1;
    inner_hits.push_back(Hit(r * std::cos(phi), r*std::sin(phi), 0, 0));
    r = 2;
    middle_hits.push_back(Hit(r * std::cos(phi), r*std::sin(phi), 0, 0));
    r = 3;
    outer_hits.push_back(Hit(r * std::cos(phi), r*std::sin(phi), 0, 0));
    }
    const TrackingRegion myRegion(10, 0, 0, 1000);

    std::vector<CMCell<Hit>::CMntuplet> foundTracklets;
    foundTracklets.reserve(5e7);
    findTripletsForTest(myRegion, inner_hits, middle_hits, outer_hits, foundTracklets);
    }


  return 0;
}
