/**
 * Tests for the initial mesh maker class
 */

#include "../Include/catch.hpp"
#include "test_config.h"
#include "Initial_mesh_maker.h"
#include "External_and_onBoundary_remover.h"

TEST_CASE("must_remove_only_cubes_with_more_than_4_external_facets", "[refine][Initial_mesh_maker]"){

    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Point basePoint1 = Point(2,2,2);
    Point basePoint2 = Point(3,2,2);
    Point basePoint3 = Point(4,2,2);
    Point basePoint4 = Point(2,2,3);
    Point basePoint5 = Point(3,2,3);

    FT lg = 1;
    blockMaker.make_cube(lcc, basePoint1, lg);
    blockMaker.make_cube(lcc, basePoint2, lg);
    blockMaker.make_cube(lcc, basePoint3, lg);
    blockMaker.make_cube(lcc, basePoint4, lg);
    blockMaker.make_cube(lcc, basePoint5, lg);

    lcc.sew3_same_facets();

    REQUIRE(lcc.one_dart_per_cell<3>().size() == 5);

    Initial_mesh_maker<External_and_onBoundary_remover> initialMeshMaker;
    initialMeshMaker.refine(lcc);

    REQUIRE(lcc.one_dart_per_cell<3>().size() == 4);
}
