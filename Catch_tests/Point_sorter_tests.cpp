#include "../Include/catch.hpp"
#include "test_config.h"
#include "Point_sorter.h"
//
TEST_CASE("Order points by Z coordinate"){
    Point_sorter pointSorter;

    Point p1(2, 2, 2);
    Point p2(2, 2, 4);
    Point p3(4, 2, 4);
    Point p4(4, 2, 2);

    std::vector<Point> pointsToSort;

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);

    iterator vector_it = pointsToSort.begin(), vector_end_it = pointsToSort.end();
    std::sort(pointsToSort.begin(), pointsToSort.end(), [](Point a, Point b) {return a.z() < b.z(); });

    REQUIRE(pointsToSort[0] == p1);
    REQUIRE(pointsToSort[1] == p4);
    REQUIRE(pointsToSort[2] == p2);
    REQUIRE(pointsToSort[3] == p3);

}

TEST_CASE("Group points by Z coordinate"){

    Point_sorter pointSorter;

    Point p1(2, 2, 2);
    Point p2(2, 2, 4);
    Point p3(4, 2, 4);
    Point p4(4, 2, 2);
    Point p5(4, 2, 5);

    std::vector<Point> points;

    points.emplace_back(p4);
    points.emplace_back(p1);
    points.emplace_back(p3);
    points.emplace_back(p2);
    points.emplace_back(p5);

    iterator vector_it = points.begin(), vector_end_it = points.end();

    std::vector<iterator> zGroupIterator;

    pointSorter.groupByZ(points, zGroupIterator,vector_it, vector_end_it);

    REQUIRE(zGroupIterator.size() == 3);
    iterator2 firstzGroupIterator = zGroupIterator.begin();
    REQUIRE(*(*firstzGroupIterator) == *vector_it);
    iterator2 secondzGroupIterator = ++firstzGroupIterator;
    vector_it = vector_it + 2;
    REQUIRE(*(*secondzGroupIterator) == *vector_it);

    iterator2 thirdzGroupIterator = ++secondzGroupIterator;
    vector_it = vector_it + 2;
    REQUIRE(*(*thirdzGroupIterator) == *vector_it);

    SECTION("Another test to group points by z"){

        Point p6(4, 5, 5);
        Point p7(4, 2, 6);
        Point p8(4, 4, 6);
        Point p9(4, 5, 6);
        Point p10(4, 2, 7);

        points.clear();

        points.emplace_back(p4);
        points.emplace_back(p1);
        points.emplace_back(p3);
        points.emplace_back(p2);
        points.emplace_back(p5);
        points.emplace_back(p6);
        points.emplace_back(p7);
        points.emplace_back(p8);
        points.emplace_back(p9);
        points.emplace_back(p10);

        std::sort(points.begin(), points.end(), [](Point a, Point b) {return a.z() < b.z(); });

        for(Point p: points){
            std::cout<< p.x() << ", " << p.y() << ", " << p.z() <<std::endl;
        }

        vector_it = points.begin();
        vector_end_it = points.end();

        zGroupIterator.clear();
        pointSorter.groupByZ(points, zGroupIterator,vector_it, vector_end_it);

        REQUIRE(zGroupIterator.size() == 5);
        firstzGroupIterator = zGroupIterator.begin();
        REQUIRE(*(*firstzGroupIterator) == *vector_it);
        secondzGroupIterator = ++firstzGroupIterator;
        vector_it = vector_it + 2;
        REQUIRE(*(*secondzGroupIterator) == *vector_it);

        thirdzGroupIterator = ++secondzGroupIterator;
        vector_it = vector_it + 2;
        REQUIRE(*(*thirdzGroupIterator) == *vector_it);

        iterator2 fourthzGroupIterator = ++thirdzGroupIterator;
        vector_it = vector_it + 2;
        REQUIRE(*(*fourthzGroupIterator) == *vector_it);

        iterator2 fifthGroupIterator = ++fourthzGroupIterator;
        vector_it = vector_it + 3;
        REQUIRE(*(*fifthGroupIterator) == *vector_it);

    }
}

