# TrickTrack 
[![Build Status](https://travis-ci.org/HSF/TrickTrack.svg?branch=master)](https://travis-ci.org/HSF/TrickTrack)

**TrickTrack** aims to encapsulate the Cellular-Automaton based seeding code used in CMSSW in a standalone library. The original sources in CMSSW are listed in `doc/CMSSW_sources.md`. 

## Building the project

    mkdir build
    cd build
    export EIGEN_INCLUDE_DIR=<eigen installation dir>
    cmake -DCMAKE_INSTALL_PREFIX=<installdir> [-Dtricktrack_documentation=ON] <path to sources>
    make -j<number of cores on your machine>
    make install

The `tricktrack_documentation` variable is optional, and should be passed if you wish to
build the Doxygen based API documentation. Please note that this requires an existing
installation of [Doxygen](http://www.doxygen.org/index.html). If CMake cannot locate
Doxygen, its install location should be added into `CMAKE_PREFIX_PATH`.
For further details please have a look at [the CMake tutorial](http://www.cmake.org/cmake-tutorial/).

TrickTrack supports the `spdlog` library for logging. Use `tricktrack_logger` cmake option to enable spd logging, and the `tricktrack_logger_standalone` option if there is no framework that creates the logging object.

A high level interface with optional python bindings can be created with the option `tricktrack_python`.

## Building the documentation

The documentation of the project is based on doxygen. To build the documentation,
the project must have been configured with `tricktrack_documentation` enabled, as
described earlier. It can then be built and installed:

    make doc
    make install

By default, this installs the documentation into `<installdir>/share/doc/tricktrack/share/doc`.

## Creating a package with CPack

A cpack based package can be created by invoking

    make package

## Running the tests

To run the tests of the project, first build it and then invoke

    make test

## Inclusion into other projects

TrckTrack is distributed under the Apache License 2.0 (see `LICENSE`). If you want to build your own project against tricktrack, CMake may be the best option for you. Just add its install location (the folder containing `cmake/tricktrackConfig.cmake` to _CMAKE_PREFIX_PATH_ and call _find_package(tricktrack)_ within your CMakeLists.txt.

A `pkg-config` `.pc` file is also installed if you do not use CMake.
Simply add the location of the `.pc` file (nominally `<installdir>/lib/pkgconfig`) and run `pkg-config --cflags --libs tricktrack` to get the
include paths and libraries needed to compile and link to tricktrack.

