// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Connect the initial mesh to the polyhedron boundary. The initial mesh is an grid where all the blocks are inside the polyhedron.
//******************************************************************************


#ifndef INC_3DMESHER_INITIALMESH_BOUNDARY_CONNECTOR_H
#define INC_3DMESHER_INITIALMESH_BOUNDARY_CONNECTOR_H

#include "MyLCC.h"
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include "PointNormal_boundary_intersectionPoint_finder.h"
#include "External_facet_finder.h"
#include "Point_sorter.h"
#include <boost/optional.hpp>
#include "Intersecting_polyhedron_finder.h"
#include "Vertex_location_finder.h"
#include "Grid_maker.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;


/**
 * @brief Connect the initial mesh to the polyhedron boundary. The initial mesh is a coarse mesh. The initial mesh is an grid where all the blocks are inside the polyhedron.
 *
 * @file InitialMesh_boundary_connector.h
 * @class InitialMesh_boundary_connector
 */
class InitialMesh_boundary_connector {

public:

    /**
     * @brief Connect the initial mesh to the boundary polyhedron.
     * First it is found all the external facets of the initial mesh. Then for each external facet point , it is computed its isomorphic point.
     * An isomorphic point is a point found as the intersection between the normal (of the external facet point) and the polyhedron boundary.
     * When all the external facets points are found, the new hexahedra are created. The latter are added to the mesh.
     * This creates the connection between the initial mesh (composed of blocks inside the polyhedron ) and the boundary polyhedron.
     *
     * @param initial_mesh The initial mesh.
     * @param polyhedron The polyhedron.
     */
    void connect_without_replace(LCC_3 &initial_mesh, const Polyhedron &polyhedron);

    /**
     * @brief Connect the initial mesh to the boundary polyhedron.
     * First it is found all the external facets of the initial mesh. Then for each external facet point , it is computed its isomorphic point.
     * An isomorphic point is a point found as the intersection between the normal (of the external facet point) and the polyhedron boundary.
     * If two isomorphic points of the same external facet are too close, one of the two is moved/removed and replaced by another point
     * which belongs to the boundary polyhedron.
     * When all the external facets points are found, the new hexahedra are created. The latter are added to the mesh.
     * This creates the connection between the initial mesh (composed of blocks inside the polyhedron ) and the boundary polyhedron.
     *
     * @param initial_mesh The initial mesh.
     * @param polyhedron The polyhedron.
     */
    void connect(LCC_3 &initial_mesh, const Polyhedron &polyhedron);

    /**
     * @brief Check if it has been computated the isomorphic point for the point passed by the dart.
     *
     * @param lcc The mesh (Usually is a coarse mesh).
     * @param vertex_handle The dart to the point to check.
     * @return true if it has already been computed the isomorphic point, false otherwise.
     */
    bool is_the_isomorphic_point_computed(LCC_3 &lcc, Dart_handle &vertex_handle);

    /**
     * @brief If two isomorphic points of the same external facet are too close, one of the two is moved/removed and replaced by another point
     * which belongs to the boundary polyhedron. It is valid only in L case that is the case where 3 blocks form a L.
     *
     * @param hexahedronVertexPoints Vector of points and their isomorphic points.
     * @param polyhedron The polyhedron.
     * @param distance The distance below which if two segments are not parallel, an isomorphic point is moved.
     */
    void replace(std::vector<Point> &hexahedronVertexPoints, const Polyhedron &polyhedron, const double distance);


    /**
     * @brief If two isomorphic points of the same external facet are too close, one of the two is moved/removed and replaced by another point
     * which belongs to the boundary polyhedron. It is valid only in L case that is the case where 3 blocks form a L and U case.
     *
     * @param initial_mesh The initial mesh.
     * @param facet The external facet under test
     * @param polyhedron The polyhedron.
     * @param distance The distance below which if two segments are not parallel, an isomorphic point is moved.
     */
    void replace(LCC_3 &initial_mesh, Dart_handle facet, const Polyhedron &polyhedron, const double distance);

    /**
     * @brief If two isomorphic points of the same external facet are too close, one of the two is moved/removed and replaced by another point
     * which belongs to the boundary polyhedron. It is valid only in L case that is the case where 3 blocks form a L and U case.
     *
     * @param initial_mesh The initial mesh.
     * @param facet The external facet under test.
     * @param polyhedron The polyhedron.
     * @param distance The distance below which if two segments are not parallel, an isomorphic point is moved.
     */
    void replace2(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance);

    void connect3(LCC_3 &lcc, const Polyhedron &polyhedron);

    /**
     * @brief If two isomorphic points of the same external facet are too close, one of the two is moved/removed and replaced by another point
     * which belongs to the boundary polyhedron. It is valid only in L case that is the case where 3 blocks form a L.
     *
     * @param lcc The initial mesh.
     * @param facet The external facet under test.
     * @param polyhedron The polyhedron.
     * @param distance The distance below which if two segments are not parallel, an isomorphic point is moved.
     * @return true if the replace is done, false otherwise.
     */
    bool replace_L_facets(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance);

    /**
     * @brief If two isomorphic points of the same external facet are too close, one of the two is moved/removed and replaced by another point
     * which belongs to the boundary polyhedron. It is valid only in U case that is the case where blocks form a U.
     *
     * @param lcc The initial mesh.
     * @param facet The external facet under test.
     * @param polyhedron The polyhedron.
     * @param distance The distance below which if two segments are not parallel, an isomorphic point is moved.
     * @return true if the replace is done, false otherwise.
     */
    void replace_U_facets(LCC_3& lcc, Dart_handle facet, const Polyhedron& polyhedron, const double distance);

    /**
     * @brief Another way to connect the initial mesh to the polyhedron boundary.
     *
     * @param lcc The initial mesh.
     * @param polyhedron The polyhedron.
     */
    void connect4(LCC_3 &lcc, const Polyhedron &polyhedron);
};

#endif //INC_3DMESHER_INITIALMESH_BOUNDARY_CONNECTOR_H
