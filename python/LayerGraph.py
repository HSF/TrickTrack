
import trackml
from trackml.dataset import load_event, load_dataset
import sys
import numpy as np
import pandas as pd
import sys

filename = sys.argv[1]

hits, cells, particles, truth = load_event(filename)
#print event_id, len(hits)
hits = pd.merge(hits,truth,on='hit_id')
hits['phi'] = np.arctan2(hits['y'],hits['x'])
hits['r'] = np.sqrt(hits['y']*hits['y']+hits['x']*hits['x'])
hits['dist'] = np.sqrt(hits['y']*hits['y']+hits['x']*hits['x'] + hits["z"]*hits["z"])
hits['tpt'] = np.sqrt(hits['tpx']*hits['tpx']+hits['tpy']*hits['tpy'])
hits['uvol'] = 100 * hits["volume_id"] + hits["layer_id"]


layer_neighbors = {}
track_sizes  = {}
for u in hits["particle_id"].unique()[1:]:
  sel = hits["particle_id"] == u
  sel_hits = hits[sel].sort_values(by=["dist"])
  track_sizes[u] = sel.sum()
  volids = sel_hits["uvol"].values
  for _id1, _id2 in zip(volids, volids[1:]):
    layer_neighbors[(_id1, _id2)] = layer_neighbors.get((_id1, _id2), 0) + 1


#print track_sizes
print np.mean(track_sizes.values())
print layer_neighbors

import  networkx as nx  
import matplotlib
matplotlib.use("qt5agg")
import matplotlib.pyplot as plt

G=nx.Graph()


for key in layer_neighbors:
  G.add_edge(*key, weight=layer_neighbors[key])


detector = pd.read_csv(sys.argv[2])
detector['r'] = np.sqrt(detector['cy']*detector['cy']+detector['cx']*detector['cx'])
layer_positions = {}

for n in G.nodes():
  print n
  seldet = detector[detector["volume_id"] == int(n/100.)][detector["layer_id"] == int(n%100)]
  seldet = seldet[seldet["module_id"] == int(seldet["module_id"].max() / 2) ]
  layer_positions[n] = seldet[["cz", "r"]].values[0]


weights = [np.log(G[u][v]['weight']) for u,v in G.edges()]


print weights
print G.number_of_edges(), G.number_of_nodes()
nx.draw(G,layer_positions, width = weights, node_size=3, alpha=0.5)
plt.savefig("true.png")


layer_neighbors = {}
track_sizes  = {}
for u in hits["particle_id"].unique()[:1]:
  sel = hits["particle_id"] == u
  sel_hits = hits[sel].sort_values(by=["dist"])
  track_sizes[u] = sel.sum()
  volids = sel_hits["uvol"].values
  for _id1, _id2 in zip(volids, volids[1:]):
    layer_neighbors[(_id1, _id2)] = layer_neighbors.get((_id1, _id2), 0) + 1


#print track_sizes
print np.mean(track_sizes.values())
print layer_neighbors

import  networkx as nx  
import matplotlib
matplotlib.use("qt5agg")
import matplotlib.pyplot as plt

G=nx.Graph()


for key in layer_neighbors:
  G.add_edge(*key, weight=layer_neighbors[key])


detector = pd.read_csv("detectors.csv")
detector['r'] = np.sqrt(detector['cy']*detector['cy']+detector['cx']*detector['cx'])
layer_positions = {}

for n in G.nodes():
  print n
  seldet = detector[detector["volume_id"] == int(n/100.)][detector["layer_id"] == int(n%100)]
  seldet = seldet[seldet["module_id"] == int(seldet["module_id"].max() / 2) ]
  layer_positions[n] = seldet[["cz", "r"]].values[0]


weights = [np.log(G[u][v]['weight']) for u,v in G.edges()]


print weights
print G.number_of_edges(), G.number_of_nodes()
nx.draw(G,layer_positions, width = weights, node_size=3, alpha=0.5)
plt.savefig("false.png")
