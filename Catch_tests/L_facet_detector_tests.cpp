#include <InitialMesh_boundary_connector.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "OFF_Reader.h"
#include "Grid_maker.h"
#include "Initial_mesh_maker.h"
#include "External_and_onBoundary_remover.h"
#include "Writer.h"
#include "External_facet_finder.h"
#include "Intersecting_polyhedron_finder.h"
#include "L_facet_detector.h"

TEST_CASE("Must_find_shared_point_between_2_facet", "[find_shared_point]"){
    Block_maker blockMaker;
    FT lg = 1;
    LCC_3 lcc;
    SECTION("Must find 4 shared point") {
        Dart_handle block1 = blockMaker.make_cube(lcc, Point(1, 1, 1), lg);
        Dart_handle block2 = blockMaker.make_cube(lcc, Point(2, 1, 1), lg);
        lcc.sew3_same_facets();

        Dart_handle facet_2 = lcc.beta(block2, 2);
        Dart_handle facet_1 = lcc.beta(block1, 1, 1, 2);

        L_facet_detector facetDetector;
        std::vector<Point> shared_points;
        shared_points = facetDetector.find_shared_point(lcc, facet_1, facet_2);

        REQUIRE(shared_points.size() == 4);
        bool p_2_1_1 = false;
        bool p_2_2_1 = false;
        bool p_2_1_2 = false;
        bool p_2_2_2 = false;
        for(Point p: shared_points)
        {
            if(p == Point(2,1,1) )
            {
                p_2_1_1 = true;
            }
            if( p == Point(2,2,1))
            {
                p_2_2_1 = true;
            }
            if(p == Point(2,1,2))
            {
                p_2_1_2 = true;
            }
            if(p == Point(2,2,2))
            {
                p_2_2_2 = true;
            }
        }
        REQUIRE(p_2_1_1 == true);
        REQUIRE(p_2_2_1 == true);
        REQUIRE(p_2_1_2 == true);
        REQUIRE(p_2_2_2 == true);
    }

    SECTION("Must find 2 shared point") {
        Dart_handle block1 = blockMaker.make_cube(lcc, Point(1, 1, 1), lg);
        Dart_handle block2 = blockMaker.make_cube(lcc, Point(2, 1, 0), lg);
        lcc.sew3_same_facets();

        Dart_handle facet_2 = lcc.beta(block2, 2);
        Dart_handle facet_1 = lcc.beta(block1, 1, 1, 2);

        L_facet_detector facetDetector;
        std::vector<Point> shared_points;
        shared_points = facetDetector.find_shared_point(lcc, facet_1, facet_2);

        REQUIRE(shared_points.size() == 2);
        bool p_2_1_1 = false;
        bool p_2_2_1 = false;
        for(Point p: shared_points)
        {
            if(p == Point(2,1,1) )
            {
                p_2_1_1 = true;
            }
            if( p == Point(2,2,1))
            {
                p_2_2_1 = true;
            }
        }
        REQUIRE(p_2_1_1 == true);
        REQUIRE(p_2_2_1 == true);
    }

    SECTION("Must find 1 shared point") {
        Dart_handle block1 = blockMaker.make_cube(lcc, Point(1, 1, 1), lg);
        Dart_handle block2 = blockMaker.make_cube(lcc, Point(2, 2, 2), lg);
        lcc.sew3_same_facets();

        Dart_handle facet_2 = lcc.beta(block2, 2);
        Dart_handle facet_1 = lcc.beta(block1, 1, 1, 2);

        L_facet_detector facetDetector;
        std::vector<Point> shared_points;
        shared_points = facetDetector.find_shared_point(lcc, facet_1, facet_2);

        REQUIRE(shared_points.size() == 1);
        bool p_2_2_2 = false;
        for(Point p: shared_points)
        {
            if(p == Point(2,2,2))
            {
                p_2_2_2 = true;
            }
        }
        REQUIRE(p_2_2_2 == true);
    }

    SECTION("Must find 0 shared point") {
        Dart_handle block1 = blockMaker.make_cube(lcc, Point(1, 1, 1), lg);
        Dart_handle block2 = blockMaker.make_cube(lcc, Point(3, 1, 1), lg);
        lcc.sew3_same_facets();

        Dart_handle facet_2 = lcc.beta(block2, 2);
        Dart_handle facet_1 = lcc.beta(block1, 1, 1, 2);

        L_facet_detector facetDetector;
        std::vector<Point> shared_points;
        shared_points = facetDetector.find_shared_point(lcc, facet_1, facet_2);

        REQUIRE(shared_points.size() == 0);
    }

}

