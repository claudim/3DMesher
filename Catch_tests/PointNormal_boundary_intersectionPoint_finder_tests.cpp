#include "../Include/catch.hpp"
#include "test_config.h"
#include "PointNormal_boundary_intersectionPoint_finder.h"
#include <Block_maker.h>
#include <OFF_Reader.h>

TEST_CASE("PointNormal_boundary_intersectionPoint_finder"){

    Point internalBlockBasePoint = Point(2, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    PointNormal_boundary_intersectionPoint_finder pointFinder = PointNormal_boundary_intersectionPoint_finder();

    // if the point of internal cube is (2, 2, 2)
    Point intercectionPoint = pointFinder.findIntersecionPoint( lcc, internalBlock, polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

    // if the point of internal cube is (2, 2, 4)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 1), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (4, 2, 2)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 1,1,1), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

    // if the point of internal cube is (4, 2, 4)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 1,1), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (2, 4, 2)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1, 1, 2, 1), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

    // if the point of internal cube is (2, 4, 4)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1 , 1, 2), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (4, 4, 4)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1, 1, 2, 1, 1, 1), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (4, 4, 2)
    intercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1, 1, 2, 1, 1), polyhedron);
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

}