TEST_CASE("Group points by Y coordinate"){

    Point_sorter pointSorter;

    Point p1(2, 2, 2);
    Point p2(2, 2, 4);
    Point p3(4, 2, 4);
    Point p4(4, 2, 2);
    Point p5(4, 2, 5);

    std::vector<Point> points;

    points.emplace_back(p4);
    points.emplace_back(p1);
    points.emplace_back(p3);
    points.emplace_back(p2);
    points.emplace_back(p5);

     std::sort(points.begin(), points.end(), [](Point a, Point b) {return a.y() < b.y(); });

    iterator vector_it = points.begin(), vector_end_it = points.end();

    std::vector<iterator> yGroupIterator;

    pointSorter.groupByY(points, yGroupIterator,vector_it, vector_end_it);

    REQUIRE(yGroupIterator.size() == 1);
    iterator2 firstyGroupIterator = yGroupIterator.begin();
    REQUIRE(*(*firstyGroupIterator) == *vector_it);

        Point p6(4, 5, 5);
        Point p7(4, 2, 6);
        Point p8(4, 4, 6);
        Point p9(4, 5, 6);
        Point p10(4, 2, 7);

        points.clear();

        points.emplace_back(p4);
        points.emplace_back(p1);
        points.emplace_back(p3);
        points.emplace_back(p2);
        points.emplace_back(p5);
        points.emplace_back(p6);
        points.emplace_back(p7);
        points.emplace_back(p8);
        points.emplace_back(p9);
        points.emplace_back(p10);

        std::sort(points.begin(), points.end(), [](Point a, Point b) {return a.y() < b.y(); });

        for(Point p: points){
            std::cout<< p.x() << ", " << p.y() << ", " << p.z() <<std::endl;
        }

        vector_it = points.begin();
        vector_end_it = points.end();

        yGroupIterator.clear();
        pointSorter.groupByY(points, yGroupIterator,vector_it, vector_end_it);

        REQUIRE(yGroupIterator.size() == 3);
        firstyGroupIterator = yGroupIterator.begin();
        REQUIRE(*(*firstyGroupIterator) == *vector_it);
        iterator2 secondyGroupIterator = ++firstyGroupIterator;
        vector_it = vector_it + 7;
        REQUIRE(*(*secondyGroupIterator) == *vector_it);

        iterator2 thirdyGroupIterator = ++secondyGroupIterator;
        vector_it = vector_it + 1;
        REQUIRE(*(*thirdyGroupIterator) == *vector_it);
//
//    }
}

TEST_CASE("Group points by X and Y coordinate"){
    Point_sorter pointSorter;

    Point p1(2, 2, 2);
    Point p2(2, 2, 4);
    Point p3(4, 2, 4);
    Point p4(4, 2, 2);
    Point p5(4, 2, 5);

    std::vector<Point> points;

    points.emplace_back(p4);
    points.emplace_back(p1);
    points.emplace_back(p3);
    points.emplace_back(p2);
    points.emplace_back(p5);

    std::sort(points.begin(), points.end(), [](Point a, Point b) {return a.z() < b.z(); });

    iterator vector_it = points.begin(), vector_end_it = points.end();

    std::vector<iterator> zGroupIterator;

    pointSorter.groupByZ(points, zGroupIterator,vector_it, vector_end_it);

    REQUIRE(zGroupIterator.size() == 3);
    iterator2 firstzGroupIterator = zGroupIterator.begin();
    REQUIRE(*(*firstzGroupIterator) == *vector_it);
    iterator2 secondzGroupIterator = ++firstzGroupIterator;
    vector_it = vector_it + 2;
    REQUIRE(*(*secondzGroupIterator) == *vector_it);
    iterator2 thirdzGroupIterator = ++secondzGroupIterator;
    vector_it = vector_it + 2;
    REQUIRE(*(*thirdzGroupIterator) == *vector_it);

    std::vector<iterator> yGroupIterator;
    for(iterator2 it = zGroupIterator.begin(),it2 = ++zGroupIterator.begin(), it_end = zGroupIterator.end(); it!= it_end; ++it, ++it2){
        if(it2 != it_end) {
            std::sort(*it, *it2, [](Point a, Point b) { return a.y() < b.y(); });
            pointSorter.groupByY(points, yGroupIterator, *it, *it2);
        }
        else{
            std::sort(*it, points.end(), [](Point a, Point b) { return a.y() < b.y(); });
            pointSorter.groupByY(points, yGroupIterator, *it, points.end());
        }
    }
    REQUIRE(yGroupIterator.size() == 3);
    iterator2 itz = zGroupIterator.begin();
    iterator2 ity = yGroupIterator.begin();
    REQUIRE(*(*itz) == *(*ity));
    itz++; ity++;
    REQUIRE(*(*itz) == *(*ity));
    itz++; ity++;
    REQUIRE(*(*itz) == *(*ity));

}

