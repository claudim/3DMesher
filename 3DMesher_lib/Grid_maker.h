#ifndef INC_3DMESHER_GRID_MAKER_H
#define INC_3DMESHER_GRID_MAKER_H

#include "OFF_Reader.h"
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <MyLCC.h>

#include <CGAL/Polygon_mesh_processing/bbox.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//typedef LCC_3::Point Point;
typedef CGAL::Bbox_3 Bbox;
//typedef LCC_3::Traits Traits;
//typedef LCC_3::FT FT;

class Grid_maker{
private:
    double x_dimension;
    double y_dimension;
    double z_dimension;
    //int resolution = 8;
    int resolution = 24;

    double grid_dimension;

private:
    Bbox grid_box;
    const int NUMBER_OF_DARTS_PER_CUBE = 24;


public:
    Grid_maker();

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

    double getGridDimension() const {
        return grid_dimension;
    }

    Bbox get_bounding_box(){
        return grid_box;
    }

    Point get_grid_centroid();

    void wrap_the_object(const Polyhedron &polyhedron);

    void set_resolution(int aResolution){
        resolution = aResolution;
    }

    LCC_3 turn_box_into_grid();

};

#endif //INC_3DMESHER_GRID_MAKER_H
