#include <Block_maker.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "Degenerate_element_finder.h"

TEST_CASE("must find if a 3-cell(a block) has or not 8 different vertices", "[has_8_different_vertices][Degenerate_element_finder]"){

    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Degenerate_element_finder degenerateElementFinder;

    SECTION("must find 8 different vertices for the cube"){
        Point basePoint = Point(0,0,0);  FT lg = 2;
        Dart_handle block_with_8_different_vertices = blockMaker.make_cube(lcc, basePoint, lg);
        bool has_8_different_vertices = degenerateElementFinder.has_8_different_vertices(lcc, block_with_8_different_vertices);
        REQUIRE(has_8_different_vertices == true);
    }

    SECTION("must not find 8 different vertices for the pyramid"){
        std::vector<Point> points;
        points.emplace_back(Point(0,0,0));
        points.emplace_back(Point(1,0,0));
        points.emplace_back(Point(1,1,0));
        points.emplace_back(Point(0,1,0));
        points.emplace_back(Point(0.5,0.5,1));
        points.emplace_back(Point(0.5,0.5,1));
        points.emplace_back(Point(0.5,0.5,1));
        points.emplace_back(Point(0.5,0.5,1));
        Dart_handle block_with_5_different_vertices = blockMaker.make_block(lcc, points);
        REQUIRE(degenerateElementFinder.getPyramids().size() == 0);
        bool has_8_different_vertices = degenerateElementFinder.has_8_different_vertices(lcc, block_with_5_different_vertices);
        REQUIRE(has_8_different_vertices == false);
        REQUIRE(degenerateElementFinder.getPyramids().size() == 1);
        REQUIRE(degenerateElementFinder.getQuadrilaterals().size() == 0);
        REQUIRE(degenerateElementFinder.getTetrahedra().size() == 0);
        REQUIRE(degenerateElementFinder.getWedges().size() == 0);
    }

    SECTION("must not find 8 different vertices for a quadrilateral"){
        std::vector<Point> points;
        points.emplace_back(Point(0,0,0));
        points.emplace_back(Point(1,0,0));
        points.emplace_back(Point(1,1,0));
        points.emplace_back(Point(0,1,0));
        points.emplace_back(Point(0,1,0));
        points.emplace_back(Point(0,0,0));
        points.emplace_back(Point(1,0,0));
        points.emplace_back(Point(1,1,0));
        Dart_handle block_with_4_different_vertices = blockMaker.make_block(lcc, points);
        bool has_8_different_vertices = degenerateElementFinder.has_8_different_vertices(lcc, block_with_4_different_vertices);
        REQUIRE(has_8_different_vertices == false);
        REQUIRE(degenerateElementFinder.getPyramids().size() == 0);
        REQUIRE(degenerateElementFinder.getQuadrilaterals().size() == 1);
        REQUIRE(degenerateElementFinder.getTetrahedra().size() == 0);
        REQUIRE(degenerateElementFinder.getWedges().size() == 0);
    }
}

TEST_CASE("must find if a face is composed by 4 coplanar vertices", "[is_a_coplanar_facet][Degenerate_element_finder]"){

    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Degenerate_element_finder degenerateElementFinder;
    Point basePoint = Point(0,0,0);  FT lg = 2;
    Dart_handle block = blockMaker.make_cube(lcc, basePoint, lg);

    SECTION("must find coplanar vertices for a cube facet"){

        bool has_coplanar_vertices= degenerateElementFinder.has_hex_a_folded_facet(lcc, block);
        REQUIRE(has_coplanar_vertices == true);
    }

    SECTION("must not find coplanar vertices for a hexahedron without coplanar vertices for each facet"){
        lcc.point(block) = Point(0,0,0.5);

        bool has_coplanar_vertices= degenerateElementFinder.has_hex_a_folded_facet(lcc, block);
        REQUIRE(has_coplanar_vertices == false);
    }
}

