// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Find all the external facet of the mesh. An external facet is a facet which belongs to a single hexahedron.
//******************************************************************************

#ifndef INC_3DMESHER_EXTERNAL_FACET_FINDER_H
#define INC_3DMESHER_EXTERNAL_FACET_FINDER_H

#include <iostream>
#include <vector>

#include <MyLCC.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

/**
 * @brief Find all the external facet of the mesh.
 *
 * @file External_facet_finder.h
 * @class External_facet_finder
 */
class External_facet_finder {

public:

    /**
     * @brief Find the all the constant external facets of the mesh.
     *
     * @param mesh The mesh.
     * @return A vector of costant external facets.
     */
    std::vector<Dart_const_handle> find(const LCC_3 & mesh);

    /**
     * @brief Find the all the external facets of the mesh.
     *
     * @param lcc The mesh.
     * @return  vector of external facets.
     */
    std::vector<Dart_handle> findFacets(LCC_3 & lcc);

    /**
     * @brief Check if a facet is external.
     *
     * @param lcc The mesh.
     * @param near_cell_facet_dart_handle The null facet.
     * @return True if is an external facet, false otherwise.
     */
    bool is_near_cell_facet_null(const LCC_3 &lcc, const Dart_const_handle &near_cell_facet_dart_handle) const;

    /**
     * @brief Check if a facet is external.
     *
     * @param lcc The mesh.
     * @param near_cell_facet_dart_handle The null facet.
     * @return True if is an external facet, false otherwise.
     */
    bool is_near_cell_facet_null(const LCC_3 &lcc, const Dart_handle &near_cell_facet_dart_handle) const;

    /**
     * Find the external facet of a block if there are.
     *
     * @param lcc Set of blocks who the block belongs.
     * @param block Block whose it wants find the external facets.
     * @return The external facets or a vector with zero size.
     */
    std::vector<Dart_handle> find(LCC_3 & lcc, Dart_handle block);
};





#endif //INC_3DMESHER_EXTERNAL_FACET_FINDER_H
