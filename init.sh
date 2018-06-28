#on lxplus / machines with cvmfs
source /cvmfs/sft.cern.ch/lcg/views/LCG_93/x86_64-slc6-gcc62-opt/setup.sh
# setup default paths for python bindings
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/install/lib/:$PWD/install/lib64
export PYTHONPATH=$PYTHONPATH:$PWD/install/lib/:$PWD/install/lib64
