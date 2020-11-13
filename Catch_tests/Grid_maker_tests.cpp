#include "../Include/catch.hpp"
#include "test_config.h"
#include "Grid_maker.h"
#include <CGAL/Polygon_mesh_processing/measure.h>

TEST_CASE("grid_x_dimension_greater_than_polyhedron_x_dimension", "[Grid_maker_test][wrap_the_object]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.make(polyhedron);

    const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);
    double polyhedron_x_dimension = polyhedron_bbox3.xmax() - polyhedron_bbox3.xmin();

    REQUIRE(gridMaker.get_x_dimension() > polyhedron_x_dimension);

    //importo la sfera
    //costruisco la griglia
    // verifico che il bounding box della sfera ha il lato più
}

TEST_CASE("grid_y_dimension_greater_than_polyhedron_y_dimension", "[Grid_maker_test][wrap_the_object]"){

    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.make(polyhedron);

    const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);
    double polyhedron_y_dimension = polyhedron_bbox3.ymax() - polyhedron_bbox3.ymin();

    REQUIRE(gridMaker.get_y_dimension() > polyhedron_y_dimension);
}

TEST_CASE("grid_z_dimension_greater_than_polyhedron_z_dimension", "[Grid_maker_test][wrap_the_object]"){

    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.make(polyhedron);

    const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);
    double polyhedron_z_dimension = polyhedron_bbox3.zmax() - polyhedron_bbox3.zmin();

    REQUIRE(gridMaker.get_z_dimension() > polyhedron_z_dimension);

    //importo la sfera
    //costruisco la griglia
    // verifico che il bounding box della sfera ha il lato più
}

TEST_CASE("object_inside_grid", "[Grid_maker_test][wrap_the_object]"){

    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.make(polyhedron);

    const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);

    Point point = Point(polyhedron_bbox3.xmin() + (polyhedron_bbox3.xmax()-polyhedron_bbox3.xmin())/2,
          polyhedron_bbox3.ymin() + (polyhedron_bbox3.ymax()-polyhedron_bbox3.ymin())/2,
          polyhedron_bbox3.zmin() + (polyhedron_bbox3.zmax()-polyhedron_bbox3.zmin())/2);

    Point grid_centroid = gridMaker.get_grid_centroid();

    REQUIRE(grid_centroid == point);
}

TEST_CASE("must_create_27_hex_over_sphere_if_resolution_is_1", "[Grid_maker_test]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.set_resolution(1);
    LCC_3 lcc = gridMaker.make(polyhedron);
    int number_of_cubes =0;
    for (LCC_3::One_dart_per_cell_range<3,3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
    {
        number_of_cubes++;
    }
    REQUIRE(number_of_cubes==27);
}

TEST_CASE("must_create_108_hex_facet_over_sphere_if_resolution_is_1", "[Grid_maker_test]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.set_resolution(1);
    LCC_3 lcc = gridMaker.make(polyhedron);
    int number_of_facets = 0;
        // per ogni faccia
        for (LCC_3::One_dart_per_cell_range<2, 3>::const_iterator facet_iterator = lcc.one_dart_per_cell<2, 3>().begin(), iterEnd = lcc.one_dart_per_cell<2, 3>().end();
             facet_iterator != iterEnd; ++facet_iterator) {
            number_of_facets++;
        }
    REQUIRE(number_of_facets==108);
}

TEST_CASE("must_create_64_verteces_over_sphere_if_resolution_is_1", "[Grid_maker_test]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker = Grid_maker();
    gridMaker.set_resolution(1);

    LCC_3 lcc = gridMaker.make(polyhedron);
    int number_of_vertices = 0;
    // per tutti i vertici
    for (LCC_3::One_dart_per_cell_range<0, 3>::const_iterator vertex_iterator = lcc.one_dart_per_cell<0, 3>().begin(), iterEnd = lcc.one_dart_per_cell<0, 3>().end();
         vertex_iterator != iterEnd; ++vertex_iterator) {
        number_of_vertices++;
    }
    REQUIRE(number_of_vertices==64);
}


