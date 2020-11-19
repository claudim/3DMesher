#include "Features_detector.h"

void Features_detector::detect(Polyhedron &polyhedron){


    // Constrain edges with a dihedral angle over 60° // dihedral angle <= 60°
    typedef boost::property_map<Polyhedron, CGAL::edge_is_feature_t>::type EIFMap;
    //typedef typename Patch_id = int;
    typedef boost::property_map<Polyhedron, CGAL::face_patch_id_t<int> >::type PIMap;
    typedef boost::property_map<Polyhedron, CGAL::vertex_incident_patches_t<int> >::type VIMap;

    EIFMap eif = get(CGAL::edge_is_feature, polyhedron);
    PIMap pid = get(CGAL::face_patch_id_t<int>(), polyhedron);
    VIMap vip = get(CGAL::vertex_incident_patches_t<int>(), polyhedron);

    CGAL::Polygon_mesh_processing::detect_sharp_edges(polyhedron, 60, eif);
    //the 1-dimensional features are described as polylines whose endpoints are the added corners.
    CGAL::Polygon_mesh_processing::detect_vertex_incident_patches(polyhedron, pid, vip, eif);

}
