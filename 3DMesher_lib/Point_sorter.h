#ifndef INC_3DMESHER_POINT_SORTER_H
#define INC_3DMESHER_POINT_SORTER_H

#include <vector>

#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/spatial_sort.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Dart_handle Dart_handle;
typedef LCC_3::Dart_const_handle Dart_const_handle;
typedef LCC_3::Point Point;
typedef LCC_3::Traits Traits;
typedef LCC_3::FT FT;
typedef std::vector<Point>::iterator iterator;
typedef std::vector<Point>::const_iterator const_iterator;
typedef std::vector<iterator>::iterator iterator2;



//struct MyLessX {
//    bool operator()(const Point& p, const Point& q) const
//    {
//        return p.x() < q.x();
//    }
//};
//
//struct MyLessY {
//    bool operator()(const Point& p, const Point& q) const
//    {
//        return p.y() < q.y();
//    }
//};
//
//struct MyLessZ {
//    bool operator()(const Point& p, const Point& q) const
//    {
//        return p.z() < q.z();
//    }
//};
//struct MySpatialSortingTraits {
//    typedef MyLessX Less_x_3;
//    typedef MyLessY Less_y_3;
//    typedef MyLessZ Less_z_3;
//    Less_x_3 less_x_3_object() const
//    {
//        return Less_x_3();
//    }
//    Less_y_3 less_y_3_object() const
//    {
//        return Less_y_3();
//    }
//    Less_z_3 less_z_3_object() const
//    {
//        return Less_z_3();
//    }
//};

class Point_sorter {

public:
   // template<typename Point>
    void clockwiseSort(std::vector<Point> &pointsToSort);

    void sortByZ(iterator vector_it, iterator vector_end_it);
    //template<typename Point, typename Point>
    void quicksort(iterator vector_it, iterator vector_end_it);

    void quicksortX(iterator vector_it, iterator vector_end_it);
    void quicksortY(iterator vector_it, iterator vector_end_it);
    void quicksortZ(iterator vector_it, iterator vector_end_it);
    //void quicksort(iterator vector_it, iterator vector_end_it, iterator (*fun)(iterator,iterator));
    //template<typename Point, typename Point>
    iterator partition(iterator vector_it, iterator vector_end_it);
    iterator zPartition(iterator vector_it, iterator vector_end_it);
    iterator yPartition(iterator vector_it, iterator vector_end_it);
    iterator xPartition(iterator vector_it, iterator vector_end_it);

    //template<typename Point, typename Point>
    void groupByZ(std::vector<Point> &vectorToGroup, std::vector<iterator> &zGroupIterator, iterator it,
                  iterator it_end);

    //template<typename Point, typename Point>
    void groupByY(std::vector<Point> &vectorToGroup, std::vector<iterator> &yGroupIterator, iterator it,
                  iterator it_end);
};


#endif //INC_3DMESHER_POINT_SORTER_H
