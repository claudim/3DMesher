#include "../Include/catch.hpp"
#include "test_config.h"
#include <OFF_Reader.h>
#include "Block_maker.h"
#include "External_facet_finder.h"
#include "Writer.h"
#include <InitialMesh_boundary_connector.h>
#include <CGAL/Polygon_mesh_processing/bbox.h>

//TEST_CASE("InitialMesh_boundary_connector"){
//
//    Point internalBlockBasePoint = Point(2, 2, 2);
//    FT internalBlockLg = 2;
//    LCC_3 lcc;
//    Block_maker blockMaker = Block_maker();
//    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);
//
//    std::string fileName = data_path + "/cubeTest.off";
//
//    OFF_Reader reader = OFF_Reader();
//    Polyhedron polyhedron = reader.read(fileName);
//
//    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
//
//    boundaryConnector.connect(lcc, polyhedron);
//
//    int number_of_cubes = 0;
//    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
//    {
//        number_of_cubes++;
//    }
//
//    REQUIRE(number_of_cubes == 7);
////    std::ofstream medit_file("test1.mesh");
////    Writer writer;
////    writer.output_to_medit(medit_file, lcc);
////    medit_file.close();
//
////    int number_of_facets = 0;
////    for (LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator lcc_facets_iterator = lcc.one_dart_per_cell<2,3>().begin(),
////                 lcc_facets_end_iterator = lcc.one_dart_per_cell<2,3>().end(); lcc_facets_iterator != lcc_facets_end_iterator; ++lcc_facets_iterator)
////    {
////        number_of_facets++;
////    }
////
////    REQUIRE( number_of_facets == 24);
//
//    int number_of_vertices = 0;
//    for (LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator lcc_vertex_iterator = lcc.one_dart_per_cell<0,3>().begin(),
//                 lcc_vertex_end_iterator = lcc.one_dart_per_cell<0,3>().end(); lcc_vertex_iterator != lcc_vertex_end_iterator; ++lcc_vertex_iterator)
//    {
//        number_of_vertices++;
//    }
//
//    REQUIRE( number_of_vertices == 16);
//
//
//    const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);
//
//    //REQUIRE( polyhedron_bbox3.operator==(CGAL::Polygon_mesh_processing::bbox(lcc)));
//
//}

