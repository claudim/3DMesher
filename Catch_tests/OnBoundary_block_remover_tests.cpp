#include "../Include/catch.hpp"
#include "test_config.h"
#include <OFF_Reader.h>
#include "STL_reader.h"
#include <Block_maker.h>
#include "OnBoundary_block_remover.h"

TEST_CASE("check on boundary block"){
    std::string fileName = data_path + "/cubeTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    OnBoundary_block_remover blockRemover = OnBoundary_block_remover();
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);

    SECTION( "must_check_onBoundary_block" ) {
        Point onBoundaryBasePoint = Point(0,0,0);  FT lg = 2;
        Dart_handle onBoundary_block = blockMaker.make_cube(lcc, onBoundaryBasePoint, lg);
        REQUIRE(blockRemover.is_block_on_boundary(lcc, onBoundary_block, polyhedron, vertexLocationFinder) == true );
    }
}

TEST_CASE("check if one block is too close to the boundary 2"){
    std::string fileName = data_path + "/cubeTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    LCC_3 lcc;
    OnBoundary_block_remover blockRemover = OnBoundary_block_remover();
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    FT distance = 2;
    Point basepoint = Point(2,2,2);  FT lg1 = 2;

    Dart_handle too_close_block = lcc.make_hexahedron(basepoint,
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, lg1)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 3)));

    REQUIRE(blockRemover.is_block_too_close_to_the_boundary2(lcc, too_close_block, polyhedron, distance,
                                                             vertexLocationFinder) == true );
    LCC_3 lcc1;
    Dart_handle not_too_close_block = lcc1.make_hexahedron(basepoint,
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(lg1, 0, 0)),
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(lg1, lg1, 0)),
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(0, lg1, 0)),
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(0, lg1, lg1)),
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(0, 0, 3)),
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(lg1, 0, 3)),
                                                      Traits::Construct_translated_point()
                                                              (basepoint, Traits::Vector(lg1, lg1, lg1)));
    REQUIRE(blockRemover.is_block_too_close_to_the_boundary2(lcc1, not_too_close_block, polyhedron, distance,
                                                             vertexLocationFinder) == false );
}

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


TEST_CASE("remove blocks if have distance from polyhedron less than parameter","[OnBoundary_block_remover]"){

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
    if(!lcc.is_empty()) {
        for (LCC_3::One_dart_per_cell_const_range<3, 3>::const_iterator cube_it = lcc.one_dart_per_cell<3>().begin(),
                     cube_it_end = lcc.one_dart_per_cell<3>().end(); cube_it != cube_it_end; ++cube_it) {
            number_of_cubes++;
        }
    }
    REQUIRE(number_of_cubes == 2);

    blockRemover.removeBlocks(lcc, polyhedron, lg1);
    number_of_cubes = 0;
    if(!lcc.is_empty()) {
    for(LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator cube_it = lcc.one_dart_per_cell<3>().begin(),
                cube_it_end = lcc.one_dart_per_cell<3>().end(); cube_it != cube_it_end; ++cube_it)
    {
        number_of_cubes++;
    }}

    REQUIRE(number_of_cubes == 1);
}

TEST_CASE("remove blocks using 3 points approach", "[OnBoundary_block_remover]"){

    std::string fileName = data_path + "/cubeTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point basepoint = Point(2,2,2);  FT lg1 = 2; FT lg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();

    lcc.make_hexahedron(basepoint,
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, lg1)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 3)));

    OnBoundary_block_remover blockRemover = OnBoundary_block_remover();
    blockRemover.removeBlocks(lcc, polyhedron, lg1);

    REQUIRE(lcc.is_empty() == true);

    lcc.make_hexahedron(basepoint,
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 3)));

    blockRemover.removeBlocks(lcc, polyhedron, lg1);

    REQUIRE(lcc.is_empty() == true);

    lcc.make_hexahedron(basepoint,
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, 0, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, lg1)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, lg1)));

    blockRemover.removeBlocks(lcc, polyhedron, lg1);

    REQUIRE(lcc.is_empty() == false);
    REQUIRE(lcc.one_dart_per_cell<3>().size() == 1);

    LCC_3 lcc2;
    lcc2.make_hexahedron(basepoint,
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 0)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, lg1, 3)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(0, 0, lg1)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, 0, lg1)),
                        Traits::Construct_translated_point()
                                (basepoint, Traits::Vector(lg1, lg1, lg1)));
    blockRemover.removeBlocks(lcc2, polyhedron, lg1);
    REQUIRE(lcc2.is_empty() == false);
    REQUIRE(lcc2.one_dart_per_cell<3>().size() == 1);

    LCC_3 lcc3;
    lcc3.make_hexahedron(basepoint,
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, 0, 0)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, lg1, 0)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(0, lg1, 0)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(0, lg1, lg1)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(0, 0, lg1)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, 0, lg1)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, lg1, lg1)));
    blockRemover.removeBlocks(lcc3, polyhedron, lg1);
    REQUIRE(lcc3.is_empty() == false);
    REQUIRE(lcc3.one_dart_per_cell<3>().size() == 1);


    LCC_3 lcc4;
    lcc4.make_hexahedron(basepoint,
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(3, 0, 0)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, lg1, 0)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(0, lg1, 0)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(0, lg1, lg1)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(0, 0, lg1)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, 0, lg1)),
                         Traits::Construct_translated_point()
                                 (basepoint, Traits::Vector(lg1, lg1, 3)));
    blockRemover.removeBlocks(lcc4, polyhedron, lg1);
    REQUIRE(lcc4.is_empty() == false);
    REQUIRE(lcc4.one_dart_per_cell<3>().size() == 1);

}

TEST_CASE("remove 3cells too close to the boundary according to a passed distance"){

    std::string fileName = data_path + "/cubeTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);
    LCC_3 lcc;
    Block_maker blockMaker;
    OnBoundary_block_remover blockRemover;
    Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
    FT lg =2;
    Dart_handle block_handle = blockMaker.make_cube(lcc, Point(2, 2, 2), lg);

    Point barycenter_point = lcc.barycenter<3>(block_handle);

    REQUIRE(barycenter_point == Point(3,3,3));


    double distance_Barycenter_Polyhedron = vertexLocationFinder.getAabbTree().squared_distance(barycenter_point);

    REQUIRE(sqrt(distance_Barycenter_Polyhedron) == 3.0);
    
    double distance = 2;
    bool isBlockTooCloseToTheBoundary = blockRemover.is_block_too_close_to_the_boundary(lcc, block_handle, polyhedron,
                                                                                        distance,vertexLocationFinder);
    REQUIRE(isBlockTooCloseToTheBoundary == false);

    distance = 3;
    isBlockTooCloseToTheBoundary = blockRemover.is_block_too_close_to_the_boundary(lcc, block_handle, polyhedron,
                                                                                   distance, vertexLocationFinder);
    REQUIRE(isBlockTooCloseToTheBoundary == true);
    
    distance = 4;
    isBlockTooCloseToTheBoundary = blockRemover.is_block_too_close_to_the_boundary(lcc, block_handle, polyhedron,
                                                                                   distance, vertexLocationFinder);
    REQUIRE(isBlockTooCloseToTheBoundary == true);

}