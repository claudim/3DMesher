#include "../Include/catch.hpp"
#include "test_config.h"
#include "Vertex_location_finder.h"
#include "OFF_Reader.h"
#include "Block_maker.h"

typedef CGAL::Vertex_location_finder Vertex_location_finder ;

TEST_CASE("point_outside_polyhedron", "[Vertex_location_finder][is_point_inside_polyhedron][is_point_onBoundary_polyhedron][is_point_external_polyhedron]"){
    OFF_Reader reader = OFF_Reader();
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
    OFF_Reader reader = OFF_Reader();
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
    OFF_Reader reader = OFF_Reader();
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
    OFF_Reader reader = OFF_Reader();
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
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(20, 0, 0 );  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    blockMaker.make_cube(lcc, onBoundaryBasePoint, lg); // it has 7 external points, 0 internal points, 1 onBoundary point

    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 7);
}

TEST_CASE("must_find_0_external_vertices", "[Vertex_location_finder][findExternalVertices]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(0,0,0);  FT lg = 10;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc, onBoundaryBasePoint, lg);
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 0);
}

TEST_CASE("must_find_3_external_vertices", "[Vertex_location_finder][findExternalVertices]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(-20, 0, 0 );  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    blockMaker.make_cube(lcc, onBoundaryBasePoint, lg); // it has 3 external points, 4 internal points, 1 onBoundary point

    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 3);
}

TEST_CASE("must find internal vertices but too close to the boundary", "[Vertex_location_finder]"){
    OFF_Reader reader = OFF_Reader();
    std::string fileName = data_path + "/cubeTest.off";
    Polyhedron polyhedron = reader.read(fileName);

    LCC_3 lcc;
    Point basepoint = Point(2, 2, 2);
    FT lg = 5;
    Block_maker blockMaker;
    blockMaker.make_cube(lcc, basepoint, lg);

    FT number_of_too_close_points = 0;
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron) ;
    for (LCC_3::One_dart_per_cell_range<0,3>::const_iterator vertex_it = lcc.one_dart_per_cell<0,3>().begin(),
                 vertex_end_it = lcc.one_dart_per_cell<0,3>().end(); vertex_it != vertex_end_it; ++vertex_it){
        Point pointToTest = lcc.point(vertex_it);
        if(vertexLocationFinder.is_point_too_close_to_the_boundary(pointToTest, 4))
        {
            number_of_too_close_points++;
        }
    }
    REQUIRE(number_of_too_close_points == 7);




}