TEST_CASE("Order points by Z then by Y and X"){
    Point_sorter pointSorter;
    std::vector<Point> pointsToSort;
    Point p1, p2, p3, p4;

    p1= Point(2, 2, 2);
    p2= Point(2, 2, 4);
    p3= Point(4, 2, 4);
    p4= Point(4, 2, 2);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);

    pointSorter.sortByZYX(pointsToSort);

    REQUIRE(pointsToSort[0] == p1);
    REQUIRE(pointsToSort[1] == p4);
    REQUIRE(pointsToSort[2] == p2);
    REQUIRE(pointsToSort[3] == p3);

    pointsToSort.clear();
    std::vector<Point> pointsToSort2;

    p1= Point(2, 2, 2);
    p2= Point(2, 2, 4);
    p3= Point(4, 1, 4);
    p4= Point(4, 2, 2);

    pointsToSort2.emplace_back(p1);
    pointsToSort2.emplace_back(p2);
    pointsToSort2.emplace_back(p3);
    pointsToSort2.emplace_back(p4);

    pointSorter.sortByZYX(pointsToSort2);

    REQUIRE(pointsToSort2[0] == p1);
    REQUIRE(pointsToSort2[1] == p4);
    REQUIRE(pointsToSort2[2] == p3);
    REQUIRE(pointsToSort2[3] == p2);

        p1 = Point(2, 4, 2);
        p2 = Point(4, 4, 2);
        p3 = Point(4, 2, 2);
        p4 = Point(2, 2, 2);

    std::vector<Point> pointsToSort3;

        pointsToSort3.emplace_back(p1);
        pointsToSort3.emplace_back(p2);
        pointsToSort3.emplace_back(p3);
        pointsToSort3.emplace_back(p4);

        pointSorter.sortByZYX(pointsToSort3);

        REQUIRE(pointsToSort3[0] == p4);
        REQUIRE(pointsToSort3[1] == p3);
        REQUIRE(pointsToSort3[2] == p1);
        REQUIRE(pointsToSort3[3] == p2);

}

