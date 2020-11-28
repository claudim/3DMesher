#include "../Include/catch.hpp"
#include "test_config.h"
#include <OFF_Reader.h>
#include "Block_maker.h"
#include "Writer.h"
#include <InitialMesh_boundary_connector.h>
#include <CGAL/Polygon_mesh_processing/bbox.h>
#include <CGAL/Bbox_3.h>
#include "Point_normal_finder.h"
#include <CGAL/intersections.h>

typedef  K::Intersect_3 Intersect_3;
typedef  K::Ray_3 Ray;
TEST_CASE("InitialMesh_boundary_connector cube in cube"){

    Point internalBlockBasePoint = Point(2, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();

    boundaryConnector.connect(lcc, polyhedron);

    int number_of_cubes = 0;
    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
    {
        number_of_cubes++;
    }
    REQUIRE(number_of_cubes == 7);

    int number_of_facets = 0;
    for (LCC_3::One_dart_per_cell_const_range<2,3>::const_iterator lcc_facets_iterator = lcc.one_dart_per_cell<2,3>().begin(),
                 lcc_facets_end_iterator = lcc.one_dart_per_cell<2,3>().end(); lcc_facets_iterator != lcc_facets_end_iterator; ++lcc_facets_iterator)
    {
        number_of_facets++;
    }
    REQUIRE( number_of_facets == 24);

    int number_of_edges = 0;
    for (LCC_3::One_dart_per_cell_const_range<1,3>::const_iterator lcc_edges_iterator = lcc.one_dart_per_cell<1,3>().begin(),
                 lcc_edges_end_iterator = lcc.one_dart_per_cell<1,3>().end(); lcc_edges_iterator != lcc_edges_end_iterator; ++lcc_edges_iterator)
    {
        number_of_edges++;
    }
    REQUIRE( number_of_edges == 32);

    int number_of_vertices = 0;
    for (LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator lcc_vertex_iterator = lcc.one_dart_per_cell<0,3>().begin(),
                 lcc_vertex_end_iterator = lcc.one_dart_per_cell<0,3>().end(); lcc_vertex_iterator != lcc_vertex_end_iterator; ++lcc_vertex_iterator)
    {
        number_of_vertices++;
    }
    REQUIRE( number_of_vertices == 16);

    // Output
    std::ofstream medit_file("out.mesh");
    Writer w;
    w.output_to_medit(medit_file,lcc);

    // const CGAL::Bbox_3 polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);
    // const CGAL::Bbox_3 lcc_bbox3 = CGAL::Polygon_mesh_processing::bbox(lcc);
    // const CGAL::Bbox_3 lcc_bbox3 = bbox_3(lcc.one_dart_per_cell<0,3>().begin(), lcc.one_dart_per_cell<0,3>().end());
    // REQUIRE( polyhedron_bbox3 == lcc_bbox3);

}
TEST_CASE("InitialMesh_boundary_connector cube in sphere"){

    Point internalBlockBasePoint = Point(2, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    std::string fileName = data_path + "/sphere.off";
}


TEST_CASE("InitialMesh_boundary_connector cubes in cube"){

    Point internalBlockBasePoint1 = Point(2, 2, 2);
    Point internalBlockBasePoint2 = Point(3, 2, 2);
    Point internalBlockBasePoint3 = Point(2, 2, 3);
    Point internalBlockBasePoint4 = Point(3, 2, 3);
//    Point internalBlockBasePoint5 = Point(2, 3, 2);
//    Point internalBlockBasePoint6 = Point(3, 3, 2);
//    Point internalBlockBasePoint7 = Point(2, 3, 3);
//    Point internalBlockBasePoint8 = Point(3, 3, 3);

    FT internalBlockLg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
    Dart_handle  d =  blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint5, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint6, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint7, internalBlockLg);
//    blockMaker.make_cube(lcc, internalBlockBasePoint8, internalBlockLg);
//lcc.display_characteristics(std::cout);
    lcc.sew3_same_facets(); // link all blocks in lcc  with same facets if they are not linked.
    //lcc.display_characteristics(std::cout);

    int i = 0;
    for(LCC_3::One_dart_per_incident_cell_const_range<2,0,3>::const_iterator f_it = lcc.one_dart_per_incident_cell<2,0,3>(d).begin(),
                f_end_it = lcc.one_dart_per_incident_cell<2,0,3>(d).end(); f_it != f_end_it; ++f_it)
    {
        //Vector map = compute_normal_of_cell_0(lcc, f_it);
        i++;
        std::cout << i <<std::endl;
    }


    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    InitialMesh_boundary_connector boundaryConnector = InitialMesh_boundary_connector();
    boundaryConnector.connect(lcc, polyhedron);

//    int number_of_cubes = 0;
//    for (LCC_3::One_dart_per_cell_const_range<3,3>::const_iterator lcc_cells_iterator = lcc.one_dart_per_cell<3,3>().begin(),
//                 lcc_cells_end_iterator = lcc.one_dart_per_cell<3,3>().end(); lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator)
//    {
//        number_of_cubes++;
//    }
//    REQUIRE(number_of_cubes == 32);

//    int number_of_vertices = 0;
//    for (LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator lcc_vertex_iterator = lcc.one_dart_per_cell<0,3>().begin(),
//                 lcc_vertex_end_iterator = lcc.one_dart_per_cell<0,3>().end(); lcc_vertex_iterator != lcc_vertex_end_iterator; ++lcc_vertex_iterator)
//    {
//        number_of_vertices++;
//    }
//    REQUIRE( number_of_vertices == 83);

//    // Output
//    std::ofstream medit_file("cubesInCube.mesh");
//    Writer w;
//    w.output_to_medit(medit_file,lcc);
}

TEST_CASE("initial mesh like L"){
    //std::string fileName = data_path + "/cubeTest.off";
    std::string fileName = data_path + "/cube10.off";
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

    Point_normal_finder<LCC_3> pnf;
    LCC_3::Vector normal_vector1;
    LCC_3::Vector normal_vector2;
    LCC_3::Vector normal_vector3;
    Point p1 = Point(3,2,2);
    Point p2 = Point(3,2,3);
    Dart_const_handle dart_p1;
    Dart_const_handle dart_p2;
    Ray ray1;
    Ray ray2;
    Ray ray3;
    for(LCC_3::One_dart_per_incident_cell_const_range<0,3,3>::const_iterator v_it = lcc.one_dart_per_incident_cell<0,3,3>(d).begin(),
                f_end_it = lcc.one_dart_per_incident_cell<0,3,3>(d).end(); v_it != f_end_it; ++v_it)
    {
        Point p = lcc.point(v_it);
        if(p == p1)
        {
            normal_vector1 = pnf.compute(lcc, p);
            ray1 = Ray(p, normal_vector1.direction());
            dart_p1 = v_it;
        }
        if(p == p2)
        {
            normal_vector2 = pnf.compute(lcc, p);
            ray2 = Ray(p, normal_vector2.direction());
            dart_p2 = v_it;
        }
    }


    for(LCC_3::One_dart_per_incident_cell_const_range<0,3,3>::const_iterator v_it = lcc.one_dart_per_incident_cell<0,3,3>(d2).begin(),
                f_end_it = lcc.one_dart_per_incident_cell<0,3,3>(d2).end(); v_it != f_end_it; ++v_it)
    {
        Point p = lcc.point(v_it);
        if(p == Point(4,1,2))
        {
            normal_vector3 = pnf.compute(lcc, p);
            ray3 = Ray(p, normal_vector3);
        }
    }

    // Is there intersection between the 2 rays?
    CGAL::cpp11::result_of<Intersect_3(Ray, Ray)>::type
            result = intersection(ray1, ray2);
    if (result) {
        if (const K::Segment_3* s = boost::get<K::Segment_3>(&*result)) {
            std::cout << *s << std::endl;
        }
        if(const Point* p = boost::get<Point>(&*result)){
            std::cout << *p << std::endl;
        }
        if(const Ray* r = boost::get<Ray >(&*result)){
            //const Ray* r = boost::get<Ray >(&*result);
            std::cout << *r << std::endl;
        }
    }
    else{
        std::cout << "no intersection" << std::endl;
    }
REQUIRE (!result.is_initialized());

    CGAL::cpp11::result_of<Intersect_3(Ray, Ray)>::type
            result2 = intersection(ray1, ray3);
    if (result2) {
        if (const K::Segment_3* s = boost::get<K::Segment_3>(&*result)) {
            std::cout << *s << std::endl;
        }
        if(const Point* p = boost::get<Point>(&*result)){
            std::cout << *p << std::endl;
        }
        if(const Ray* r = boost::get<Ray >(&*result)){
            //const Ray* r = boost::get<Ray >(&*result);
            std::cout << *r << std::endl;
        }
    }
    else{
        std::cout << "no intersection" << std::endl;
    }
    REQUIRE (!result2.is_initialized());

    CGAL::cpp11::result_of<Intersect_3(Ray, Ray)>::type
            result3 = intersection(ray2, ray3);
    if (result3) {
        if (const K::Segment_3* s = boost::get<K::Segment_3>(&*result)) {
            std::cout << *s << std::endl;
        }
        if(const Point* p = boost::get<Point>(&*result)){
            std::cout << *p << std::endl;
        }
        if(const Ray* r = boost::get<Ray >(&*result)){
            //const Ray* r = boost::get<Ray >(&*result);
            std::cout << *r << std::endl;
        }
    }
    else{
        std::cout << "no intersection" << std::endl;
    }
    REQUIRE (!result3.is_initialized());

    PointNormal_boundary_intersectionPoint_finder intersectionPointFinder;
    boost::optional<Point> boostIntersectionPoint1 = intersectionPointFinder.findIntersecionPoint(lcc, dart_p1, polyhedron);
    boost::optional<Point> boostIntersectionPoint2 = intersectionPointFinder.findIntersecionPoint(lcc, dart_p2, polyhedron);

    if(boostIntersectionPoint1.is_initialized())
    {
        std::cout<<"p1 "<<boostIntersectionPoint1.get()<<std::endl;
    }
    if(boostIntersectionPoint2.is_initialized())
    {
        std::cout<<"p2 "<<boostIntersectionPoint2.get()<<std::endl;
    }
}