enable_testing()

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

add_executable(TestPolyhedron TestPolyhedron.cpp)
target_link_libraries(TestPolyhedron PRIVATE Boost::unit_test_framework ${PROJECT_NAME})
add_test(TestPolyhedronUnit TestPolyhedron)
