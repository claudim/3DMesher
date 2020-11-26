#include "../Include/catch.hpp"
#include "test_config.h"
#include "PointNormal_boundary_intersectionPoint_finder.h"
#include <Block_maker.h>
#include <OFF_Reader.h>

TEST_CASE("PointNormal_boundary_intersectionPoint_finder"){

    Point internalBlockBasePoint = Point(2, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    PointNormal_boundary_intersectionPoint_finder pointFinder = PointNormal_boundary_intersectionPoint_finder();

    // if the point of internal cube is (2, 2, 2)
    boost::optional<Point> boostIntercectionPoint = pointFinder.findIntersecionPoint( lcc, internalBlock, polyhedron);
   REQUIRE (boostIntercectionPoint.is_initialized()== true);

    Point intercectionPoint = boostIntercectionPoint.get();

    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

    // if the point of internal cube is (2, 2, 4)
    boostIntercectionPoint  = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 1), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (4, 2, 2)
    boostIntercectionPoint = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 1,1,1), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

    // if the point of internal cube is (4, 2, 4)
    boostIntercectionPoint  = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 1,1), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 0);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (2, 4, 2)
    boostIntercectionPoint  = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1, 1, 2, 1), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 0);

    // if the point of internal cube is (2, 4, 4)
    boostIntercectionPoint  = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1 , 1, 2), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 0);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (4, 4, 4)
    boostIntercectionPoint  = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1, 1, 2, 1, 1, 1), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 6);

    // if the point of internal cube is (4, 4, 2)
    boostIntercectionPoint  = pointFinder.findIntersecionPoint( lcc, lcc.beta(internalBlock, 2, 1, 1, 2, 1, 1), polyhedron);
    REQUIRE (boostIntercectionPoint.is_initialized()== true);
    intercectionPoint = boostIntercectionPoint.get();
    REQUIRE(std::round(intercectionPoint.x()) == 6);
    REQUIRE(std::round(intercectionPoint.y()) == 6);
    REQUIRE(std::round(intercectionPoint.z()) == 0);
}

TEST_CASE("Test over the computation of the normal function"){

    Point internalBlockBasePoint1 = Point(2, 2, 2);
    Point internalBlockBasePoint2 = Point(3, 2, 2);

    FT internalBlockLg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle d0 =blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);
    Dart_handle d1 = blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
    lcc.display_characteristics(std::cout);
    std::cout<<std::endl;
    lcc.sew3_same_facets(); // link all blocks in lcc  with same facets if they are not linked.
    lcc.display_characteristics(std::cout);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    double d = CGAL::Polygon_mesh_processing::is_outward_oriented(polyhedron)?-1:1;
    //Dart_const_handle d2 = lcc.one_dart_per_incident_cell<0, 3, 3>(d1).begin();
    Dart_const_handle d2 = lcc.beta(d0,1,1,1);
    PointNormal_boundary_intersectionPoint_finder finder;
    Vector v = finder.my_compute_normal_of_cell_0(lcc, d2);
            Point p1 = lcc.point(d2);
            Ray ray = Ray(p1, d*v);
      Point     intersectionPoint;
    Tree tree(faces(polyhedron).begin(), faces(polyhedron).end(), polyhedron);
    auto intersection = tree.first_intersection(ray);
    if(intersection)
    {
        if(boost::get<Point>(&(intersection->first)))
        {
            intersectionPoint = boost::get<Point>(intersection->first);
        }
    }
   std::cout<<"punto inters"<< intersectionPoint.x() <<","<<intersectionPoint.y() <<","<<intersectionPoint.z() <<std::endl;




}

