#on lxplus / machines with cvmfs
source /cvmfs/fcc.cern.ch/sw/views/releases/0.9.1/x86_64-slc6-gcc62-opt/setup.sh
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/install/lib/:$PWD/install/lib64
export PYTHONPATH=$PYTHONPATH:$PWD/install/lib/:$PWD/install/lib64
