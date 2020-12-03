#ifndef INC_3DMESHER_GRID_BOUNDARY_CONNECTOR_H
#define INC_3DMESHER_GRID_BOUNDARY_CONNECTOR_H

#include <MyLCC.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Point Point;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> AABB_Traits;
typedef CGAL::AABB_tree<AABB_Traits> Tree;

namespace CGAL {
    class Grid_boundary_connector {

    public:
        //template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
        void connect(LCC_3 &lcc, const Polyhedron &polyhedron);
    };

}


#endif //INC_3DMESHER_GRID_BOUNDARY_CONNECTOR_H