TEST_CASE("Test over the computation of the normal function2"){

    Point internalBlockBasePoint1 = Point(1, 2, 2);
    Point internalBlockBasePoint2 = Point(2, 2, 2);
    Point internalBlockBasePoint3 = Point(3, 2, 2);
    Point internalBlockBasePoint4 = Point(2, 2, 3);
    Point internalBlockBasePoint5 = Point(3, 2, 3);
    Point internalBlockBasePoint6 = Point(2, 1, 2);

    FT internalBlockLg = 1;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle d0 =blockMaker.make_cube(lcc, internalBlockBasePoint1, internalBlockLg);
    Dart_handle d1 = blockMaker.make_cube(lcc, internalBlockBasePoint2, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint3, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint4, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint5, internalBlockLg);
    blockMaker.make_cube(lcc, internalBlockBasePoint6, internalBlockLg);

    lcc.display_characteristics(std::cout);
    std::cout<<std::endl;
    lcc.sew3_same_facets(); // link all blocks in lcc  with same facets if they are not linked.
    lcc.display_characteristics(std::cout);

    std::string fileName = data_path + "/cubeTest.off";

    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    double d = CGAL::Polygon_mesh_processing::is_outward_oriented(polyhedron)?-1:1;
    //Dart_const_handle d2 = lcc.one_dart_per_incident_cell<0, 3, 3>(d1).begin();
    Dart_const_handle d2 = lcc.beta(d0,1,1,1);
    PointNormal_boundary_intersectionPoint_finder finder;
    Vector v = finder.my_compute_normal_of_cell_0(lcc, d2);
    Point p1 = lcc.point(d2);
    Ray ray = Ray(p1, d*v);
    Point     intersectionPoint;
    Tree tree(faces(polyhedron).begin(), faces(polyhedron).end(), polyhedron);
    auto intersection = tree.first_intersection(ray);
    if(intersection)
    {
        if(boost::get<Point>(&(intersection->first)))
        {
            intersectionPoint = boost::get<Point>(intersection->first);
        }
    }
    std::cout<<"punto inters"<< intersectionPoint.x() <<","<<intersectionPoint.y() <<","<<intersectionPoint.z() <<std::endl;
//    for(LCC_3::One_dart_per_cell_const_range<0,3>::const_iterator vertex_it = lcc.one_dart_per_cell<0,3>().begin(),
//                    vertex_end_it = lcc.one_dart_per_cell<0,3>().end(); vertex_it != vertex_end_it; ++vertex_it){
//        double d = CGAL::Polygon_mesh_processing::is_outward_oriented(polyhedron)?-1:1;
//        Vector v = compute_normal_of_cell_0(lcc, vertex_it);
//        auto direction =v.direction();
//        Point p1 = lcc.point(vertex_it);
//        Ray ray = Ray(p1, d*v);
//    }

}

