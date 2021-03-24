// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Sort points
//******************************************************************************

#ifndef INC_3DMESHER_POINT_SORTER_H
#define INC_3DMESHER_POINT_SORTER_H

#include <vector>
#include <MyLCC.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/spatial_sort.h>

typedef std::vector<Point>::iterator iterator;
typedef std::vector<Point>::const_iterator const_iterator;
typedef std::vector<iterator>::iterator iterator2;

/**
 * @brief Sort points.
 *
 * @file Point_sorter.h
 * @class Point_sorter
 */
class Point_sorter {

public:
    /**
     * @brief Sort the given points first with respect to the Z axis, then Y-axis and finally x-axis.
     *
     * @param pointsToSort  Points to sort
     */
    void sortByZYX(std::vector<Point> &pointsToSort);

    /**
     * @brief Group point by Z-axis.
     *
     * @param vectorToGroup
     * @param zGroupIterator
     * @param it
     * @param it_end
     */
    void groupByZ(std::vector<Point> &vectorToGroup, std::vector<iterator> &zGroupIterator, iterator it,
                  iterator it_end);

    /**
     * @brief Group point by Y-axis.
     *
     * @param vectorToGroup
     * @param yGroupIterator
     * @param it
     * @param it_end
     */
    void groupByY(std::vector<Point> &vectorToGroup, std::vector<iterator> &yGroupIterator, iterator it,
                  iterator it_end);

    /**
     * @brief Sort the southest points.
     *
     * @param points
     * @param southestFacetPoints
     */
    void sort_southest_points_facet(std::vector<Point> &points, std::vector<Point> &southestFacetPoints);

    /**
     * @brief Sort the northest points.
     *
     * @param points
     * @param northestFacetPoints
     */
    void sort_northest_points_facet(std::vector<Point> &points, std::vector<Point> &northestFacetPoints);
};


#endif //INC_3DMESHER_POINT_SORTER_H
