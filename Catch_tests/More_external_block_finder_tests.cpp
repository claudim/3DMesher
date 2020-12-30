#include "../Include/catch.hpp"
#include "test_config.h"
#include "Block_maker.h"
#include "More_external_block_finder.h"

TEST_CASE("Must_find_more_external_blocks","[More_external_block_finder]")
{
    Block_maker blockMaker;

    FT lg = 2;
    More_external_block_finder moreExternalBlockFinder;

    SECTION("must_find_9_more_external_blocks"){
        LCC_3 lcc;
        //generate a 3x3 cubes
        blockMaker.make_cube(lcc, Point(0,0,0), lg);
        blockMaker.make_cube(lcc, Point(2,0,0), lg);
        blockMaker.make_cube(lcc, Point(4,0,0), lg);

        blockMaker.make_cube(lcc, Point(0,0,2), lg);
        blockMaker.make_cube(lcc, Point(2,0,2), lg);
        blockMaker.make_cube(lcc, Point(4,0,2), lg);

        blockMaker.make_cube(lcc, Point(0,0,4), lg);
        blockMaker.make_cube(lcc, Point(2,0,4), lg);
        blockMaker.make_cube(lcc, Point(4,0,4), lg);

        lcc.sew3_same_facets();

        std::vector<Dart_handle> externalBlock = moreExternalBlockFinder.find(lcc);
        REQUIRE(externalBlock.size() == 9);
    }


    SECTION( "must_find_26_more_external_blocks" ) {
        LCC_3 lcc;
        //generate a 27 cubes
        blockMaker.make_cube(lcc, Point(0,0,0), lg);
        blockMaker.make_cube(lcc, Point(2,0,0), lg);
        blockMaker.make_cube(lcc, Point(4,0,0), lg);

        blockMaker.make_cube(lcc, Point(0,0,2), lg);
        blockMaker.make_cube(lcc, Point(2,0,2), lg);
        blockMaker.make_cube(lcc, Point(4,0,2), lg);

        blockMaker.make_cube(lcc, Point(0,0,4), lg);
        blockMaker.make_cube(lcc, Point(2,0,4), lg);
        blockMaker.make_cube(lcc, Point(4,0,4), lg);

        blockMaker.make_cube(lcc, Point(0,2,0), lg);
        blockMaker.make_cube(lcc, Point(2,2,0), lg);
        blockMaker.make_cube(lcc, Point(4,2,0), lg);

        blockMaker.make_cube(lcc, Point(0,2,2), lg);
        blockMaker.make_cube(lcc, Point(2,2,2), lg);
        blockMaker.make_cube(lcc, Point(4,2,2), lg);

        blockMaker.make_cube(lcc, Point(0,2,4), lg);
        blockMaker.make_cube(lcc, Point(2,2,4), lg);
        blockMaker.make_cube(lcc, Point(4,2,4), lg);

        blockMaker.make_cube(lcc, Point(0,4,0), lg);
        blockMaker.make_cube(lcc, Point(2,4,0), lg);
        blockMaker.make_cube(lcc, Point(4,4,0), lg);

        blockMaker.make_cube(lcc, Point(0,4,2), lg);
        blockMaker.make_cube(lcc, Point(2,4,2), lg);
        blockMaker.make_cube(lcc, Point(4,4,2), lg);

        blockMaker.make_cube(lcc, Point(0,4,4), lg);
        blockMaker.make_cube(lcc, Point(2,4,4), lg);
        blockMaker.make_cube(lcc, Point(4,4,4), lg);

        lcc.sew3_same_facets();

        std::vector<Dart_handle> externalBlock = moreExternalBlockFinder.find(lcc);
        REQUIRE(externalBlock.size() == 26);

    }

    SECTION( "must_not_find_any_more_external_blocks" ){
        LCC_3 lcc;
        std::vector<Dart_handle> externalBlock = moreExternalBlockFinder.find(lcc);
        REQUIRE(externalBlock.size() == 0);

    }

}