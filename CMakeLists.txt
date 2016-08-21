cmake_minimum_required (VERSION 2.6)
project (projector)

find_program( MEMORYCHECK_COMMAND valgrind )

set( CMAKE_BUILD_TYPE debug)
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set( MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full" )

include_directories("${PROJECT_BINARY_DIR}")
file(GLOB projector_src
  "*.h"
  "*.cpp"
)

add_executable(projector ${projector_src})
