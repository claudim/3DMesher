#ifndef INC_3DMESHER_HEXAHEDRON_FITTER_H
#define INC_3DMESHER_HEXAHEDRON_FITTER_H


#include "MyLCC.h"
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include "Vertex_location_finder.h"
#include "OnBoundary_block_remover.h"
#include "External_facet_finder.h"
#include "Point_sorter.h"
#include <CGAL/Kernel/global_functions.h>
#include <CGAL/squared_distance_3.h>
#include <CGAL/Segment_3.h>
#include "PointNormal_boundary_intersectionPoint_finder.h"
#include "Point_sorter.h"


//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC;
//typedef LCC::Dart_handle Dart_handle;
//typedef LCC::Point Point;
//typedef LCC::Vector Vector;

class Hexahedron_fitter {
    //todo: rendere vertexLocationFinder un attributo dell'oggetto
public:

    void fix3(LCC& lcc, Dart_handle& block_to_fix, const Polyhedron& polyhedron){
        Vertex_location_finder vertexLocationFinder(polyhedron);
        std::vector<Dart_handle> normals;
        for (LCC::One_dart_per_incident_cell_range<1, 3, 3>::iterator edge_it = lcc.one_dart_per_incident_cell<1, 3, 3>(
                block_to_fix).begin(),
                     edge_end_it = lcc.one_dart_per_incident_cell<1, 3, 3>(block_to_fix).end();
             edge_it != edge_end_it; ++edge_it) {
            Point p1 = lcc.point(edge_it);
            Point p2 = lcc.point(lcc.opposite(edge_it));
            if (vertexLocationFinder.is_point_onBoundary_polyhedron(p1) &&
                !vertexLocationFinder.is_point_onBoundary_polyhedron(p2)) {
                Dart_handle e = lcc.opposite(edge_it);
                normals.emplace_back(e);
            }
            if (!vertexLocationFinder.is_point_onBoundary_polyhedron(p1) &&
                vertexLocationFinder.is_point_onBoundary_polyhedron(p2)) {
                normals.emplace_back(edge_it);
//
            }
        }


    }

    void fix2(LCC& lcc, Dart_handle& block_to_fix, const Polyhedron& polyhedron){
        std::vector<Point> onBoundary_points;
        std::vector<Point> points_on_map;
        std::vector<Dart_handle> darts;
        std::map<Point, Dart_handle> points_darts_map;

        Vertex_location_finder vertexLocationFinder(polyhedron);
        for (LCC::One_dart_per_incident_cell_range<0, 3, 3>::iterator v_it = lcc.one_dart_per_incident_cell<0, 3, 3>(
                block_to_fix).begin(),
                     v_end_it = lcc.one_dart_per_incident_cell<0, 3, 3>(block_to_fix).end(); v_it != v_end_it; ++v_it) {
            Point p = lcc.point(v_it);
            if(vertexLocationFinder.is_point_onBoundary_polyhedron(p))
            {
                onBoundary_points.emplace_back(p);
                points_on_map.emplace_back(p);
                points_darts_map[p] = v_it;
                darts.emplace_back(v_it);
            }
        }
//        for(auto p: onBoundary_points){
//            std::cout<<"punto non ord "<<p<< std::endl;
//        }
        std::vector<Point> onBoundary_sorted_points;
        Point_sorter pointSorter;
        if(onBoundary_points.size()==4) {
            std::cout<<"ci sono 4 onBoundary point "<< std::endl;
            pointSorter.sort_northest_points_facet(onBoundary_points, onBoundary_sorted_points);

//        for(auto coppia: points_darts_map){
//            std::cout<<"punto "<<coppia.first<< std::endl;
//        }
            std::vector<Point> sorted_points_on_map;
            pointSorter.sort_southest_points_facet(points_on_map, sorted_points_on_map);


            lcc.point(darts.at(0)) = onBoundary_sorted_points.at(0);
            lcc.point(darts.at(1)) = onBoundary_sorted_points.at(1);
            lcc.point(darts.at(2)) = onBoundary_sorted_points.at(2);
            lcc.point(darts.at(3)) = onBoundary_sorted_points.at(3);

//            lcc.point(darts.at(2)) = onBoundary_sorted_points.at(0);
//            lcc.point(darts.at(1)) = onBoundary_sorted_points.at(2);
//            lcc.point(darts.at(0)) = onBoundary_sorted_points.at(1);
//            lcc.point(darts.at(3)) = onBoundary_sorted_points.at(3);

//        for(int i=0; i<4; i++)
//        {
//            lcc.point(darts.at(i)) = onBoundary_sorted_points.at(i);
//            std::cout<<"punto ordinato "<< onBoundary_sorted_points.at(i)<< std::endl;
//        }
        }
    }