TEST_CASE("must find if a block is composed by 3 collinear vertices", "[has_3_collinear_vertices][Degenerate_element_finder]"){

    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Degenerate_element_finder degenerateElementFinder;
    Point basePoint = Point(0,0,0);  FT lg = 2;
    Dart_handle block = blockMaker.make_cube(lcc, basePoint, lg);

    SECTION("must not find collinear vertices for a cube "){

        bool has_3_collinear_vertices = degenerateElementFinder.has_3_collinear_vertices(lcc, block);
        REQUIRE(has_3_collinear_vertices == false);
    }

    SECTION("must find collinear vertices"){
        lcc.point(block) = Point(1,0,1);

        bool has_3_collinear_vertices = degenerateElementFinder.has_3_collinear_vertices(lcc, block);
        REQUIRE(has_3_collinear_vertices == true );
    }
}

TEST_CASE("must find degenerate element present in the mesh", "[find_degenerate_elements][Degenerate_element_finder]"){

    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Degenerate_element_finder degenerateElementFinder;
    Point basePoint = Point(0,0,0);  FT lg = 2;
    Dart_handle block = blockMaker.make_cube(lcc, basePoint, lg);

    SECTION("must not find degenerate element"){
        blockMaker.make_cube(lcc, Point(2,0,0), lg);
        lcc.sew3_same_facets();
        std::vector<Dart_handle> degenerate_elements = degenerateElementFinder.find_degenerate_elements(lcc);
        REQUIRE( degenerate_elements.size()  == 0);
        REQUIRE(degenerateElementFinder.getPyramids().size() == 0);
        REQUIRE(degenerateElementFinder.getQuadrilaterals().size() == 0);
        REQUIRE(degenerateElementFinder.getTetrahedra().size() == 0);
        REQUIRE(degenerateElementFinder.getWedges().size() == 0);
    }

    SECTION("must find degenerate element"){
        //generate a pyramid
        std::vector<Point> pyramid_points;
        pyramid_points.emplace_back(0,0,2);
        pyramid_points.emplace_back(2,0,2);
        pyramid_points.emplace_back(2,2,2);
        pyramid_points.emplace_back(0,2,2);
        pyramid_points.emplace_back(1,1,3);
        pyramid_points.emplace_back(1,1,3);
        pyramid_points.emplace_back(1,1,3);
        pyramid_points.emplace_back(1,1,3);
        blockMaker.make_block(lcc, pyramid_points);

        //generate a wedge
        std::vector<Point> wedge_points;
        wedge_points.emplace_back(2,0,0);
        wedge_points.emplace_back(4,0,0);
        wedge_points.emplace_back(4,2,0);
        wedge_points.emplace_back(2,2,0);
        wedge_points.emplace_back(2,2,2);
        wedge_points.emplace_back(2,0,2);
        wedge_points.emplace_back(2,0,2);
        wedge_points.emplace_back(2,2,2);
        blockMaker.make_block(lcc, wedge_points);

        //generate a quadrilateral
        std::vector<Point> quadrilateral_points;
        quadrilateral_points.emplace_back(0,0,0);
        quadrilateral_points.emplace_back(0,0,0);
        quadrilateral_points.emplace_back(0,2,0);
        quadrilateral_points.emplace_back(0,2,0);
        quadrilateral_points.emplace_back(0,2,2);
        quadrilateral_points.emplace_back(0,0,2);
        quadrilateral_points.emplace_back(0,0,2);
        quadrilateral_points.emplace_back(0,2,2);
        blockMaker.make_block(lcc, quadrilateral_points);

        //generate a tetrahedron
        std::vector<Point> tetrahedron_points;
        tetrahedron_points.emplace_back(6,0,0);
        tetrahedron_points.emplace_back(8,0,0);
        tetrahedron_points.emplace_back(8,0,0);
        tetrahedron_points.emplace_back(6,2,0);
        tetrahedron_points.emplace_back(6,0,2);
        tetrahedron_points.emplace_back(6,0,2);
        tetrahedron_points.emplace_back(8,0,0);
        tetrahedron_points.emplace_back(6,0,2);
        blockMaker.make_block(lcc, tetrahedron_points);

        lcc.sew3_same_facets();
        std::vector<Dart_handle> degenerate_elements = degenerateElementFinder.find_degenerate_elements(lcc);
        REQUIRE(degenerate_elements.size()  == 4);
        REQUIRE(degenerateElementFinder.getPyramids().size() == 1);
        REQUIRE(degenerateElementFinder.getQuadrilaterals().size() == 1);
        REQUIRE(degenerateElementFinder.getTetrahedra().size() == 1);
        REQUIRE(degenerateElementFinder.getWedges().size() == 1);
    }
}





