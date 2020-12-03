//
// Created by Claudia Di Marco on 01/11/2020.
//

#ifndef INC_3DMESHER_WRITER_H
#define INC_3DMESHER_WRITER_H

#include "MyLCC.h"
#include <ostream>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//typedef LCC_3::Point Point;
typedef CGAL::Bbox_3 Bbox;
//typedef LCC_3::Traits Traits;
//typedef LCC_3::FT FT;


class Writer {

public:
    void output_to_medit(std::ostream& os, const LCC_3& lcc);
    int get();

    LCC_3::size_type number_of_facets_in_lcc(const LCC_3 &lcc);

    LCC_3::size_type number_of_cells_in_lcc(const LCC_3 &lcc);

};


#endif //INC_3DMESHER_WRITER_H
