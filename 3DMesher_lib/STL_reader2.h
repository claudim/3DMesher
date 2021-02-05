// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Read a STL file.
//******************************************************************************

#ifndef INC_3DMESHER_STL_READER2_H
#define INC_3DMESHER_STL_READER2_H

#include <fstream>
#include "CGAL/Polyhedral_mesh_domain_with_features_3.h"
#include "CGAL/IO/STL_reader.h"
#include "CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h"
#include "CGAL/Polygon_mesh_processing/corefinement.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

/**
 * @brief Reader for a STL file.
 *
 * @file STL_reader.h
 * @class STL_reader
 */
class STL_reader2 {

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
std::string fileName1 = "/Users/claudia/Desktop/Prova.stl";
std::string fileName2 = "/Users/claudia/Desktop/Prova2.stl";
std::string fileName3 = "/Users/claudia/Desktop/Prova3.stl";
        std::ifstream input1(fileName1, std::ios::in);
        std::ifstream input2(fileName2, std::ios::in);
        std::ifstream input3(fileName3, std::ios::in);
        input.exceptions(std::ifstream::badbit); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
        std::vector <std::array<double, 3>> vertices;
        std::vector <std::array<int, 3>> triangles;
        std::vector <std::array<double, 3>> vertices2;
        std::vector <std::array<double, 3>> vertices3;
        std::vector <std::array<int, 3>> triangles2;
        std::vector <std::array<int, 3>> triangles3;
        Polyhedron polyhedron1;
        Polyhedron polyhedron2;
        Polyhedron polyhedron3;

//        while(!input.eof())
//        {
            if (!CGAL::read_STL(input1, vertices, triangles, true)) //if the reading process did not go well
            {
                std::cerr << "Error: invalid STL file" << std::endl;
            }
            else{
                if (CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh(triangles)) {

                    std::cout<< "It is a polygon soup"<<std::endl;
                    CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, triangles, polyhedron1);
                }
                else
                {
                    std::cout<< "It is not a polygon soup"<<std::endl;
                }
            }
        if (!CGAL::read_STL(input2, vertices2, triangles2, true)) //if the reading process did not go well
        {
            std::cerr << "Error: invalid STL file" << std::endl;
        }
        else{
            if (CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh(triangles2)) {

                std::cout<< "It is a polygon soup"<<std::endl;
                CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices2, triangles2, polyhedron2);
            }
            else
            {
                std::cout<< "It is not a polygon soup"<<std::endl;
            }
        }
        if (!CGAL::read_STL(input3, vertices3, triangles3, true)) //if the reading process did not go well
        {
            std::cerr << "Error: invalid STL file" << std::endl;
        }
        else{
            if (CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh(triangles3)) {

                std::cout<< "It is a polygon soup"<<std::endl;
                CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices3, triangles3, polyhedron3);
            }
            else
            {
                std::cout<< "It is not a polygon soup"<<std::endl;
            }
        }
        bool b = CGAL::Polygon_mesh_processing::corefine_and_compute_union(polyhedron1, polyhedron2, polyhedron);
        if(b)
        {
            std::cout<<"unione effettuata"<<std::endl;
        }
        else
        {std::cout<<"unione non effettuata"<<std::endl;}
         b = CGAL::Polygon_mesh_processing::corefine_and_compute_union(polyhedron, polyhedron3, polyhedron);
        if(b)
        {
            std::cout<<"unione effettuata"<<std::endl;
        }
        else
        {std::cout<<"unione non effettuata"<<std::endl;}


        //}

        if(!polyhedron.is_valid() && !polyhedron.is_pure_triangle())
        {
            std::cerr << "Error: Polyhedron not valid or not composed of all triangles " << std::endl;
        }
        input.close();
        return polyhedron;
    }

};



#endif //INC_3DMESHER_STL_READER2_H
