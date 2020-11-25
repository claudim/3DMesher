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
//#include <CGAL/draw_polyhedron.h>
#include "Writer.h"
#include "PointNormal_boundary_intersectionPoint_finder.h"

int main(int argc, char* argv[]) {
    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
    std::string name = "cube100x100rotated";
    std::string fileName = data_path + "/" + name + ".stl";

    try {
        //lettura lancia errore
        STL_reader reader;
        Polyhedron polyhedron = reader.read(fileName);

        Features_detector featuresDetector;
        std::vector<Point> featuresPoints;
        featuresDetector.detect(polyhedron, featuresPoints);


        Grid_maker gridMaker = Grid_maker();
        LCC_3 hex_mesh = gridMaker.make(polyhedron);

        //detect the initial mesh
        Initial_mesh_maker<External_and_onBoundary_remover> initialMeshMaker;
        //initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/4);
        initialMeshMaker.removeBlocks(hex_mesh, polyhedron);
        initialMeshMaker.refine(hex_mesh);

        //connect the initial mesh to the polyhedron boundary
        InitialMesh_boundary_connector initialMeshBoundaryConnector = InitialMesh_boundary_connector();
        initialMeshBoundaryConnector.connect(hex_mesh, polyhedron);


    }

    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
