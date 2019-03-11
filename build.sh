mkdir build install integration || true
#git submodule add https://github.com/pybind/pybind11 python/pybind11 || true
#cd python
#patch -p1 -t < python2.7.patch || true
#cd ../build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install  -Dtricktrack_python=OFF
make install -j 4
make test
cd ..
export CMAKE_PREFIX_PATH=$CMAKE_PREFIX_PATH:$PWD/install
cd integration
cmake ../tests/integration
make -j 4
make test
cd ..



