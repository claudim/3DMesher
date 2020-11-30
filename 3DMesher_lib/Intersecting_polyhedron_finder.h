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
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Bbox_3.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;


template <class Polyhedron = Polyhedron, class LCC = CGAL::Linear_cell_complex_for_combinatorial_map<3> >
class Intersecting_polyhedron_finder {

public:
    /**
     * Check if two polyhedra intesect. True if they intersect, false otherwise.
     *
     */
    bool do_polyhedra_intersect(const Polyhedron& polyhedron1, const Polyhedron& polyhedron2){
        return CGAL::Polygon_mesh_processing::do_intersect(polyhedron1,polyhedron2);
    }

    /**
    * Check if the block facets intersect. True if they intersect, false otherwise.
    */
    bool do_polyhedron_facets_intersect(const LCC& lcc, const typename LCC::Dart_handle& block) {

        typedef typename LCC::Dart_handle Dart_handle;
        typedef typename LCC::Dart_const_handle Dart_const_handle;
        typedef typename LCC::Point Point;
        typedef CGAL::Bbox_3 Bbox;

        bool facets_intersect = false;

        for(typename LCC::template One_dart_per_incident_cell_const_range<2,3>::const_iterator facet_it(lcc, block); facet_it.cont(); ++facet_it)
            {
                std::vector<Point> facet_points;
                for(typename LCC::template One_dart_per_incident_cell_const_range<0,2,3>::const_iterator vertex_it(lcc, facet_it); vertex_it.cont(); ++vertex_it)
                {
                    facet_points.emplace_back(lcc.point(vertex_it));
                }

                Bbox facet_bbox = CGAL::bbox_3(facet_points.begin(), facet_points.end());

                Dart_const_handle  opposite_facet = lcc.beta(facet_it, 2, 1, 1, 2);
                std::vector<Point> opposite_facet_points;
                for(typename LCC::template One_dart_per_incident_cell_const_range<0,2,3>::const_iterator vertex_it(lcc, opposite_facet); vertex_it.cont(); ++vertex_it)
                {
                    opposite_facet_points.emplace_back(lcc.point(vertex_it));
                }
                Bbox opposite_facet_bbox = CGAL::bbox_3(opposite_facet_points.begin(), opposite_facet_points.end());

                if(CGAL::do_overlap(facet_bbox, opposite_facet_bbox))
                {
                    facets_intersect = true;
                }
        }
        return facets_intersect;
    }
};


#endif //INC_3DMESHER_INTERSECTING_POLYHEDRON_FINDER_H