TEST_CASE("must find the same intersection point for the same point which is incident to 2 adjacent facets") {
    std::string fileName = data_path + "/hexTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point internalBlockBasePoint = Point(2, 2, 2);
    Point internalAdjacentBlockBasePoint = Point(4, 2, 2);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);
    Dart_handle internalAdjacentBlock = blockMaker.make_cube(lcc, internalAdjacentBlockBasePoint, internalBlockLg);
    lcc.sew3_same_facets();

    // detect top facet dart of internalBlock cube
    Dart_handle topFacetBlock = lcc.beta(internalBlock, 2, 1, 1, 1, 2);
    // detect top facet dart of internalAdjacentBlock cube
    Dart_handle topFacetAdjacentBlock = lcc.beta(internalAdjacentBlock, 2, 1, 1, 1, 2);

    Point commonPoint1 = Point(4, 2, 4);
    Point commonPoint2 = Point(4, 4, 4);

    // find the intersection point of the 2 points in common of the top facet
    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
    Point blockIntersectionPoint1;
    boost::optional<Point> boostBlockIntersectionPoint1;
    boost::optional<Point> boostBlockIntersectionPoint2;
    Point blockIntersectionPoint2;
    for (LCC_3::One_dart_per_incident_cell_range<0, 2, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 2, 3>(
            topFacetBlock).begin(),
                 vertex_end_it = lcc.one_dart_per_incident_cell<0, 2, 3>(topFacetBlock).end();
         vertex_it != vertex_end_it; ++vertex_it) {
        if (lcc.point(vertex_it) == commonPoint1) {
            boostBlockIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                      vertex_it,
                                                                                                      polyhedron);
            REQUIRE (boostBlockIntersectionPoint1.is_initialized()== true);
            blockIntersectionPoint1 = boostBlockIntersectionPoint1.get();
        }

        if (lcc.point(vertex_it) == commonPoint2) {
            boostBlockIntersectionPoint2 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                      vertex_it,
                                                                                                      polyhedron);
            REQUIRE (boostBlockIntersectionPoint2.is_initialized()== true);
            blockIntersectionPoint2 = boostBlockIntersectionPoint2.get();
        }
    }

    //  find the intersection point of the 2 points in common of the adjacent top facet
    Point adjacentBlockIntersectionPoint1;
    Point adjacentBlockIntersectionPoint2;
    boost::optional<Point> boostAdjacentBlockIntersectionPoint1;
    boost::optional<Point> boostAdjacentBlockIntersectionPoint2;
    for (LCC_3::One_dart_per_incident_cell_range<0, 2, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 2, 3>(
            topFacetAdjacentBlock).begin(),
                 vertex_end_it = lcc.one_dart_per_incident_cell<0, 2, 3>(topFacetAdjacentBlock).end();
         vertex_it != vertex_end_it; ++vertex_it) {
        if (lcc.point(vertex_it) == commonPoint1) {
            boostAdjacentBlockIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                              vertex_it,
                                                                                                              polyhedron);
            REQUIRE (boostAdjacentBlockIntersectionPoint1.is_initialized()== true);
            adjacentBlockIntersectionPoint1 = boostAdjacentBlockIntersectionPoint1.get();
        }

        if (lcc.point(vertex_it) == commonPoint2) {
            boostAdjacentBlockIntersectionPoint2 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                              vertex_it,
                                                                                                              polyhedron);
            REQUIRE (boostAdjacentBlockIntersectionPoint2.is_initialized()== true);
            adjacentBlockIntersectionPoint2 = boostAdjacentBlockIntersectionPoint2.get();
        }
    }

//    std::cout<<"Point1: " <<blockIntersectionPoint1<<std::endl;
//    std::cout<<"Point2: " <<blockIntersectionPoint2<<std::endl;
    REQUIRE(blockIntersectionPoint1 == adjacentBlockIntersectionPoint1);
    REQUIRE(blockIntersectionPoint2 == adjacentBlockIntersectionPoint2);
}


