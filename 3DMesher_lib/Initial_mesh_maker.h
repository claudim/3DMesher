// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Remove Blocks operations for the construction of the initial mesh starting from a grid that contains the input(polyhedron). The initial mesh is a coarse mesh.
//******************************************************************************

#ifndef INC_3DMESHER_INITIAL_MESH_MAKER_H
#define INC_3DMESHER_INITIAL_MESH_MAKER_H

#include "MyLCC.h"
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Side_of_triangle_mesh.h>
#include "External_block_remover.h"

typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

/**
 * @brief Some operations for the construction of the initial mesh. The initial mesh is a coarse mesh.
 *
 * @file Initial_mesh_maker.h
 * @class Initial_mesh_maker
 * @tparam Block_remover_strategy The block remover concrete strategy class to use for remove the unuseful blocks.
 * The default concrete strategy is the External_block_remover class.
 *
 *
 * The initial mesh is the context part in the Strategy design pattern. It is implemented using C++ template approach.
 * How use this class: Initial_mesh_maker<Block_remover_concrete_strategy> initMeshMaker;
 */
template<class Block_remover_strategy = External_block_remover>
class Initial_mesh_maker{
public:

    /**
     * @brief Remove unuseful blocks, according to the adopted strategy, from the lcc.
     *
     * @param lcc A grid that contains the polyhedron input. The mesh to improve.
     * @param polyhedron The input which the mesh must represent.
     */
    void removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron){
        blockRemover.removeBlocks(lcc, polyhedron);
        std::cout<<"Removed Blocks"<<std::endl;
    }

    /**
     * @brief Remove unuseful blocks, according to the adopted strategy, from the lcc.
     *
     * @param lcc A grid that contains the polyhedron input. The mesh to improve.
     * @param polyhedron The input which the mesh must represent.
     * @param distance The distance according which some blocks must be removed.
     */
    void removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance){
        blockRemover.removeBlocks(lcc, polyhedron, distance);
    }

private:
    /*
     * The reference to the block remover concrete strategy.
     */
    Block_remover_strategy blockRemover;
};


#endif //INC_3DMESHER_INITIAL_MESH_MAKER_H
