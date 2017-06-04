enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_path(CDDLIB_HEADER cdd.h HINTS /usr/include/cdd PATHS ENV PATH PATH_SUFFIXES ../include/cdd)
if(${CDDLIB_HEADER} STREQUAL "CDDLIB_HEADER-NOTFOUND")
    message(FATAL_ERROR "cdd headers have not been found !!!")
endif()
#CDDLIB_HEADER ends with the cdd subdirectory. we need one directory up
get_filename_component(CDDLIB_HEADER "${CDDLIB_HEADER}/.." ABSOLUTE)
find_library(CDDLIB_LIB NAMES libcdd.so)
if(${CDDLIB_LIB} STREQUAL "CDDLIB_LIB-NOTFOUND")
    message(FATAL_ERROR "cdd lib have not been found !!!")
endif()

add_definitions(-DBOOST_TEST_DYN_LINK)
include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CDDLIB_HEADER})

macro(addTest testName)
    add_executable(${testName} ${testName}.cpp)
    target_link_libraries(${testName} ${Boost_LIBRARIES} ${PROJECT_NAME} ${CDDLIB_LIB})
    add_test(${testName}Unit ${testName})
endmacro(addTest)

addTest(TestPolyhedron)