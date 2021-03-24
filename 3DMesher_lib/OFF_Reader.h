// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// The OFF file reader.
//******************************************************************************

#ifndef INC_3DMESHER_OFF_READER_H
#define INC_3DMESHER_OFF_READER_H

#include <string>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <exception>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;

/**
 * @brief The OFF file reader.
 *
 * @file OFF_Reader.h
 * @class OFF_Reader
 */
class OFF_Reader {

public:
    /**
     * @brief Read a polyhedron from an OFF file.
     *
     * @param fileName The filename
     * @return  The polyhedron read.
     */
    Polyhedron read(std::string fileName) noexcept(false); //it could throw std::ios_base::failure
};


#endif //INC_3DMESHER_OFF_READER_H
