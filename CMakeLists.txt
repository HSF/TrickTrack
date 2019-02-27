# - Define the minimum CMake version
cmake_minimum_required(VERSION 3.2)
# - Call project() to setup system
# From CMake 3, we can set the project version easily in one go
project(tricktrack VERSION 1.0.7)

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

#--- Define the C++ Standard to use -------------------------------------------
set(CMAKE_CXX_STANDARD 14 CACHE STRING "")

#--- Declare options -----------------------------------------------------------
option(tricktrack_documentation "Create doxygen doc target." OFF)
option(tricktrack_python "Create python bindings for tricktrack" OFF)
option(tricktrack_logger "Use spdlog for logging" OFF)
option(tricktrack_logger_standalone "Use spdlog standalone (as opposed to in a framework" OFF)


#--- enable unit testing capabilities ------------------------------------------
include(CTest)

#--- enable CPack --------------------------------------------------------------
include(cmake/tricktrackCPack.cmake)

#--- add path to Find modules -------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#--- search for Eigen package --------------------------------------------------
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

#--- logger setup --------------------------------------------------------------
if (tricktrack_logger)
  find_package(spdlog REQUIRED)
  include_directories(${SPDLOG_INCLUDE_DIR})
  find_package(Threads REQUIRED)
  add_definitions(-DUSE_SPDLOG)
endif()

if (tricktrack_logger_standalone)
  add_definitions(-DUSE_SPDLOG_STANDALONE)
endif()


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

#--- add actual code -----------------------------------------------------------
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(profiling)
if (tricktrack_python) 
  add_subdirectory(python)
endif()

#--- create uninstall target ---------------------------------------------------
include(cmake/tricktrackUninstall.cmake)
