#include "../Include/catch.hpp"
#include "test_config.h"
#include "Block_refiner.h"
#include "OFF_Reader.h"
#include "STL_reader.h"
#include "Block_maker.h"
#include "InitialMesh_boundary_connector.h"

TEST_CASE("must_move_1_vertices_from_its_position_to_the_feature_vertice_position", "[refineBlock][Block_refiner]") {
    
    std::string fileName = data_path + "/hexTest.off";
    OFF_Reader reader;
    const Polyhedron polyhedron = reader.read(fileName);

    Point basePoint = Point(2,2,2);  FT lg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc,basePoint,lg);

    InitialMesh_boundary_connector connector;
    connector.connect(lcc, polyhedron);

    Block_refiner blockRefiner;
    Point p = Point(0,0,7);
    std::vector<Point> points;
    points.emplace_back(p);
    
    for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
         lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
        blockRefiner.refineBlock(lcc, lcc_cells_iterator, points, lg);
    }

    // DEVE ESSERCI IL PUNTO 007
    // DEVE ESSERCI IN 3 ESAEDRI
    // #0-cells=16, #1-cells=32, #2-cells=24, #3-cells=7
    bool isTherePPoint = false;
    FT number_of_Found_pPoint = 0;

    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
    {
        for(LCC_3::One_dart_per_incident_cell_const_range<0,3,3>::const_iterator vertex_cell_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).begin(),
                    vertex_cell_end_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).end();
                    vertex_cell_it != vertex_cell_end_it; ++vertex_cell_it)
        {
            if(lcc.point(vertex_cell_it) == p)
            {
                isTherePPoint = true;
                number_of_Found_pPoint++;
            }
        }
    }
    REQUIRE(isTherePPoint == true);
    REQUIRE(number_of_Found_pPoint == 3);
    const FT number_of_cubes = lcc.one_dart_per_cell<3>().size();
    const FT number_of_facets = lcc.one_dart_per_cell<2>().size();
    const FT number_of_vertices = lcc.one_dart_per_cell<0>().size();
    REQUIRE(number_of_cubes == 7);
    REQUIRE(number_of_facets == 24);
    REQUIRE(number_of_vertices == 16);

//    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
//    {
//        std::cout<<"hex: "<<std::endl;
//        for(LCC_3::One_dart_per_incident_cell_const_range<0,3,3>::const_iterator vertex_cell_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).begin(),
//                    vertex_cell_end_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).end();
//                    vertex_cell_it != vertex_cell_end_it; ++vertex_cell_it)
//        {
//            std::cout<<lcc.point(vertex_cell_it)<<std::endl;
//        }
//    }

}

TEST_CASE("must_move_2_vertices_from_its_position_to_the_feature_vertice_position", "[refineBlock][Block_refiner]") {

    std::string fileName = data_path + "/hexTest2.off";
    OFF_Reader reader;
    const Polyhedron polyhedron = reader.read(fileName);

    Point basePoint = Point(2,2,2);  FT lg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc,basePoint,lg);

    InitialMesh_boundary_connector connector;
    connector.connect(lcc, polyhedron);

    Block_refiner blockRefiner;
    Point p1 = Point(0,0,7);
    Point p2 = Point(7,7,7);
    std::vector<Point> points;
    points.emplace_back(p1);points.emplace_back(p2);

    for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
         lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
        blockRefiner.refineBlock(lcc, lcc_cells_iterator, points, lg);
    }

    bool isThereP1Point = false;
    bool isThereP2Point = false;
    FT number_of_Found_p1Point = 0;
    FT number_of_Found_p2Point = 0;

    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
    {
        for(LCC_3::One_dart_per_incident_cell_const_range<0,3,3>::const_iterator vertex_cell_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).begin(),
                    vertex_cell_end_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).end();
            vertex_cell_it != vertex_cell_end_it; ++vertex_cell_it)
        {
            if(lcc.point(vertex_cell_it) == p1)
            {
                isThereP1Point = true;
                number_of_Found_p1Point++;
            }
            if(lcc.point(vertex_cell_it) == p2)
            {
                isThereP2Point = true;
                number_of_Found_p2Point++;
            }
        }
    }
    REQUIRE(isThereP1Point == true);
    REQUIRE(isThereP2Point == true);
    REQUIRE(number_of_Found_p1Point == 3);
    REQUIRE(number_of_Found_p2Point == 3);
    const FT number_of_cubes = lcc.one_dart_per_cell<3>().size();
    const FT number_of_facets = lcc.one_dart_per_cell<2>().size();
    const FT number_of_vertices = lcc.one_dart_per_cell<0>().size();
    REQUIRE(number_of_cubes == 7);
    REQUIRE(number_of_facets == 24);
    REQUIRE(number_of_vertices == 16);

}

TEST_CASE("must_move_2_vertices_from_its_position_to_the_feature_vertice_position2", "[refineBlocks][Block_refiner]") {

    std::string fileName = data_path + "/hexTest2.off";
    OFF_Reader reader;
    const Polyhedron polyhedron = reader.read(fileName);

    Point basePoint = Point(2,2,2);  FT lg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc,basePoint,lg);

    InitialMesh_boundary_connector connector;
    connector.connect(lcc, polyhedron);

    Block_refiner blockRefiner;
    Point p1 = Point(0,0,7);
    Point p2 = Point(7,7,7);
    std::vector<Point> points;
    points.emplace_back(p1); points.emplace_back(p2);

    blockRefiner.refineBlocks(lcc, points, lg);

//    for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
//         lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
//        blockRefiner.refineBlock(lcc, lcc_cells_iterator, points, lg);
//    }

    bool isThereP1Point = false;
    bool isThereP2Point = false;
    FT number_of_Found_p1Point = 0;
    FT number_of_Found_p2Point = 0;

    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
    {
        for(LCC_3::One_dart_per_incident_cell_const_range<0,3,3>::const_iterator vertex_cell_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).begin(),
                    vertex_cell_end_it = lcc.one_dart_per_incident_cell<0,3,3>(lcc_cells_iterator).end();
            vertex_cell_it != vertex_cell_end_it; ++vertex_cell_it)
        {
            Point p = lcc.point(vertex_cell_it);
            if( p == p1)
            {
                isThereP1Point = true;
                number_of_Found_p1Point++;
            }
            if(p == p2)
            {
                isThereP2Point = true;
                number_of_Found_p2Point++;
            }
        }
    }
    REQUIRE(isThereP1Point == true);
    REQUIRE(isThereP2Point == true);
    REQUIRE(number_of_Found_p1Point == 3);
    REQUIRE(number_of_Found_p2Point == 3);
    const FT number_of_cubes = lcc.one_dart_per_cell<3>().size();
    const FT number_of_facets = lcc.one_dart_per_cell<2>().size();
    const FT number_of_vertices = lcc.one_dart_per_cell<0>().size();
    REQUIRE(number_of_cubes == 7);
    REQUIRE(number_of_facets == 24);
    REQUIRE(number_of_vertices == 16);

}