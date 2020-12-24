#include <CGAL/Mesh_polyhedron_3.h>
#include "External_block_remover.h"

typedef CGAL::Vertex_location_finder Vertex_location_finder;

// i cicli for su lcc lanciano un'eccezione quando lcc è vuoto per questo ho aggiunto l'if not empty
bool External_block_remover::is_block_to_be_removed(const LCC_3& lcc, const Dart_handle& block, const Polyhedron& polyhedron){
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
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per tutti i vertici del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator
                     it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 3>(block).end(); it != itend; ++it) {
            //if (is_point_inside_polyhedron(lcc.point(it), inside)) {
            if (vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it)) ) {
                number_of_internal_points++;
            }
        }
    }
    if (number_of_internal_points == 0) {
        toRemove = true;
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
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
            if (is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron)) {
                removeBlock(lcc, lcc_cells_iterator);
            }
        }
    }
}

//template<typename Linear_cell_complex_traits, typename allocator>
void External_block_remover::removeBlock(LCC_3& lcc, Dart_handle& blockToRemove) {
    lcc.remove_cell<3>(blockToRemove);
}

void External_block_remover::removeBlocks(LCC_3& lcc, const Polyhedron& polyhedron, const double &distance) {}