// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Read a STL file.
//******************************************************************************

#ifndef INC_3DMESHER_STL_READER_H
#define INC_3DMESHER_STL_READER_H

#include <fstream>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/IO/STL_reader.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <CGAL/IO/STL_writer.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

/**
 * @brief Reader for a STL file.
 *
 * @file STL_reader.h
 * @class STL_reader
 */
class STL_reader {

public:
    /**
     * @brief Read a STL file and starting from the contents of the file create a polyhedron.
     *
     * @tparam Polyhedron The Polyhedron class where store the contents of the file.
     * @param fileName The STL file name to read.
     * @return A polyhedron read from the STL file.
     */
    template<class Polyhedron = Polyhedron>
    Polyhedron read(const std::string fileName){
        std::ifstream input(fileName, std::ios::in |
                                      std::ios::binary); // construction of input (a ifstream object) and stream opening filename file for input operations or in binary mode
        if (!input) {
            std::cerr << "Error! Cannot open file " << fileName << std::endl;
        }
        Polyhedron polyhedron;
        if (fileName.size() == 0) {
            std::cerr << "The file you are trying to load is empty." << std::endl;;
        }
        input.exceptions(std::ifstream::badbit); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
        std::vector <std::array<double, 3>> vertices;
        std::vector <std::array<int, 3>> triangles;
        while(!input.eof())
        {

            if (!CGAL::read_STL(input, vertices, triangles, true)) //if the reading process did not go well
            {
                std::cerr << "Error: invalid STL file" << std::endl;
                break;
            }
            if(!input.eof())
            {
                std::string s;
                input >> s;
                std::cout <<s<<std::endl;
            }


        }

//        if (CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh(triangles))
//            CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, triangles, polyhedron);

        CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, triangles, polyhedron);
        if(!polyhedron.is_valid() && !polyhedron.is_pure_triangle())
        {
            std::cerr << "Error: Polyhedron not valid or not composed of all triangles " << std::endl;

        }
        input.close();
        size_t startIndex = fileName.find_last_of(".");
        std::string fileName_stl_to_write = fileName.substr(0, startIndex) + "3.stl";
        std::ofstream out(fileName_stl_to_write, std::ios::out);
        CGAL::set_mode(out, CGAL::IO::ASCII);
        CGAL::write_STL(polyhedron, out);
        return polyhedron;
    }

};
#endif //INC_3DMESHER_STL_READER_H
