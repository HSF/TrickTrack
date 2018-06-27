mkdir build install
git submodule add https://github.com/pybind/pybind11 python/pybind11
patch -p1 < python2.7.patch 
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install
make install -j 4
cd ..



