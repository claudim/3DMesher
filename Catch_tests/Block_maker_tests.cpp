#include "../Include/catch.hpp"
#include "test_config.h"
#include "Block_maker.h"
#include "Writer.h"

TEST_CASE("cube_must_have_8_vertices","[make_cube][Block_maker_test]"){
    LCC_3 lcc;
    Point basePoint = Point(0,0,0);
    Block_maker blockMaker = Block_maker();
    FT lg = 1;
    const Dart_handle &block = blockMaker.make_cube(lcc, basePoint, lg);
    int number_of_vertices = 0;
    // per tutti i vertici
    for (LCC_3::One_dart_per_cell_const_range<0, 3>::const_iterator vertex_iterator = lcc.one_dart_per_cell<0, 3>().begin(), iterEnd = lcc.one_dart_per_cell<0, 3>().end();
         vertex_iterator != iterEnd; ++vertex_iterator) {
        number_of_vertices++;
    }
    REQUIRE(number_of_vertices==8);
}

TEST_CASE("cube_must_have_6_facets","[make_cube][Block_maker_test]"){
    LCC_3 lcc;
    Point basePoint = Point(0,0,0);
    FT lg = 1;
    Block_maker blockMaker = Block_maker();
    const Dart_handle &block = blockMaker.make_cube(lcc, basePoint, lg);
    int number_of_facets = 0;
    // per tutte la facce
    for (LCC_3::One_dart_per_cell_const_range<2, 3>::const_iterator facet_iterator = lcc.one_dart_per_cell<2, 3>().begin(), iterEnd = lcc.one_dart_per_cell<2, 3>().end();
         facet_iterator != iterEnd; ++facet_iterator) {
        number_of_facets++;
    }
    REQUIRE(number_of_facets == 6);
}


TEST_CASE("block_must_have_6_facets","[make_block][Block_maker_test]"){
    LCC_3 lcc;
    std::vector<Point> blockVertices;
    blockVertices.emplace_back(0, 0, 0);
    blockVertices.emplace_back(5, 0, 0);
    blockVertices.emplace_back(5, 0, 3);
    blockVertices.emplace_back(0, 0, 3);
    blockVertices.emplace_back(0, 2, 3);
    blockVertices.emplace_back(0, 2, 0);
    blockVertices.emplace_back(3, 2, 0);
    blockVertices.emplace_back(3, 2, 3);
    FT lg = 1;
    Block_maker blockMaker;
    const Dart_handle block = blockMaker.make_block(lcc, blockVertices);

    int number_of_facets = 0;
    // per tutte la facce
    for (LCC_3::One_dart_per_cell_const_range<2, 3>::const_iterator facet_iterator = lcc.one_dart_per_cell<2, 3>().begin(), iterEnd = lcc.one_dart_per_cell<2, 3>().end();
         facet_iterator != iterEnd; ++facet_iterator) {
        number_of_facets++;
    }
    REQUIRE(number_of_facets == 6);

    SECTION("Checking points"){
        for (LCC_3::One_dart_per_cell_const_range<0, 3>::const_iterator vertex_iterator = lcc.one_dart_per_cell<0, 3>().begin(), iterEnd = lcc.one_dart_per_cell<0, 3>().end();
             vertex_iterator != iterEnd; ++vertex_iterator) {

            Point p = lcc.point(vertex_iterator);

            for (int j = 0; j <blockVertices.size() ; ++j) {
                if (blockVertices[j] == p)
                    blockVertices.erase(blockVertices.begin()+j);
            }
        }
        REQUIRE(blockVertices.size() == 0);
    }
}
