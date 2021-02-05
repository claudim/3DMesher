#include <iostream>
//#include "test_congif.h" //TODO da aggiungere
#include "STL_reader.h"
//#include "OFF_Reader.h"
//#include "Features_detector.h"
#include "Grid_maker.h"
#include "External_and_onBoundary_remover.h"
//#include "Initial_mesh_maker.h"
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
#include "Degenerate_element_finder.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

void bad_hex_finder(LCC_3 &lcc);

bool generateStatistics(vtkSmartPointer<vtkUnstructuredGrid> &unstructuredGrid);

int main(int argc, char* argv[]) {
//    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
   // const std::string data_path = "/home/claudia/CLionProjects/3DMesher/DataInput";
//     std::string name = "bolt";
    //std::string name = "bunny";
    //std::string name = "ellipse";
    //std::string name = "cube100x100axisAligned";
    //std::string name = "cube100x100rotated";
    //std::string name = "sphere";
    //std::string name = "rotatedTrapezoid";

    //std::string name = "sphere";
    //std::string fileName = data_path + "/" + name + ".off";
//    std::string fileName = data_path + "/" + name + ".stl";

    if (argc == 3 || argc == 4) {
        //get the stl file fileName_without_extension
        std::string inputPathFileName = argv[1]; // filename is path to filename with extension
        size_t startIndex = inputPathFileName.find_last_of(".");
        std::string fileName_extension = inputPathFileName.substr((startIndex + 1), (inputPathFileName.size()));
        if (fileName_extension == "stl") {
            try {

                // read input from file
                //OFF_Reader reader;
                STL_reader reader;
                Polyhedron polyhedron = reader.read(inputPathFileName);

//        Features_detector featuresDetector;
//        std::vector<Point> featuresPoints;
//        featuresDetector.detect(polyhedron, featuresPoints);

                Grid_maker gridMaker = Grid_maker();
                if (argc == 4) {
                    gridMaker.set_resolution(std::stoi(argv[3]));
                }
                LCC_3 hex_mesh = gridMaker.make(polyhedron);
                //std::cout << "fatto" << std::endl;

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
                //std::cout << "valido: " << hex_mesh.is_valid() << std::endl;
//
                auto stop_connect = std::chrono::high_resolution_clock::now();
                // Get duration
                auto duration_connect = std::chrono::duration_cast<std::chrono::microseconds>(
                        stop_connect - start_connect);

                std::cout << "Time taken by connect function is : "
                          << duration_connect.count() << " microseconds" << std::endl;

//        Block_refiner blockRefiner;
//        blockRefiner.refineBlocks(hex_mesh, featuresPoints ,gridMaker.getGridDimension()/2);

//delete element with Volume <= 0
                Volume_Validator volumeValidator;
                volumeValidator.delete_blocks_with_less_than_or_equal_to_zero(hex_mesh);
                // CGAL::draw(hex_mesh);

                //output
                std::string outputPathFileName = argv[2]; // filename is path to filename with extension of the output
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

//                const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/SchneidersHexMeshOutput";
//                // const std::string out_data_path = "/home/claudia/CLionProjects/3DMesher/MeshOutput/SchneidersHexMeshOutput";
//                std::string outputFileName = out_data_path + "/" + name + "_R8_Mesh.mesh";
//                std::ofstream medit_file(outputFileName);
//                Writer writer;
//                writer.output_to_medit(medit_file, hex_mesh);
//                medit_file.close();
//
//                outputFileName = out_data_path + "/" + name + "_8Res.vtk";
//                //std::string outputFileName2 = out_data_path + "/" + name + "2_8Res.vtk";
//                //std::ofstream vtk_file(outputFileName);
//                // writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
//                writer.output_to_legacy_vtk_ascii_unstructured(outputFileName, hex_mesh);

//                Degenerate_element_finder degenerate_element_finder;
//                std::vector<Dart_handle> degenerate_element = degenerate_element_finder.find_degenerate_elements(
//                        hex_mesh);
//                std::cout << "Quadrilaterals: " << degenerate_element_finder.getQuadrilaterals().size() << std::endl;
//                std::cout << "Pyramids: " << degenerate_element_finder.getPyramids().size() << std::endl;
//                std::cout << "Tets: " << degenerate_element_finder.getTetrahedra().size() << std::endl;
//                std::cout << "Wedges: " << degenerate_element_finder.getWedges().size() << std::endl;
//                std::cout << "Degeneri: " << degenerate_element.size() << std::endl;
//                std::cout << "Blocks with 3 collinear vertices: "
//                          << degenerate_element_finder.getBlockWith3CollinearVertices().size() << std::endl;
//                std::cout << "Blocks with no facets vertices coplanar: "
//                          << degenerate_element_finder.getBlockWithNotCoplanarFacetsVertices().size() << std::endl;


            }
            catch (std::ios_base::failure e) {
                std::cerr << "Exception opening/reading/closing file\n";
                return EXIT_FAILURE;
            }
        }
        else {
            std::cerr << "Cannot open and read the file with extension "<< fileName_extension <<"\n";
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


