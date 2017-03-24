set(SOURCES Polyhedron.cpp)
set(HEADERS Polyhedron.h typedefs.h)

find_path(CDDLIB_HEADER cdd.h HINTS /usr/include/cdd)
if(${CDDLIB_HEADER} STREQUAL "CDDLIB_HEADER-NOTFOUND")
    message(FATAL_ERROR "cdd headers have not been found !!!")
endif()
find_library(CDDLIB_LIB NAMES libcdd.so)
if(${CDDLIB_LIB} STREQUAL "CDDLIB_LIB-NOTFOUND")
    message(FATAL_ERROR "cdd lib have not been found !!!")
endif()

include_directories(${CDDLIB_HEADER})
add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${CDDLIB_LIB})

set(INSTALL_PATH include/${PROJECT_NAME})
install(FILES ${HEADERS} DESTINATION ${INSTALL_PATH})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
