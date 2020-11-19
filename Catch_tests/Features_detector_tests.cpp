#include "../Include/catch.hpp"
#include "test_config.h"
#include "Features_detector.h"
#include <OFF_Reader.h>
#include "STL_reader.h"

TEST_CASE("must_detect_8_Corners_and_12_edges") {

//    std::string fileName = data_path + "/cubeTest.off";
//    OFF_Reader reader = OFF_Reader();
    std::string fileName = data_path + "/cubeTest.stl";
    //std::string fileName = data_path + "/cube_with_more_than_12_triangles.stl";
    STL_reader reader = STL_reader();

    Polyhedron polyhedron = reader.read(fileName);

    Features_detector featuresDetector;
    featuresDetector.detect(polyhedron);

    // Constrain edges with a dihedral angle over 60°
    typedef boost::property_map<Polyhedron, CGAL::edge_is_feature_t>::type EIFMap;
    typedef boost::property_map<Polyhedron, CGAL::vertex_incident_patches_t<int> >::type VIMap;
    typedef typename boost::property_map<Polyhedron, CGAL::vertex_point_t>::type Vpmap;

    //typedef boost::property_map<Polyhedron , CGAL::vertex_feature_degree_t>::type VGDMap;
    EIFMap eif = get(CGAL::edge_is_feature, polyhedron);
    VIMap vip = get(CGAL::vertex_incident_patches_t<int>(), polyhedron);
    Vpmap vpmap = get(CGAL::vertex_point, polyhedron);
    //VGDMap vgd = get(CGAL::vertex_feature_degree, polyhedron);
    int sharp_edges_counter = 0;
    std::vector<Point> vertices;
    for (Edge_descriptor e : edges(polyhedron)) //For all stl borders edges
    {   if (get(eif, e))
        { ++sharp_edges_counter;
            Point startPoint = e.halfedge()->vertex()->point();
            Point endPoint = e.halfedge()->opposite()->vertex()->point();
            vertices.emplace_back(startPoint);
            vertices.emplace_back(endPoint);


//    bool s1 = e.halfedge()->is_feature_edge();
//    bool s2 = e.halfedge()->opposite()->is_feature_edge();
//    bool s3 = e.halfedge()->is_border();
//    bool s4 = e.halfedge()->opposite()->is_border();
//    bool s5 = e.halfedge()->vertex()->is_corner();
//    bool s6 = e.halfedge()->opposite()->vertex()->is_corner();
//    bool s8 = e.halfedge()->vertex()->is_feature_vertex();
//    bool s7 = e.halfedge()->opposite()->vertex()->is_feature_vertex();
//    bool s9 = e.halfedge()->opposite()->is_border_edge();
//
//    std::cout << startPoint << " e " << endPoint << std::endl;
        }
    }
    std::sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

    std::cout << sharp_edges_counter << " sharp edges" << std::endl;
    REQUIRE(sharp_edges_counter == 12);

    int sharp_vertices_counter = vertices.size();
//
//    for(Vertex_descriptor v :vertices(polyhedron)) //For all stl vertices
//    {
//
//       // std::cout<< v->point() <<" grado "<< v->vertex_degree()<<"  nb_of_feature_edges" <<  v->nb_of_feature_edges<<std::endl;
//
//        // Look only at feature vertices
//       Edge_descriptor e = edge(halfedge(v, polyhedron), polyhedron);
//        if( get(eif, e))
////            ++sharp_vertices_counter;
//

//        Point startPoint = e.halfedge()->vertex()->point();
//        Point endPoint = e.halfedge()->opposite()->vertex()->point();
//        std::cout << startPoint << " e " << endPoint << std::endl;
//
////        bool s1 = e.halfedge()->is_feature_edge();
////        bool s2 = e.halfedge()->opposite()->is_feature_edge();
////        bool s3 =e.halfedge()->is_border();
////        bool s4 = e.halfedge()->opposite()->is_border();
////        bool s5 = e.halfedge()->vertex()->is_corner();
////        bool s6 = e.halfedge()->opposite()->vertex()->is_corner();
////        bool s8 = e.halfedge()->vertex()->is_feature_vertex();
////        bool s7 = e.halfedge()->opposite()->vertex()->is_feature_vertex();
////        bool s9 = e.halfedge()->opposite()->is_border_edge();
////        Point startPoint = e.halfedge()->vertex()->point();
////        Point endPoint = e.halfedge()->opposite()->vertex()->point();
//
//
//    }
    REQUIRE(sharp_vertices_counter == 8);

}

TEST_CASE("must_detect_16_features_edges_and_12_features_vertices") {

    std::string fileName = data_path + "/cube_with_more_than_12_triangles.stl";
    STL_reader reader = STL_reader();

    Polyhedron polyhedron = reader.read(fileName);

    Features_detector featuresDetector;
    featuresDetector.detect(polyhedron);

    // Constrain edges with a dihedral angle over 60°
    typedef boost::property_map<Polyhedron, CGAL::edge_is_feature_t>::type EIFMap;

    EIFMap eif = get(CGAL::edge_is_feature, polyhedron);
    int sharp_edges_counter = 0, number_of_corner = 0;
    std::vector<Point> vertices;
    for (Edge_descriptor e : edges(polyhedron)) //For all stl borders edges
    {   if (get(eif, e))
        {
            ++sharp_edges_counter;
            Point startPoint = e.halfedge()->vertex()->point();
            Point endPoint = e.halfedge()->opposite()->vertex()->point();
            vertices.emplace_back(startPoint);
            vertices.emplace_back(endPoint);
        }
    }
    std::sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

    std::cout << sharp_edges_counter << " sharp edges" << std::endl;
    REQUIRE(sharp_edges_counter == 16);

    int sharp_vertices_counter = vertices.size();
    REQUIRE(sharp_vertices_counter == 12);

    //cornes are sharp features that have more than 2 incident sharp edges.

}
