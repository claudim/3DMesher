#include "../Include/catch.hpp"
#include "test_config.h"
#include "Block_maker.h"

TEST_CASE("block_must_have_8_vertices","[Block_maker_test]"){
    LCC_3 lcc;
    Point basePoint = Point(0,0,0);
    Block_maker blockMaker = Block_maker();
    FT lg = 1;
    const Dart_handle &block = blockMaker.make_block(lcc, basePoint, lg);
    int number_of_vertices = 0;
    // per tutti i vertici
    for (LCC_3::One_dart_per_cell_const_range<0, 3>::const_iterator vertex_iterator = lcc.one_dart_per_cell<0, 3>().begin(), iterEnd = lcc.one_dart_per_cell<0, 3>().end();
         vertex_iterator != iterEnd; ++vertex_iterator) {
        number_of_vertices++;
    }
    REQUIRE(number_of_vertices==8);
}

TEST_CASE("block_must_have_6_facets","[Block_maker_test]"){
    LCC_3 lcc;
    Point basePoint = Point(0,0,0);
    FT lg = 1;
    Block_maker blockMaker = Block_maker();
    const Dart_handle &block = blockMaker.make_block(lcc, basePoint, lg);
    int number_of_facets = 0;
    // per tutte la facce
    for (LCC_3::One_dart_per_cell_const_range<2, 3>::const_iterator facet_iterator = lcc.one_dart_per_cell<2, 3>().begin(), iterEnd = lcc.one_dart_per_cell<2, 3>().end();
         facet_iterator != iterEnd; ++facet_iterator) {
        number_of_facets++;
    }
    REQUIRE(number_of_facets == 6);
}

//TEST_CASE("block_must_have_1_length_between_2_vertices","[Block_maker_test]"){
//    LCC_3 lcc;
//    Point basePoint = Point(0,0,0);
//    Block_maker blockMaker = Block_maker();
//    FT lg = 1;
//    const Dart_handle block = blockMaker.make_block(lcc, basePoint, lg);
//    Point prevoiusPoint = basePoint;
//    for(LCC_3::Dart_of_cell_const_range<2,3>::const_iterator facet_block_iterator = lcc.darts_of_cell<2,3>(block).begin(),
//            end_iterator = lcc.darts_of_cell<2,3>(block).end(); facet_block_iterator != end_iterator; ++facet_block_iterator)
//    {
//        if(facet_block_iterator != block) {
//            bool length_between_2_vertices_is_1 = false;
//            Point point = lcc.point(facet_block_iterator);
//
//            if (prevoiusPoint.x() == point.x() - lg || prevoiusPoint.y() == point.y() - lg ||
//                prevoiusPoint.z() == point.z() - lg) {
//                length_between_2_vertices_is_1 = true;
//            }
//            REQUIRE(length_between_2_vertices_is_1 == true);
//            prevoiusPoint = point;
//        }
//    }
//}