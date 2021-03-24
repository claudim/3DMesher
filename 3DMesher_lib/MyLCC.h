// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// File with all type definitions.
//******************************************************************************

#ifndef INC_3DMESHER_MYLCC_H
#define INC_3DMESHER_MYLCC_H

#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Simple_cartesian.h>
#include <boost/optional.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

//typedef CGAL::Point_3<K> Isomorphic_point;
typedef boost::optional<CGAL::Point_3<K> > Isomorphic_point;

struct Myitem
{
    template<class Refs>
    struct Dart_wrapper
    {
        typedef CGAL::Cell_attribute_with_point< Refs, Isomorphic_point> Vertex_attribute;
        typedef std::tuple<Vertex_attribute> Attributes;
    };
};


//typedef CGAL::Linear_cell_complex_traits<3, CGAL::Exact_predicates_inexact_constructions_kernel> Traits;
typedef CGAL::Linear_cell_complex_traits<3, K> Traits;
typedef CGAL::Linear_cell_complex_for_combinatorial_map<3,3,Traits,Myitem> LCC_3;
typedef LCC_3::Dart_handle                               Dart_handle;
typedef LCC_3::Dart_const_handle                         Dart_const_handle;
typedef LCC_3::Point                                     Point;
typedef LCC_3::Vector                                    Vector;
typedef LCC_3::FT                                        FT;
typedef LCC_3::Traits Traits;
typedef LCC_3 LCC;




#endif //INC_3DMESHER_MYLCC_H


