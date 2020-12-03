#ifndef INC_3DMESHER_EXTERNAL_FACET_FINDER_H
#define INC_3DMESHER_EXTERNAL_FACET_FINDER_H

#include <iostream>
#include <vector>

#include <MyLCC.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//typedef LCC_3::Dart_const_handle Dart_const_handle;
//typedef LCC_3::Point Point;
//typedef LCC_3::Traits Traits;
//typedef LCC_3::FT FT;

class External_facet_finder {

public:
    //template<typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
    std::vector<Dart_const_handle> find(const LCC_3 & lcc);

    std::vector<Dart_handle> findFacets(LCC_3 & lcc);

    //template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits, typename allocator, typename Linear_cell_complex_traits>
    bool is_near_cell_facet_null(const LCC_3 &lcc, const Dart_const_handle &near_cell_facet_dart_handle) const;

    bool is_near_cell_facet_null(const LCC_3 &lcc, const Dart_handle &near_cell_facet_dart_handle) const;

    std::vector<Dart_handle> find(LCC_3 & lcc, Dart_handle block);
    };





#endif //INC_3DMESHER_EXTERNAL_FACET_FINDER_H
