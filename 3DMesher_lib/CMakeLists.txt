project(3DMesher)

set(HEADER_FILES
        OFF_Reader.h
        STL_reader.h
        Features_detector.h
        Block_maker.h
        Vertex_location_finder.h
        Grid_maker.h
        Initial_mesh_maker.h
        External_and_onBoundary_remover.h
        External_block_remover.h
        Grid_boundary_connector.h
        OnBoundary_block_remover.h
        External_facet_finder.h
        More_external_block_finder.h
        Point_normal_finder.h
        PointNormal_boundary_intersectionPoint_finder.h
        InitialMesh_boundary_connector.h
        Writer.h
        Point_sorter.h
        Block_refiner.h
        Bad_hex_finder.h
        Intersecting_polyhedron_finder.h
        MyLCC.h
        L_facet_detector.h
        Volume_Validator.h
        Degenerate_element_finder.h
        VTK_manager.h
        STL_reader3.h
        HexMesh_from_TetMesh_maker.h
        UnivaqHexMeshAlgorithm.h
        UnivaqSplitFromTetAlgorithm.h
        DelaunayCGALTetMeshAlgorithm.h)

set(SOURCE_FILES
        OFF_Reader.cpp
        #STL_reader.cpp
        Features_detector.cpp
        Block_maker.cpp
        Vertex_location_finder.cpp
        Grid_maker.cpp
        External_and_onBoundary_remover.cpp
        External_block_remover.cpp
        Grid_boundary_connector.cpp
        OnBoundary_block_remover.cpp
        External_facet_finder.cpp
        More_external_block_finder.cpp
        PointNormal_boundary_intersectionPoint_finder.cpp
        InitialMesh_boundary_connector.cpp
        Writer.cpp
        Point_sorter.cpp
        Block_refiner.cpp
        Bad_hex_finder.cpp
        L_facet_detector.cpp
        VTK_manager.cpp
        STL_reader2.h
        HexMesh_from_TetMesh_maker.cpp
        UnivaqHexMeshAlgorithm.cpp
        UnivaqSplitFromTetAlgorithm.cpp
        DelaunayCGALTetMeshAlgorithm.cpp)

#include_directories(${PROJECT_SOURCE_DIR}/3DMesher_lib/3D_hex_mesh_algorithms)

# You get to pick a type of library, STATIC, SHARED, or MODULE. If you leave this choice off, the value of BUILD_SHARED_LIBS will be used to pick between STATIC and SHARED.
#add_library(3DMesher_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(3DMesher_lib ${SOURCE_FILES} ${HEADER_FILES})