TEST_CASE("must find the same intersection point for the same point which is incident to 2 adjacent facets second version") {
    std::string fileName = data_path + "/hexTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point internalBlockBasePoint = Point(1, 1, 1);
    Point internalAdjacentBlockBasePoint = Point(3, 1, 1);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);
    Dart_handle internalAdjacentBlock = blockMaker.make_cube(lcc, internalAdjacentBlockBasePoint, internalBlockLg);
    lcc.sew3_same_facets();

    // detect top facet dart of internalBlock cube
    Dart_handle topFacetBlock = lcc.beta(internalBlock, 2, 1, 1, 1, 2);
    // detect top facet dart of internalAdjacentBlock cube
    Dart_handle topFacetAdjacentBlock = lcc.beta(internalAdjacentBlock, 2, 1, 1, 1, 2);

    Point commonPoint1 = Point(3, 1, 3);
    Point commonPoint2 = Point(3, 3, 3);

    // find the intersection point of the 2 points in common of the top facet
    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
    Point blockIntersectionPoint1;
    Point blockIntersectionPoint2;
    boost::optional<Point> boostBlockIntersectionPoint1;
    boost::optional<Point> boostBlockIntersectionPoint2;
    for (LCC_3::One_dart_per_incident_cell_range<0, 2, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 2, 3>(
            topFacetBlock).begin(),
                 vertex_end_it = lcc.one_dart_per_incident_cell<0, 2, 3>(topFacetBlock).end();
         vertex_it != vertex_end_it; ++vertex_it) {
        if (lcc.point(vertex_it) == commonPoint1) {
            boostBlockIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                      vertex_it,
                                                                                                      polyhedron);
            REQUIRE (boostBlockIntersectionPoint1.is_initialized()== true);
            blockIntersectionPoint1 = boostBlockIntersectionPoint1.get();
        }

        if (lcc.point(vertex_it) == commonPoint2) {
            boostBlockIntersectionPoint2 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                      vertex_it,
                                                                                                      polyhedron);
            REQUIRE (boostBlockIntersectionPoint2.is_initialized()== true);
            blockIntersectionPoint2 = boostBlockIntersectionPoint2.get();
        }
    }

    //  find the intersection point of the 2 points in common of the adjacent top facet
    Point adjacentBlockIntersectionPoint1;
    Point adjacentBlockIntersectionPoint2;
    boost::optional<Point> boostAdjacentBlockIntersectionPoint1;
    boost::optional<Point> boostAdjacentBlockIntersectionPoint2;
    for (LCC_3::One_dart_per_incident_cell_range<0, 2, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 2, 3>(
            topFacetAdjacentBlock).begin(),
                 vertex_end_it = lcc.one_dart_per_incident_cell<0, 2, 3>(topFacetAdjacentBlock).end();
         vertex_it != vertex_end_it; ++vertex_it) {
        if (lcc.point(vertex_it) == commonPoint1) {
            boostAdjacentBlockIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                              vertex_it,
                                                                                                              polyhedron);
            REQUIRE (boostAdjacentBlockIntersectionPoint1.is_initialized()== true);
            adjacentBlockIntersectionPoint1 = boostAdjacentBlockIntersectionPoint1.get();
        }

        if (lcc.point(vertex_it) == commonPoint2) {
            boostAdjacentBlockIntersectionPoint2 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                              vertex_it,
                                                                                                              polyhedron);
            REQUIRE (boostAdjacentBlockIntersectionPoint2.is_initialized()== true);
            adjacentBlockIntersectionPoint2 = boostAdjacentBlockIntersectionPoint2.get();
        }
    }

//    std::cout<<"Point1: " <<blockIntersectionPoint1<<std::endl;
//    std::cout<<"Point2: " <<blockIntersectionPoint2<<std::endl;
    REQUIRE(blockIntersectionPoint1 == adjacentBlockIntersectionPoint1);
    REQUIRE(blockIntersectionPoint2 == adjacentBlockIntersectionPoint2);
}

TEST_CASE("must find the same intersection point for the same point which is incident to 1 adjacent edges")
{
    std::string fileName = data_path + "/hexTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point internalBlockBasePoint = Point(2, 2, 2);
    Point internalAdjacentBlockBasePoint = Point(4, 2, 4);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);
    Dart_handle internalAdjacentBlock = blockMaker.make_cube(lcc, internalAdjacentBlockBasePoint, internalBlockLg);
    lcc.sew3_same_facets();

    Point commonPoint1 = Point(4, 4, 4);
    Point commonPoint2 = Point(4, 2, 4);

    Dart_handle vertex1Handle;
    Dart_handle vertex2Handle;

// find the front  intersection point of the common  edge
PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
Point intersectionPoint1;
Point intersectionPoint2;
    boost::optional<Point> boostIntersectionPoint1;
    boost::optional<Point> boostIntersectionPoint2;
    for(LCC_3::One_dart_per_incident_cell_range<0,3,3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0,3,3>(internalBlock).begin(),
                vertex_end_it = lcc.one_dart_per_incident_cell<0,3,3>(internalBlock).end(); vertex_it != vertex_end_it; ++vertex_it){
        if(lcc.point(vertex_it) == commonPoint1)
        {
            boostIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                 vertex_it,
                                                                                                 polyhedron);
            REQUIRE (boostIntersectionPoint1.is_initialized()== true);
            intersectionPoint1 = boostIntersectionPoint1.get();
        }
        if(lcc.point(vertex_it) == commonPoint2)
        {
            boostIntersectionPoint2 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                     vertex_it,
                                                                                     polyhedron);
            REQUIRE (boostIntersectionPoint2.is_initialized()== true);
            intersectionPoint2 = boostIntersectionPoint2.get();
        }
    }

