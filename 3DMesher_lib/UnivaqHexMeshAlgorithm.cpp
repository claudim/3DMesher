#include "UnivaqHexMeshAlgorithm.h"

void UnivaqHexMeshAlgorithm::run(const Polyhedron &polyhedron, LCC_3 &hex_mesh, double resolution) {

    Grid_maker gridMaker = Grid_maker();
    gridMaker.set_resolution(resolution);

    hex_mesh = gridMaker.make(polyhedron);

    External_block_remover externalBlockRemover = External_block_remover();
    externalBlockRemover.removeBlocks(hex_mesh, polyhedron);

    //fit on boundary blocks to polyhedron boundary
    CGAL::Grid_boundary_connector gridBoundaryConnector;
    gridBoundaryConnector.connect(hex_mesh, polyhedron);

    //delete element with Volume <= volume threshold
    double volume_threshold = std::pow(gridMaker.getGridDimension(), 3) / 1000;
    Volume_Validator volumeValidator;
    volumeValidator.setVolumeTreshold(volume_threshold);
    volumeValidator.delete_blocks_with_less_than_or_equal_to_volume_threshold(hex_mesh);
}

void UnivaqHexMeshAlgorithm::run(const Polyhedron &polyhedron, LCC_3 &hex_mesh) {

    Grid_maker gridMaker = Grid_maker();
    hex_mesh = gridMaker.make(polyhedron);

    External_block_remover externalBlockRemover = External_block_remover();
    externalBlockRemover.removeBlocks(hex_mesh, polyhedron);

    //fit on boundary blocks to polyhedron boundary
    CGAL::Grid_boundary_connector gridBoundaryConnector;
    gridBoundaryConnector.connect(hex_mesh, polyhedron);

    //delete element with Volume <= volume threshold
    double volume_threshold = std::pow(gridMaker.getGridDimension(), 3) / 1000;
    Volume_Validator volumeValidator;
    volumeValidator.setVolumeTreshold(volume_threshold);
    volumeValidator.delete_blocks_with_less_than_or_equal_to_volume_threshold(hex_mesh);
}
