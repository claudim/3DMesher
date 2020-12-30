#ifndef INC_3DMESHER_BLOCK_REFINER_H
#define INC_3DMESHER_BLOCK_REFINER_H

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
//#include <CGAL/Cell_const_iterators.h>
#include <CGAL/squared_distance_3.h>
#include "Block_maker.h"
#include "External_facet_finder.h"


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

class Block_refiner {

public:

    void refineBlock(LCC_3 &lcc, Dart_handle &blockToRefine, const std::vector<Point> &featuresPoints,
                     double distance);

    //template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits, typename Point, typename Point, typename FT>
    void refineBlocks(LCC_3 &lcc, const std::vector<Point> &points, FT distance);
};


#endif //INC_3DMESHER_BLOCK_REFINER_H
