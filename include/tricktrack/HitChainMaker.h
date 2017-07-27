#ifndef TRICKTRACK_HITCHAINMAKER_H
#define TRICKTRACK_HITCHAINMAKER_H

#include <array>
#include <memory>
#include "tricktrack/CMCell.h"
#include "tricktrack/CMGraph.h"
#include "tricktrack/TrackingRegion.h"

// forward declarations
namespace tricktrack {
  class TrackingRegion;
}


namespace tricktrack {


/** @class HitChainMaker
 * 
 * Top level object of the seeding algorithm: connects and evolves the links of the chain
 */
template <typename Hit>
class HitChainMaker
{
public:
  HitChainMaker(CMGraph& graph)
    : theLayerGraph(graph)
  {
    
  }
  
  std::vector<CMCell<Hit>> & getAllCells() { return allCells;}
  
  void createAndConnectCells(std::vector<HitDoublets<Hit> *>&,
			     const TrackingRegion& region, const float, const float, const float);
  
  void evolve(const unsigned int);
  void findNtuplets(std::vector<typename CMCell<Hit>::CMntuplet>&, const unsigned int);
  
  void findTriplets(std::vector<HitDoublets<Hit>*>& hitDoublets,std::vector<typename CMCell<Hit>::CMntuplet>& foundTriplets, const TrackingRegion& region, 
		    const float thetaCut, const float phiCut, const float hardPtCut);
  
private:
  CMGraph & theLayerGraph;

  std::vector<CMCell<Hit>> allCells;
  std::vector<CMCellStatus> allStatus;

  std::vector<unsigned int> theRootCells;
  std::vector<std::vector<CMCell<Hit>*> > theNtuplets;
  
};

} // namespace tricktrack

#include "HitChainMaker.ipp"

#endif 
