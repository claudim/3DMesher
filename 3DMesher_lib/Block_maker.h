#ifndef INC_3DMESHER_BLOCK_MAKER_H
#define INC_3DMESHER_BLOCK_MAKER_H

#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
typedef LCC_3::Dart_handle Dart_handle;
typedef LCC_3::Point Point;
typedef LCC_3::Traits Traits;
typedef LCC_3::FT FT;

class Block_maker {
public:
    Dart_handle make_block(LCC_3& lcc, const Point& basepoint, FT& lg);
};


#endif //INC_3DMESHER_BLOCK_MAKER_H
