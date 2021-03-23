// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Find the vertex position. The vertex could be inside, on_boundary, outside the boundary polyhedron.
//******************************************************************************

#ifndef INC_3DMESHER_VERTEX_LOCATION_FINDER_H
#define INC_3DMESHER_VERTEX_LOCATION_FINDER_H

#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/AABB_tree.h>
#include <CGAL/AABB_traits.h>
#include <CGAL/AABB_face_graph_triangle_primitive.h>
#include <CGAL/Side_of_triangle_mesh.h>
#include <MyLCC.h>


typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Side_of_triangle_mesh<Polyhedron, K> Point_inside;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> AABB_Traits;
typedef CGAL::AABB_tree<AABB_Traits> Tree;

/**
 * @brief Class responsible to find the vertex position.
 *
 * @file Vertex_location_finder.h
 * @class Vertex_location_finder
 * @namespace CGAL
 */
namespace CGAL {
    class Vertex_location_finder {
    protected:
        Polyhedron polyhedron;
        Point_inside inside;
        Tree AABB_tree;
        int point_internal_check_tolerance = 0; // distance_tolerance between the point_to_check and the boundary surface

    public:

        /**
         * @brief Constructor.
         *
         * @param polyhedron The polyhedron
         */
        Vertex_location_finder(const Polyhedron &polyhedron)
                : inside(polyhedron), AABB_tree(faces(polyhedron).first, faces(polyhedron).second, polyhedron) {
            this->polyhedron = polyhedron;
            AABB_tree.accelerate_distance_queries();
        }

        /**
         * @brief Check if a point is inside the polyhedron.
         *
         * @param pointToBeCheck The point to check.
         * @return true if the point is inside, false otherwise.
         */
        bool is_point_inside_polyhedron(const Point &pointToBeCheck);

        /**
         * @brief Check if a point on the polyhedron boundary. If a tolerance is > 0, an external point which
         * is less than the tolerance can be considered on the boundary.
         *
         * @param pointToBeCheck The point to check.
         * @return true if the point is on boundary, false otherwise.
         */
        bool is_point_onBoundary_polyhedron(const Point &pointToBeCheck) const;

        /**
         * @brief Check if a point is external to the polyhedron.
         *
         * @param pointToBeCheck Point to check.
         * @return true if the point is external, false otherwise.
         */
        bool is_point_external_polyhedron(const Point &pointToBeCheck);


        /**
         * @brief Find all the external points of the mesh.
         * If a tolerance> 0 is passed, some external points closer than the distance from the boundary are considered on the boundary.
         *
         * @param lcc The mesh.
         * @param number_of_external_vertices Number of external points to fill.
         * @param tolerance The tolerance.
         */
        void findExternalVertices(const LCC_3 &lcc, int &number_of_external_vertices, const double &tolerance);

        /**
         * @brief Get the AABB tree.
         */
        const Tree &getAabbTree();


        /**
         * @brief Check if a point is closer than distance.
         *
         * @param point Point to check.
         * @param distance The distance from the boundary.
         * @return true if is too close, false otherwise.
         */
       bool is_point_too_close_to_the_boundary(const Point &point, const FT &distance);
    };

}

#endif //INC_3DMESHER_VERTEX_LOCATION_FINDER_H