TEST_CASE("Must_detect_L_facet","[L_facets_detect_tests]"){
    Block_maker blockMaker;
    FT lg = 1;

    SECTION("Must not find L facet") {
        LCC_3 hex_mesh;
        blockMaker.make_cube(hex_mesh, Point(1, 1, 1), lg);
        blockMaker.make_cube(hex_mesh, Point(2, 1, 1), lg);
        blockMaker.make_cube(hex_mesh, Point(1, 1, 2), lg);
        hex_mesh.sew3_same_facets();

        L_facet_detector facetDetector;
        std::vector<Dart_handle> L_facets = facetDetector.detect_L_facets(hex_mesh);
        std::cout<<"size di l facets"<<L_facets.size()<<std::endl;
        REQUIRE(L_facets.size() == 0);
    }
//    SECTION("Must find 1 L facet") {
//        LCC_3 hex_mesh;
//        blockMaker.make_cube(hex_mesh, Point(1, 1, 1), lg);
//        blockMaker.make_cube(hex_mesh, Point(2, 1, 1), lg);
//        blockMaker.make_cube(hex_mesh, Point(3,1,1), lg);
//        blockMaker.make_cube(hex_mesh, Point(1, 1, 2), lg);
//        hex_mesh.sew3_same_facets();
//
//        L_facet_detector facetDetector;
//        std::vector<Dart_handle> L_facets = facetDetector.detect_L_facets(hex_mesh);
//        REQUIRE(L_facets.size() == 1);
//    }
//    SECTION("Must find 2 L facet") {
//        LCC_3 hex_mesh;
//        blockMaker.make_cube(hex_mesh, Point(1, 1, 1), lg);
//        blockMaker.make_cube(hex_mesh, Point(2, 1, 1), lg);
//        blockMaker.make_cube(hex_mesh, Point(3, 1, 1), lg);
//        blockMaker.make_cube(hex_mesh, Point(1, 1, 2), lg);
//        blockMaker.make_cube(hex_mesh, Point(1, 1, 3), lg);
//        hex_mesh.sew3_same_facets();
//
//        L_facet_detector facetDetector;
//        std::vector<Dart_handle> L_facets = facetDetector.detect_L_facets(hex_mesh);
//        REQUIRE(L_facets.size() == 2);
//    }


}

TEST_CASE("Must_find_L_facets","[L_facets_detect_tests]")
{
    std::string name = "trapezoidTest";
    std::string fileName = data_path + "/trapezoidTest.off";
    OFF_Reader reader;
    Polyhedron polyhedron = reader.read(fileName);

    Grid_maker gridMaker;
    gridMaker.set_resolution(4);
    LCC_3 hex_mesh = gridMaker.make(polyhedron);

    Initial_mesh_maker<External_and_onBoundary_remover> initMeshMaker;
    initMeshMaker.removeBlocks(hex_mesh, polyhedron, gridMaker.getGridDimension()/2);


    const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput";
    std::string outputFileName = out_data_path + "/" + name + "_L_facet_detector_initMesh.mesh";
    std::ofstream medit_file(outputFileName);
    Writer writer;
    writer.output_to_medit(medit_file,hex_mesh);
    medit_file.close();

//    External_facet_finder facet_finder;
//    std::vector<Dart_handle> external_facets = facet_finder.findFacets(hex_mesh);
//
//    int l_facets = 0;
//    for(Dart_handle facet: external_facets)
//    {
//        Vector facet_normal = CGAL::compute_normal_of_cell_2(hex_mesh, facet);
//        for(LCC::One_dart_per_incident_cell_range<2,2,3>::iterator f_it =hex_mesh.one_dart_per_incident_cell<2,2,3>(facet).begin(),
//                f_end_it = hex_mesh.one_dart_per_incident_cell<2,2,3>(facet).end(); f_it!= f_end_it; ++f_it){
//            Vector near_facet_normal = CGAL::compute_normal_of_cell_2(hex_mesh, f_it);
//
//
//        }
//    }

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
    boundaryConnector.connect(hex_mesh, polyhedron);

    std::string outputFileName1 = out_data_path + "/" + name + "_L_facet_detector_Mesh.mesh";
    std::ofstream medit_file1(outputFileName1);
    //Writer writer;
    writer.output_to_medit(medit_file1,hex_mesh);
    medit_file1.close();

}

