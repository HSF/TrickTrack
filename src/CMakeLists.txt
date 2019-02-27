


file(GLOB sources tricktrack/*.cpp)
file(GLOB headers  ${CMAKE_SOURCE_DIR}/include/tricktrack/*.h)

add_library(tricktrack SHARED ${sources})
target_include_directories(tricktrack PUBLIC ${CMAKE_SOURCE_DIR}/include)

set_target_properties(tricktrack PROPERTIES PUBLIC_HEADER "${headers}")
INSTALL(TARGETS tricktrack
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/tricktrack
)


