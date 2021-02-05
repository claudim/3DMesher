// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Create a new block.
//******************************************************************************

#ifndef INC_3DMESHER_BLOCK_MAKER_H
#define INC_3DMESHER_BLOCK_MAKER_H

#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include "MyLCC.h"

/**
 * @brief This class is responsible for the creation of a new block.
 *
 * @file Block_maker.h
 * @class Block_maker
 */
class Block_maker {
public:
    /**
     * @brief Create a cube of lg dimension in the mesh starting from basepoint.
     *
     * @param lcc The mesh where create the cube.
     * @param basepoint The cube starting point.
     * @param lg The cube dimension.
     * @return A cube handle.
     */
    Dart_handle make_cube(LCC_3& lcc, const Point& basepoint, FT& lg);

    /**
     * @brief Create a single hexahedron (a block) in the mesh.
     *
     * @param lcc The mesh.
     * @param vertices The hexahedron vertices.
     * @return A block handle.
     */
    Dart_handle make_block(LCC_3 &lcc, const std::vector<Point> &vertices);
};


#endif //INC_3DMESHER_BLOCK_MAKER_H
