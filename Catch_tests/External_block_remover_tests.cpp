#include "../Include/catch.hpp"
#include "test_config.h"
#include "OFF_Reader.h"
#include "External_block_remover.h"

TEST_CASE("remove_block","[External_block_remover]"){

    Point externalBasePoint = Point(-35,-35,-35);  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle block = blockMaker.make_cube(lcc, externalBasePoint, lg);

    External_block_remover blockRemover = External_block_remover();
    blockRemover.removeBlock(lcc, block);

    REQUIRE( lcc.darts().size() == 0 );

}

TEST_CASE("must_remove_esternal_blocks","[External_block_remover]"){

    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point externalBasePoint = Point(-35,-35,-35);  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle external_block = blockMaker.make_cube(lcc, externalBasePoint, lg);

    External_block_remover blockRemover = External_block_remover();
    blockRemover.removeBlocks(lcc, polyhedron);
    REQUIRE( lcc.darts().size() == 0 );
}

TEST_CASE("must_not_remove_internal_blocks","[External_block_remover]"){
    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point internalBasePoint = Point(0,0,0);  FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    Dart_handle internal_block = blockMaker.make_cube(lcc, internalBasePoint, lg);

    External_block_remover blockRemover = External_block_remover();
    blockRemover.removeBlocks(lcc, polyhedron);

    int number_of_blocks = 0;
    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator block_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 end_iterator = lcc.one_dart_per_cell<3,3>().end(); block_iterator != end_iterator; ++block_iterator){
        number_of_blocks++;
    }
    REQUIRE(number_of_blocks == 1 );

}

TEST_CASE("must_not_remove_on_boundary_blocks","[External_block_remover]"){

    std::string fileName = data_path + "/sphere.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point onBoundaryBasePoint = Point(-20,0,0);  FT lg = 10;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    Dart_handle onBoundary_block = blockMaker.make_cube(lcc, onBoundaryBasePoint, lg); // it has 4 external points and 4 internal points

    FT size_before_call_removeBlocks = lcc.darts().size();
    External_block_remover blockRemover = External_block_remover();
    blockRemover.removeBlocks(lcc, polyhedron);
    FT size_after_call_removeBlocks = lcc.darts().size();
    REQUIRE(size_after_call_removeBlocks == size_before_call_removeBlocks );

}

