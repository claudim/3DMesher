// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Detect geometric features in a polyhedron.
//******************************************************************************

#ifndef INC_3DMESHER_FEATURES_DETECTOR_H
#define INC_3DMESHER_FEATURES_DETECTOR_H

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Polygon_mesh_processing/detect_features.h>
#include "External_block_remover.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

typedef boost::graph_traits<Polyhedron>::edge_descriptor Edge_descriptor;
typedef boost::graph_traits<Polyhedron>::vertex_descriptor Vertex_descriptor;

/**
 * @brief Detect geometric features in the polyhedron.
 *
 * @file Features_detector.h
 * @class Features_detector
 */
class Features_detector {
public:

    /**
     * @brief Detect the geometric features.
     *
     * @param polyhedron The polyhedron where detect the geometric features.
     */
    void detect(Polyhedron &polyhedron);

    /**
     * @brief Detect the geometric features.
     *
     * @param polyhedron The polyhedron where detect the geometric features.
     * @param featuresPoints Vector where stores vertices.
     */
    void detect(Polyhedron &polyhedron, std::vector<Point> &featuresPoints);
};


#endif //INC_3DMESHER_FEATURES_DETECTOR_H
