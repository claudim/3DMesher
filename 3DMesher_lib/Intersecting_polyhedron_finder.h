// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Find polyhedra which intersect each other.
// In other words if two polyhedra share portion of space, it must be detected.
//******************************************************************************


#ifndef INC_3DMESHER_INTERSECTING_POLYHEDRON_FINDER_H
#define INC_3DMESHER_INTERSECTING_POLYHEDRON_FINDER_H

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Polygon_mesh_processing/intersection.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

template <class Polyhedron = Polyhedron>
class Intersecting_polyhedron_finder {

public:
    bool do_polyhedra_intersect(const Polyhedron& polyhedron1, const Polyhedron& polyhedron2){
        return CGAL::Polygon_mesh_processing::do_intersect(polyhedron1,polyhedron2);
    }


};


#endif //INC_3DMESHER_INTERSECTING_POLYHEDRON_FINDER_H
