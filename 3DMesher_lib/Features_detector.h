#ifndef INC_3DMESHER_FEATURES_DETECTOR_H
#define INC_3DMESHER_FEATURES_DETECTOR_H

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Polygon_mesh_processing/detect_features.h>
#include "External_block_remover.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

typedef boost::graph_traits<Polyhedron>::edge_descriptor Edge_descriptor;
typedef boost::graph_traits<Polyhedron>::vertex_descriptor Vertex_descriptor;

class Features_detector {
public:

    void detect(Polyhedron &polyhedron);
};


#endif //INC_3DMESHER_FEATURES_DETECTOR_H
