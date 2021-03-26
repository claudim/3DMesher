#include "UnivaqSplitFromTetAlgorithm.h"

void UnivaqSplitFromTetAlgorithm::run(const Polyhedron &polyhedron, LCC_3 &hex_mesh, double max_edge_dimension) {
    // 1. Create Tet Mesh
    DelaunayCGALTetMeshAlgorithm delaunayCgalTetMeshAlgorithm;
    C3t3 tet_mesh;
    delaunayCgalTetMeshAlgorithm.run(polyhedron, tet_mesh, max_edge_dimension);

    //2. Split tet mesh generating a hex mesh
    HexMesh_from_TetMesh_maker hex_mesh_maker;
    hex_mesh_maker.split_from_tet(tet_mesh, hex_mesh);
}

void UnivaqSplitFromTetAlgorithm::run(const Polyhedron &polyhedron, LCC_3 &hex_mesh)
{
    // 1. Create Tet Mesh
    DelaunayCGALTetMeshAlgorithm delaunayCgalTetMeshAlgorithm;
    C3t3 tet_mesh;
    delaunayCgalTetMeshAlgorithm.run(polyhedron, tet_mesh);

    //2. Split tet mesh generating a hex mesh
    HexMesh_from_TetMesh_maker hex_mesh_maker;
    hex_mesh_maker.split_from_tet(tet_mesh, hex_mesh);

}
