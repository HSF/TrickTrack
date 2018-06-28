mkdir build install || true
git submodule add https://github.com/pybind/pybind11 python/pybind11 || true
patch -p1 -t < python2.7.patch || true
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install -Dtricktrack_logger=ON -Dtricktrack_logger_standalone=ON -Dtricktrack_python=ON
make install -j 4
make test
cd ..



