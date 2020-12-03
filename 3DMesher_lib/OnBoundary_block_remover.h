
#ifndef INC_3DMESHER_ONBOUNDARY_BLOCK_REMOVER_H
#define INC_3DMESHER_ONBOUNDARY_BLOCK_REMOVER_H

#include <MyLCC.h>
#include "Vertex_location_finder.h"
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include "External_facet_finder.h"


typedef CGAL::Vertex_location_finder Vertex_location_finder;
//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//typedef LCC_3::Point Point;
typedef CGAL::Bbox_3 Bbox;
//typedef LCC_3::Traits Traits;
//typedef LCC_3::FT FT;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;

class OnBoundary_block_remover {

public:
    //template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
    void removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron);

    void removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance);

    void removeBlock(LCC_3& lcc, Dart_handle& blockToRemove);

    //template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
//    bool is_block_to_be_removed(const LCC_3 &lcc,
//                                const CGAL::Combinatorial_map_base::One_dart_per_cell_const_range()<3, 3>::const_iterator &lcc_cells_iterator,
//                                const Polyhedron &polyhedron);
    bool is_block_to_be_removed(const LCC_3 &lcc,
                                const Dart_handle& block,
                                const Polyhedron &polyhedron);

    bool is_block_to_be_removed(const LCC_3 &lcc,
                                const Dart_handle& block,
                                const Polyhedron &polyhedron,
                                const double &distance);

    bool is_block_too_close_to_the_boundary(const LCC_3 &lcc,const Dart_handle& block,const Polyhedron &polyhedron,const double &distance);
    bool is_block_too_close_to_the_boundary2(const LCC_3 &lcc,const Dart_handle& block,const Polyhedron &polyhedron,const double &distance);


    //template<typename allocator, typename allocator, typename Linear_cell_complex_traits, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
    bool is_block_on_boundary(const LCC_3 &lcc, const Dart_handle &block, const Polyhedron &polyhedron);
};




#endif //INC_3DMESHER_ONBOUNDARY_BLOCK_REMOVER_H
