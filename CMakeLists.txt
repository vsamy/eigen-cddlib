cmake_minimum_required(VERSION 2.8)

include(cmake/base.cmake)
include(cmake/eigen.cmake)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")

set(PROJECT_NAME eigen-cddlib)
set(PROJECT_DESCRIPTION "Eigen C++ wrapper for using cddlib")
set(PROJECT_URL "https://github.com/vsamy/eigen-cddlib")

project(${PROJECT_NAME} CXX)

set(DOXYGEN_USE_MATHJAX "YES")

setup_project()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

SEARCH_FOR_EIGEN()

if(${_Eigen_VERSION} VERSION_LESS 3.2)
  message(FATAL_ERROR "Version of Eigen is inferior to 3.2: " ${_Eigen_VERSION})
endif()
if(${_Eigen_VERSION} VERSION_LESS 3.3)
  add_definitions(-DEIGEN_3_2_FOUND)
endif()

add_subdirectory(src)
add_subdirectory(tests)

setup_project_finalize()
