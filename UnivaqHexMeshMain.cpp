#include <iostream>
#include <chrono>
//#include "test_congif.h" //TODO da aggiungere
#include "STL_reader.h"
#include "OFF_Reader.h"
#include "Grid_maker.h"
#include "Initial_mesh_maker.h"
#include "External_block_remover.h"
#include "Grid_boundary_connector.h"
#include <CGAL/draw_linear_cell_complex.h>
#include <CGAL/draw_polyhedron.h>
#include "Volume_Validator.h"
#include "Degenerate_element_finder.h"
#include "Writer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

int main(int argc, char* argv[]) {

    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
    //std::string name = "bolt";
    //std::string name = "bunny";
    //std::string name = "ellipse";
    //std::string name = "Tronco_cono_3D";
    //std::string name = "cube100x100axisAligned";
    //std::string name = "cube100x100rotated";
    std::string name = "sfera";
    //std::string name = "rotatedTrapezoid";

    //std::string fileName = data_path + "/cubeTest.stl";
    //const char* fname = (argc>1)?argv[1]:"sfera.off";
    //std::string fileName = data_path + "/sphere.off";
    //std::string name = "cube100x100rotated";

   // std::string name = "cube100x100axisAligned";
    std::string fileName = data_path + "/" + name + ".stl";

    try {
        // Get starting timepoint
        auto start_reading = std::chrono::high_resolution_clock::now();

        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        const Polyhedron polyhedron = reader.read(fileName);

        // Get ending timepoint
        auto stop_reading = std::chrono::high_resolution_clock::now();

        // Get duration
        auto duration = duration_cast<std::chrono::microseconds>(stop_reading - start_reading);

        std::cout << "Time taken by read function is : "
             << duration.count() << " microseconds" << std::endl;


        //CGAL::draw(polyhedron);
        Grid_maker gridMaker = Grid_maker();
        LCC_3 hex_mesh = gridMaker.make(polyhedron);
        std::cout<<"fatto"<<std::endl;

        //remove external blocks
        Initial_mesh_maker<External_block_remover> initialMeshMaker;
        initialMeshMaker.removeBlocks(hex_mesh, polyhedron);
//        External_block_remover externalBlockRemover = External_block_remover();
//        externalBlockRemover.removeBlocks(hex_mesh, polyhedron);
        std::cout<<"rimossi i blocchi esterni"<<std::endl;
        //get the number of hex_mesh element
        int number_of_int_element = 0;
        for(LCC_3::One_dart_per_cell_range<3,3>::iterator cell_it = hex_mesh.one_dart_per_cell<3,3>().begin(),
                    cell_it_end = hex_mesh.one_dart_per_cell<3,3>().end(); cell_it != cell_it_end; ++cell_it)
        {
            number_of_int_element++;
        }
        std::cout<<"Number of initial mesh element "<< number_of_int_element<<std::endl;

        //fit on boundary blocks to polyhedron boundary
        CGAL::Grid_boundary_connector gridBoundaryConnector;
        gridBoundaryConnector.connect(hex_mesh, polyhedron);

        //delete element with Volume <= 0
        Volume_Validator volumeValidator;
        volumeValidator.delete_blocks_with_less_than_or_equal_to_zero(hex_mesh);

        // Get ending timepoint
        auto stop = std::chrono::high_resolution_clock::now();

        // Get duration
        auto duration2 = duration_cast<std::chrono::microseconds>(stop - start_reading);

        std::cout << "Time taken by mesh generation is : "
                  << duration2.count() << " microseconds" << std::endl;

//        //get the number of hex_mesh element
//        int number_of_element = 0;
//        for(LCC_3::One_dart_per_cell_range<3,3>::iterator cell_it = hex_mesh.one_dart_per_cell<3,3>().begin(),
//                cell_it_end = hex_mesh.one_dart_per_cell<3,3>().end(); cell_it != cell_it_end; ++cell_it)
//        {
//            number_of_element++;
//        }
//        std::cout<<"Number of element "<< number_of_element<<std::endl;
        
        Degenerate_element_finder degenerateElementFinder;
        std::vector<Dart_handle> degenerateElements = degenerateElementFinder.find_degenerate_elements(hex_mesh);
        std::cout<<"Degenerate elements are " << degenerateElements.size() <<std::endl;

        //output
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/UnivaqHexMeshOutput/";
        std::string outputFileName = out_data_path + "/" + name + "_8Res.mesh";

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

