cmake_minimum_required(VERSION 3.16)
project(3DMesher VERSION 1.0
        DESCRIPTION "A 3D Mesher project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

#set(CMAKE_BUILD_TYPE Release) #the debugger does not work

# rows 9 to 15 and 24 are needed for draw an object in CGAL
#find the package CGAL with the component Qt5
find_package(CGAL COMPONENTS Qt5)

#Set the CGAL_USE_BASIC_VIEWER compiler flag
if(CGAL_Qt5_FOUND)
    add_definitions(-DCGAL_USE_BASIC_VIEWER -DQT_NO_KEYWORDS)
endif()

# Find CGAL
find_package(CGAL REQUIRED COMPONENTS Core) # If the dependency is required, use REQUIRED option - if it's not found CMake will issue an error
include( ${CGAL_USE_FILE} )

set(SOURCE_FILES main.cpp)
add_executable(3DMesher ${SOURCE_FILES})

include_directories(3DMesher_lib )
add_subdirectory(3DMesher_lib )

# Link 3DMesher_lib with 3DMesher
target_link_libraries(3DMesher PUBLIC 3DMesher_lib)
target_link_libraries(3DMesher PUBLIC Evaluator_lib)

# Link CGAL_Qt5 with your program
target_link_libraries(3DMesher PUBLIC CGAL::CGAL_Qt5)

add_subdirectory(Catch_tests )
add_subdirectory(Evaluator_lib )