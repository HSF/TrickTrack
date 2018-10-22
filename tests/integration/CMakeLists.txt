
cmake_minimum_required(VERSION 3.5)

find_package(tricktrack)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${tricktrack_INCLUDE_DIR})

include(CTest)

set (TT_TESTS
      test_integration)

foreach (test ${TT_TESTS})
  add_executable(${test} ${test}.cpp)
  add_test(NAME ${test} COMMAND ${test})
endforeach()
