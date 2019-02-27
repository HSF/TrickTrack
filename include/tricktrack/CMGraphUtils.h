#ifndef TRICKTRACK_CMGRAPHUTILS_H
#define TRICKTRACK_CMGRAPHUTILS_H

#include "CMGraph.h"

namespace tricktrack {

/** createGraph
 *
 *  utility function to facilitate filling the CMGraph
 */
CMGraph createGraph(std::vector<std::vector<std::string>> graphList, std::size_t numberOfHits=1000000);


}  // namespace tricktrack



#endif