TEST_CASE("Find and sort the southest hex facet"){
    Point_sorter pointSorter;
    std::vector<Point> pointsToSort;
    std::vector<Point> southestFacetPoints;
    Point p1, p2, p3, p4, p5, p6, p7, p8;

    p1= Point(2, 4, 4);
    p2= Point(2, 2, 4);
    p3= Point(4, 2, 4);
    p4= Point(4, 4, 4);
    p5= Point(0, 0, 6);
    p6= Point(6, 0, 6);
    p7= Point(6, 6, 6);
    p8= Point(0, 6, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_southest_points_facet(pointsToSort, southestFacetPoints);

    REQUIRE(southestFacetPoints[0] == p2);
    REQUIRE(southestFacetPoints[1] == p3);
    REQUIRE(southestFacetPoints[2] == p4);
    REQUIRE(southestFacetPoints[3] == p1);

    pointsToSort.clear();
    southestFacetPoints.clear();

    p1= Point(2, 4, 2);
    p2= Point(2, 2, 2);
    p3= Point(4, 2, 2);
    p4= Point(4, 4, 2);
    p5= Point(0, 6, 0);
    p6= Point(0, 0, 0);
    p7= Point(6, 0, 0);
    p8= Point(6, 6, 0);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_southest_points_facet(pointsToSort, southestFacetPoints);

    REQUIRE(southestFacetPoints[0] == p6);
    REQUIRE(southestFacetPoints[1] == p7);
    REQUIRE(southestFacetPoints[2] == p8);
    REQUIRE(southestFacetPoints[3] == p5);

    pointsToSort.clear();
    southestFacetPoints.clear();

    p1= Point(2, 2, 2);
    p2= Point(2, 2, 4);
    p3= Point(2, 4, 4);
    p4= Point(2, 4, 2);
    p5= Point(0, 0, 6);
    p6= Point(0, 0, 0);
    p7= Point(0, 6, 0);
    p8= Point(0, 6, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_southest_points_facet(pointsToSort, southestFacetPoints);

//    REQUIRE(southestFacetPoints[0] == p6);
//    REQUIRE(southestFacetPoints[1] == p7);
//    REQUIRE(southestFacetPoints[2] == p4);
//    REQUIRE(southestFacetPoints[3] == p1);
    REQUIRE(southestFacetPoints[0] == p6);
    REQUIRE(southestFacetPoints[1] == p1);
    REQUIRE(southestFacetPoints[2] == p4);
    REQUIRE(southestFacetPoints[3] == p7);

    pointsToSort.clear();
    southestFacetPoints.clear();

    p1= Point(2, 2, 2);
    p2= Point(2, 2, 4);
    p3= Point(4, 2, 2);
    p4= Point(4, 2, 4);
    p5= Point(0, 0, 6);
    p6= Point(0, 0, 0);
    p7= Point(6, 0, 0);
    p8= Point(6, 0, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_southest_points_facet(pointsToSort, southestFacetPoints);

    REQUIRE(southestFacetPoints[0] == p6);
    REQUIRE(southestFacetPoints[1] == p7);
    REQUIRE(southestFacetPoints[2] == p3);
    REQUIRE(southestFacetPoints[3] == p1);

    pointsToSort.clear();
    southestFacetPoints.clear();

    p1= Point(2, 4, 4);
    p2= Point(4, 4, 4);
    p3= Point(4, 4, 2);
    p4= Point(2, 4, 2);
    p5= Point(0, 6, 6);
    p6= Point(0, 6, 0);
    p7= Point(6, 6, 0);
    p8= Point(6, 6, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_southest_points_facet(pointsToSort, southestFacetPoints);

//    REQUIRE(southestFacetPoints[0] == p6);
//    REQUIRE(southestFacetPoints[1] == p7);
//    REQUIRE(southestFacetPoints[2] == p3);
//    REQUIRE(southestFacetPoints[3] == p4);

    REQUIRE(southestFacetPoints[0] == p4);
    REQUIRE(southestFacetPoints[1] == p3);
    REQUIRE(southestFacetPoints[2] == p7);
    REQUIRE(southestFacetPoints[3] == p6);

    pointsToSort.clear();
    southestFacetPoints.clear();

    p1= Point(4, 2, 2);
    p2= Point(4, 2, 4);
    p3= Point(4, 4, 4);
    p4= Point(4, 4, 2);
    p5= Point(6, 0, 0);
    p6= Point(6, 6, 0);
    p7= Point(6, 6, 6);
    p8= Point(6, 0, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_southest_points_facet(pointsToSort, southestFacetPoints);

    REQUIRE(southestFacetPoints[0] == p1);
    REQUIRE(southestFacetPoints[1] == p5);
    REQUIRE(southestFacetPoints[2] == p6);
    REQUIRE(southestFacetPoints[3] == p4);

}

TEST_CASE("Find and sort the northest hex facet"){
    Point_sorter pointSorter;
    std::vector<Point> pointsToSort;
    std::vector<Point> northestFacetPoints;
    Point p1, p2, p3, p4, p5, p6, p7, p8;

    //Top hex
    p1= Point(2, 4, 4);
    p2= Point(2, 2, 4);
    p3= Point(4, 2, 4);
    p4= Point(4, 4, 4);
    p5= Point(0, 0, 6);
    p6= Point(6, 0, 6);
    p7= Point(6, 6, 6);
    p8= Point(0, 6, 6);


    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_northest_points_facet(pointsToSort, northestFacetPoints);

    REQUIRE(northestFacetPoints[0] == p8);
    REQUIRE(northestFacetPoints[1] == p5);
    REQUIRE(northestFacetPoints[2] == p6);
    REQUIRE(northestFacetPoints[3] == p7);

    pointsToSort.clear();
    northestFacetPoints.clear();

    //Bottom hex
    p1= Point(2, 4, 2);
    p2= Point(2, 2, 2);
    p3= Point(4, 2, 2);
    p4= Point(4, 4, 2);
    p5= Point(0, 6, 0);
    p6= Point(0, 0, 0);
    p7= Point(6, 0, 0);
    p8= Point(6, 6, 0);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_northest_points_facet(pointsToSort, northestFacetPoints);

    REQUIRE(northestFacetPoints[0] == p1);
    REQUIRE(northestFacetPoints[1] == p2);
    REQUIRE(northestFacetPoints[2] == p3);
    REQUIRE(northestFacetPoints[3] == p4);

    pointsToSort.clear();
    northestFacetPoints.clear();

    //Left  hex
    p1= Point(2, 2, 2);
    p2= Point(2, 2, 4);
    p3= Point(2, 4, 4);
    p4= Point(2, 4, 2);
    p5= Point(0, 0, 6);
    p6= Point(0, 0, 0);
    p7= Point(0, 6, 0);
    p8= Point(0, 6, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_northest_points_facet(pointsToSort, northestFacetPoints);

    REQUIRE(northestFacetPoints[0] == p8);
    REQUIRE(northestFacetPoints[1] == p5);
    REQUIRE(northestFacetPoints[2] == p2);
    REQUIRE(northestFacetPoints[3] == p3);

    pointsToSort.clear();
    northestFacetPoints.clear();

    //Front hex
    p1= Point(2, 2, 2);
    p2= Point(2, 2, 4);
    p3= Point(4, 2, 2);
    p4= Point(4, 2, 4);
    p5= Point(0, 0, 6);
    p6= Point(0, 0, 0);
    p7= Point(6, 0, 0);
    p8= Point(6, 0, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_northest_points_facet(pointsToSort, northestFacetPoints);

    REQUIRE(northestFacetPoints[0] == p2);
    REQUIRE(northestFacetPoints[1] == p5);
    REQUIRE(northestFacetPoints[2] == p8);
    REQUIRE(northestFacetPoints[3] == p4);

    pointsToSort.clear();
    northestFacetPoints.clear();

    //Back hex
    p1= Point(2, 4, 4);
    p2= Point(4, 4, 4);
    p3= Point(4, 4, 2);
    p4= Point(2, 4, 2);
    p5= Point(0, 6, 6);
    p6= Point(0, 6, 0);
    p7= Point(6, 6, 0);
    p8= Point(6, 6, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_northest_points_facet(pointsToSort, northestFacetPoints);

    REQUIRE(northestFacetPoints[0] == p5);
    REQUIRE(northestFacetPoints[1] == p1);
    REQUIRE(northestFacetPoints[2] == p2);
    REQUIRE(northestFacetPoints[3] == p8);

    pointsToSort.clear();
    northestFacetPoints.clear();

    //Right hex
    p1= Point(4, 2, 2);
    p2= Point(4, 2, 4);
    p3= Point(4, 4, 4);
    p4= Point(4, 4, 2);
    p5= Point(6, 0, 0);
    p6= Point(6, 6, 0);
    p7= Point(6, 6, 6);
    p8= Point(6, 0, 6);

    pointsToSort.emplace_back(p1);
    pointsToSort.emplace_back(p2);
    pointsToSort.emplace_back(p3);
    pointsToSort.emplace_back(p4);
    pointsToSort.emplace_back(p5);
    pointsToSort.emplace_back(p6);
    pointsToSort.emplace_back(p7);
    pointsToSort.emplace_back(p8);

    pointSorter.sort_northest_points_facet(pointsToSort, northestFacetPoints);

    REQUIRE(northestFacetPoints[0] == p3);
    REQUIRE(northestFacetPoints[1] == p2);
    REQUIRE(northestFacetPoints[2] == p8);
    REQUIRE(northestFacetPoints[3] == p7);

}
