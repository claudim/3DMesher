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

#include "MyLCC.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Polygon_mesh_processing/intersection.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Bbox_3.h>
#include <CGAL/Triangle_3.h>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

template <class Polyhedron = Polyhedron, class LCC = LCC_3 >
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
    bool do_polyhedron_facets_intersect(const LCC& lcc, const typename LCC::Dart_handle& block, std::vector<typename LCC::Dart_const_handle>& intersecting_facets) {

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
                    intersecting_facets.emplace_back(facet_it);
                    intersecting_facets.emplace_back(opposite_facet);
                }
        }
        return facets_intersect;
    }


    bool do_polyhedron_facets_intersect(LCC& lcc, const typename LCC::Dart_handle& block, std::vector<typename LCC::Dart_handle>& intersecting_facets) {

        typedef typename LCC::Dart_handle Dart_handle;
        typedef typename LCC::Point Point;
        typedef CGAL::Bbox_3 Bbox;

        bool facets_intersect = false;

        for(typename LCC::template One_dart_per_incident_cell_range<2,3>::iterator facet_it(lcc, block); facet_it.cont(); ++facet_it)
        {
            std::vector<Point> facet_points;
            for(typename LCC::template One_dart_per_incident_cell_range<0,2,3>::iterator vertex_it(lcc, facet_it); vertex_it.cont(); ++vertex_it)
            {
                facet_points.emplace_back(lcc.point(vertex_it));
            }

            Bbox facet_bbox = CGAL::bbox_3(facet_points.begin(), facet_points.end());

            Dart_handle  opposite_facet = lcc.beta(facet_it, 2, 1, 1, 2);
            std::vector<Point> opposite_facet_points;
            for(typename LCC::template One_dart_per_incident_cell_range<0,2,3>::iterator vertex_it(lcc, opposite_facet); vertex_it.cont(); ++vertex_it)
            {
                opposite_facet_points.emplace_back(lcc.point(vertex_it));
            }
            Bbox opposite_facet_bbox = CGAL::bbox_3(opposite_facet_points.begin(), opposite_facet_points.end());

            if(CGAL::do_overlap(facet_bbox, opposite_facet_bbox))
            {
                facets_intersect = true;
                if(std::find(intersecting_facets.begin(), intersecting_facets.end(), facet_it) == intersecting_facets.end())
                {
                    intersecting_facets.emplace_back(facet_it);
                }
                if(std::find(intersecting_facets.begin(), intersecting_facets.end(),opposite_facet) == intersecting_facets.end()) {
                    intersecting_facets.emplace_back(opposite_facet);
                }

            }
        }
        return facets_intersect;
    }

    bool do_polyhedron_facets_intersect(LCC& lcc, const typename LCC::Dart_handle& block){
        typedef typename LCC::Dart_handle Dart_handle;
        typedef typename LCC::Point Point;
        typedef K::Triangle_3 Triangle;
        typedef K::Intersect_3 Intersect;

        bool facets_intersect = false;

        for(typename LCC::template One_dart_per_incident_cell_range<2,3>::iterator facet_it(lcc, block); facet_it.cont(); ++facet_it)
        {
            std::vector<Point> facet_points;
            for(typename LCC::template One_dart_per_incident_cell_range<0,2,3>::iterator vertex_it(lcc, facet_it); vertex_it.cont(); ++vertex_it)
            {
                facet_points.emplace_back(lcc.point(vertex_it));
            }

            Triangle triangle1_facet(facet_points.at(0),facet_points.at(1),facet_points.at(2));
            Triangle triangle2_facet(facet_points.at(0),facet_points.at(3),facet_points.at(2));
            std::vector<Triangle> facet;
            facet.emplace_back(triangle1_facet);
            facet.emplace_back(triangle2_facet);

            Dart_handle  opposite_facet_it = lcc.beta(facet_it, 2, 1, 1, 2);
            std::vector<Point> opposite_facet_points;
            for(typename LCC::template One_dart_per_incident_cell_range<0,2,3>::iterator vertex_it(lcc, opposite_facet_it); vertex_it.cont(); ++vertex_it)
            {
                opposite_facet_points.emplace_back(lcc.point(vertex_it));
            }

            Triangle triangle1_oppositeFacet(opposite_facet_points.at(0),opposite_facet_points.at(1),opposite_facet_points.at(2));
            Triangle triangle2_oppositeFacet(opposite_facet_points.at(0),opposite_facet_points.at(3),opposite_facet_points.at(2));
            std::vector<Triangle> opposite_facet;
            opposite_facet.emplace_back(triangle1_oppositeFacet);
            opposite_facet.emplace_back(triangle2_oppositeFacet);

            // Is there intersection between the 2 opposite facets?
            for(Triangle facet_t: facet)
            {
                for(Triangle oppositeFacet_t: opposite_facet){
                    CGAL::cpp11::result_of<Intersect(Triangle, Triangle)>::type
                            result = intersection(facet_t,oppositeFacet_t);
                    if (result) {
                        facets_intersect = true;
//                        if (const K::Segment_3* s = boost::get<K::Segment_3>(&*result)) {
//                            std::cout << *s << std::endl;
//                        }
//                        if(const Point* p = boost::get<Point>(&*result)){
//                            std::cout << *p << std::endl;
//                        }
//                        if(const Triangle* t = boost::get<Triangle >(&*result)){
//                            std::cout << *t << std::endl;
//                        }
//                        if(const std::vector< Point >* v = boost::get<std::vector<Point> >(&*result)){
//                            std::cout << *v << std::endl;
//                        }
                    }
//                    else{
//                        std::cout << "no intersection" << std::endl;
//                    }
                }
            }
        }

        return facets_intersect;
    }
};


#endif //INC_3DMESHER_INTERSECTING_POLYHEDRON_FINDER_H
