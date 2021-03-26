// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Main file to generate a conforming hexahedral mesh using Univaq Hex Mesh algorithm.
//******************************************************************************

#include <iostream>
#include "STL_reader3.h"
#include "OFF_Reader.h"
#include "UnivaqHexMeshAlgorithm.h"
#include "Writer.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

int main(int argc, char* argv[]) {

    if (argc == 3 || argc == 4) {
        try {

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
                }
                else if(fileName_extension == "off") {
                    OFF_Reader reader;
                    polyhedron = reader.read(inputPathFileName);
                }
                else{
                    std::cerr << "Output File format not supported.\n";
                    return EXIT_FAILURE;
                }

                // execute UnivaqHexMeshAlgorithm
                LCC_3 hex_mesh;
                UnivaqHexMeshAlgorithm univaqHexMeshAlgorithm;
                if (argc == 4) {
                    univaqHexMeshAlgorithm.run(polyhedron, hex_mesh, std::stod(argv[3]));
                }
                else{
                    univaqHexMeshAlgorithm.run(polyhedron, hex_mesh);
                }

                // write on file
                std::string outputPathFileName = argv[2]; // filename is path to filename with extension of the output
                size_t startIndex = outputPathFileName.find_last_of(".");
                Writer writer;
                std::string output_file_extension = outputPathFileName.substr(startIndex + 1,
                                                                              outputPathFileName.size());
                if (output_file_extension == "vtk") {
                    std::ofstream vtk_file(outputPathFileName);
                  //  writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
                        writer.output_to_legacy_vtk_ascii_unstructured(outputPathFileName, hex_mesh);
                    vtk_file.close();
                }
               else if (output_file_extension == "mesh") {
                    std::ofstream medit_file(outputPathFileName);
                    writer.output_to_medit(medit_file, hex_mesh);
                    medit_file.close();
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
            std::cerr << "Too many input parameters. At most : path to the STL file input; path to the output file; the integer grid resolution\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}