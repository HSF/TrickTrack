#ifndef TRACKSEEDTOOLS_CELLULARAUTOMATON_H
#define TRACKSEEDTOOLS_CELLULARAUTOMATON_H
#include <array>
#include "CACell.h"
#include "CAGraph.h"
#include "tricktrack/TrackingRegion.h"

// forward declarations
namespace tricktrack {
  class TrackingRegion;
}


namespace tricktrack {

class CellularAutomaton
{
public:
  CellularAutomaton(CAGraph& graph)
    : theLayerGraph(graph)
  {
    
  }
  
  std::vector<CACell> & getAllCells() { return allCells;}
  
  void createAndConnectCells(std::vector<HitDoublets *>&,
			     const TrackingRegion& region, const float, const float, const float);
  
  void evolve(const unsigned int);
  void findNtuplets(std::vector<CACell::CAntuplet>&, const unsigned int);
  void findTriplets(std::vector<HitDoublets*>& hitDoublets,std::vector<CACell::CAntuplet>& foundTriplets, const TrackingRegion& region, 
		    const float thetaCut, const float phiCut, const float hardPtCut);
  
private:
  CAGraph & theLayerGraph;

  std::vector<CACell> allCells;
  std::vector<CACellStatus> allStatus;

  std::vector<unsigned int> theRootCells;
  std::vector<std::vector<CACell*> > theNtuplets;
  
};

} // namespace tricktrack

#endif 
