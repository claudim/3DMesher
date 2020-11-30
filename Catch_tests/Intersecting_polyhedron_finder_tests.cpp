#include <Point_sorter.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "OFF_Reader.h"
#include "Intersecting_polyhedron_finder.h"
#include "Block_maker.h"

TEST_CASE("must_not_detect_intersection", "[Intersecting_polyhedron_finder_tests][do_polyhedra_intersect]"){
    std::string fileName = data_path + "/cubeTest.off";
    std::string fileName2 = data_path + "/cubeTest2.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    Polyhedron polyhedron2 = reader.read(fileName2);

    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
    bool intersection = intersectingPolyhedronFinder.do_polyhedra_intersect(polyhedron, polyhedron2);
    REQUIRE_FALSE(intersection);

    LCC_3 lcc;
    Block_maker blockMaker;
    FT lg1 = 6;
    FT lg2 = 8;
    Dart_const_handle block1 = blockMaker.make_cube(lcc, Point(0,0,0), lg1);
    Dart_const_handle block2 = blockMaker.make_cube(lcc, Point(7, 0, 3), lg2);

    std::cout << lcc.is_sewable<3>(block1, block2) << std::endl;
    std::cout << lcc.is_sewable<2>(block1, block2) << std::endl;
    std::cout << lcc.is_sewable<1>(block1, block2) << std::endl;
    std::cout << lcc.is_sewable<0>(block1, block2) << std::endl;

}

TEST_CASE("must_detect_intersection", "[Intersecting_polyhedron_finder_tests][do_polyhedra_intersect]"){
    std::string fileName = data_path + "/cubeTest.off";
    std::string fileName3 = data_path + "/cubeTest3.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    Polyhedron polyhedron3 = reader.read(fileName3);

    // polyhedra share portion of space
    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
    bool intersection = intersectingPolyhedronFinder.do_polyhedra_intersect(polyhedron, polyhedron3);
    REQUIRE(intersection);

    LCC_3 lcc;
    Block_maker blockMaker;
    FT lg1 = 6;
    FT lg2 = 8;
    Dart_const_handle block1 = blockMaker.make_cube(lcc, Point(0,0,0), lg1);
    Dart_const_handle block2 = blockMaker.make_cube(lcc, Point(5, 5, 5), lg2);

    std::cout << lcc.is_sewable<3>(block1, block2) << std::endl;
    std::cout << lcc.is_sewable<2>(block1, block2) << std::endl;
    std::cout << lcc.is_sewable<1>(block1, block2) << std::endl;
    std::cout << lcc.is_sewable<0>(block1, block2) << std::endl;



}

TEST_CASE("must_detect_intersection2", "[Intersecting_polyhedron_finder_tests][do_polyhedra_intersect]"){
    std::string fileName = data_path + "/cubeTest.off";
    std::string fileName4 = data_path + "/cubeTest4.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    Polyhedron polyhedron4 = reader.read(fileName4);

    // polyhedra share a facet
    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
    bool intersection = intersectingPolyhedronFinder.do_polyhedra_intersect(polyhedron, polyhedron4);
    REQUIRE(intersection);


    LCC_3 lcc;
    Block_maker blockMaker;
    FT lg1 = 6;
    Dart_const_handle block1 = blockMaker.make_cube(lcc, Point(0,0,0), lg1);
    Dart_const_handle block5 = blockMaker.make_cube(lcc, Point(6, 0, 0), lg1);

    std::cout << lcc.is_sewable<3>(block1, block5) << std::endl;
    std::cout << lcc.is_sewable<2>(block1, block5) << std::endl;
    std::cout << lcc.is_sewable<1>(block1, block5) << std::endl;
    std::cout << lcc.is_sewable<0>(block1, block5) << std::endl;

}

TEST_CASE("must_detect_intersection_if_2_polyhedra_share_one_point", "[Intersecting_polyhedron_finder_tests][do_polyhedra_intersect]"){
    std::string fileName = data_path + "/cubeTest.off";
    std::string fileName5 = data_path + "/cubeTest5.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    Polyhedron polyhedron5 = reader.read(fileName5);

    // polyhedra share a point
    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
    bool intersection = intersectingPolyhedronFinder.do_polyhedra_intersect(polyhedron, polyhedron5);
    REQUIRE(intersection);

    LCC_3 lcc;
    Block_maker blockMaker;
    FT lg1 = 6;
    FT lg5 = 1;
    Dart_const_handle block1 = blockMaker.make_cube(lcc, Point(0,0,0), lg1);
    Dart_const_handle block5 = blockMaker.make_cube(lcc, Point(6, 6, 6), lg5);
    REQUIRE(lcc.is_sewable<2>(block1, block5) == false);
    //REQUIRE(lcc.is_sewable<3>(block1, block5) == false);
    REQUIRE(lcc.is_sewable<1>(block1, block5) == false);
   // REQUIRE(lcc.is_sewable<0>(block1, block5) == true);


}

TEST_CASE("must_detect_intersection_if_2_polyhedra_share_one_edge", "[Intersecting_polyhedron_finder_tests][do_polyhedra_intersect]"){
    std::string fileName = data_path + "/cubeTest.off";
    std::string fileName6 = data_path + "/cubeTest6.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    Polyhedron polyhedron6 = reader.read(fileName6);

    // polyhedra share an edge
    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
    bool intersection = intersectingPolyhedronFinder.do_polyhedra_intersect(polyhedron, polyhedron6);
    REQUIRE(intersection);

    LCC_3 lcc;
    Block_maker blockMaker;
    FT lg1 = 6;
    Dart_const_handle block1 = blockMaker.make_cube(lcc, Point(0,0,0), lg1);
    Dart_const_handle block5 = blockMaker.make_cube(lcc, Point(6, 0, 6), lg1);

    std::cout << lcc.is_sewable<3>(block1, block5) << std::endl;
    std::cout << lcc.is_sewable<2>(block1, block5) << std::endl;
    std::cout << lcc.is_sewable<1>(block1, block5) << std::endl;
    std::cout << lcc.is_sewable<0>(block1, block5) << std::endl;
}

TEST_CASE("Intersection between the polyhedron facets")
{
    LCC_3 lcc;
    Block_maker blockMaker;
    Intersecting_polyhedron_finder intersectingPolyhedronFinder;

    SECTION("No intersection")
    {
        FT lg = 2;
        const Dart_handle cube = blockMaker.make_cube(lcc, Point(2, 2, 2), lg);
        bool facets_intersection = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc, cube);
        REQUIRE(facets_intersection == false);
    }

    SECTION("Intersection")
    {
        std::vector<Point> block_points;
        block_points.emplace_back(Point(2,2,2));
        block_points.emplace_back(Point(4,2,2));
        block_points.emplace_back(Point(4,4,2));
        block_points.emplace_back(Point(2,4,2));
        block_points.emplace_back(Point(2,4,4));
        block_points.emplace_back(Point(2,2,4));
        block_points.emplace_back(Point(1,3,5));
        block_points.emplace_back(Point(4,4,4));
        const Dart_handle intersecting_block = blockMaker.make_block(lcc, block_points);
        bool facets_intersection = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,intersecting_block);
        REQUIRE(facets_intersection == true);
    }


}