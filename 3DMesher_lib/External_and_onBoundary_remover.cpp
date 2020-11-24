#include "External_and_onBoundary_remover.h"

void External_and_onBoundary_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron) {
    External_block_remover externalBlockRemover = External_block_remover();
    externalBlockRemover.removeBlocks(lcc, polyhedron);

    OnBoundary_block_remover onBoundaryBlockRemover = OnBoundary_block_remover();
    onBoundaryBlockRemover.removeBlocks(lcc, polyhedron);
}

void External_and_onBoundary_remover::removeBlocks(LCC_3 &lcc, const Polyhedron &polyhedron, const double &distance) {
    External_block_remover externalBlockRemover = External_block_remover();
    externalBlockRemover.removeBlocks(lcc, polyhedron);

    OnBoundary_block_remover onBoundaryBlockRemover = OnBoundary_block_remover();
    onBoundaryBlockRemover.removeBlocks(lcc, polyhedron, distance);
}

void External_and_onBoundary_remover::removeBlock(LCC_3& lcc, Dart_handle& blockToRemove) {
    lcc.remove_cell<3>(blockToRemove);
}