// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Univaq Hex Mesh algorithm
//******************************************************************************


#ifndef INC_3DMESHER_UNIVAQHEXMESHALGORITHM_H
#define INC_3DMESHER_UNIVAQHEXMESHALGORITHM_H

#include "Grid_maker.h"
#include "External_block_remover.h"
#include "Volume_Validator.h"
#include "Grid_boundary_connector.h"

/**
 * @brief Execute the Univaq Hex Mesh algorithm.
 *
 * @file UnivaqHexMeshAlgorithm.h
 * @class UnivaqHexMeshAlgorithm
 */
class UnivaqHexMeshAlgorithm {

public:
    /**
     * @brief Execute the Univaq Hex Mesh algorithm with a specified resolution.
     *
     * @param polyhedron The polyhedron
     * @param hex_mesh The hexahedral mesh generated by the algorithm.
     * @param resolution The resolution is the number of subdivisions to be made in the edge of minimum dimension of the bounding box of the polyhedron.
     */
    void run(const Polyhedron& polyhedron, LCC_3& hex_mesh, double resolution);

    /**
     * @brief Execute the Univaq Hex Mesh algorithm.
     *
     * @param polyhedron The polyhedron
     * @param hex_mesh The hexahedral mesh generated by the algorithm.
     */
    void run(const Polyhedron& polyhedron, LCC_3& hex_mesh);

};


#endif //INC_3DMESHER_UNIVAQHEXMESHALGORITHM_H
