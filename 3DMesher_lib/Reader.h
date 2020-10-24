#ifndef INC_3DMESHER_READER_H
#define INC_3DMESHER_READER_H

#include <string>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <exception>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

class Reader {

public:
    Polyhedron read(std::string fileName) noexcept(false); //it could throw std::ios_base::failure
};


#endif //INC_3DMESHER_READER_H
