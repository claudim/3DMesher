#include "../Include/catch.hpp"
#include "test_config.h"
#include "Vertex_location_finder.h"
#include "Reader.h"
#include "Block_maker.h"

typedef CGAL::Vertex_location_finder Vertex_location_finder ;

TEST_CASE("point_outside_polyhedron", "[Vertex_location_finder][is_point_inside_polyhedron][is_point_onBoundary_polyhedron][is_point_external_polyhedron]"){
    Reader reader = Reader();
    std::string fileName = data_path + "/sphere.off";
    Polyhedron polyhedron = reader.read(fileName);

    Point externalPoint = Point(-40, -40, -40);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    bool isInternalPoint = vertexLocationFinder.is_point_inside_polyhedron(externalPoint);
    REQUIRE(isInternalPoint == false);
    bool isOnBoundaryPoint = vertexLocationFinder.is_point_onBoundary_polyhedron(externalPoint);
    REQUIRE(isOnBoundaryPoint == false);
    bool isExternalPoint = vertexLocationFinder.is_point_external_polyhedron(externalPoint);
    REQUIRE(isExternalPoint == true);
}

TEST_CASE("point_inside_polyhedron", "[Vertex_location_finder][is_point_inside_polyhedron][is_point_onBoundary_polyhedron][is_point_external_polyhedron]"){
    Reader reader = Reader();
    std::string fileName = data_path + "/sphere.off";
    Polyhedron polyhedron = reader.read(fileName);

    Point externalPoint = Point(0, 0, 0);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    bool isInternalPoint = vertexLocationFinder.is_point_inside_polyhedron(externalPoint);
    REQUIRE(isInternalPoint == true);
    bool isOnBoundaryPoint = vertexLocationFinder.is_point_onBoundary_polyhedron(externalPoint);
    REQUIRE(isOnBoundaryPoint == false);
    bool isExternalPoint = vertexLocationFinder.is_point_external_polyhedron(externalPoint);
    REQUIRE(isExternalPoint == false);
}

TEST_CASE("point_onBoundary_polyhedron", "[Vertex_location_finder][is_point_inside_polyhedron][is_point_onBoundary_polyhedron][is_point_external_polyhedron]"){
    Reader reader = Reader();
    std::string fileName = data_path + "/sphere.off";
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryPoint = Point(20, 0, 0);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    bool isInternalPoint = vertexLocationFinder.is_point_inside_polyhedron(onBoundaryPoint);
    REQUIRE(isInternalPoint == false);
    bool isOnBoundaryPoint = vertexLocationFinder.is_point_onBoundary_polyhedron(onBoundaryPoint);
    REQUIRE(isOnBoundaryPoint == true);
    bool isExternalPoint = vertexLocationFinder.is_point_external_polyhedron(onBoundaryPoint);
    REQUIRE(isExternalPoint == false);
}

TEST_CASE("point_almost_onBoundary_polyhedron", "[Vertex_location_finder][is_point_inside_polyhedron][is_point_onBoundary_polyhedron][is_point_external_polyhedron]"){
    Reader reader = Reader();
    std::string fileName = data_path + "/sphere.off";
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryPoint = Point(-20, 0, 0);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    bool isInternalPoint = vertexLocationFinder.is_point_inside_polyhedron(onBoundaryPoint);
    REQUIRE(isInternalPoint == false);
    bool isOnBoundaryPoint = vertexLocationFinder.is_point_onBoundary_polyhedron(onBoundaryPoint);
    REQUIRE(isOnBoundaryPoint == true);
    bool isExternalPoint = vertexLocationFinder.is_point_external_polyhedron(onBoundaryPoint);
    REQUIRE(isExternalPoint == false);
}


TEST_CASE("must_find_7_external_vertices", "[Vertex_location_finder][findExternalVertices]"){
    std::string fileName = data_path + "/sphere.off";
    Reader reader = Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(20, 0, 0 );  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    blockMaker.make_block(lcc, onBoundaryBasePoint, lg); // it has 7 external points, 0 internal points, 1 onBoundary point

    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 7);
}

TEST_CASE("must_find_0_external_vertices", "[Vertex_location_finder][findExternalVertices]"){
    std::string fileName = data_path + "/sphere.off";
    Reader reader = Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(0,0,0);  FT lg = 10;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_block(lcc, onBoundaryBasePoint, lg);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 0);
}

TEST_CASE("must_find_3_external_vertices", "[Vertex_location_finder][findExternalVertices]"){
    std::string fileName = data_path + "/sphere.off";
    Reader reader = Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(-20, 0, 0 );  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    blockMaker.make_block(lcc, onBoundaryBasePoint, lg); // it has 3 external points, 4 internal points, 1 onBoundary point

    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 3);
}

