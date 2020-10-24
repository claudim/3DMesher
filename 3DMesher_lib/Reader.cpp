#include "Reader.h"

Polyhedron Reader::read(std::string fileName) noexcept(false) {
    std::ifstream input(fileName);
    Polyhedron polyhedron;
    input.exceptions ( std::ifstream::failbit | std::ifstream::badbit ); //if a bit in the mask becomes set in the error flags, then an exception of type std::ios_base::failure is thrown.
    input >> polyhedron;
    return polyhedron;
}
