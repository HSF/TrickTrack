#ifndef TRICKTRACK_CHAINMAKER_H
#define TRICKTRACK_CHAINMAKER_H

#include <array>
#include "CMCell.h"
#include "CMGraph.h"
#include "tricktrack/TrackingRegion.h"

// forward declarations
namespace tricktrack {
  class TrackingRegion;
}


namespace tricktrack {

class ChainMaker
{
public:
  ChainMaker(CMGraph& graph)
    : theLayerGraph(graph)
  {
    
  }
  
  std::vector<CMCell> & getAllCells() { return allCells;}
  
  void createAndConnectCells(std::vector<HitDoublets *>&,
			     const TrackingRegion& region, const float, const float, const float);
  
  void evolve(const unsigned int);
  void findNtuplets(std::vector<CMCell::CMntuplet>&, const unsigned int);
  void findTriplets(std::vector<HitDoublets*>& hitDoublets,std::vector<CMCell::CMntuplet>& foundTriplets, const TrackingRegion& region, 
		    const float thetaCut, const float phiCut, const float hardPtCut);
  
private:
  CMGraph & theLayerGraph;

  std::vector<CMCell> allCells;
  std::vector<CMCellStatus> allStatus;

  std::vector<unsigned int> theRootCells;
  std::vector<std::vector<CMCell*> > theNtuplets;
  
};

} // namespace tricktrack

#endif 
