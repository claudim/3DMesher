#include "../Include/catch.hpp"
#include "test_config.h"
#include <OFF_Reader.h>
#include <Block_maker.h>
#include "OnBoundary_block_remover.h"

TEST_CASE("remove_all_onBoundary_blocks","[OnBoundary_block_remover]"){

    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    OnBoundary_block_remover blockRemover = OnBoundary_block_remover();

    SECTION( "must_remove_onBoundary_block" ) {
        Point onBoundaryBasePoint = Point(-20,0,0);  FT lg = 10;

        Dart_handle onBoundary_block = blockMaker.make_cube(lcc, onBoundaryBasePoint, lg);

        FT size_before_call_removeBlocks = lcc.darts().size();
        blockRemover.removeBlocks(lcc, polyhedron);
        FT size_after_call_removeBlocks = lcc.darts().size();
        REQUIRE(size_after_call_removeBlocks != size_before_call_removeBlocks );
        REQUIRE(size_after_call_removeBlocks == 0);

    }

    SECTION( "must_not_remove_external_block" ) {
        Point externalBasePoint = Point(-30,0,0);  FT lg = 1;

        Dart_handle onBoundary_block = blockMaker.make_cube(lcc, externalBasePoint, lg);

        FT size_before_call_removeBlocks = lcc.darts().size();
        blockRemover.removeBlocks(lcc, polyhedron);
        FT size_after_call_removeBlocks = lcc.darts().size();
        REQUIRE(size_after_call_removeBlocks == size_before_call_removeBlocks );
    }

    SECTION( "must_not_remove_internal_block" ) {
        Point internalBasePoint = Point(0,0,0);  FT lg = 1;
        Dart_handle internal_block = blockMaker.make_cube(lcc, internalBasePoint, lg);
        FT size_before_call_removeBlocks = lcc.darts().size();
        blockRemover.removeBlocks(lcc, polyhedron);
        FT size_after_call_removeBlocks = lcc.darts().size();
        REQUIRE( size_after_call_removeBlocks == size_before_call_removeBlocks );
    }
}

