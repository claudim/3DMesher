// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Main file to generate a conforming hexahedral mesh using Univaq Split from Tet algorithm.
//******************************************************************************

#include <iostream>

#include "MyLCC.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include "OFF_Reader.h"
#include "STL_reader3.h"
#include "UnivaqSplitFromTetAlgorithm.h"
#include "Writer.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

using namespace CGAL::parameters;

int main(int argc, char* argv[]) {
    if (argc == 3 || argc == 4) {
        try {

            //get the stl file fileName_without_extension
            std::string inputPathFileName = argv[1]; // filename is path to filename with extension
            size_t startIndex = inputPathFileName.find_last_of(".");
            std::string fileName_extension = inputPathFileName.substr((startIndex + 1), (inputPathFileName.size()));

            // read input from file
            if (fileName_extension == "stl" || fileName_extension == "off") {

                Polyhedron polyhedron;
                if (fileName_extension == "stl") {
                    STL_reader3 reader;
                    polyhedron = reader.read(inputPathFileName);

                }
                else if(fileName_extension == "off") {
                    OFF_Reader reader;
                    polyhedron = reader.read(inputPathFileName);
                }
                if(polyhedron.empty())
                {
                    std::cerr << "Empty polyhedron. \n";
                    return EXIT_FAILURE;
                }

                //mesh generation
                double desired_edge_size;
                UnivaqSplitFromTetAlgorithm univaqSplitFromTetAlgorithm;
                LCC_3 hex_mesh;
                if(argc == 4)
                {
                   desired_edge_size = std::stod(argv[3]) * 2;
                   univaqSplitFromTetAlgorithm.run(polyhedron, hex_mesh, desired_edge_size);
                }
                else
                {
                    univaqSplitFromTetAlgorithm.run(polyhedron, hex_mesh);
                }

                //Output
                std::string outputFileName = argv[2]; // outputFileName is path to filename with extension
                size_t outputStartIndex = outputFileName.find_last_of(".");
                std::string outputFileName_extension = outputFileName.substr((outputStartIndex  + 1), (outputFileName.size()));
                Writer hex_writer;
                if(outputFileName_extension == "mesh")
                {
                    std::ofstream medit_file(outputFileName);
                    hex_writer.output_to_medit(medit_file, hex_mesh);
                    medit_file.close();
                }
                else if(outputFileName_extension == "vtk")
                {
                    std::ofstream vtk_file(outputFileName);
                  //  hex_writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
                    hex_writer.output_to_legacy_vtk_ascii_unstructured(outputFileName, hex_mesh);
                    vtk_file.close();
                }
                else{
                    std::cerr << "Output File format not supported.\n";
                    return EXIT_FAILURE;
                }
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
                std::cerr << "Too many input parameters. At most : path to the STL file input; path to the output file; the double cell_size\n";
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

