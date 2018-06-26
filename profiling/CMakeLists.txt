
include_directories(${CMAKE_SOURCE_DIR}/include)




add_executable(profiling_cm profiling_cm.cpp)

add_executable(profiling_fitter profiling_fitter.cpp)
include_directories( $ENV{EIGEN_INCLUDE_DIR})



