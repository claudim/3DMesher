#include <iostream>
#include "Block_maker.h"
#include <CGAL/draw_linear_cell_complex.h>
#include "STL_reader.h"
#include "OFF_Reader.h"
#include "Features_detector.h"
#include "Grid_maker.h"
#include "External_and_onBoundary_remover.h"
#include "Initial_mesh_maker.h"
//#include "External_block_remover.h"
//#include "OnBoundary_block_remover.h"
#include "External_facet_finder.h"
#include "InitialMesh_boundary_connector.h"
#include "Block_refiner.h"
#include <verdict.h> //to include verdict library
#include <CGAL/draw_linear_cell_complex.h>
#include <CGAL/draw_polyhedron.h>
#include "Writer.h"
#include "PointNormal_boundary_intersectionPoint_finder.h"

#include <CGAL/Qt/Basic_viewer_qt.h>
#include <qapplication.h>

int main(int argc, char* argv[]) {
    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
    std::string name = "cube100x100rotated";
    std::string fileName = data_path + "/" + name + ".stl";

    try {
        //lettura lancia errore
//        STL_reader reader;
//        Polyhedron polyhedron = reader.read(fileName);
//
//        Features_detector featuresDetector;
//        std::vector<Point> featuresPoints;
//        featuresDetector.detect(polyhedron, featuresPoints);
//
//
//        Grid_maker gridMaker = Grid_maker();
//        LCC_3 hex_mesh = gridMaker.make(polyhedron);
//
//        //detect the initial mesh
//        Initial_mesh_maker<External_and_onBoundary_remover> initialMeshMaker;
//        //initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/4);
//        initialMeshMaker.removeBlocks(hex_mesh, polyhedron);
//        initialMeshMaker.refine(hex_mesh);
//
//        //connect the initial mesh to the polyhedron boundary
//        InitialMesh_boundary_connector initialMeshBoundaryConnector = InitialMesh_boundary_connector();
//        initialMeshBoundaryConnector.connect(hex_mesh, polyhedron);

        Point internalBlockBasePoint1 = Point(1, 1, 1);
        Point internalBlockBasePoint2 = Point(2, 1, 1);
        Point internalBlockBasePoint3 = Point(3, 1, 1);

        Point internalBlockBasePoint4 = Point(1, 2, 1);
        Point internalBlockBasePoint5 = Point(2, 2, 1);
        Point internalBlockBasePoint6 = Point(3, 2, 1);
        Point internalBlockBasePoint7 = Point(1, 3, 1);
        Point internalBlockBasePoint8 = Point(2, 3, 1);
        Point internalBlockBasePoint9 = Point(3, 3, 1);

        Point internalBlockBasePoint10 = Point(1, 2, 2);
        Point internalBlockBasePoint11 = Point(2, 2, 2);
        Point internalBlockBasePoint12 = Point(1, 3, 2);
        Point internalBlockBasePoint13 = Point(2, 3, 2);
        Point internalBlockBasePoint14 = Point(1, 2, 3);
        Point internalBlockBasePoint15 = Point(2, 2, 3);
        Point internalBlockBasePoint16 = Point(1, 3, 3);
        Point internalBlockBasePoint17 = Point(2, 3, 3);

        FT internalBlockLg = 1;
        LCC_3 lcc;
        Block_maker blockMaker = Block_maker();
        blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint5, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint6, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint7, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint8, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint9, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint10, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint11, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint12, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint13, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint14, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint15, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint16, internalBlockLg);
        blockMaker.make_cube(lcc, internalBlockBasePoint17, internalBlockLg);

        lcc.sew3_same_facets();
        //CGAL::draw(lcc);

        Polyhedron p;


    }

    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
