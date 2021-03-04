// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Remove Blocks for the construction of the initial mesh starting from a grid that contains the input(polyhedron). The initial mesh is a coarse mesh.
// The blocks to remove do not have any internal point at the boundary.
//******************************************************************************


#ifndef INC_3DMESHER_EXTERNAL_BLOCK_REMOVER_H
#define INC_3DMESHER_EXTERNAL_BLOCK_REMOVER_H

#include <MyLCC.h>
#include "Block_maker.h"
#include "Vertex_location_finder.h"
#include "External_and_onBoundary_remover.h"
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Side_of_triangle_mesh.h>

//
//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//typedef LCC_3::Point Point;
typedef CGAL::Bbox_3 Bbox;
//typedef LCC_3::Traits Traits;
//typedef LCC_3::FT FT;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;
typedef CGAL::Vertex_location_finder Vertex_location_finder;


/**
 * @brief Some operations to obtain the initial mesh starting from a grid. The initial mesh is a coarse mesh.
 * The grid is a discretization with voxels of the bounding box of the input polyhedron.
 *
 * @file External_block_remover.h
 * @class External_block_remover
 */
class External_block_remover {

public:

    /**
     * @brief Remove the block from the mesh.
     *
     * @param hex_mesh The mesh to improve
     * @param blockToRemove The block to remove.
     */
    void removeBlock(LCC_3& hex_mesh, Dart_handle& blockToRemove);

    /**
     * @brief Check if a block is to remove. The grid block is to remove if it do not have any internal point.
     * A point is an internal point if is inside the boundary polyhedron.
     *
     * @param lcc The grid to improve according to the external blocks removing.
     * @param block The block to check if it is to remove.
     * @param polyhedron The polyhedron.
     * @return true if the block is to remove, false otherwise.
     */
    bool is_block_to_be_removed(const LCC_3 &lcc, const Dart_handle &block, const Polyhedron &polyhedron,
                                Vertex_location_finder &vertexLocationFinder);

    /**
     * @brief Revome all grid blocks that have external points. A point is an external point if is outside the boundary polyhedron.
     * At the end of the operation, the grid becomes the initial mesh.
     *
     * @param lcc The grid.
     * @param polyhedron The polyhedron.
     */
    void removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron);

    /**
     * @brief Empty implementation. Do not remove blocks.
     *
     * @param lcc The grid.
     * @param polyhedron The polyhedron.
     * @param distance The distance according which some blocks must be removed.
     */
    void removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron, const double &distance);

    void get_block_centroid(LCC_3 &hex_mesh, Dart_handle &block, Point &centroid_to_find);
    void get_const_block_centroid(const LCC_3& hex_mesh, const Dart_handle& block, Point &centroid_to_find);
};




#endif //INC_3DMESHER_EXTERNAL_BLOCK_REMOVER_H
