#include "../Include/catch.hpp"
#include "test_config.h"
#include "Point_normal_finder.h"
#include <Block_maker.h>
#include "PointNormal_boundary_intersectionPoint_finder.h"
#include "STL_reader.h"

TEST_CASE("must find normal vector parallel to y"){

    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
    typedef CGAL::Ray_3<K> Ray;

    // the 2 cubes share an edge
    Point internalBlockBasePoint1 = Point(2, 2, 2);
    Point internalBlockBasePoint2 = Point(4, 2, 4);

    FT internalBlockLg = 2;
    LCC_3 lcc1;
    Block_maker blockMaker = Block_maker();
    Dart_handle d0 =blockMaker.make_cube(lcc1, internalBlockBasePoint1, internalBlockLg);
    Dart_handle d1 = blockMaker.make_cube(lcc1, internalBlockBasePoint2, internalBlockLg);
    lcc1.sew3_same_facets(); // link all blocks in lcc  with same facets if they are not linked.

    Point_normal_finder<LCC_3> pointNormalFinder;
    LCC_3::Vector normal1 =  pointNormalFinder.compute(lcc1, Point(4,2,4));

    LCC_3::Vector normal2 =  pointNormalFinder.compute(lcc1, Point(4,4,4));
    Ray ray1 = Ray(Point(4,2,4), normal1);

    Ray ray2 = Ray(Point(4,4,4), normal2);

    Ray rayPositiveY = Ray(Point(0,0,0), Point(0,1,0));
    Ray rayNegativeY = Ray(Point(0,0,0), Point(0,-1,0));
    REQUIRE(CGAL::parallel(ray1, ray2));
    REQUIRE(CGAL::parallel(ray1, rayNegativeY));
    REQUIRE(CGAL::parallel(ray2, rayPositiveY));


    // the 2 cubes share a vertex
    Point internalBlockBasePoint3 = Point(2, 2, 2);
    Point internalBlockBasePoint4 = Point(4, 4, 4);
    LCC_3 lcc2;
    Dart_handle d3 =blockMaker.make_cube(lcc2, internalBlockBasePoint3, internalBlockLg);
    Dart_handle d4 = blockMaker.make_cube(lcc2, internalBlockBasePoint4, internalBlockLg);
    lcc2.sew3_same_facets();

    LCC_3::Vector normal3 =  pointNormalFinder.compute(lcc2, internalBlockBasePoint4);
    REQUIRE(normal3.squared_length() == 0) ;

    std::string fileName = data_path + "/cubeTest.stl";
    STL_reader reader = STL_reader();
    Polyhedron polyhedron = reader.read(fileName);
    LCC_3::One_dart_per_incident_cell_range<0,3,3>::iterator it = lcc2.one_dart_per_incident_cell<0,3,3>(d4).begin(),
    vertex_end_it = lcc2.one_dart_per_incident_cell<0,3,3>(d4).end() ;
    Dart_handle vertexIt;
    while(it != vertex_end_it)
    {
        if(lcc2.point(it) == internalBlockBasePoint4){
            vertexIt = it;
        }
        ++it;
    }

    PointNormal_boundary_intersectionPoint_finder pointNormalBoundaryIntersectionPointFinder;
    boost::optional<Point> p = pointNormalBoundaryIntersectionPointFinder.findIntersecionPoint(lcc2, vertexIt, polyhedron);
    REQUIRE(p.is_initialized() == false);


}

