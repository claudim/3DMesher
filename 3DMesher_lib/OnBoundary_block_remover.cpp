#include "OnBoundary_block_remover.h"

//template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
void OnBoundary_block_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron) {
    if(!lcc.is_empty())
    {
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
            if (is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron)) {
                removeBlock(lcc, lcc_cells_iterator);
            }
        }
    }
}


void OnBoundary_block_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance) {
    if(!lcc.is_empty())
    {
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
            if (is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron, distance)) {
                removeBlock(lcc, lcc_cells_iterator);
            }

        }
    }
}

bool OnBoundary_block_remover::is_block_to_be_removed(const LCC_3 &lcc,
                                                      const Dart_handle& block,
                                                      const Polyhedron &polyhedron,
                                                      const double &distance) {

    bool toRemove = false;
    int number_of_internal_points = 0;
    if(!lcc.is_empty()) {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per tutti i vertici del cubo
        LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator
                it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
                itend = lcc.one_dart_per_incident_cell<0, 3>(block).end();
        while ( it != itend && !toRemove) {
            //if (is_point_inside_polyhedron(lcc.point(it), inside)) {
            Point point = lcc.point(it);
            if (vertexLocationFinder.is_point_inside_polyhedron(point)) {
                number_of_internal_points++;
                toRemove = vertexLocationFinder.is_point_too_close_to_the_boundary(point, distance);
            }
            ++it;
        }
    }
    if (number_of_internal_points > 0 &&  number_of_internal_points < 8) {
        toRemove = true;
    }
    return toRemove;

//    bool toRemove = false;
//    if(!lcc.is_empty()) {
//        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
//        // per tutte le facce del cubo
//        LCC_3::One_dart_per_incident_cell_const_range<2, 3>::const_iterator
//                it = lcc.one_dart_per_incident_cell<2,3>(block).begin(),
//                itend = lcc.one_dart_per_incident_cell<2, 3>(block).end();
//        while ( it != itend && !toRemove) {
//            Point barycenter = lcc.barycenter<2>(it);
//            double distanceBarycenterPolyhedron = vertexLocationFinder.getAabbTree().squared_distance(barycenter);
//            //Point point = lcc.point(it);
//            distanceBarycenterPolyhedron = sqrt(distanceBarycenterPolyhedron);
//            if ( distanceBarycenterPolyhedron < distance) {
//                toRemove = true;
//           }
//            ++it;
//        }
//    }
   // return toRemove;
}

//template<typename Linear_cell_complex_traits, typename allocator, typename allocator, typename Linear_cell_complex_traits>
bool OnBoundary_block_remover::is_block_to_be_removed(const LCC_3 &lcc,
                                                      const Dart_handle& block,
                                                      const Polyhedron &polyhedron) {

    bool toRemove = false;
    int number_of_internal_points = 0;
    if(!lcc.is_empty()) {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per tutti i vertici del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator
                     it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 3>(block).end(); it != itend; ++it) {
            //if (is_point_inside_polyhedron(lcc.point(it), inside)) {
            if (vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it))) {
                number_of_internal_points++;
            }
        }
    }
    if (number_of_internal_points > 0 &&  number_of_internal_points < 8) {
        toRemove = true;
    }
    return toRemove;
}

void OnBoundary_block_remover::removeBlock(LCC_3& lcc, Dart_handle& blockToRemove) {
    lcc.remove_cell<3>(blockToRemove);
}