cmake_minimum_required(VERSION 3.1.3)

include(cmake/base.cmake)

set(PROJECT_NAME eigen-cdd)
set(PROJECT_DESCRIPTION "Eigen C++ wrapper for using cddlib")
set(PROJECT_URL "https://github.com/vsamy/eigen-cddlib")
set(PROJECT_DEBUG_POSTFIX "_d")
set(INSTALL_GENERATED_HEADERS OFF CACHE BOOL "Generate and install standard headers")

set(DOXYGEN_USE_MATHJAX "YES")

option(BUILD_TESTING "Build unit tests." ON)
option(BUILD_TEST_STATIC_BOOST "Build unit tests with static boost libraries" OFF)

setup_project()

set(Eigen_REQUIRED "eigen3 >= 3.2")
add_project_dependency(Eigen3 REQUIRED)
add_project_dependency(cdd REQUIRED)

add_subdirectory(src)

if(${BUILD_TESTING})
    add_subdirectory(tests)
endif()

setup_project_finalize()
setup_project_package_finalize()