Point intersectionAdjacentPoint1;
Point intersectionAdjacentPoint2;
    boost::optional<Point> boostAdjacentBlockIntersectionPoint1;
    boost::optional<Point> boostAdjacentBlockIntersectionPoint2;
for(LCC_3::One_dart_per_incident_cell_range<0,3,3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0,3,3>(internalAdjacentBlock).begin(),
        vertex_end_it = lcc.one_dart_per_incident_cell<0,3,3>(internalAdjacentBlock).end(); vertex_it != vertex_end_it; ++vertex_it){
if(lcc.point(vertex_it) == commonPoint1)
{
    boostAdjacentBlockIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                     vertex_it,
                                                                                     polyhedron);
    REQUIRE (boostAdjacentBlockIntersectionPoint1.is_initialized()== true);
    intersectionAdjacentPoint1 = boostAdjacentBlockIntersectionPoint1.get();
}
if(lcc.point(vertex_it) == commonPoint2)
{
    boostAdjacentBlockIntersectionPoint2 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                     vertex_it,
                                                                                     polyhedron);
    REQUIRE (boostAdjacentBlockIntersectionPoint2.is_initialized()== true);
    intersectionAdjacentPoint2 = boostAdjacentBlockIntersectionPoint2.get();
}
}

REQUIRE(intersectionAdjacentPoint2 == intersectionPoint2);
REQUIRE(intersectionAdjacentPoint1 == intersectionPoint1);
}

TEST_CASE("must find the same intersection point for the same point")
{
    std::string fileName = data_path + "/hexTest.off";
    OFF_Reader reader = OFF_Reader();
    Polyhedron polyhedron = reader.read(fileName);

    Point internalBlockBasePoint = Point(2, 2, 2);
    Point internalAdjacentBlockBasePoint = Point(4, 4, 4);
    FT internalBlockLg = 2;
    LCC_3 lcc;
    Block_maker blockMaker = Block_maker();
    Dart_handle internalBlock = blockMaker.make_cube(lcc, internalBlockBasePoint, internalBlockLg);
    Dart_handle internalAdjacentBlock = blockMaker.make_cube(lcc, internalAdjacentBlockBasePoint, internalBlockLg);
    lcc.sew3_same_facets();

    Point commonPoint1 = Point(4, 4, 4);

    Dart_handle vertex1Handle;
    Dart_handle vertex2Handle;

// find the front  intersection point of the common  edge
    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
    Point intersectionPoint1;
    boost::optional<Point> boostIntersectionPoint1;
    for(LCC_3::One_dart_per_incident_cell_range<0,3,3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0,3,3>(internalBlock).begin(),
                vertex_end_it = lcc.one_dart_per_incident_cell<0,3,3>(internalBlock).end(); vertex_it != vertex_end_it; ++vertex_it){
        if(lcc.point(vertex_it) == commonPoint1)
        {
            boostIntersectionPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                 vertex_it,
                                                                                                 polyhedron);
            REQUIRE (boostIntersectionPoint1.is_initialized()== false);
        }
    }

    Point intersectionAdjacentPoint1;
    boost::optional<Point> boostIntersectionAdjacentPoint1;
    for(LCC_3::One_dart_per_incident_cell_range<0,3,3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0,3,3>(internalAdjacentBlock).begin(),
                vertex_end_it = lcc.one_dart_per_incident_cell<0,3,3>(internalAdjacentBlock).end(); vertex_it != vertex_end_it; ++vertex_it){
        if(lcc.point(vertex_it) == commonPoint1)
        {
            boostIntersectionAdjacentPoint1 = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc,
                                                                                                         vertex_it,
                                                                                                         polyhedron);
            REQUIRE (boostIntersectionAdjacentPoint1.is_initialized()== false);
        }
    }

    REQUIRE(boostIntersectionAdjacentPoint1 == boostIntersectionPoint1);
}