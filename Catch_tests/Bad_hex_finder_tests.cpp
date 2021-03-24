#include <Block_maker.h>
#include <OFF_Reader.h>
#include <InitialMesh_boundary_connector.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "Bad_hex_finder.h"

TEST_CASE("1x1x1 cube must not be considered bad"){
    Point basepoint = Point(2, 2, 2);

    FT blockLg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    const Dart_handle cube = blockMaker.make_cube(lcc, basepoint, blockLg);
    Bad_hex_finder badHexFinder;
    REQUIRE(badHexFinder.is_hex_bad(cube, lcc) == false);

}

TEST_CASE("cube malformed must be considered bad"){
    LCC_3 lcc;
    std::vector<Point> vertices;
    vertices.emplace_back(Point(0,0,0));
    vertices.emplace_back(Point(2,0,0));
    vertices.emplace_back(Point(2,2,0));
    vertices.emplace_back(Point(0,2,0));
    vertices.emplace_back(Point(0,2,0));
    vertices.emplace_back(Point(0,0,0));
    vertices.emplace_back(Point(2,0,2));
    vertices.emplace_back(Point(2,2,0));

    Block_maker blockMaker = Block_maker();

    Dart_handle cube = blockMaker.make_block(lcc, vertices);
    Bad_hex_finder badHexFinder;
    badHexFinder.setScaledJacobianThreshold(0.5);
    REQUIRE(badHexFinder.is_hex_bad(cube, lcc));
}

TEST_CASE("No bad hex in lcc"){
    Point internalBlockBasePoint1 = Point(2, 2, 2);

    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
    boundaryConnector.connect(lcc, polyhedron);
    Bad_hex_finder badHexFinder;
    std::vector<Dart_handle> bad_hexes;
    badHexFinder.find_bad_hexes(lcc, bad_hexes);

    REQUIRE(bad_hexes.size() == 0);

}

//todo add a test where the provided lcc has some malformed hexahedra