cmake_minimum_required (VERSION 3.5)
project (projector)

include(ExternalProject)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

set(DOCOPT_ROOT ${PROJECT_SOURCE_DIR}/external/docopt)
set(DOCOPT_INCLUDE_DIRS ${DOCOPT_ROOT}/include/docopt)
set(DOCOPT_LIBRARIES ${DOCOPT_ROOT}/lib/libdocopt.a)
set(docopt_INSTALL_DIR "${DOCOPT_ROOT}")
set(docopt_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${docopt_INSTALL_DIR})

ExternalProject_Add(docopt
  PREFIX ${DOCOPT_ROOT}
  GIT_REPOSITORY https://github.com/docopt/docopt.cpp.git
  BINARY_DIR ${DOCOPT_ROOT}
  INSTALL_DIR ${DOCOPT_ROOT}
  CMAKE_ARGS ${docopt_CMAKE_ARGS}
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  LOG_INSTALL ON
)
add_library(libdocopt STATIC IMPORTED)
set_target_properties(libdocopt PROPERTIES IMPORTED_LOCATION ${DOCOPT_LIBRARIES})
add_dependencies(libdocopt docopt)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${DOCOPT_INCLUDE_DIRS})

file(GLOB projector_src
  "*.h"
  "*.cpp"
  )

set( Boost_USE_STATIC_LIBS OFF )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME OFF )



find_package(Boost COMPONENTS filesystem exception REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
add_executable(projector ${projector_src})
target_link_libraries(projector ${Boost_LIBRARIES})
target_link_libraries(projector libdocopt)
