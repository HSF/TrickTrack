#ifndef TRICKTRACK_CMGRAPH_H
#define TRICKTRACK_CMGRAPH_H

#include <array>
#include <string>
#include <vector>
#include <set>
#include <map>

namespace tricktrack {

/** @struct CMLayer
 *
 * struct representing a layer in the detector topology
 */
struct CMLayer {
  CMLayer(const std::string& layerName, std::size_t numberOfHits) : theName(layerName) {
    isOuterHitOfCell.resize(numberOfHits);
  }

  bool operator==(const std::string& otherString) { return otherString == theName; }

  std::string name() const { return theName; }

  std::vector<int> theOuterLayerPairs;
  std::vector<int> theInnerLayerPairs;

  std::vector<int> theOuterLayers;
  std::vector<int> theInnerLayers;
  std::vector<std::vector<unsigned int>> isOuterHitOfCell;

private:
  std::string theName;
};

/** @struct CMLayerPair
 *
 * struct representing a pair of layers in the detector topology.
 */
struct CMLayerPair {

  CMLayerPair(int a, int b)

  {
    theLayers[0] = a;
    theLayers[1] = b;
  }

  bool operator==(const CMLayerPair& otherLayerPair) {
    return (theLayers[0] == otherLayerPair.theLayers[0]) && (theLayers[1] == otherLayerPair.theLayers[1]);
  }

  std::array<int, 2> theLayers;
  std::array<unsigned int, 2> theFoundCells = {{0, 0}};
};

/** struct CMGraph
 *
 * struct representing the full topology of the detector
 */
struct CMGraph {
  std::vector<CMLayer> theLayers;
  std::vector<CMLayerPair> theLayerPairs;
  std::vector<int> theRootLayers;
};


/** createGrap
 *
 *  utility function to facilitate filling the CMGraph
 */
CMGraph createGraph(std::vector<std::vector<std::string>> graphList, std::size_t numberOfHits=1000000) {

  // temporary containers for bookkeeping of layers
  std::set<std::string> uniqueLayers;
  std::set<std::string> uniqueRootLayers;
  std::map<std::string, int> layerName2Index;

  // the vectors for each layer that need to be filled
  std::map<std::string, std::set<int>> outerLayersMap;
  std::map<std::string, std::set<int>> innerLayersMap;
  std::map<std::string, std::set<int>> outerLayerPairsMap;
  std::map<std::string, std::set<int>> innerLayerPairsMap;

  // get a list of unique layers (and root layers)
  for (auto layerPath: graphList) {
    uniqueRootLayers.insert(layerPath[0]);
    for (auto layerName: layerPath) {
      uniqueLayers.insert(layerName);
      outerLayerPairsMap.insert(std::make_pair(layerName, std::set<int>()));
      innerLayerPairsMap.insert(std::make_pair(layerName, std::set<int>()));
      outerLayerPairsMap.insert(std::make_pair(layerName, std::set<int>()));
      innerLayerPairsMap.insert(std::make_pair(layerName, std::set<int>()));
    }
  }

  // get indices of each layer in the layer list
  int layerCounter = 0;
  for (auto layerName: uniqueLayers) {
    layerName2Index.insert(std::make_pair(layerName, layerCounter));
    layerCounter++;
  }

  // fill the inner / outer layers list
  for (auto layerPath: graphList) {
    for (int i = 0; i < layerPath.size(); ++i) {
      auto layerName = layerPath[i];
      if (i > 0) {
       innerLayersMap[layerName].insert(layerName2Index[layerPath[i-1]]);
      }
      if (i < layerPath.size() - 1) {
       outerLayersMap[layerName].insert(layerName2Index[layerPath[i+1]]);
      }
      uniqueLayers.insert(layerName);
    }
  }

  // get a list of unique layer pairs
  std::set<std::pair<int, int>> uniqueLayerPairs;
  for (auto layerPath: graphList) {
    for (int i = 0; i < layerPath.size() - 1; i++) {
      std::string thisLayerName = layerPath[i];
      std::string nextLayerName = layerPath[i+1];
      int indexOfThisLayer = layerName2Index[thisLayerName];
      int indexOfNextLayer = layerName2Index[nextLayerName];
      uniqueLayerPairs.insert(std::make_pair(indexOfThisLayer, indexOfNextLayer));
    }
  }

  CMGraph theGraph = CMGraph();

  // register layers with the CM graph
  // each layer needs to fill its vectors of inner/outer layers/layerpairs,
  // for the inner/outer layers this is done using the previously created maps
  // the layerpair vectors are filled from the set
  for (int i = 0; i < uniqueLayers.size(); ++i) {
    std::string layerName = *std::next(uniqueLayers.begin(), i);
    auto layer = tricktrack::CMLayer(layerName, numberOfHits);
    for (auto outerLayerIndex: outerLayersMap[layerName]) {
      layer.theOuterLayers.push_back(outerLayerIndex);
    }
    for (auto innerLayerIndex: innerLayersMap[layerName]) {
      layer.theInnerLayers.push_back(innerLayerIndex);
    }
    int layerPairCounter = 0;
    for (auto layerPairIndices: uniqueLayerPairs) {
      // if the layerName appears first in the pair, the pair is an outerlayerpair for this layer
      if (layerName == *std::next(uniqueLayers.begin(), layerPairIndices.first)) {
        layer.theOuterLayerPairs.push_back(layerPairCounter);
      }
      // if the layerName appears second in the pair, the pair is an innerlayerpair for this layer
      if (layerName == *std::next(uniqueLayers.begin(), layerPairIndices.second)) {
        layer.theInnerLayerPairs.push_back(layerPairCounter);
      }


      layerPairCounter++;
    }
    theGraph.theLayers.push_back(layer);
    if (std::find(uniqueRootLayers.begin(), uniqueRootLayers.end(), layerName) != uniqueRootLayers.end()) {
      theGraph.theRootLayers.push_back(i);
    }
  }

  // register layerPairs with the CMGraph
  for (auto layerPairIndices: uniqueLayerPairs) {
    auto layerpair = tricktrack::CMLayerPair(layerPairIndices.first, layerPairIndices.second);
    theGraph.theLayerPairs.push_back(layerpair);
  }


  return theGraph;
}

}  // namespace tricktrack



#endif /* TRICKTRACK_CMGRAPH_H */
