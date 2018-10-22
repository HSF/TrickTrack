
include_directories(${CMAKE_SOURCE_DIR}/include)

#file(GLOB sources *.cpp)
file(GLOB headers  ${CMAKE_SOURCE_DIR}/include/tricktrack/*.h)

add_library(tricktrack INTERFACE)


#target_link_libraries(...)
#install(TARGETS tricktrack DESTINATION lib)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/tricktrack DESTINATION include)

