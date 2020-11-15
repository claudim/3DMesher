#include "../Include/catch.hpp"
#include "test_config.h"
#include <OFF_Reader.h>
#include "Block_maker.h"
#include "Writer.h"
#include <InitialMesh_boundary_connector.h>
#include <CGAL/Polygon_mesh_processing/bbox.h>
#include <CGAL/Bbox_3.h>

TEST_CASE("InitialMesh_boundary_connector cube in cube"){

    Point internalBlockBasePoint = Point(2, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();

    boundaryConnector.connect(lcc, polyhedron);

    int number_of_cubes = 0;
    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
    {
        number_of_cubes++;
    }
    REQUIRE(number_of_cubes == 7);

    int number_of_facets = 0;
    for (LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator lcc_facets_iterator = lcc.one_dart_per_cell<2,3>().begin(),
                 lcc_facets_end_iterator = lcc.one_dart_per_cell<2,3>().end(); lcc_facets_iterator != lcc_facets_end_iterator; ++lcc_facets_iterator)
    {
        number_of_facets++;
    }
    REQUIRE( number_of_facets == 24);

    int number_of_edges = 0;
    for (LCC_3::One_dart_per_cell_const_range<1,3>::const_iterator lcc_edges_iterator = lcc.one_dart_per_cell<1,3>().begin(),
                 lcc_edges_end_iterator = lcc.one_dart_per_cell<1,3>().end(); lcc_edges_iterator != lcc_edges_end_iterator; ++lcc_edges_iterator)
    {
        number_of_edges++;
    }
    REQUIRE( number_of_edges == 32);

    int number_of_vertices = 0;
    for (LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator lcc_vertex_iterator = lcc.one_dart_per_cell<0,3>().begin(),
                 lcc_vertex_end_iterator = lcc.one_dart_per_cell<0,3>().end(); lcc_vertex_iterator != lcc_vertex_end_iterator; ++lcc_vertex_iterator)
    {
        number_of_vertices++;
    }
    REQUIRE( number_of_vertices == 16);

    // Output
    std::ofstream medit_file("out.mesh");
    Writer w;
    w.output_to_medit(medit_file,lcc);

    // const CGAL::Bbox_3 polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);
    // const CGAL::Bbox_3 lcc_bbox3 = CGAL::Polygon_mesh_processing::bbox(lcc);
    // const CGAL::Bbox_3 lcc_bbox3 = bbox_3(lcc.one_dart_per_cell<0,3>().begin(), lcc.one_dart_per_cell<0,3>().end());
    // REQUIRE( polyhedron_bbox3 == lcc_bbox3);

}
TEST_CASE("InitialMesh_boundary_connector cube in sphere"){

    Point internalBlockBasePoint = Point(2, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    std::string fileName = data_path + "/sphere.off";


}


TEST_CASE("InitialMesh_boundary_connector cubes in cube"){

    Point internalBlockBasePoint1 = Point(2, 2, 2);
    Point internalBlockBasePoint2 = Point(3, 2, 2);
    Point internalBlockBasePoint3 = Point(2, 2, 3);
    Point internalBlockBasePoint4 = Point(3, 2, 3);
//    Point internalBlockBasePoint5 = Point(2, 3, 2);
//    Point internalBlockBasePoint6 = Point(3, 3, 2);
//    Point internalBlockBasePoint7 = Point(2, 3, 3);
//    Point internalBlockBasePoint8 = Point(3, 3, 3);

    FT internalBlockLg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
    Dart_handle  d =  blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint5, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint6, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint7, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint8, internalBlockLg);
//lcc.display_characteristics(std::cout);
    lcc.sew3_same_facets(); // link all blocks in lcc  with same facets if they are not linked.
    //lcc.display_characteristics(std::cout);

    int i = 0;
    for(LCC_3::One_dart_per_incident_cell_const_range<2,0,3>::const_iterator f_it = lcc.one_dart_per_incident_cell<2,0,3>(d).begin(),
                f_end_it = lcc.one_dart_per_incident_cell<2,0,3>(d).end(); f_it != f_end_it; ++f_it)
    {
        //Vector map = compute_normal_of_cell_0(lcc, f_it);
        i++;
        std::cout << i <<std::endl;
    }


    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
    boundaryConnector.connect(lcc, polyhedron);

//    int number_of_cubes = 0;
//    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
//    {
//        number_of_cubes++;
//    }
//    REQUIRE(number_of_cubes == 32);

//    int number_of_vertices = 0;
//    for (LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator lcc_vertex_iterator = lcc.one_dart_per_cell<0,3>().begin(),
//                 lcc_vertex_end_iterator = lcc.one_dart_per_cell<0,3>().end(); lcc_vertex_iterator != lcc_vertex_end_iterator; ++lcc_vertex_iterator)
//    {
//        number_of_vertices++;
//    }
//    REQUIRE( number_of_vertices == 83);

//    // Output
//    std::ofstream medit_file("cubesInCube.mesh");
//    Writer w;
//    w.output_to_medit(medit_file,lcc);
}

//TEST_CASE("link blocks") {
//
//    Point internalBlockBasePoint = Point(2, 0, 0);
//    FT internalBlockLg = 2;
//    LCC_3 lcc;
//    Block_maker blockMaker = Block_maker();
//    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);
//
//    SECTION("second block built with make_cube function") {
//
//        //una faccia in comune
//        Point internalBlockBasePoint2 = Point(0, 0, 0);
//        Dart_handle internalBlock2 = blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
//
//        //lcc.display_characteristics(std::cout);
//
//        InitialMesh_boundary_connector initialMeshBoundaryConnector;
//        initialMeshBoundaryConnector.linkBlock(lcc, internalBlock, internalBlock2);
//
//        FT number_of_facets = 0;
//        for(LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator facet_it = lcc.one_dart_per_cell<2>().begin(),
//                    facet_end_it = lcc.one_dart_per_cell<2>().end(); facet_it != facet_end_it; ++facet_it){
//            number_of_facets++;
//        }
//        REQUIRE(number_of_facets == 11);
//
//        FT number_of_vertices = 0;
//        for(LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator vertex_it = lcc.one_dart_per_cell<0>().begin(),
//                    vertex_end_it = lcc.one_dart_per_cell<0>().end(); vertex_it != vertex_end_it; ++vertex_it){
//            number_of_vertices ++;
//        }
//        REQUIRE(number_of_vertices  == 12);
//    }
//
//    SECTION("second block built with make_hexahedron function") {
//        std::vector<std::pair<Point, Point>> hexahedronPoints;
//
//        hexahedronPoints.emplace_back(Point(0,0,0),Point(2,2,2));
//        hexahedronPoints.emplace_back(Point(0,0,6),Point(2,2,4));
//        hexahedronPoints.emplace_back(Point(6,0,6),Point(4,2,4));
//        hexahedronPoints.emplace_back(Point(6,0,0),Point(4,2,2));
//
//
//        //una faccia in comune
//        Dart_handle  block2 = lcc.make_hexahedron(hexahedronPoints[0].second,
//                            hexahedronPoints[1].second,
//                            hexahedronPoints[2].second,
//                            hexahedronPoints[3].second,
//                            hexahedronPoints[3].first,
//                            hexahedronPoints[0].first,
//                            hexahedronPoints[1].first,
//                            hexahedronPoints[2].first);
//
//
//
//        lcc.display_characteristics(std::cout);
//
//        InitialMesh_boundary_connector initialMeshBoundaryConnector;
//        initialMeshBoundaryConnector.linkBlock(lcc, internalBlock, block2);
//        lcc.display_characteristics(std::cout);
//
//        FT number_of_facets = 0;
//        for(LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator facet_it = lcc.one_dart_per_cell<2>().begin(),
//                    facet_end_it = lcc.one_dart_per_cell<2>().end(); facet_it != facet_end_it; ++facet_it){
//            number_of_facets++;
//        }
//        REQUIRE(number_of_facets == 11);
//
//        FT number_of_vertices = 0;
//        for(LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator vertex_it = lcc.one_dart_per_cell<0>().begin(),
//                    vertex_end_it = lcc.one_dart_per_cell<0>().end(); vertex_it != vertex_end_it; ++vertex_it){
//            number_of_vertices ++;
//        }
//        REQUIRE(number_of_vertices  == 12);
//
//        hexahedronPoints.emplace_back(Point(6,0,0),Point(4,2,2));
//        hexahedronPoints.emplace_back(Point(6,0,6),Point(4,2,4));
//        hexahedronPoints.emplace_back(Point(6,6,6),Point(4,4,4));
//        hexahedronPoints.emplace_back(Point(6,6,0),Point(2,4,4));
//
//
//        hexahedronPoints.emplace_back(Point(6,6,0),Point(4,4,2));
//        hexahedronPoints.emplace_back(Point(6,6,6),Point(4,4,4));
//        hexahedronPoints.emplace_back(Point(0,6,6),Point(2,4,4));
//        hexahedronPoints.emplace_back(Point(0,6,0),Point(2,4,2));
//
//        hexahedronPoints.emplace_back(Point(0,6,0),Point(2,4,2));
//        hexahedronPoints.emplace_back(Point(0,6,6),Point(2,4,4));
//        hexahedronPoints.emplace_back(Point(0,0,6),Point(2,2,4));
//        hexahedronPoints.emplace_back(Point(0,0,0),Point(2,2,2));
//
//        hexahedronPoints.emplace_back(Point(0,0,0),Point(2,2,2));
//        hexahedronPoints.emplace_back(Point(6,0,0),Point(4,2,2));
//        hexahedronPoints.emplace_back(Point(6,6,0),Point(4,4,2));
//        hexahedronPoints.emplace_back(Point(0,6,0),Point(2,4,2));
//
//        hexahedronPoints.emplace_back(Point(0,0,6),Point(2,2,4));
//        hexahedronPoints.emplace_back(Point(0,6,6),Point(2,4,4));
//        hexahedronPoints.emplace_back(Point(6,6,6),Point(4,4,4));
//        hexahedronPoints.emplace_back(Point(6,0,6),Point(4,2,4));
//    }
//
//
////    //uno spigolo in comune
////    Point internalBlockBasePoint3 = Point(4, 2, 0);
////    Dart_handle internalBlock3 = blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
////    number_of_incident_cubes = 0;
////    for (LCC_3::One_dart_per_incident_cell_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).begin(),
////                 lcc_cells_end_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
////    {
////        number_of_incident_cubes++;
////    }
////    REQUIRE(number_of_incident_cubes == 2);
////
////    //un solo vertice in comune
////    Point internalBlockBasePoint4 = Point(4, 2, 2);
////    Dart_handle internalBlock4 = blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
////    number_of_incident_cubes = 0;
////    for (LCC_3::One_dart_per_incident_cell_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).begin(),
////                 lcc_cells_end_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
////    {
////        number_of_incident_cubes++;
////    }
////    REQUIRE(number_of_incident_cubes == 3);
//
//}