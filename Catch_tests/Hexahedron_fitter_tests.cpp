#include "../Include/catch.hpp"
#include "test_config.h"
#include "Hexahedron_fitter.h"
#include <Vertex_location_finder.h>
#include <Block_maker.h>
#include <Intersecting_polyhedron_finder.h>
#include "InitialMesh_boundary_connector.h"
#include <OFF_Reader.h>
#include "Writer.h"


TEST_CASE("initial mesh with L shape creates intersecting polyhedron")
{
    std::string fileName = data_path + "/cubeTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point internalBlockBasePoint1 = Point(1, 1, 1);
    Point internalBlockBasePoint2 = Point(2, 1, 1);
    Point internalBlockBasePoint3 = Point(3, 1, 1);

    Point internalBlockBasePoint4 = Point(1, 2, 1);
    Point internalBlockBasePoint5 = Point(2, 2, 1);
    Point internalBlockBasePoint6 = Point(3, 2, 1);
    Point internalBlockBasePoint7 = Point(1, 3, 1);
    Point internalBlockBasePoint8 = Point(2, 3, 1);
    Point internalBlockBasePoint9 = Point(3, 3, 1);

    Point internalBlockBasePoint10 = Point(1, 2, 2);
    Point internalBlockBasePoint11 = Point(2, 2, 2);
    Point internalBlockBasePoint12 = Point(1, 3, 2);
    Point internalBlockBasePoint13 = Point(2, 3, 2);
    Point internalBlockBasePoint14 = Point(1, 2, 3);
    Point internalBlockBasePoint15 = Point(2, 2, 3);
    Point internalBlockBasePoint16 = Point(1, 3, 3);
    Point internalBlockBasePoint17 = Point(2, 3, 3);

    FT internalBlockLg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
    Dart_handle d2 = blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint5, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint6, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint7, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint8, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint9, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint10, internalBlockLg);
    Dart_handle d = blockMaker.make_cube(lcc, internalBlockBasePoint11, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint12, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint13, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint14, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint15, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint16, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint17, internalBlockLg);

    lcc.sew3_same_facets();

    InitialMesh_boundary_connector initialMeshBoundaryConnector;
    initialMeshBoundaryConnector.connect(lcc, polyhedron);

    int number_of_self_intersecting_hex = 0;
    Intersecting_polyhedron_finder< Polyhedron, LCC_3> intersectingPolyhedronFinder;

    // for each hex in lcc
    for(LCC_3::One_dart_per_cell_range<3,3>::iterator hex_it = lcc.one_dart_per_cell<3>().begin(),
            hex_end_it = lcc.one_dart_per_cell<3>().end(); hex_it != hex_end_it; ++hex_it)
    {
        if(intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc, hex_it))
        {
            number_of_self_intersecting_hex++;
        }
    }
   // REQUIRE(number_of_self_intersecting_hex == 6);

    // for each hexahedron created check if there is intersection.
    unsigned long i = 0;
    for(LCC_3::One_dart_per_cell_range<3,3>::iterator hex_it = lcc.one_dart_per_cell<3>().begin(),
                hex_end_it = lcc.one_dart_per_cell<3>().end(); hex_it != hex_end_it; ++hex_it)
    {
        Dart_handle hexahedra_to_check =  hex_it;
        //std::vector<Dart_handle> intersecting_facets;
        //bool toModify = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,hexahedra_to_check, intersecting_facets);
        bool toModify = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,hexahedra_to_check);
        if(toModify == true){
            Hexahedron_fitter hexahedronFitter;
            hexahedronFitter.fix2(lcc, hexahedra_to_check, polyhedron);
        }
        i++;
    }

    number_of_self_intersecting_hex = 0;
    // for each hex in lcc
    for(LCC_3::One_dart_per_cell_range<3,3>::iterator hex_it = lcc.one_dart_per_cell<3>().begin(),
                hex_end_it = lcc.one_dart_per_cell<3>().end(); hex_it != hex_end_it; ++hex_it)
    {
        if(intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc, hex_it))
        {
            number_of_self_intersecting_hex++;
        }
    }

   // REQUIRE(number_of_self_intersecting_hex == 0);

    const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput";
    std::string outputFileName = out_data_path + "/cubeIntersectingL_TEST.mesh";
    std::ofstream medit_file(outputFileName);
    Writer writer;
    writer.output_to_medit(medit_file,lcc);
    medit_file.close();

}



//TEST_CASE("Fix an intersecting itself hexahedron")
//{
//    //typedef typename CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
//    std::string fileName = data_path + "/cubeIntersecting.off";
//    OFF_Reader reader = OFF_Reader();
//    Polyhedron polyhedron = reader.read(fileName);
//    LCC lcc;
//    Block_maker blockMaker;
//    Intersecting_polyhedron_finder intersectingPolyhedronFinder;
//    std::vector<Point> block_points;
//    block_points.emplace_back(Point(2,2,2));
//    block_points.emplace_back(Point(4,2,2));
//    block_points.emplace_back(Point(4,4,2));
//    block_points.emplace_back(Point(2,4,2));
//    block_points.emplace_back(Point(2,4,4));
//    block_points.emplace_back(Point(2,2,4));
//    block_points.emplace_back(Point(1,3,5));
//    block_points.emplace_back(Point(4,4,4));
//
//    std::vector<Dart_handle> facets;
//    Dart_handle intersecting_block = blockMaker.make_block(lcc, block_points);
//    bool facets_intersection = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc,intersecting_block, facets);
//    REQUIRE(facets_intersection == true);
//
//    std::cout<<"punti prima"<<std::endl;
//    for(LCC::One_dart_per_incident_cell_range<0,3,3>::iterator v_it = lcc.one_dart_per_incident_cell<0,3,3>(intersecting_block).begin(),
//                v_end_it = lcc.one_dart_per_incident_cell<0,3,3>(intersecting_block).end(); v_it != v_end_it; ++v_it)
//    {
//        std::cout<<lcc.point(v_it)<<std::endl;
//    }
//    std::cout<<"fine punti prima"<<std::endl;
//    Hexahedron_fitter hexahedronFitter;
//   // hexahedronFitter.fix(lcc, intersecting_block, facets, polyhedron);
//    hexahedronFitter.fix2(lcc, intersecting_block, polyhedron);
//
//    facets.clear();
//    std::cout<<"size "<<facets.size()<<std::endl;
//    facets_intersection = intersectingPolyhedronFinder.do_polyhedron_facets_intersect(lcc, intersecting_block, facets);
//    std::cout<<"punti dopo"<<std::endl;
//    for(LCC::One_dart_per_incident_cell_range<0,3,3>::iterator v_it = lcc.one_dart_per_incident_cell<0,3,3>(intersecting_block).begin(),
//                v_end_it = lcc.one_dart_per_incident_cell<0,3,3>(intersecting_block).end(); v_it != v_end_it; ++v_it)
//    {
//        std::cout<<lcc.point(v_it)<<std::endl;
//    }
//    std::cout<<"size "<<facets.size()<<std::endl;
//    std::cout<<"le facce che si intersecano"<<std::endl;
//
//
//   // REQUIRE(facets_intersection == false);
//
//    const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput";
//    std::string outputFileName = out_data_path + "/cubeIntersectingTEST.mesh";
//    std::ofstream medit_file(outputFileName);
//    Writer writer;
//    writer.output_to_medit(medit_file,lcc);
//    medit_file.close();
//
//
//
//}
