// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Improve the mesh blocks.
//******************************************************************************

#ifndef INC_3DMESHER_BLOCK_REFINER_H
#define INC_3DMESHER_BLOCK_REFINER_H

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/squared_distance_3.h>
#include "Block_maker.h"
#include "External_facet_finder.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

/**
 * @brief Improve blocks.
 *
 * @file Block_refiner.h
 * @class Block_refiner
 */
class Block_refiner {

public:

    /**
     * @brief Improve a single block. Move vertex to a nearest features point according to the distance.
     *
     * @param lcc The mesh.
     * @param blockToRefine The block to improve.
     * @param featuresPoints The features points.
     * @param distance The distance.
     */
    void refineBlock(LCC_3 &lcc, Dart_handle &blockToRefine, const std::vector<Point> &featuresPoints,
                     double distance);

    /**
     * @brief Improve all blocks. Move vertex to a nearest features point according to the distance.
     *
     * @param lcc The mesh.
     * @param points The features points.
     * @param distance The distance.
     */
    void refineBlocks(LCC_3 &lcc, const std::vector<Point> &points, FT distance);
};


#endif //INC_3DMESHER_BLOCK_REFINER_H
