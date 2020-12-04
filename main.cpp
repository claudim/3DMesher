#include <iostream>
#include "Block_maker.h"
#include <CGAL/draw_linear_cell_complex.h>
#include "STL_reader.h"
#include "OFF_Reader.h"
#include "Features_detector.h"
#include "Grid_maker.h"
#include "External_and_onBoundary_remover.h"
#include "Initial_mesh_maker.h"
#include "Hexahedron_fitter.h"
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
//    std::string name = "cube100x100rotated";
//    std::string fileName = data_path + "/" + name + ".stl";

    try {
        //lettura lancia errore

        typedef typename CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
        std::string fileName = data_path + "/cubeTest.off";
        OFF_Reader reader = OFF_Reader();
        Polyhedron polyhedron = reader.read(fileName);
        LCC lcc;
        Block_maker blockMaker;
        Intersecting_polyhedron_finder intersectingPolyhedronFinder;
        std::vector<Point> block_points;
        block_points.emplace_back(Point(2,2,2));
        block_points.emplace_back(Point(4,2,2));
        block_points.emplace_back(Point(4,4,2));
        block_points.emplace_back(Point(2,4,2));
        block_points.emplace_back(Point(2,4,4));
        block_points.emplace_back(Point(2,2,4));
        block_points.emplace_back(Point(1,3,5));
        block_points.emplace_back(Point(4,4,4));

        std::vector<Dart_handle> facets;
        Dart_handle intersecting_block = blockMaker.make_block(lcc, block_points);
        bool facets_intersection = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,intersecting_block, facets);
       std::cout<<facets_intersection <<std::endl;

        Hexahedron_fitter hexahedronFitter;
        hexahedronFitter.fix(lcc, intersecting_block, facets, polyhedron);

    }

    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
