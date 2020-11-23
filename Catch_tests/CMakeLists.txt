set(SOURCE_TESTS_FILES
        OFFReader_tests.cpp
        STLReader_tests.cpp
        Features_detector_tests.cpp
        Block_maker_tests.cpp
        Vertex_location_finder_tests.cpp
        Grid_maker_tests.cpp
        External_block_remover_tests.cpp
        Grid_boundary_connector_tests.cpp
        OnBoundary_block_remover_tests.cpp
        External_facet_finder_tests.cpp
        PointNormal_boundary_intersectionPoint_finder_tests.cpp
        InitialMesh_boundary_connector_tests.cpp
        Point_sorter_tests.cpp
        Block_refiner_tests.cpp
        Bad_hex_finder_tests.cpp
        )

set(HEADER_TESTS_FILES
        "${CMAKE_CURRENT_BINARY_DIR}/test_config.h")


set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/Catch_tests/Data" TEST_DATA_DIR)
configure_file("test_config.h.in" "test_config.h" @ONLY)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(Catch_tests_run ${SOURCE_TESTS_FILES}  ${HEADER_TESTS_FILES})
target_link_libraries(Catch_tests_run 3DMesher_lib)

