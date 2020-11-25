// Copyright (c) 2020 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Remove external and onBoundary Blocks for the construction of the initial mesh starting from a grid that contains the input(polyhedron). The initial mesh is a coarse mesh.
//******************************************************************************

#ifndef INC_3DMESHER_EXTERNAL_AND_ONBOUNDARY_REMOVER_H
#define INC_3DMESHER_EXTERNAL_AND_ONBOUNDARY_REMOVER_H
#include "External_block_remover.h"
#include "OnBoundary_block_remover.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

/**
 * @brief Some operations to remove blocks from the mesh.
 *
 * @file External_and_onBoundary_remover.h
 * @class External_and_onBoundary_remover
 *
 *
 * The External_and_onBoundary_remover is one of the concrete strategy class in the Strategy design pattern.
 */
class External_and_onBoundary_remover {

public:
/**
     * @brief Remove Remove external and on boundary blocks from lcc.
     *
     * @param lcc A grid that contains the polyhedron input. The mesh to improve.
     * @param polyhedron The input which the mesh must represent.
     */
    void removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron);

    /**
     * @brief Remove blocks from the lcc. It removes external,on boundary blocks and blocks which are blocks less than distance from the boundary.
     *
     * @param lcc A grid that contains the polyhedron input. The mesh to improve.
     * @param polyhedron The input which the mesh must represent.
     * @param distance The distance according which some blocks must be removed.
     */
    void removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance);

    /**
     * @brief Remove the block from the mesh.
     *
     * @param lcc The mesh.
     * @param blockToRemove The block to remove from the mesh.
     */
    void removeBlock(LCC_3& lcc, Dart_handle& blockToRemove);
};


#endif //INC_3DMESHER_EXTERNAL_AND_ONBOUNDARY_REMOVER_H