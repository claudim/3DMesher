#ifndef INC_3DMESHER_INITIALMESH_BOUNDARY_CONNECTOR_H
#define INC_3DMESHER_INITIALMESH_BOUNDARY_CONNECTOR_H

#include "MyLCC.h"
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include "PointNormal_boundary_intersectionPoint_finder.h"
#include "External_facet_finder.h"
#include "Point_sorter.h"
#include <boost/optional.hpp>
#include "Intersecting_polyhedron_finder.h"
#include "Vertex_location_finder.h"
#include "Grid_maker.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;


class InitialMesh_boundary_connector {

public:
//    template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
    void connect(LCC_3 &lcc, const Polyhedron &polyhedron);
//
//   // template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
//    void linkBlock(LCC_3 &lcc, Dart_handle &block1, Dart_handle &block2);
    bool is_the_isomorphic_point_computed(LCC_3 &lcc, Dart_handle &vertex_handle);


    void replace(std::vector<Point> &hexahedronVertexPoints, const Polyhedron &polyhedron, const double distance);

    //template<typename allocator, typename allocator, typename allocator, typename allocator>
    void replace(LCC_3 &lcc, Dart_handle facet, const Polyhedron &polyhedron, const double distance);
};

#endif //INC_3DMESHER_INITIALMESH_BOUNDARY_CONNECTOR_H
