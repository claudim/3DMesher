project(3DMesher)

set(HEADER_FILES
        OFF_Reader.h
        STL_reader.h
        Features_detector.h
        Block_maker.h
        Vertex_location_finder.h
        Grid_maker.h
        External_block_remover.h
        Grid_boundary_connector.h
        OnBoundary_block_remover.h
        External_facet_finder.h
        PointNormal_boundary_intersectionPoint_finder.h
        InitialMesh_boundary_connector.h
        Writer.h
        Point_sorter.h
        Block_refiner.h
        Bad_hex_finder.h
        )

set(SOURCE_FILES
        OFF_Reader.cpp
        #STL_reader.cpp
        Features_detector.cpp
        Block_maker.cpp
        Vertex_location_finder.cpp
        Grid_maker.cpp
        External_block_remover.cpp
        Grid_boundary_connector.cpp
        OnBoundary_block_remover.cpp
        External_facet_finder.cpp
        PointNormal_boundary_intersectionPoint_finder.cpp
        InitialMesh_boundary_connector.cpp
        Writer.cpp
        Point_sorter.cpp
        Block_refiner.cpp
        Bad_hex_finder.cpp
        )

# You get to pick a type of library, STATIC, SHARED, or MODULE. If you leave this choice off, the value of BUILD_SHARED_LIBS will be used to pick between STATIC and SHARED.
#add_library(3DMesher_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(3DMesher_lib ${SOURCE_FILES} ${HEADER_FILES})