// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Remove blocks that intersect the boundary.
//******************************************************************************

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
#include "More_external_block_finder.h"


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
    /**
     * @brief Remove all blocks that intersect the polyhedron boundary.
     *
     * @param lcc The mesh to remove the block from.
     * @param polyhedron The polyhedron.
     */
    void removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron);

    void removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance);

    void removeBlock(LCC_3& lcc, Dart_handle& blockToRemove);

    //template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
//    bool is_block_to_be_removed(const LCC_3 &lcc,
//                                const CGAL::Combinatorial_map_base::One_dart_per_cell_const_range()<3, 3>::const_iterator &lcc_cells_iterator,
//                                const Polyhedron &polyhedron);
    /**
     * @brief Check if a block has to be removed.
     *
     * @param lcc The mesh.
     * @param block The block to check.
     * @param polyhedron The polyhedron.
     * @return true if has to be removed, false otherwise.
     */
    bool is_block_to_be_removed(const LCC_3 &lcc,
                                const Dart_handle& block,
                                const Polyhedron &polyhedron);

    /**
     * @brief Check if a block has to be removed.
     *
     * @param lcc The mesh.
     * @param block The block to check.
     * @param polyhedron The polyhedron.
     * @param distance How far a block must be from the polyhedron to be removed.
     * @return true if has to be removed, false otherwise.
     */
    bool is_block_to_be_removed(const LCC_3 &lcc,
                                const Dart_handle& block,
                                const Polyhedron &polyhedron,
                                const double &distance);

    /**
     * @brief Check if a block is too close to the boundary using the block barycenter approach.
     * A block is too close if the distance between the block barycenter and the polyhedron < the distance parameter.
     *
     * @param lcc The mesh.
     * @param block The block to check.
     * @param polyhedron The polyhedron.
     * @param distance How far a block must be from the polyhedron.
     * @param vertexLocationFinder Object capable to check if a point is inside/outside/on_boundary of a polyhedron.
     * @return true if it is too close, false otherwise.
     */
    bool is_block_too_close_to_the_boundary(const LCC_3 &lcc, const Dart_handle &block,
                                            const Polyhedron &polyhedron, const double &distance,
                                            Vertex_location_finder& vertexLocationFinder);

    /**
     * @brief Check if a block is too close to the boundary using 3 points approach. If a block facet has 3 or 4 points too close to the boundary, the block must be removed.
     *
     * @param lcc The mesh.
     * @param block The block to check.
     * @param polyhedron The polyhedron.
     * @param distance How far a block must be from the polyhedron.
     * @param vertexLocationFinder Object capable to check if a point is inside/outside/on_boundary of a polyhedron.
     * @return true if it is too close, false otherwise.
     */
    bool is_block_too_close_to_the_boundary2(const LCC_3 &lcc, const Dart_handle &block,
                                             const Polyhedron &polyhedron, const double &distance,
                                             Vertex_location_finder &vertexLocationFinder);

    /**
     * @brief Check if the block intersects the polyhedron boundary.
     *
     * @param lcc The mesh.
     * @param block The block to check.
     * @param polyhedron The polyhedron.
     * @param vertexLocationFinder Object capable to check if a point is inside/outside/on_boundary of a polyhedron.
     * @return true if the block intersects the polyhedron boundary, false otherwise.
     */
    bool is_block_on_boundary(const LCC_3 &lcc, const Dart_handle &block, const Polyhedron &polyhedron,
                              Vertex_location_finder &vertexLocationFinder);

    /**
     * @brief Remove the on_boundary blocks and blocks that are too close to the boundary. Use this function only if the external blocks has already been removed.
     *
     * @param lcc The mesh.
     * @param polyhedron The polyhedron.
     * @param distance How far a block must be from the polyhedron.
     */
    void removeBlocks_afterRemovedExternalBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance);

    /**
     * @brief Remove on boundary blocks and blocks too close to the boundary.
     * To find the blocks that are too close to the boundary is used 3 points approach. If a block facet has 3 or 4 points too close to the boundary, the block must be removed.
     *
     * @param lcc The mesh.
     * @param polyhedron The polyhedron.
     * @param distance how far a block must be from the polyhedron.
     */
    void removeBlocks2(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance);
};




#endif //INC_3DMESHER_ONBOUNDARY_BLOCK_REMOVER_H
