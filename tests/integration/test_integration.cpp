
#include <cmath>
#include <vector>
#include <functional>

#include "tricktrack/HitChainMaker.h"
#include "tricktrack/HitDoublets.h"
#include "tricktrack/SpacePoint.h"
#include "tricktrack/TripletFilter.h"
#include "tricktrack/CMGraphUtils.h"

using Hit = tricktrack::SpacePoint<size_t>;
using namespace tricktrack;
using namespace std::placeholders;



void findTripletsForTest( std::vector<Hit>
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
  
  CMGraph g = createGraph({{"innerlayer", "middleLayer", "outerLayer"}});


  
  auto automaton = new HitChainMaker<Hit>(g);

  // create 
  TripletFilter<Hit> ff = std::bind(defaultGeometricFilter<Hit>, _1, _2,  
                                    0.8, // ptmin 
                                    0.,  // region_origin_x
                                    0.,  // region_origin_y
                                    0.002, // region_origin_radius
                                    0.2, // phiCut
                                    0.8, // hardPtCut
                                    0.2  // thetaCut
                                    );
  automaton->createAndConnectCells(doublets, ff);
  automaton->evolve(3);
  automaton->findNtuplets(foundTracklets, 3);
}

int main() {


    std::vector<Hit> inner_hits;
    inner_hits.push_back(Hit(0, 1, 0, 0));
    inner_hits.push_back(Hit(0, 1.001, 0, 1));
    std::vector<Hit> middle_hits;
    middle_hits.push_back(Hit(0, 2, 0, 0));
    middle_hits.push_back(Hit(0, 2.002, 0, 1));
    std::vector<Hit> outer_hits;
    outer_hits.push_back(Hit(0, 3, 0, 0));
    outer_hits.push_back(Hit(0, 3.003, 0, 1));

    std::vector<CMCell<Hit>::CMntuplet> foundTracklets;
    findTripletsForTest(inner_hits, middle_hits, outer_hits, foundTracklets);
    // fail on unexpected output
    if (foundTracklets.size() != 8) {
      return 1;
    }
    return 0;
}
