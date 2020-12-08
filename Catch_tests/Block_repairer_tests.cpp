#include <Block_maker.h>
#include <OFF_Reader.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "InitialMesh_boundary_connector.h"

TEST_CASE("Must not detect non-intersecting normal vectors"){
    
    Block_maker blockMaker;
    LCC_3 lcc;
    FT lg = 4;
    OFF_Reader reader;
    const Polyhedron &polyhedron3 = reader.read("/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/cubeTest.off");
    
    blockMaker.make_cube(lcc,Point(1,1,1),lg);

    InitialMesh_boundary_connector boundaryConnector;
    boundaryConnector.connect(lcc, polyhedron3);

    //Block_repairer blockRepairer;

    for(LCC_3::One_dart_per_cell_range<3>::iterator block_it = lcc.one_dart_per_cell<3>().begin(),
                block_it_end = lcc.one_dart_per_cell<3>().end(); block_it != block_it_end; ++block_it){
        
    }
};