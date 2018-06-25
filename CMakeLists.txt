# - Define the minimum CMake version
cmake_minimum_required(VERSION 3.2)
# - Call project() to setup system
# From CMake 3, we can set the project version easily in one go
project(tricktrack VERSION 0.1.0)

#--- Define basic build settings -----------------------------------------------
# - Use GNU-style hierarchy for installing build products
include(GNUInstallDirs)

# - Define a default build type when using a single-mode tool like make/ninja
# If you're using a build tool that supports multiple modes (Visual Studio,
# Xcode), this setting has no effect.
if(NOT CMAKE_CONFIGURATION_TYPES)
  if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo
      CACHE STRING "Choose the type of build, options are: None Release MinSizeRel Debug RelWithDebInfo"
      FORCE
      )
  else()
    set(CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}"
      CACHE STRING "Choose the type of build, options are: None Release MinSizeRel Debug RelWithDebInfo"
      FORCE
      )
  endif()
endif()

# - Define the C++ Standard to use (Simplest Possible)
# This will add any compiler flags needed to compile against the required standard
# without any vendor extensions
# NOTE: It *does not* guarantee that the compiler in use supports the complete
# standard. Nor does it inform clients of the project what standard was used.
# Both of these issues can be resolved using CMake's compile features, see
#
# - https://cmake.org/cmake/help/v3.3/manual/cmake-compile-features.7.html
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#--- Declare options -----------------------------------------------------------
option(tricktrack_documentation "Whether or not to create doxygen doc target.")

#--- enable unit testing capabilities ------------------------------------------
include(CTest)

#--- enable CPack --------------------------------------------------------------
include(cmake/tricktrackCPack.cmake)

#--- add path to Find modules -------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#--- search for Eigen package --------------------------------------------------
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

#--- target for Doxygen documentation ------------------------------------------
if(tricktrack_documentation)
  include(cmake/tricktrackDoxygen.cmake)
endif()

#--- add version files ---------------------------------------------------------
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tricktrackVersion.h
               ${CMAKE_CURRENT_BINARY_DIR}/tricktrackVersion.h )
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tricktrackVersion.h
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tricktrack )

#--- add CMake infrastructure --------------------------------------------------
include(cmake/tricktrackCreateConfig.cmake)

#--- add license files ---------------------------------------------------------
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE
              ${CMAKE_CURRENT_SOURCE_DIR}/NOTICE
              DESTINATION ${CMAKE_INSTALL_DOCDIR})

add_subdirectory(tests)
add_subdirectory(src)
add_subdirectory(profiling)
add_subdirectory(python)

#--- create uninstall target ---------------------------------------------------
include(cmake/tricktrackUninstall.cmake)
