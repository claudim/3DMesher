#include "UnivaqSplitFromTetAlgorithm.h"

void UnivaqSplitFromTetAlgorithm::run(const Polyhedron &polyhedron, LCC_3 &hex_mesh, double max_edge_dimension) {
    // 1. Create Tet Mesh
    //Create domain
    Mesh_Domain domain(polyhedron);

    //Get sharp features
    domain.detect_features();

    C3t3 c3t3;

    Mesh_Criteria criteria(
            facet_angle = 30,
            cell_radius_edge_ratio = 2,
            cell_size = max_edge_dimension * sqrt(6) / 4,
            edge_size = max_edge_dimension
    );

    //Mesh generation
    c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());

    //2. Split tet mesh generating a hex mesh
    HexMesh_from_TetMesh_maker hex_mesh_maker;
    hex_mesh_maker.split_from_tet(c3t3, hex_mesh);
}

void UnivaqSplitFromTetAlgorithm::run(const Polyhedron &polyhedron, LCC_3 &hex_mesh)
{
    // 1. Create Tet Mesh
    //Create domain
    Mesh_Domain domain(polyhedron);

    //Get sharp features
    domain.detect_features();

    C3t3 c3t3;

    Mesh_Criteria criteria(
            facet_angle = 30,
            cell_radius_edge_ratio = 2
    );

    //Mesh generation
    c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());

    //2. Split tet mesh generating a hex mesh
    HexMesh_from_TetMesh_maker hex_mesh_maker;
    hex_mesh_maker.split_from_tet(c3t3, hex_mesh);

}
