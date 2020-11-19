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


TEST_CASE("remove blocks if have distance from polyhedron lesser than parameter","[OnBoundary_block_remover]"){

    std::string fileName = data_path + "/cubeTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Point basePoint1 = Point(2,2,2);  FT lg1 = 2;
    Point basepoint2 = Point(2,2,4);  FT lg = 1;

    blockMaker.make_cube(lcc, basePoint1, lg1);
    lcc.make_hexahedron(basepoint2,
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(lg1, 0, 0)),
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(lg1, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(0, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(0, lg1, lg)),
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(0, 0, lg)),
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(lg1, 0, lg)),
                        Traits::Construct_translated_point()
                                (basepoint2, Traits::Vector(lg1, lg1, lg)));

    lcc.sew3_same_facets();
    lcc.display_characteristics(std::cout);


    OnBoundary_block_remover blockRemover = OnBoundary_block_remover();
    blockRemover.removeBlocks(lcc, polyhedron, lg);

    FT number_of_cubes = 0;
    for(LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator cube_it = lcc.one_dart_per_cell<3>().begin(),
            cube_it_end = lcc.one_dart_per_cell<3>().end(); cube_it != cube_it_end; ++cube_it)
    {
        number_of_cubes++;
    }
    REQUIRE(number_of_cubes == 2);

    blockRemover.removeBlocks(lcc, polyhedron, lg1);
    number_of_cubes = 0;
    for(LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator cube_it = lcc.one_dart_per_cell<3>().begin(),
                cube_it_end = lcc.one_dart_per_cell<3>().end(); cube_it != cube_it_end; ++cube_it)
    {
        number_of_cubes++;
    }

    REQUIRE(number_of_cubes == 1);



}