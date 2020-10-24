#ifndef INC_3DMESHER_EXTERNAL_BLOCK_REMOVER_H
#define INC_3DMESHER_EXTERNAL_BLOCK_REMOVER_H

#include "Block_maker.h"
#include "Vertex_location_finder.h"
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Side_of_triangle_mesh.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Dart_handle Dart_handle;
typedef LCC_3::Point Point;
typedef CGAL::Bbox_3 Bbox;
typedef LCC_3::Traits Traits;
typedef LCC_3::FT FT;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;

class External_block_remover {

public:
    //template<typename Linear_cell_complex_traits, typename allocator>
    void removeBlock(LCC_3& lcc, Dart_handle& blockToRemove);

    bool is_block_to_be_removed(const LCC_3& lcc, const Dart_handle& block, const Polyhedron& polyhedron);

    void removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron);

};




#endif //INC_3DMESHER_EXTERNAL_BLOCK_REMOVER_H
