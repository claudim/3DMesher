#include <iostream>
#include <chrono>
//#include "test_congif.h" //TODO da aggiungere
#include "STL_reader.h"
//#include "STL_reader2.h"
#include "STL_reader3.h"
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

    if (argc == 3 || argc == 4) {
        try {

//            auto time_s =std::chrono::high_resolution_clock::now();
            //get the stl file fileName_without_extension
            std::string inputPathFileName = argv[1]; // filename is path to filename with extension
            size_t startIndex = inputPathFileName.find_last_of(".");
            std::string fileName_extension = inputPathFileName.substr((startIndex + 1), (inputPathFileName.size()));
            if (fileName_extension == "stl" || fileName_extension == "off") {

                // read input from file
                Polyhedron polyhedron;
                if (fileName_extension == "stl") {
                    STL_reader3 reader;
                    polyhedron = reader.read(inputPathFileName);
                } else if (fileName_extension == "off") {
                    OFF_Reader reader;
                    polyhedron = reader.read(inputPathFileName);
                } else {
                    std::cerr << "Output File format not supported.\n";
                    return EXIT_FAILURE;
                }

                Grid_maker gridMaker = Grid_maker();
                if (argc == 4) {
                    gridMaker.set_resolution(std::stod(argv[3]));
                }
                LCC_3 hex_mesh = gridMaker.make(polyhedron);

                External_block_remover externalBlockRemover = External_block_remover();
                externalBlockRemover.removeBlocks(hex_mesh, polyhedron);

                //fit on boundary blocks to polyhedron boundary
                CGAL::Grid_boundary_connector gridBoundaryConnector;
                gridBoundaryConnector.connect(hex_mesh, polyhedron);

                //delete element with Volume <= volume treshold
                double volume_treshold = std::pow(gridMaker.getGridDimension(), 3) / 1000;
                Volume_Validator volumeValidator;
                volumeValidator.setVolumeTreshold(volume_treshold);
                volumeValidator.delete_blocks_with_less_than_or_equal_to_volume_treshold(hex_mesh);


                std::string outputPathFileName = argv[2]; // filename is path to filename with extension of the output
                //size_t startIndex  = outputPathFileName.find_last_of("/");
                //std::string output_fileName_with_extension = outputPathFileName.substr(startIndex + 1,outputPathFileName.size());
                // std::string fileName_without_extension = output_fileName_with_extension.substr(0,(output_fileName_with_extension.size()-4));
                // std::string output_file_extension = output_fileName_with_extension.substr((output_fileName_with_extension.size()-3),(output_fileName_with_extension.size()));
                size_t startIndex = outputPathFileName.find_last_of(".");
                Writer writer;
                std::string output_file_extension = outputPathFileName.substr(startIndex + 1,
                                                                              outputPathFileName.size());


                External_facet_finder externalFacetFinder;
                const std::vector<Dart_handle>  external_facets = externalFacetFinder.findFacets(hex_mesh);
                unsigned long numberOfExternalFacets = external_facets.size();
                std::cout<< "facce esterne : "<< numberOfExternalFacets <<std::endl;

            }
            else{
                std::cerr << "Input File format not supported.\n";
                return EXIT_FAILURE;
            };
        }
        catch (std::ios_base::failure e) {
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