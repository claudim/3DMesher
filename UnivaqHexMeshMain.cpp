#include <iostream>
#include <chrono>
//#include "test_congif.h" //TODO da aggiungere
#include "STL_reader.h"
#include "OFF_Reader.h"
#include "Grid_maker.h"
#include "Initial_mesh_maker.h"
#include "External_block_remover.h"
#include "Grid_boundary_connector.h"
//#include <CGAL/draw_linear_cell_complex.h>
//#include <CGAL/draw_polyhedron.h>
#include "Volume_Validator.h"
#include "Degenerate_element_finder.h"
#include "Writer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

int main(int argc, char* argv[]) {

//    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
////    const std::string data_path = "/home/claudia/CLionProjects/3DMesher/DataInput";
//    std::string fileName_without_extension = "bolt";
//    //std::string fileName_without_extension = "bunny";
//    //std::string fileName_without_extension = "ellipse";
//    //std::string fileName_without_extension = "Tronco_cono_3D";
//    //std::string fileName_without_extension = "cube100x100axisAligned";
//    //std::string fileName_without_extension = "cube100x100rotated";
////    std::string name = "sfera";
//    //std::string fileName_without_extension = "rotatedTrapezoid";
//
//    //std::string fileName = data_path + "/cubeTest.stl";
//    //const char* fname = (argc>1)?argv[1]:"sfera.off";
//    //std::string fileName = data_path + "/sphere.off";
//    //std::string fileName_without_extension = "cube100x100rotated";
//
//   // std::string fileName_without_extension = "cube100x100axisAligned";
//    std::string fileName = data_path + "/" + fileName_without_extension + ".stl";

    if (argc == 3 || argc == 4) {
        try {

            //get the stl file fileName_without_extension
            std::string inputPathFileName = argv[1]; // filename is path to filename with extension

//            size_t startIndex  = inputPathFileName.find_last_of("/");
//            std::string fileName_with_extension = inputPathFileName.substr(startIndex + 1,inputPathFileName.size());
//            std::string fileName_without_extension = fileName_with_extension.substr(0,(fileName_with_extension.size()-4));
//            std::string fileName_extension = fileName_with_extension.substr((fileName_with_extension.size()-3),(fileName_with_extension.size()));

            size_t startIndex = inputPathFileName.find_last_of(".");
            std::string fileName_extension = inputPathFileName.substr((startIndex + 1), (inputPathFileName.size()));
            if (fileName_extension == "stl" || fileName_extension == "off") {

                // Get starting timepoint
                //  auto start_reading = std::chrono::high_resolution_clock::now();

                // read input from file
                //OFF_Reader reader;
                Polyhedron polyhedron;
                if (fileName_extension == "stl") {
                    STL_reader reader;
                    polyhedron = reader.read(inputPathFileName);
                }
                //const Polyhedron polyhedron = reader.read(inputPathFileName);
                if (fileName_extension == "off") {
                    OFF_Reader reader;
                    polyhedron = reader.read(inputPathFileName);
                }

                // Get ending timepoint
//        auto stop_reading = std::chrono::high_resolution_clock::now();

                // Get duration
//        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_reading - start_reading);

//        std::cout << "Time taken by read function is : "
//             << duration.count() << " microseconds" << std::endl;


                //CGAL::draw(polyhedron);
                Grid_maker gridMaker = Grid_maker();
                if (argc == 4) {
                    gridMaker.set_resolution(std::stoi(argv[3]));
                }
                LCC_3 hex_mesh = gridMaker.make(polyhedron);
//        std::cout<<"fatto"<<std::endl;

                //remove external blocks
                auto start_reading = std::chrono::high_resolution_clock::now();

//        Initial_mesh_maker<External_block_remover> initialMeshMaker;
//        initialMeshMaker.removeBlocks(hex_mesh, polyhedron);
                External_block_remover externalBlockRemover = External_block_remover();
                externalBlockRemover.removeBlocks(hex_mesh, polyhedron);
                auto stop_reading = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_reading - start_reading);

                std::cout << "Time taken by remove block function is : "
                          << duration.count() << " microseconds" << std::endl;
                std::cout << "rimossi i blocchi esterni" << std::endl;

                hex_mesh.display_characteristics(std::cout);
                std::cout << "" << std::endl;

//        //get the number of hex_mesh element
//        int number_of_int_element = 0;
//        for(LCC_3::One_dart_per_cell_range<3,3>::iterator cell_it = hex_mesh.one_dart_per_cell<3,3>().begin(),
//                    cell_it_end = hex_mesh.one_dart_per_cell<3,3>().end(); cell_it != cell_it_end; ++cell_it)
//        {
//            number_of_int_element++;
//        }
//        std::cout<<"Number of initial mesh element "<< number_of_int_element<<std::endl;

                auto start_reading_connect = std::chrono::high_resolution_clock::now();


                //fit on boundary blocks to polyhedron boundary
                CGAL::Grid_boundary_connector gridBoundaryConnector;
                gridBoundaryConnector.connect(hex_mesh, polyhedron);

                auto stop_reading_connect = std::chrono::high_resolution_clock::now();
                auto duration_connect = std::chrono::duration_cast<std::chrono::microseconds>(
                        stop_reading_connect - start_reading_connect);

                std::cout << "Time taken by connect block function is : "
                          << duration_connect.count() << " microseconds" << std::endl;

                //delete element with Volume <= 0
                Volume_Validator volumeValidator;
                volumeValidator.delete_blocks_with_less_than_or_equal_to_zero(hex_mesh);

                // Get ending timepoint
//        auto stop = std::chrono::high_resolution_clock::now();

                // Get duration
//        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start_reading);

//        std::cout << "Time taken by mesh generation is : "
//                  << duration2.count() << " microseconds" << std::endl;

//
//                Degenerate_element_finder degenerate_element_finder;
//                std::vector<Dart_handle> degenerate_element = degenerate_element_finder.find_degenerate_elements(hex_mesh);
//                std::cout<< "Quadrilaterals: " <<degenerate_element_finder.getQuadrilaterals().size()<<std::endl;
//                std::cout<< "Pyramids: " <<degenerate_element_finder.getPyramids().size()<<std::endl;
//                std::cout<< "Tets: " <<degenerate_element_finder.getTetrahedra().size()<<std::endl;
//                std::cout<< "Wedges: " <<degenerate_element_finder.getWedges().size()<<std::endl;
//                std::cout<< "Degeneri: " <<degenerate_element.size()<<std::endl;
//                std::cout<< "Blocks with 3 collinear vertices: " <<degenerate_element_finder.getBlockWith3CollinearVertices().size()<<std::endl;
//                std::cout<< "Blocks with no facets vertices coplanar: " <<degenerate_element_finder.getBlockWithNotCoplanarFacetsVertices().size()<<std::endl;
//


                //output
              //  if (argc == 3 || argc == 4) {

                    std::string outputPathFileName = argv[2]; // filename is path to filename with extension of the output
                    //size_t startIndex  = outputPathFileName.find_last_of("/");
                    //std::string output_fileName_with_extension = outputPathFileName.substr(startIndex + 1,outputPathFileName.size());
                    // std::string fileName_without_extension = output_fileName_with_extension.substr(0,(output_fileName_with_extension.size()-4));
                    // std::string output_file_extension = output_fileName_with_extension.substr((output_fileName_with_extension.size()-3),(output_fileName_with_extension.size()));
                    size_t startIndex = outputPathFileName.find_last_of(".");
                    Writer writer;
                    std::string output_file_extension = outputPathFileName.substr(startIndex + 1,
                                                                                  outputPathFileName.size());
                    if (output_file_extension == "vtk") {
                        std::ofstream vtk_file(outputPathFileName);
                        //writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
                        writer.output_to_legacy_vtk_ascii_unstructured(outputPathFileName, hex_mesh);
                        vtk_file.close();
                    }
                    if (output_file_extension == "mesh") {
                        std::ofstream medit_file(outputPathFileName);
                        writer.output_to_medit(medit_file, hex_mesh);
                        medit_file.close();
                    }


//                const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/UnivaqHexMeshOutput/";
////        const std::string out_data_path = "/home/claudia/CLionProjects/3DMesher/MeshOutput/UnivaqHexMeshOutput";
//                std::string outputFileName = out_data_path + "/" + fileName_without_extension + "_8Res.mesh";

//                Writer writer;
//                std::ofstream medit_file(outputFileName);
//                writer.output_to_medit(medit_file, hex_mesh);
//                medit_file.close();

//                outputFileName = out_data_path + "/" + fileName_without_extension + "_8Res.vtk";
//                std::ofstream vtk_file(outputFileName);
//                writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
//                vtk_file.close();

                }
                //draw in cgal the final hex mesh
                // CGAL::draw(hex_mesh);


            }
        //}
        catch (std::ios_base::failure e) {
            std::cout<<e.what()<<std::endl;
            std::cerr << "Exception opening/reading/closing file\n";
            return EXIT_FAILURE;
        }
    }
    else{
        if(argc<3)
            std::cerr << "Too few input parameters. At least : path to the STL file input; path to the output file\n";
        if(argc>4)
            std::cerr << "Too many input parameters. At most : path to the STL file input; path to the output file; the integer grid resolution\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}