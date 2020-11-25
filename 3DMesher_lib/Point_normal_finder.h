// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Compute the normal of a 0-cell.
//******************************************************************************


#ifndef INC_3DMESHER_POINT_NORMAL_FINDER_H
#define INC_3DMESHER_POINT_NORMAL_FINDER_H

#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include "External_facet_finder.h"

typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;

/**
 * @brief Compute the normal of a 0-cell point.
 *
 * @file Point_normal_finder.h
 * @class Point_normal_finder
 * @tparam The Linear Cell Complex where store the mesh
 */
template <class LCC = LCC_3>
class Point_normal_finder {


public:
    /**
     * @brief Compute the normal of a 0-cell point.
     *
     * @param lcc The lcc where store the mesh.
     * @param point_of_0_cell Point associated to a 0-cell.
     * @return The normal vector of the point.
     */
    typename LCC::Vector compute(LCC &lcc, const typename LCC::Point &point_of_0_cell){
        typedef typename LCC::Vector Vector;
        typedef typename LCC::Dart_handle Dart_handle;
        //typedef typename LCC::template LCC::Dart_of_orbit_const_range<1>::iterator iterator;

        Vector normal(CGAL::NULL_VECTOR);
        std::vector<Dart_handle> incidentFacets;
        unsigned int nb = 0;

        External_facet_finder externalFacetFinder;
        const std::vector<Dart_handle> externalFacets = externalFacetFinder.findFacets(lcc);

        for(Dart_handle facet: externalFacets){
//            for(typename LCC::template Dart_of_orbit_const_range<1>::
//                    iterator vertexIt = lcc.darts_of_orbit<1>(facet).begin(),
//                        vertexItEnd = lcc.darts_of_orbit<1>(facet).end(); vertexIt != vertexItEnd; ++vertexIt) {
                for(typename LCC::template  One_dart_per_incident_cell_range<0,2>::
                iterator vertexIt(lcc,facet); vertexIt.cont(); ++vertexIt) {
                if(lcc.point(vertexIt) == point_of_0_cell){
                    incidentFacets.emplace_back(facet);
                }
            }
        }

        for(Dart_handle facet: incidentFacets)
        {
                normal = typename LCC::Traits::Construct_sum_of_vectors()
                        (normal, CGAL::compute_normal_of_cell_2(lcc, facet));
                ++nb;
        }
        if ( nb<2 ) return normal;
        return (typename LCC::Traits::Construct_scaled_vector()(normal, 1.0/nb));
    }
};


#endif //INC_3DMESHER_POINT_NORMAL_FINDER_H
