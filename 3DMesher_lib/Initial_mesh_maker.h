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

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Side_of_triangle_mesh.h>
#include "External_block_remover.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
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
        std::cout<<"Blocchi rimossi"<<std::endl;
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


    /**
     * @brief Remove blocks with more than 4 external facets from the lcc.
     *
     * @param lcc The mesh to improve.
     */
    void refine(LCC_3 &lcc) {
        std::vector<Dart_handle> cubes_with_more_than_4_external_facets;
        bool cubes_with_more_than_4_external_facets_not_found = true;

        while(cubes_with_more_than_4_external_facets_not_found) {
            // find the external cubes with more than 4 external facets
            for (LCC_3::One_dart_per_cell_range<3, 3>::iterator cube_it = lcc.one_dart_per_cell<3>().begin(),
                         cube_end_it = lcc.one_dart_per_cell<3>().end(); cube_it != cube_end_it; ++cube_it) {
                FT number_of_external_facets = 0;
                for (LCC_3::One_dart_per_incident_cell_range<2, 3, 3>::iterator facet_it = lcc.one_dart_per_incident_cell<2, 3, 3>(
                        cube_it).begin(),
                             facet_end_it = lcc.one_dart_per_incident_cell<2, 3, 3>(cube_it).end();
                     facet_it != facet_end_it; ++facet_it) {

                    Dart_handle near_cell_facet_dart_handle = lcc.beta(facet_it, 3);
                    if (near_cell_facet_dart_handle == lcc.null_dart_handle) {
                        number_of_external_facets++;
                    }
                }
                if (number_of_external_facets > 4) {
                    cubes_with_more_than_4_external_facets.emplace_back(cube_it);
                }
            }
            if(!cubes_with_more_than_4_external_facets.empty())
            {
                cubes_with_more_than_4_external_facets_not_found = false;
            }
            // remove the cubes found
            for (Dart_handle cube: cubes_with_more_than_4_external_facets) {
                blockRemover.removeBlock(lcc, cube);
            }
            cubes_with_more_than_4_external_facets.clear();
        }
        std::cout<<"Blocchi rimossi nel refiner"<<std::endl;
    }

private:
    /*
     * The reference to the block remover concrete strategy.
     */
    Block_remover_strategy blockRemover;
};


#endif //INC_3DMESHER_INITIAL_MESH_MAKER_H
