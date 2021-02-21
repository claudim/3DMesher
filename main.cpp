#include <iostream>
#include "STL_reader3.h"
//#include "Block_maker.h"
//#include <CGAL/draw_linear_cell_complex.h>
//#include "STL_reader.h"
//#include "OFF_Reader.h"
//#include "Features_detector.h"
//#include "Grid_maker.h"
//#include "External_and_onBoundary_remover.h"
//#include "Initial_mesh_maker.h"
//#include "Hexahedron_fitter.h"
////#include "External_block_remover.h"
////#include "OnBoundary_block_remover.h"
//#include "External_facet_finder.h"
//#include "InitialMesh_boundary_connector.h"
//#include "Block_refiner.h"
//#include <verdict.h> //to include verdict library
//#include <CGAL/draw_linear_cell_complex.h>
//#include <CGAL/draw_polyhedron.h>
//#include "Writer.h"
//#include "PointNormal_boundary_intersectionPoint_finder.h"
//
//#include <CGAL/Qt/Basic_viewer_qt.h>
//#include <qapplication.h>

int main(int argc, char* argv[]) {
    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
//    std::string name = "cube100x100rotated";
//    std::string fileName = data_path + "/" + name + ".stl";

    try {
        //lettura lancia errore

//        Block_maker blockMaker;
//        LCC_3 hex_mesh;
//        FT lg = 1;
//        blockMaker.make_cube(hex_mesh, Point(1,1,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(2,1,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(3,1,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(4,1,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(5,1,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(1,2,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(2,2,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(3,2,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(4,2,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(5,2,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(1,3,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(2,3,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(3,3,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(4,3,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(5,3,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(1,1,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(2,1,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(3,1,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(4,1,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(5,1,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(1,2,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(5,2,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(1,3,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(2,3,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(3,3,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(4,3,2), lg);
//        blockMaker.make_cube(hex_mesh, Point(5,3,2), lg);
//        hex_mesh.sew3_same_facets();
//
//        CGAL::draw(hex_mesh);

        Polyhedron polyhedron;
        std::string inputPathFileName = argv[1]; // filename is path to filename with extension
        STL_reader3 reader;
        polyhedron = reader.read(inputPathFileName);
    }

    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