TEST_CASE("link blocks") {

    Point internalBlockBasePoint = Point(2, 0, 0);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    SECTION("second block built with make_cube function") {

        //una faccia in comune
        Point internalBlockBasePoint2 = Point(0, 0, 0);
        Dart_handle internalBlock2 = blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);

        //lcc.display_characteristics(std::cout);

        InitialMesh_boundary_connector initialMeshBoundaryConnector;
        initialMeshBoundaryConnector.linkBlock(lcc, internalBlock, internalBlock2);

        FT number_of_facets = 0;
        for(LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator facet_it = lcc.one_dart_per_cell<2>().begin(),
                    facet_end_it = lcc.one_dart_per_cell<2>().end(); facet_it != facet_end_it; ++facet_it){
            number_of_facets++;
        }
        REQUIRE(number_of_facets == 11);

        FT number_of_vertices = 0;
        for(LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator vertex_it = lcc.one_dart_per_cell<0>().begin(),
                    vertex_end_it = lcc.one_dart_per_cell<0>().end(); vertex_it != vertex_end_it; ++vertex_it){
            number_of_vertices ++;
        }
        REQUIRE(number_of_vertices  == 12);
    }

    SECTION("second block built with make_hexahedron function") {
        std::vector<std::pair<Point, Point>> hexahedronPoints;

        hexahedronPoints.emplace_back(Point(0,0,0),Point(2,2,2));
        hexahedronPoints.emplace_back(Point(0,0,6),Point(2,2,4));
        hexahedronPoints.emplace_back(Point(6,0,6),Point(4,2,4));
        hexahedronPoints.emplace_back(Point(6,0,0),Point(4,2,2));




        //una faccia in comune
        Dart_handle  block2 = lcc.make_hexahedron(hexahedronPoints[0].second,
                            hexahedronPoints[1].second,
                            hexahedronPoints[2].second,
                            hexahedronPoints[3].second,
                            hexahedronPoints[3].first,
                            hexahedronPoints[0].first,
                            hexahedronPoints[1].first,
                            hexahedronPoints[2].first);



        lcc.display_characteristics(std::cout);

        InitialMesh_boundary_connector initialMeshBoundaryConnector;
        initialMeshBoundaryConnector.linkBlock(lcc, internalBlock, block2);
        lcc.display_characteristics(std::cout);

        FT number_of_facets = 0;
        for(LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator facet_it = lcc.one_dart_per_cell<2>().begin(),
                    facet_end_it = lcc.one_dart_per_cell<2>().end(); facet_it != facet_end_it; ++facet_it){
            number_of_facets++;
        }
        REQUIRE(number_of_facets == 11);

        FT number_of_vertices = 0;
        for(LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator vertex_it = lcc.one_dart_per_cell<0>().begin(),
                    vertex_end_it = lcc.one_dart_per_cell<0>().end(); vertex_it != vertex_end_it; ++vertex_it){
            number_of_vertices ++;
        }
        REQUIRE(number_of_vertices  == 12);

        hexahedronPoints.emplace_back(Point(6,0,0),Point(4,2,2));
        hexahedronPoints.emplace_back(Point(6,0,6),Point(4,2,4));
        hexahedronPoints.emplace_back(Point(6,6,6),Point(4,4,4));
        hexahedronPoints.emplace_back(Point(6,6,0),Point(2,4,4));


        hexahedronPoints.emplace_back(Point(6,6,0),Point(4,4,2));
        hexahedronPoints.emplace_back(Point(6,6,6),Point(4,4,4));
        hexahedronPoints.emplace_back(Point(0,6,6),Point(2,4,4));
        hexahedronPoints.emplace_back(Point(0,6,0),Point(2,4,2));

        hexahedronPoints.emplace_back(Point(0,6,0),Point(2,4,2));
        hexahedronPoints.emplace_back(Point(0,6,6),Point(2,4,4));
        hexahedronPoints.emplace_back(Point(0,0,6),Point(2,2,4));
        hexahedronPoints.emplace_back(Point(0,0,0),Point(2,2,2));

        hexahedronPoints.emplace_back(Point(0,0,0),Point(2,2,2));
        hexahedronPoints.emplace_back(Point(6,0,0),Point(4,2,2));
        hexahedronPoints.emplace_back(Point(6,6,0),Point(4,4,2));
        hexahedronPoints.emplace_back(Point(0,6,0),Point(2,4,2));

        hexahedronPoints.emplace_back(Point(0,0,6),Point(2,2,4));
        hexahedronPoints.emplace_back(Point(0,6,6),Point(2,4,4));
        hexahedronPoints.emplace_back(Point(6,6,6),Point(4,4,4));
        hexahedronPoints.emplace_back(Point(6,0,6),Point(4,2,4));
    }


//    //uno spigolo in comune
//    Point internalBlockBasePoint3 = Point(4, 2, 0);
//    Dart_handle internalBlock3 = blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
//    number_of_incident_cubes = 0;
//    for (LCC_3::One_dart_per_incident_cell_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
//    {
//        number_of_incident_cubes++;
//    }
//    REQUIRE(number_of_incident_cubes == 2);
//
//    //un solo vertice in comune
//    Point internalBlockBasePoint4 = Point(4, 2, 2);
//    Dart_handle internalBlock4 = blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
//    number_of_incident_cubes = 0;
//    for (LCC_3::One_dart_per_incident_cell_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_incident_cell<3,3,3>(internalBlock).end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
//    {
//        number_of_incident_cubes++;
//    }
//    REQUIRE(number_of_incident_cubes == 3);

}