    void fix( LCC& lcc, Dart_handle& block_to_fix, std::vector<Dart_handle> intersecting_facets, const Polyhedron& polyhedron) {
        std::vector<Dart_handle> normals;
        std::vector<std::vector<Point> > points_to_compute_dihedral_angles;

        Vertex_location_finder vertexLocationFinder(polyhedron);
        //find edges parallel to normals
        for (Dart_handle facet: intersecting_facets) {
            for (LCC::One_dart_per_incident_cell_range<1, 2, 3>::iterator edge_it = lcc.one_dart_per_incident_cell<1, 2, 3>(
                    facet).begin(),
                         edge_end_it = lcc.one_dart_per_incident_cell<1, 2, 3>(facet).end();
                 edge_it != edge_end_it; ++edge_it) {
                Point p1 = lcc.point(edge_it);
                Point p2 = lcc.point(lcc.opposite(edge_it));
                if (vertexLocationFinder.is_point_onBoundary_polyhedron(p1) &&
                    !vertexLocationFinder.is_point_onBoundary_polyhedron(p2)) {
                    Dart_handle e = lcc.opposite(edge_it);
                    normals.emplace_back(e);
//                    std::vector<Point> points;
//                    //add p2 and 3 incident vertices
//                    points.emplace_back(lcc.point(lcc.next(lcc.next(edge_it))));
//                    points.emplace_back(p2);
//                    points.emplace_back(p1);
//                    points.emplace_back(lcc.point(lcc.previous(e)));
//
//                    points_to_compute_dihedral_angles.emplace_back(points);
//                    for(Point p: points)
//                    {
//                        std::cout<<p<<std::endl;
//                    }
                }
                if (!vertexLocationFinder.is_point_onBoundary_polyhedron(p1) &&
                    vertexLocationFinder.is_point_onBoundary_polyhedron(p2)) {
                    normals.emplace_back(edge_it);
//                    std::vector<Point> points;
//                    //add p1 and 3 incident vertices
//                    points.emplace_back(lcc.point(lcc.previous(edge_it)));
//                    points.emplace_back(p1);
//                    points.emplace_back(lcc.point(lcc.next(edge_it)));
//                    points.emplace_back(lcc.point(lcc.previous(lcc.previous(lcc.opposite(edge_it)))));
//                    points_to_compute_dihedral_angles.emplace_back(points);
//                    for(Point p: points)
//                    {
//                        std::cout<<p<<std::endl;
//                    }
                }
            }
        }
        std::vector<Dart_handle> minEdges;
        Dart_handle edgeMin1;
        Dart_handle edgeMin2;
        K::FT minimum_squared_distance;
        for (int i = 0; i < 2; i++) {
            Dart_handle edge1 = normals.at(i);
            Dart_handle edge2 = normals.at(2);
            Dart_handle edge3 = normals.at(3);
            //CGAL::Segment_3<K> segment1 = CGAL::Segment_3<K>(lcc.point(edge1), lcc.point(lcc.opposite(edge1)));
            CGAL::Segment_3<K> segment1(lcc.point(edge1), lcc.point(lcc.opposite(edge1)));

            CGAL::Segment_3<K> segment2(lcc.point(edge2), lcc.point(lcc.opposite(edge2)));
            CGAL::Segment_3<K> segment3(lcc.point(edge3), lcc.point(lcc.opposite(edge3)));
            K::FT squared_distance12 = CGAL::squared_distance(segment1, segment2);
            K::FT squared_distance13 = CGAL::squared_distance(segment1, segment3);
            if (i == 0) {
                minimum_squared_distance = std::min(squared_distance12, squared_distance13);
            } else {// i =1
                minimum_squared_distance = std::min(minimum_squared_distance,
                                                    std::min(squared_distance12, squared_distance13));
            }
            if (minimum_squared_distance == squared_distance12) {
                edgeMin1 = normals.at(i);
                edgeMin2 = normals.at(2);
            }
            if (minimum_squared_distance == squared_distance13) {
                edgeMin1 = normals.at(i);
                edgeMin2 = normals.at(3);
            }
        }

        minEdges.emplace_back(edgeMin1);
        minEdges.emplace_back(edgeMin2);
        std::cout << lcc.point(edgeMin1) << " e " << lcc.point(lcc.opposite(edgeMin1)) << std::endl;
        std::cout << lcc.point(edgeMin2) << " e " << lcc.point(lcc.opposite(edgeMin2)) << std::endl;

        //for the closest edges, must be found dihedral angles to detect the point to recompute intersection (it is always the third)
        Point point_to_recompute_intersection;
        for (Dart_handle edge: minEdges) {
            Point p1 = lcc.point(edge);
            Point p2 = lcc.point(lcc.opposite(edge));
            if (vertexLocationFinder.is_point_onBoundary_polyhedron(p1) &&
                !vertexLocationFinder.is_point_onBoundary_polyhedron(p2)) {
                Dart_handle e = lcc.opposite(edge);
                std::vector<Point> points;
                //add p2 and 3 incident vertices
                points.emplace_back(lcc.point(lcc.next(lcc.next(edge))));
                points.emplace_back(p2);
                points.emplace_back(p1);
                points.emplace_back(lcc.point(lcc.previous(e)));
                points_to_compute_dihedral_angles.emplace_back(points);
                for (Point p: points) {
                    std::cout << p << std::endl;
                }
            }
            if (!vertexLocationFinder.is_point_onBoundary_polyhedron(p1) &&
                vertexLocationFinder.is_point_onBoundary_polyhedron(p2)) {
                std::vector<Point> points;
                //add p1 and 3 incident vertices
                points.emplace_back(lcc.point(lcc.previous(edge)));
                points.emplace_back(p1);
                points.emplace_back(lcc.point(lcc.next(edge)));
                points.emplace_back(lcc.point(lcc.previous(lcc.previous(lcc.opposite(edge)))));
                points_to_compute_dihedral_angles.emplace_back(points);
                for (Point p: points) {
                    std::cout << p << std::endl;
                }
            }

        }
        Point point_l;
        for (std::vector<Point> points :points_to_compute_dihedral_angles) {
            K::FT dihedral_angle = CGAL::approximate_dihedral_angle(points.at(0), points.at(1), points.at(2),
                                                                    points.at(3));
            if (dihedral_angle == 45 || dihedral_angle == -45) {
                //detect the point to recompute intersection: it is always the third
                point_to_recompute_intersection = points.at(3);
                point_l = points.at(1);
                if( point_to_recompute_intersection == lcc.point(minEdges.at(0)))
                {
                    Point support = lcc.point(lcc.opposite(minEdges.at(0)));
                    lcc.point(lcc.opposite(minEdges.at(0))) = lcc.point(lcc.opposite(minEdges.at(1)));
                    lcc.point(lcc.opposite(minEdges.at(1))) = support;
                }
                else{
                    Point support = lcc.point(lcc.opposite(minEdges.at(1)));
                    lcc.point(lcc.opposite(minEdges.at(1))) = lcc.point(lcc.opposite(minEdges.at(0)));
                    lcc.point(lcc.opposite(minEdges.at(0))) = support;
                }
            }
            std::cout << dihedral_angle << std::endl;
        }
//
//        std::cout << "Punto da ricalcolare "<<point_to_recompute_intersection  << std::endl;
//        std::cout << "Punto L "<<point_l << std::endl;
//
//        Dart_handle vertex_handle;
//        Dart_handle vertex_handle_l;
//        for (LCC::One_dart_per_incident_cell_range<0, 3, 3>::iterator v_it = lcc.one_dart_per_incident_cell<0, 3, 3>(
//                block_to_fix).begin(),
//                     v_end_it = lcc.one_dart_per_incident_cell<0, 3, 3>(block_to_fix).end(); v_it != v_end_it; ++v_it) {
//            if (lcc.point(v_it) == point_to_recompute_intersection) {
//                vertex_handle = v_it;
//            }
//            if (lcc.point(v_it) == point_l) {
//                vertex_handle_l = v_it;
//            }
//        }
//
//        // compute the new normal
//        //LCC::Vector v(CGAL::NULL_VECTOR);
//        LCC::Vector v1, v2, v3, new_normal;
////        v1 = Vector(lcc.point(vertex_handle), lcc.point(lcc.opposite(vertex_handle)));
////        v2 = Vector(lcc.point(vertex_handle_l), lcc.point(lcc.opposite(vertex_handle_l)));
//
////        if( point_to_recompute_intersection == lcc.point(minEdges.at(0))
////        || point_to_recompute_intersection == lcc.point(lcc.opposite(minEdges.at(0))))
////        {
////           v1 = Vector(lcc.point(minEdges.at(0)), lcc.point(lcc.opposite(minEdges.at(0)))) ;
////           v2 = Vector(lcc.point(minEdges.at(1)), lcc.point(lcc.opposite(minEdges.at(1)))) ;
////        }
////        else{
////            v1 = Vector(lcc.point(minEdges.at(1)), lcc.point(lcc.opposite(minEdges.at(1)))) ;
////            v2 = Vector(lcc.point(minEdges.at(0)), lcc.point(lcc.opposite(minEdges.at(0)))) ;
////        }
//
//        v1 = Vector(Point(2,2,4), Point(2,2,2) );
//        v2 = Vector(Point(1,3,5), Point(4,2,2) );
//       // K::Ray_3 r = K::Ray_3(lcc.point(vertex_handle), v2.direction());
//        K::Ray_3 r = K::Ray_3(Point(2,2,2), v2.direction());
//        //v3 = r.to_vector();
//        new_normal = r.to_vector();
//
////        std::cout<<v1.direction()<<std::endl;
////        std::cout<<v2.direction()<<std::endl;
//        new_normal = typename LCC::Traits::Construct_sum_of_vectors()(v1,  new_normal);
////        std::cout<<new_normal.direction()<<std::endl;
//        // new_normal = LCC::Traits::Construct_scaled_vector()(new_normal, 1.0/2);
//        std::cout << new_normal.direction() << std::endl;
//
//
//        // compute the new intersection point
//        PointNormal_boundary_intersectionPoint_finder intersectionPoint_finder;
//        boost::optional<Point> boostIntersectionPoint = intersectionPoint_finder.findIntersecionPoint(lcc,
//                                                                                                      vertex_handle,
//                                                                                                      polyhedron,
//                                                                                                      new_normal);
//        if (boostIntersectionPoint.is_initialized()) {
//            lcc.point(lcc.opposite(vertex_handle)) = boostIntersectionPoint.get();
//        } else {
//            Point support_point = lcc.point(lcc.opposite(vertex_handle_l));
//            lcc.point(lcc.opposite(vertex_handle_l)) = lcc.point(lcc.opposite(vertex_handle));
//            lcc.point(lcc.opposite(vertex_handle)) = support_point;
//        }


    }

    bool is_edge_parallel_to_normal(const Vertex_location_finder &vertexLocationFinder, const Point& p1, const Point& p2 ) const {

        return (vertexLocationFinder.is_point_onBoundary_polyhedron(p1) && !vertexLocationFinder.is_point_onBoundary_polyhedron(p2))
                       || (!vertexLocationFinder.is_point_onBoundary_polyhedron(p1) && vertexLocationFinder.is_point_onBoundary_polyhedron(p2));
    }
};


#endif //INC_3DMESHER_HEXAHEDRON_FITTER_H
