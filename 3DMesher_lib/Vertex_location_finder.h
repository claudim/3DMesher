#ifndef INC_3DMESHER_VERTEX_LOCATION_FINDER_H
#define INC_3DMESHER_VERTEX_LOCATION_FINDER_H

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Side_of_triangle_mesh.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Point Point;
typedef LCC_3::Dart_handle Dart_handle;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> AABB_Traits;
typedef CGAL::AABB_tree<AABB_Traits> Tree;
typedef LCC_3::FT FT;

namespace CGAL {
    class Vertex_location_finder {
    protected:
        Polyhedron polyhedron;
        Point_inside inside;
        Tree AABB_tree;

    public:

        Vertex_location_finder(const Polyhedron &polyhedron)
                : inside(polyhedron), AABB_tree(faces(polyhedron).first, faces(polyhedron).second, polyhedron) {
            this->polyhedron = polyhedron;
        }

        //template<typename Point>
        bool is_point_inside_polyhedron(const Point &pointToBeCheck);

        bool is_point_onBoundary_polyhedron(const Point &pointToBeCheck);

        bool is_point_external_polyhedron(const Point &pointToBeCheck);


        //template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
        //int findExternalVertices(const LCC_3 &lcc, const Polyhedron &polyhedron);
        //template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
        void findExternalVertices(const LCC_3 &lcc, int &number_of_external_vertices, const double &tolerance);

        const Tree &getAabbTree();
    };

}

#endif //INC_3DMESHER_VERTEX_LOCATION_FINDER_H