TEST_CASE("Must_resolve_U_case","[L_facets_detect_tests]")
{

    std::string fileName = data_path + "/parallelepipedTest.off";
    std::string name =  "parallelepipedTest";
    OFF_Reader reader;
    Polyhedron polyhedron = reader.read(fileName);

    Block_maker blockMaker;
    LCC_3 hex_mesh;
    FT lg = 1;
    // base
    blockMaker.make_cube(hex_mesh, Point(1,1,1), lg);
    blockMaker.make_cube(hex_mesh, Point(2,1,1), lg);
    blockMaker.make_cube(hex_mesh, Point(3,1,1), lg);
    blockMaker.make_cube(hex_mesh, Point(4,1,1), lg);
    blockMaker.make_cube(hex_mesh, Point(5,1,1), lg);
    blockMaker.make_cube(hex_mesh, Point(1,2,1), lg);
    blockMaker.make_cube(hex_mesh, Point(2,2,1), lg);
    blockMaker.make_cube(hex_mesh, Point(3,2,1), lg);
    blockMaker.make_cube(hex_mesh, Point(4,2,1), lg);
    blockMaker.make_cube(hex_mesh, Point(5,2,1), lg);
    blockMaker.make_cube(hex_mesh, Point(1,3,1), lg);
    blockMaker.make_cube(hex_mesh, Point(2,3,1), lg);
    blockMaker.make_cube(hex_mesh, Point(3,3,1), lg);
    blockMaker.make_cube(hex_mesh, Point(4,3,1), lg);
    blockMaker.make_cube(hex_mesh, Point(5,3,1), lg);

    blockMaker.make_cube(hex_mesh, Point(1,1,2), lg);
    blockMaker.make_cube(hex_mesh, Point(2,1,2), lg);
    blockMaker.make_cube(hex_mesh, Point(3,1,2), lg);
    blockMaker.make_cube(hex_mesh, Point(4,1,2), lg);
    blockMaker.make_cube(hex_mesh, Point(5,1,2), lg);
    blockMaker.make_cube(hex_mesh, Point(1,2,2), lg);
    blockMaker.make_cube(hex_mesh, Point(5,2,2), lg);
    blockMaker.make_cube(hex_mesh, Point(1,3,2), lg);
    blockMaker.make_cube(hex_mesh, Point(2,3,2), lg);
    blockMaker.make_cube(hex_mesh, Point(3,3,2), lg);
    blockMaker.make_cube(hex_mesh, Point(4,3,2), lg);
    blockMaker.make_cube(hex_mesh, Point(5,3,2), lg);
    hex_mesh.sew3_same_facets();

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
    boundaryConnector.connect3(hex_mesh, polyhedron);
    int number_of_intersecting_hexes = 0;
    Intersecting_polyhedron_finder< Polyhedron, LCC_3> intersectingPolyhedronFinder;
    std::vector<typename LCC::Dart_const_handle> intersecting_facets;
    for(LCC_3::One_dart_per_cell_range<3,3>::iterator it = hex_mesh.one_dart_per_cell<3>().begin(),
                end_it = hex_mesh.one_dart_per_cell<3>().end(); it != end_it; ++it)
    {
        if(intersectingPolyhedronFinder.do_polyhedron_facets_intersect(hex_mesh, it,intersecting_facets))
            number_of_intersecting_hexes++;
        intersecting_facets.clear();
    }

    //REQUIRE(number_of_intersecting_hexes == 0); //37
    const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput";
    std::string outputFileName1 = out_data_path + "/" + name + "_U_facet_detector_Mesh.mesh";
    std::ofstream medit_file(outputFileName1);
    Writer writer;
    writer.output_to_medit(medit_file,hex_mesh);
    medit_file.close();

}