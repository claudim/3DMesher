#include <CGAL/Mesh_polyhedron_3.h>
#include "External_block_remover.h"


// i cicli for su lcc lanciano un'eccezione quando lcc è vuoto per questo ho aggiunto l'if not empty
bool
External_block_remover::is_block_to_be_removed(const LCC_3 &lcc, const Dart_handle &block, const Polyhedron &polyhedron,
                                               Vertex_location_finder &vertexLocationFinder) {
    bool toRemove = false;
    int number_of_internal_points = 0;
//    if(!lcc.is_empty()) {
//        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
//        // per tutti i vertici del cubo
//        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
//                     itend = lcc.one_dart_per_incident_cell<0, 3>(block).end(); it != itend; ++it) {
//            if (!vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it))) {
//                toRemove = true;
//                break;
//            }
//        }
//    }

//it is necessary for univaq algorithm
    if(!lcc.is_empty()) {
//        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per tutti i vertici del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator
                     it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 3>(block).end(); it != itend; ++it) {
            //if (is_point_inside_polyhedron(lcc.point(it), inside)) {
            if (vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it))) {
           // if (vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it)) || vertexLocationFinder.is_point_onBoundary_polyhedron(lcc.point(it))) {
                number_of_internal_points++;
            }
        }
    }
    if (number_of_internal_points == 0) {
        toRemove = true;

//        Point centroid;
//        this->get_const_block_centroid(lcc, block, centroid);
//        if (vertexLocationFinder.is_point_inside_polyhedron(centroid) ||
//            vertexLocationFinder.is_point_onBoundary_polyhedron(centroid)) {
//            toRemove = false;
//        }
    }
    return toRemove;
}

//bool External_block_remover::is_point_inside_polyhedron(const Point& pointToBeCheck, const Point_inside& inside){
//    if (inside(pointToBeCheck) == CGAL::ON_BOUNDED_SIDE){
//        return true;
//    }
//    else{
//        return false;
//    }
//}

void External_block_remover::removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron) {
    if(!lcc.is_empty())
    {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
            if (is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron, vertexLocationFinder)) {
                //removeBlock(lcc, lcc_cells_iterator);
                lcc.remove_cell<3>(lcc_cells_iterator);
            }
        }
    }
}

void External_block_remover::removeBlock(LCC_3& hex_mesh, Dart_handle& blockToRemove) {
    hex_mesh.remove_cell<3>(blockToRemove);
}

void External_block_remover::removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron, const double &distance) {}

void External_block_remover::get_block_centroid(LCC_3 &hex_mesh, Dart_handle &block, Point &centroid_to_find) {
    if(!hex_mesh.is_empty()) {
        Dart_handle opposite_facet = hex_mesh.beta(block, 2, 1, 1, 2);
        std::vector<Point> facet_points;
        //for(LCC_3::Dart_of_cell_range<0,3>::iterator it = hex_mesh.darts_of_cell<0,3>(block).begin(), e_it = hex_mesh.darts_of_cell<0,3>(block).end();
        for(LCC_3::Dart_of_orbit_range<1>::iterator it = hex_mesh.darts_of_orbit<1>(block).begin(), e_it = hex_mesh.darts_of_orbit<1>(block).end();
        it != e_it; ++it){
            facet_points.emplace_back(hex_mesh.point(it));
        }
        std::vector<Point> opposite_facet_points;
        for(LCC_3::Dart_of_orbit_range<1>::iterator it = hex_mesh.darts_of_orbit<1>(opposite_facet).begin(), e_it = hex_mesh.darts_of_orbit<1>(opposite_facet).end();
            it != e_it; ++it){
            opposite_facet_points.emplace_back(hex_mesh.point(it));
        }
        Point facet_centroid = CGAL::centroid(facet_points.at(0), facet_points.at(1), facet_points.at(2),
                                              facet_points.at(3));
        Point opposite_facet_centroid = CGAL::centroid(opposite_facet_points.at(0), opposite_facet_points.at(1),
                                                       opposite_facet_points.at(2), opposite_facet_points.at(3));

        centroid_to_find = CGAL::midpoint(facet_centroid, opposite_facet_centroid);
    }
}

void External_block_remover::get_const_block_centroid(const LCC_3& hex_mesh, const Dart_handle& block, Point& centroid_to_find) {
    if(!hex_mesh.is_empty()) {
        Dart_const_handle opposite_facet = hex_mesh.beta(block, 2, 1, 1, 2);
        std::vector<Point> facet_points;
        //for(LCC_3::Dart_of_cell_range<0,3>::iterator it = hex_mesh.darts_of_cell<0,3>(block).begin(), e_it = hex_mesh.darts_of_cell<0,3>(block).end();
        for(LCC_3::Dart_of_orbit_const_range<1>::const_iterator it = hex_mesh.darts_of_orbit<1>(block).begin(), e_it = hex_mesh.darts_of_orbit<1>(block).end();
            it != e_it; ++it){
            facet_points.emplace_back(hex_mesh.point(it));
        }
        std::vector<Point> opposite_facet_points;
        for(LCC_3::Dart_of_orbit_const_range<1>::const_iterator it = hex_mesh.darts_of_orbit<1>(opposite_facet).begin(), e_it = hex_mesh.darts_of_orbit<1>(opposite_facet).end();
            it != e_it; ++it){
            opposite_facet_points.emplace_back(hex_mesh.point(it));
        }
        Point facet_centroid = CGAL::centroid(facet_points.at(0), facet_points.at(1), facet_points.at(2),
                                              facet_points.at(3));
        Point opposite_facet_centroid = CGAL::centroid(opposite_facet_points.at(0), opposite_facet_points.at(1),
                                                       opposite_facet_points.at(2), opposite_facet_points.at(3));

        centroid_to_find = CGAL::midpoint(facet_centroid, opposite_facet_centroid);
    }
}

