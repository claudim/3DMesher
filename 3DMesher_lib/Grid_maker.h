// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Generate the grid.
//******************************************************************************

#ifndef INC_3DMESHER_GRID_MAKER_H
#define INC_3DMESHER_GRID_MAKER_H

#include "OFF_Reader.h"
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <MyLCC.h>

#include <CGAL/Polygon_mesh_processing/bbox.h>

typedef CGAL::Bbox_3 Bbox;

/**
* @brief Generate the grid.
*
* @file Grid_maker.h
* @class Grid_maker
*/
class Grid_maker{
private:
    double x_dimension;
    double y_dimension;
    double z_dimension;
    double resolution = 8;

    double grid_dimension;

    Bbox grid_box;
    const int NUMBER_OF_DARTS_PER_CUBE = 24;


public:
    Grid_maker();

    /**
     * @brief Generate a grid that contains the object entirely.
     *
     * @param polyhedron The object described by a polyhedron.
     * @return The grid.
     */
    LCC_3 make(const Polyhedron& polyhedron);

    void set_x_dimension(double xDimension){
        x_dimension = xDimension;
    }

    double get_x_dimension() {
        return x_dimension;
    }

    double get_y_dimension() {
        return y_dimension;
    }

    double get_z_dimension() {
        return z_dimension;
    }

    /**
     * @brief Compute and get the edge dimension of the grid.
     *
     * @param polyhedron The poluhedron
     * @return The edge dimension
     */
    double getGridDimension(const Polyhedron &polyhedron){
            const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);

            double delta_x = polyhedron_bbox3.xmax() - polyhedron_bbox3.xmin();
            double delta_y = polyhedron_bbox3.ymax() - polyhedron_bbox3.ymin();
            double delta_z = polyhedron_bbox3.zmax() - polyhedron_bbox3.zmin();

            grid_dimension =  std::min(std::min(delta_y, delta_z), delta_x) / resolution;
        return grid_dimension;
    }

    void setGridDimension(double gridDimension);

    double getGridDimension(){
        return grid_dimension;
    }

    Bbox get_bounding_box(){
        return grid_box;
    }

    Point get_grid_centroid();

    /**
     * @brief Find the Grid Box that contains the polyhedron.
     *
     * @param polyhedron The polyhedron
     */
    void wrap_the_object(const Polyhedron &polyhedron);

    /**
     * @brief Set the resolution
     *
     * @param aResolution The resolution to set.
     */
    void set_resolution(double aResolution){
        resolution = aResolution;
    }

    /**
     * @brief Starting from the grid box, generate the grid.
     */
    LCC_3 turn_box_into_grid();

};

#endif //INC_3DMESHER_GRID_MAKER_H
