#ifndef INC_3DMESHER_POINTNORMAL_BOUNDARY_INTERSECTIONPOINT_FINDER_H
#define INC_3DMESHER_POINTNORMAL_BOUNDARY_INTERSECTIONPOINT_FINDER_H

#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Polygon_mesh_processing/compute_normal.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Dart_handle Dart_handle;
typedef LCC_3::Dart_const_handle Dart_const_handle;
typedef LCC_3::Point Point;
typedef LCC_3::Traits Traits;
typedef LCC_3::FT FT;
typedef LCC_3::Vector Vector;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> AABB_Traits;
typedef CGAL::AABB_tree<AABB_Traits> Tree;
typedef AABB_Traits::Ray_3 Ray;


class PointNormal_boundary_intersectionPoint_finder {

public:
   // template<typename Point, typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
    Point findIntersecionPoint(const LCC_3 &lcc, const Dart_const_handle &block_handle, const Polyhedron &polyhedron);

   /**
    * Compute the normal of the 0-cell. For each external facets(2-cell) incident to the 0-cell, it is compute its normal. Afterwards, every normal of the 2-cell are weighed added.
    * In this way the normal of the 0-cell is unique.
    */
    template <class LCC = LCC_3>
    typename LCC::Vector my_compute_normal_of_cell_0
            (const LCC& lcc, typename LCC::Dart_const_handle adart)
    {
        typedef typename LCC::Vector Vector;
        Vector normal(CGAL::NULL_VECTOR);
        unsigned int nb = 0;

        for ( typename LCC::template One_dart_per_incident_cell_range<2,0>::
        const_iterator it(lcc, adart); it.cont(); ++it )
        {
            //compute normal only for the external 2-cell
            if(lcc.beta(it, 3) == lcc.null_dart_handle) {
                normal = typename LCC::Traits::Construct_sum_of_vectors()
                        (normal, CGAL::compute_normal_of_cell_2(lcc, it));
                ++nb;
            }
        }
        if ( nb<2 ) return normal;
        return (typename LCC::Traits::Construct_scaled_vector()(normal, 1.0/nb));
    }
};



#endif //INC_3DMESHER_POINTNORMAL_BOUNDARY_INTERSECTIONPOINT_FINDER_H
