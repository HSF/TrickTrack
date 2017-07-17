# - Use CMake's module to help generating relocatable config files
include(CMakePackageConfigHelpers)

# - Versioning
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/tricktrackConfigVersion.cmake
  VERSION ${tricktrack_VERSION}
  COMPATIBILITY SameMajorVersion)

# - Install time config and target files
configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/tricktrackConfig.cmake.in
  "${PROJECT_BINARY_DIR}/tricktrackConfig.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/../share/cmake/tricktrack"
  PATH_VARS
    CMAKE_INSTALL_BINDIR
    CMAKE_INSTALL_INCLUDEDIR
    CMAKE_INSTALL_LIBDIR
  )

# - install and export
install(FILES
  "${PROJECT_BINARY_DIR}/tricktrackConfigVersion.cmake"
  "${PROJECT_BINARY_DIR}/tricktrackConfig.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/../share/cmake/tricktrack"
  )


#install( 
#  EXPORT tricktrackTargets
#  NAMESPACE tricktrack::
#  DESTINATION "${CMAKE_INSTALL_LIBDIR}/../share/cmake/tricktrack"
#  )

