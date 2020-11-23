#include <iostream>
//#include "test_congif.h" //TODO da aggiungere
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

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

void bad_hex_finder(LCC_3 &lcc);

int main(int argc, char* argv[]) {
    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
    std::string name = "cube100x100rotated";
   // std::string name = "cube100x100axisAligned";
    //std::string name = "sphere";
    //std::string fileName = data_path + "/" + name + ".off";
    std::string fileName = data_path + "/" + name + ".stl";

    try {
        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        Polyhedron polyhedron = reader.read(fileName);

        Features_detector featuresDetector;
        featuresDetector.detect(polyhedron);

       // CGAL::draw(polyhedron);

        Grid_maker gridMaker = Grid_maker();
        LCC_3 hex_mesh = gridMaker.make(polyhedron);
        std::cout<<"fatto"<<std::endl;

        //detect the initial mesh
        Initial_mesh_maker<External_and_onBoundary_remover> initialMeshMaker;
        initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/4);


//        External_block_remover externalBlockRemover = External_block_remover();
//        externalBlockRemover.removeBlocks(hex_mesh, polyhedron);
//        std::cout<<"rimossi i blocchi esterni"<<std::endl;
//
//        OnBoundary_block_remover onBoundaryBlockRemover = OnBoundary_block_remover();
//       // onBoundaryBlockRemover.removeBlocks(hex_mesh, polyhedron);
//        onBoundaryBlockRemover.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/4);
//        std::cout<<"rimossi i blocchi sul boundary"<<std::endl;



        CGAL::draw(hex_mesh);

        //connect the initial mesh to the polyhedron boundary
        InitialMesh_boundary_connector initialMeshBoundaryConnector = InitialMesh_boundary_connector();
        initialMeshBoundaryConnector.connect(hex_mesh, polyhedron);
        std::cout<<"valido: " << hex_mesh.is_valid()<<std::endl;

       // CGAL::draw(hex_mesh);

        //output
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/SchneidersHexMeshOutput";
        std::string outputFileName = out_data_path + "/" + name + "3.mesh";
        std::ofstream medit_file(outputFileName);
        Writer writer;
        writer.output_to_medit(medit_file,hex_mesh);
        medit_file.close();

        //draw in cgal the final hex mesh
        //CGAL::draw(hex_mesh);
    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}