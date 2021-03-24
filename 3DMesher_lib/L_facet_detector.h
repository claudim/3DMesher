// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Find the mesh facets that form an L.
//******************************************************************************


#ifndef INC_3DMESHER_L_FACET_DETECTOR_H
#define INC_3DMESHER_L_FACET_DETECTOR_H

#include "MyLCC.h"
#include "External_facet_finder.h"
#include "Grid_maker.h"

/**
 * @brief Find the mesh facets that form an L.
 *
 * @file L_facet_detector.h
 * @class L_facet_detector
 */
class L_facet_detector {

public:
    /**
     * @brief Detect the mesh facets that form an L.
     *
     * @param lcc The mesh
     * @return The facets
     */
    std::vector<Dart_handle> detect_L_facets(LCC_3 &lcc);

    /**
     * @brief Compute the facet normal segment.
     *
     * @param lcc The mesh
     * @param facet The facet
     */
    CGAL::Segment_3<K> compute_facet_normal_segment(LCC_3 &lcc, Dart_handle &facet);

    /**
     * @brief  Find the shared point between two facets.
     *
     * @param lcc The mesh.
     * @param facet_1 The first facet.
     * @param facet_2 The second facet.
     * @return The shared points.
     */
    std::vector<Point> find_shared_point(LCC_3 &lcc, Dart_handle& facet_1, Dart_handle& facet_2);

    /**
     * @brief Check if a facet belong to a block that form a L.
     *
     * @param lcc the mesh.
     * @param facet the facet.
     * @param shared_points the shared points.
     */
    bool is_a_L_facets(LCC_3 &lcc, Dart_handle &facet, std::vector<Point> shared_points);
};




#endif //INC_3DMESHER_L_FACET_DETECTOR_H
