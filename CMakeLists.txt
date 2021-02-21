cmake_minimum_required(VERSION 3.16)
project(3DMesher VERSION 1.0
        DESCRIPTION "A 3D Mesher project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

# start Doxygen
# look for Doxygen package
find_package(Doxygen)

if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs_doxygen/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
    add_custom_target( docs
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
# end Doxygen



#set(VTK_DIR "/usr/local/include/vtk-9.0")

#set(VTK_INCLUDE_DIRS "/usr/local/include/vtk-9.0")
#set(VTK_LIBRARY_DIRS "/usr/local/lib")
find_package(VTK REQUIRED) #all vtk modules
#find_package(VTK REQUIRED COMPONENTS
#        CommonCore
#        CommonDataModel
#        FiltersCore
#        FiltersSources
#        IOLegacy
#        IOXML
#        )

IF(VTK_FOUND)
    message("found VTK. Version:" ${VTK_VERSION}. VTK_DIR: ${VTK_DIR}. VTK_LIBRARIES: ${VTK_USE_FILE}.
            VTK_LIBRARY_DIRS: ${VTK_LIBRARY_DIRS})

    IF (VTK_VERSION VERSION_LESS "8.90.0")
        # old system
        include(${VTK_USE_FILE})
    ENDIF (VTK_VERSION VERSION_LESS "8.90.0")

ELSE(VTK_NOT_FOUND)
    MESSAGE(FATAL_ERROR
            "Cannot build the executable without VTK. Please set the VTK_DIR")
    message("${VTK_NOT_FOUND_MESSAGE}")

ENDIF(VTK_FOUND)



#set(CMAKE_BUILD_TYPE Release) #the debugger does not work

# --------------------------------------------------------------------------- #
# CGAL
# --------------------------------------------------------------------------- #
# rows 14 to 25 and 43 are needed for draw an object in CGAL
#find the package CGAL with the component Qt5
find_package(CGAL COMPONENTS Qt5)

#Set the CGAL_USE_BASIC_VIEWER compiler flag
if(CGAL_Qt5_FOUND)
    add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
endif()

# Find CGAL
find_package(CGAL REQUIRED COMPONENTS Core) # If the dependency is required, use REQUIRED option - if it's not found CMake will issue an error
include( ${CGAL_USE_FILE} )

find_package(verdict)

# --------------------------------------------------------------------------- #
# GMSH
# --------------------------------------------------------------------------- #
find_library(GMSH_LIB gmsh)
if(NOT GMSH_LIB)
    message(FATAL_ERROR "Could not find libgmsh")
endif()

find_path(GMSH_INC gmsh.h)
if(NOT GMSH_INC)
    message(FATAL_ERROR "Could not find gmsh.h")
endif()

# --------------------------------------------------------------------------- #
# SMESH
# --------------------------------------------------------------------------- #
#find_package(SMESH REQUIRED)


##vtk
#find_package(VTK COMPONENTS
#        vtkCommonColor
#        vtkCommonCore
#        vtkCommonDataModel
#        vtkFiltersCore
#        vtkFiltersSources
#        vtkIOLegacy
#        vtkIOXML
#        vtkInteractionStyle
#        )
#if (NOT VTK_FOUND)
#    message("${VTK_NOT_FOUND_MESSAGE}")
#    # return ()
#endif()



#set(SOURCE_FILES main.cpp)
#set(SOURCE_FILES mainWriteStatistics.cpp)
#set(SOURCE_FILES SchneidersHexMeshMain.cpp)
#set(SOURCE_FILES DelaunayTetMeshMain.cpp)
#set(SOURCE_FILES UnivaqHexMeshMain.cpp)
#set(SOURCE_FILES UnivaqHexMeshMain2.cpp)
#set(SOURCE_FILES main_gmsh.cpp)
#set(SOURCE_FILES main_getBBox.cpp)
set(SOURCE_FILES DelaunayTetMeshMain_Hex.cpp)
#set(SOURCE_FILES Get_Resolution_and_dimension.cpp)
add_executable(3DMesher ${SOURCE_FILES})

include_directories(3DMesher_lib )
add_subdirectory(3DMesher_lib )


##Link VTK library
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
    # old system
    target_link_libraries(3DMesher PUBLIC ${VTK_LIBRARIES})
else ()
    # include all components
    target_link_libraries(3DMesher PUBLIC ${VTK_LIBRARIES})
    # vtk_module_autoinit is needed
    vtk_module_autoinit(
            TARGETS 3DMesher
            MODULES ${VTK_LIBRARIES}
    )
endif ()


# Link 3DMesher_lib with 3DMesher
target_link_libraries(3DMesher PUBLIC 3DMesher_lib)

# Link CGAL_Qt5 with your program
#target_link_libraries(3DMesher PUBLIC CGAL::CGAL_Qt5)

target_link_libraries(3DMesher_lib PUBLIC Verdict::verdict)

target_link_libraries(3DMesher PUBLIC ${GMSH_LIB} )

#target_link_libraries(3DMesher  PUBLIC ${SMESH_LIBRARIES})
message(cia0 ${VTK_LIBRARIES})



add_subdirectory(Catch_tests)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include/vtk-9.0")

#for the documentation
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)