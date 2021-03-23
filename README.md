#3D Mesher 

A C++ implementation of full automatic tool for 3D Meshing.

3D Mesher can create a Tet-mesh or Hex-mesh using CGAL library.

## Getting Started

### Requirements

1. clang++ 10.0 or higher or an equivalent compiler (gcc/g++ 9.x or higher)
2. C++ 20
3. CMake 3.16 or newer
4. CGAL library 5.1 (https://www.cgal.org/releases.html)
5. Verdict library(https://gitlab.kitware.com/verdict/verdict/-/tree/master)
6. VTK library (https://gitlab.kitware.com/vtk/vtk.git)


### Installing
- From terminal, move to the 3DMesher directory

- Create a build folder
    `mkdir build`
    
- Navigate to the newly build folder  
    `cd build` 
    
- digit    
`cmake ..`

- digit
`make` or `make -j6`

 
### Usage

To use the executable:

-  Open terminal

-  Move to the build directory

-  Digit

    `./3DMesher path/to/the/STLfile/filename.stl  path/to/the/output/filename.vtk resolution`
    
    or 
    
    `./3DMesher path/to/the/STLfile/filename.stl  path/to/the/output/filename.mesh resolution`
    
    Example:
    
    `./3DMesher /Users/claudia/CLionProjects/3DMesher/DataInput/bolt.stl  /Users/claudia/CLionProjects/3DMesher/MeshOutput/bolt.mesh 8`
    
## Authors

 * Claudia Di Marco
 * Riccardo Mantini

