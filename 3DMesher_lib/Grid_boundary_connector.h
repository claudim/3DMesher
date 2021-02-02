// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Connect the grid to the polyhedron. Among the grid blocks, there are some that have external point.
// External point is a point outside the polyhedron.
// The objective of this class is to move the external points to points belonging to the polyhedron boundary.
//******************************************************************************


#ifndef INC_3DMESHER_GRID_BOUNDARY_CONNECTOR_H
#define INC_3DMESHER_GRID_BOUNDARY_CONNECTOR_H

#include <MyLCC.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Point Point;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> AABB_Traits;
typedef CGAL::AABB_tree<AABB_Traits> Tree;

namespace CGAL {
    /**
     * @brief Connect the grid to the polyhedron. Among the grid blocks, there are some that have external point.
     * External point is a point outside the polyhedron.
     * The objective of this class is to move the external points to points belonging to the polyhedron boundary.
     *
     * @file Grid_boundary_connector.h
     * @class Grid_boundary_connector
     */
    class Grid_boundary_connector {

    public:
        /**
         * @brief Foreach grid block, move all the external points of the grid block to points belonging to the polyhedron boundary.
         *
         * @param lcc The initial grid/mesh.
         * @param polyhedron The polyhedron to discretize.
         */
        void connect(LCC_3 &lcc, const Polyhedron &polyhedron);
    };

}


#endif //INC_3DMESHER_GRID_BOUNDARY_CONNECTOR_H
