#include "STL_reader.h"

//// it could throw std::ios_base::failure exception
template<class Polyhedron>
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
    input.exceptions(std::ifstream::failbit |
                     std::ifstream::badbit); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
    std::vector <std::array<double, 3>> vertices;
    std::vector <std::array<int, 3>> triangles;
    if (!CGAL::read_STL(input, vertices, triangles)) //if the reading process did not go well
    {
        std::cerr << "Error: invalid STL file" << std::endl;
    }

    if (CGAL::Polygon_mesh_processing::is_polygon_soup_a_polygon_mesh(triangles))
        CGAL::Polygon_mesh_processing::polygon_soup_to_polygon_mesh(vertices, triangles, polyhedron);
    if(!polyhedron.is_valid() && !polyhedron.is_pure_triangle())
    {
        std::cerr << "Error: Polyhedron not valid or not composed of all triangles " << std::endl;
    }
    return polyhedron;
}