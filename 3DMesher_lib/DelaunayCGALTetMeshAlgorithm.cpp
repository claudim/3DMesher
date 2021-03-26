#include "DelaunayCGALTetMeshAlgorithm.h"

void DelaunayCGALTetMeshAlgorithm::run(const Polyhedron& polyhedron, C3t3& tet_mesh, double max_edge_dimension){
    //Create domain
    Mesh_Domain domain(polyhedron);

    //Get sharp features
    domain.detect_features();

    Mesh_Criteria criteria(
            facet_angle = 30,
            cell_radius_edge_ratio = 2,
            cell_size = max_edge_dimension * sqrt(6) / 4,
            edge_size = max_edge_dimension
    );

    //Mesh generation
    tet_mesh = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());
}

void DelaunayCGALTetMeshAlgorithm::run(const Polyhedron& polyhedron, C3t3& tet_mesh){
    //Create domain
    Mesh_Domain domain(polyhedron);

    //Get sharp features
    domain.detect_features();

    Mesh_Criteria criteria(
            facet_angle = 30,
            cell_radius_edge_ratio = 2
    );

    //Mesh generation
    tet_mesh = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());
}