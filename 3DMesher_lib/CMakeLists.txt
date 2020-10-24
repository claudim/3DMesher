project(3DMesher)

set(HEADER_FILES
        Reader.h
        Block_maker.h
        Vertex_location_finder.h
        Grid_maker.h
        External_block_remover.h
        )

set(SOURCE_FILES
        Reader.cpp
        Block_maker.cpp
        Vertex_location_finder.cpp
        Grid_maker.cpp
        External_block_remover.cpp
        )

# You get to pick a type of library, STATIC, SHARED, or MODULE. If you leave this choice off, the value of BUILD_SHARED_LIBS will be used to pick between STATIC and SHARED.
#add_library(3DMesher_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_library(3DMesher_lib ${SOURCE_FILES} ${HEADER_FILES})