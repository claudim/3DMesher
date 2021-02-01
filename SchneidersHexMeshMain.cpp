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
//#include <CGAL/draw_linear_cell_complex.h>
#include "Volume_Validator.h"
//#include <CGAL/draw_polyhedron.h>
#include "Writer.h"
#include "VTK_manager.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

void bad_hex_finder(LCC_3 &lcc);

int main(int argc, char* argv[]) {
    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
   // const std::string data_path = "/home/claudia/CLionProjects/3DMesher/DataInput";
    // std::string name = "bolt";
    //std::string name = "bunny";
    //std::string name = "ellipse";
    //std::string name = "cube100x100axisAligned";
    //std::string name = "cube100x100rotated";
    std::string name = "sphere";
    //std::string name = "rotatedTrapezoid";

    //std::string name = "sphere";
    //std::string fileName = data_path + "/" + name + ".off";
    std::string fileName = data_path + "/" + name + ".stl";

    try {
        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        Polyhedron polyhedron = reader.read(fileName);

//        Features_detector featuresDetector;
//        std::vector<Point> featuresPoints;
//        featuresDetector.detect(polyhedron, featuresPoints);

       // CGAL::draw(polyhedron);

        Grid_maker gridMaker = Grid_maker();
        LCC_3 hex_mesh = gridMaker.make(polyhedron);
        std::cout<<"fatto"<<std::endl;

        auto start = std::chrono::high_resolution_clock::now();


        //detect the initial mesh
//        Initial_mesh_maker<External_and_onBoundary_remover> initialMeshMaker;
//        initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension() * 0.55);
        External_and_onBoundary_remover initialMeshMaker;
       // initialMeshMaker.setBlockDimension(gridMaker.getGridDimension());
        initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension() * 0.55);
        //initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()* 3/5);
        //initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()* 2/3);
       // initialMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/2);
        //initialMeshMaker.removeBlocks(hex_mesh, polyhedron);

        auto stop = std::chrono::high_resolution_clock::now();
        // Get duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "Time taken by remove blocks function is : "
                  << duration.count() << " microseconds" << std::endl;


        auto start_connect = std::chrono::high_resolution_clock::now();

//        CGAL::draw(hex_mesh);
//        //connect the initial mesh to the polyhedron boundary
        InitialMesh_boundary_connector initialMeshBoundaryConnector = InitialMesh_boundary_connector();
        initialMeshBoundaryConnector.connect(hex_mesh, polyhedron);
        std::cout<<"valido: " << hex_mesh.is_valid()<<std::endl;
//
        auto stop_connect = std::chrono::high_resolution_clock::now();
        // Get duration
        auto duration_connect = std::chrono::duration_cast<std::chrono::microseconds>(stop_connect - start_connect);

        std::cout << "Time taken by connect function is : "
                  << duration_connect.count() << " microseconds" << std::endl;

//        Block_refiner blockRefiner;
//        blockRefiner.refineBlocks(hex_mesh, featuresPoints ,gridMaker.getGridDimension()/2);

//delete element with Volume <= 0
        Volume_Validator volumeValidator;
        volumeValidator.delete_blocks_with_less_than_or_equal_to_zero(hex_mesh);
       // CGAL::draw(hex_mesh);

        //output
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/SchneidersHexMeshOutput";
       // const std::string out_data_path = "/home/claudia/CLionProjects/3DMesher/MeshOutput/SchneidersHexMeshOutput";
        std::string outputFileName = out_data_path + "/" + name + "_R8_Mesh.mesh";
        std::ofstream medit_file(outputFileName);
        Writer writer;
        writer.output_to_medit(medit_file,hex_mesh);
        medit_file.close();

        outputFileName = out_data_path + "/" + name + "_8Res.vtk";
        std::ofstream vtk_file(outputFileName);
        writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
        //draw in cgal the final hex mesh
        //CGAL::draw(hex_mesh);

        VTK_manager vtk_manager;
        vtk_manager.readUnstructuredGrid(outputFileName);


    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}