#include <iostream>
//#include "test_congif.h" //TODO da aggiungere
#include "STL_reader.h"
#include "OFF_Reader.h"
#include "Grid_maker.h"
#include "External_block_remover.h"
#include "Grid_boundary_connector.h"
#include <CGAL/draw_linear_cell_complex.h>
#include <CGAL/draw_polyhedron.h>
#include "Writer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

int main(int argc, char* argv[]) {

    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
    //std::string fileName = data_path + "/cubeTest.stl";
    //const char* fname = (argc>1)?argv[1]:"sfera.off";
    //std::string fileName = data_path + "/sphere.off";
    std::string name = "cube100x100rotated";
   // std::string name = "cube100x100axisAligned";
    std::string fileName = data_path + "/" + name + ".stl";

    try {
        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        const Polyhedron polyhedron = reader.read(fileName);

        //CGAL::draw(polyhedron);
        Grid_maker gridMaker = Grid_maker();
        LCC_3 hex_mesh = gridMaker.make(polyhedron);
        std::cout<<"fatto"<<std::endl;

        //remove external blocks
        Initial_mesh_maker<External_block_remover> initialMeshMaker;
        initialMeshMaker.removeBlocks(hex_mesh, polyhedron);
//        External_block_remover externalBlockRemover = External_block_remover();
//        externalBlockRemover.removeBlocks(hex_mesh, polyhedron);
//        std::cout<<"rimossi i blocchi esterni"<<std::endl;

        //fit on boundary blocks to polyhedron boundary
        CGAL::Grid_boundary_connector gridBoundaryConnector;
        gridBoundaryConnector.connect(hex_mesh, polyhedron);


        //output
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/UnivaqHexMeshOutput/";
        std::string outputFileName = out_data_path + "/" + name + ".mesh";

        std::ofstream medit_file(outputFileName);
        Writer writer;
        writer.output_to_medit(medit_file,hex_mesh);
        medit_file.close();

        //draw in cgal the final hex mesh
       // CGAL::draw(hex_mesh);


    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}

