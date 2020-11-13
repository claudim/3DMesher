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

class Point_sorter {

public:
   // template<typename Point>
    void sortByZYX(std::vector<Point> &pointsToSort);

    //template<typename Point, typename Point>
    void groupByZ(std::vector<Point> &vectorToGroup, std::vector<iterator> &zGroupIterator, iterator it,
                  iterator it_end);

    //template<typename Point, typename Point>
    void groupByY(std::vector<Point> &vectorToGroup, std::vector<iterator> &yGroupIterator, iterator it,
                  iterator it_end);

    // template<typename Point, typename Point>
    void sort_southest_points_facet(std::vector<Point> &points, std::vector<Point> &southestFacetPoints);

    //template<typename Point, typename Point, typename Point, typename Point>
    void sort_northest_points_facet(std::vector<Point> &points, std::vector<Point> &northestFacetPoints);
};


#endif //INC_3DMESHER_POINT_SORTER_H
