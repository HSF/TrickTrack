add_subdirectory(pybind11)
include_directories(${CMAKE_SOURCE_DIR}/include)
pybind11_add_module(pyTT pyTT.cpp)
install(TARGETS pyTT DESTINATION ${CMAKE_INSTALL_LIBDIR})
