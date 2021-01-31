#include "External_and_onBoundary_remover.h"

void External_and_onBoundary_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron) {
    if(!lcc.is_empty())
    {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
            if (this->is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron, vertexLocationFinder)) {
                removeBlock(lcc, lcc_cells_iterator);
            }
        }
    }

    OnBoundary_block_remover onBoundaryBlockRemover = OnBoundary_block_remover();
    onBoundaryBlockRemover.removeBlocks(lcc, polyhedron);
}

void External_and_onBoundary_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance) {
    if(!lcc.is_empty())
    {
        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        for (LCC_3::One_dart_per_cell_range<3, 3>::iterator lcc_cells_iterator = lcc.one_dart_per_cell<3, 3>().begin(),
                     lcc_cells_end_iterator = lcc.one_dart_per_cell<3, 3>().end();
             lcc_cells_iterator != lcc_cells_end_iterator; ++lcc_cells_iterator) {
            if (this->is_block_to_be_removed(lcc, lcc_cells_iterator, polyhedron,vertexLocationFinder)) {
                removeBlock(lcc, lcc_cells_iterator);
            }
        }
    }

    OnBoundary_block_remover onBoundaryBlockRemover = OnBoundary_block_remover();
    onBoundaryBlockRemover.removeBlocks(lcc, polyhedron, distance);
}

void External_and_onBoundary_remover::removeBlock(LCC_3& lcc, Dart_handle& blockToRemove) {
    lcc.remove_cell<3>(blockToRemove);
}

bool External_and_onBoundary_remover::is_block_to_be_removed(const LCC_3 &lcc, const Dart_handle &block,
                                                             const Polyhedron &polyhedron,
                                                             Vertex_location_finder &vertexLocationFinder) {
    bool toRemove = false;
    if(!lcc.is_empty()) {
//        Vertex_location_finder vertexLocationFinder = Vertex_location_finder(polyhedron);
        // per tutti i vertici del cubo
        for (LCC_3::One_dart_per_incident_cell_const_range<0, 3>::const_iterator it = lcc.one_dart_per_incident_cell<0,3>(block).begin(),
                     itend = lcc.one_dart_per_incident_cell<0, 3>(block).end(); it != itend; ++it) {
            if (!vertexLocationFinder.is_point_inside_polyhedron(lcc.point(it))) {
                toRemove = true;
                break;
            }
        }
    }
    return toRemove;
}