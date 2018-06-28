
from pyTT import TTReco
import trackml
from trackml.dataset import load_event, load_dataset
import sys
import numpy as np
import pandas as pd

filename = sys.argv[1]

hits, cells, particles, truth = load_event(filename)
hits = pd.merge(hits,truth,on='hit_id')
hits['phi'] = np.arctan2(hits['y'],hits['x'])
hits['r'] = np.sqrt(hits['y']*hits['y']+hits['x']*hits['x'])
hits['tpt'] = np.sqrt(hits['tpx']*hits['tpx']+hits['tpy']*hits['tpy'])
hits['index'] = hits.index
hits.sort_values(by=['phi'],inplace=True)
hl1 = hits.query('volume_id==8 & layer_id==2')
hl2 = hits.query('volume_id==8 & layer_id==4')
hl3 = hits.query('volume_id==8 & layer_id==6')
hl4 = hits.query('volume_id==8 & layer_id==8')

i1 = hl1.index

d1 =  [list(x) for x in hl1[["x", "y", "z", "particle_id", "index"]].values]
d2 =  [list(x) for x in hl2[["x", "y", "z", "particle_id", "index"]].values]
d3 =  [list(x) for x in hl3[["x", "y", "z", "particle_id", "index"]].values]


# xyz coordinates of hits on three seeding layers
layerPoints = [d1, d2, d3]
result = TTReco(theHits=layerPoints, thetaCut=0.002, phiCut=1., phiCut_d = 0.04, ptMin=0.8, regionOriginRadius=100, hardPtCut=0.0)
print len(result)
for indices in result[:4]:
  for i in indices:
    print hits.loc[i],
  print "\n\n\n"
