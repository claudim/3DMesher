#include "../Include/catch.hpp"
#include "test_config.h"
#include "Reader.h"
#include "Block_maker.h"
#include "Vertex_location_finder.h"
#include "Grid_boundary_connector.h"

typedef CGAL::Vertex_location_finder Vertex_location_finder ;
typedef CGAL::Grid_boundary_connector Grid_boundary_connector ;

TEST_CASE("hex_must_have_all_vertices_onBoundary_or_inside_boundary", "[Grid_boundary_connector]"){
    std::string fileName = data_path + "/sphere.off";
    Reader reader = Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(-20,0,0);  FT lg = 10;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    Dart_handle onBoundary_block = blockMaker.make_cube(lcc, onBoundaryBasePoint, lg); // it has 3 external points, 1 boundary point and 4 internal points
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    int number_of_external_vertices;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 3);

    Grid_boundary_connector gridBoundaryConnector = Grid_boundary_connector();
    gridBoundaryConnector.connect(lcc, polyhedron);
    number_of_external_vertices = 0;
    vertexLocationFinder.findExternalVertices(lcc, number_of_external_vertices, 0);
    REQUIRE(number_of_external_vertices == 0);

}

