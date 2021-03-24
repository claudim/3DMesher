// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Main file to count the external facets from a conforming hexahedral mesh
// generated using Univaq Split From Tet algorithm.
// ******************************************************************************

#include <iostream>

#include "MyLCC.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/helpers.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/make_mesh_3.h>
#include "STL_reader.h"
#include "OFF_Reader.h"
#include "STL_reader3.h"
#include "Writer.h"
#include "HexMesh_from_TetMesh_maker.h"
#include "External_facet_finder.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_with_features_3<K> Mesh_Domain;
typedef CGAL::Mesh_triangulation_3<Mesh_Domain, CGAL::Default>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;
typedef CGAL::Mesh_criteria_3<Tr> Mesh_Criteria;

template<typename allocator>
void split_from_tet(const C3t3 &c3t3, LCC_3 &hex_mesh);

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

                //Create domain
                Mesh_Domain domain(polyhedron);

                //Get sharp features
                domain.detect_features();

                C3t3 c3t3;
                if(argc == 4)
                {
                    double desired_edge_size = std::stod(argv[3]) * 2;
                    Mesh_Criteria criteria(
                            facet_angle = 30,
                            cell_radius_edge_ratio = 2,
                            cell_size = desired_edge_size * sqrt(6) / 4,
                            edge_size = desired_edge_size);
                    //Mesh generation
                    c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());

                }
                else
                {
                    Mesh_Criteria criteria(facet_angle = 30, cell_radius_edge_ratio = 2);
                    //Mesh generation
                    c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());
                }


                //split tet mesh in all hex mesh
                LCC_3 hex_mesh;
                HexMesh_from_TetMesh_maker hex_mesh_maker;
                hex_mesh_maker.split_from_tet(c3t3, hex_mesh);

                External_facet_finder externalFacetFinder;
                const std::vector<Dart_handle>  external_facets = externalFacetFinder.findFacets(hex_mesh);
                unsigned long numberOfExternalFacets = external_facets.size();
                std::cout<< "External facets : "<< numberOfExternalFacets <<std::endl;

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

