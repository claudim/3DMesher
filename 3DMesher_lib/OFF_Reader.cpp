#include "OFF_Reader.h"

Polyhedron OFF_Reader::read(std::string fileName) noexcept(false) {
    std::ifstream input(fileName);
    Polyhedron polyhedron;
    input.exceptions ( std::ifstream::failbit | std::ifstream::badbit ); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
    input >> polyhedron;
    if(!polyhedron.is_valid() && !polyhedron.is_pure_triangle())
    {
        std::cerr << "Error: Polyhedron not valid or not composed of all triangles " << std::endl;
    }
    if(!CGAL::is_triangle_mesh(polyhedron))
    {
        std::cerr << "Input geometry is not triangulated." << std::endl;
    }
    input.close();
    return polyhedron;
}
