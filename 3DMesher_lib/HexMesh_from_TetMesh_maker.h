// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// This class is responsible for the creation of a Hexahedral mesh starting from
// a Tetrahedral mesh by splitting each tetrahedron in 4 hexahedra.
// ******************************************************************************


#ifndef INC_3DMESHER_HEXMESH_FROM_TETMESH_MAKER_H
#define INC_3DMESHER_HEXMESH_FROM_TETMESH_MAKER_H

#include "MyLCC.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Polyhedral_mesh_domain_with_features_3<K> Mesh_Domain;
typedef CGAL::Mesh_triangulation_3<Mesh_Domain, CGAL::Default>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;

/**
 * @brief Create a Hexahedral mesh starting from a Tetrahedral mesh by splitting each tetrahedron in 4 hexahedra.
 *
 * @file HexMesh_from_TetMesh_maker.h
 * @class HexMesh_from_TetMesh_maker
 */
class HexMesh_from_TetMesh_maker {
public:
    /**
     * @brief Create a Hexahedral mesh starting from a Tetrahedral mesh by splitting each tetrahedron in 4 hexahedra.
     *
     * @param c3t3 The Tetrahedral mesh variable where is stored the tet mesh.
     * @param hex_mesh The Hexahedral mesh variable where store the new hex mesh.
     */
    void split_from_tet(const C3t3 &c3t3, LCC_3 &hex_mesh);
};


#endif //INC_3DMESHER_HEXMESH_FROM_TETMESH_MAKER_H
