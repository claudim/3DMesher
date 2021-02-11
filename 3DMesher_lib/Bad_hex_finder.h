// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Detect degenerate or bad hexahedra.
//******************************************************************************

#ifndef INC_3DMESHER_BAD_HEX_FINDER_H
#define INC_3DMESHER_BAD_HEX_FINDER_H

#include "verdict.h"
#include "MyLCC.h"
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>

//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//const float SCALED_JACOBIAN_THRESHOLD = 0.5;
const float SCALED_JACOBIAN_THRESHOLD = 0.1;

/**
 * @brief Find degenerate or bad shaped hexahedra.
 *
 * @file Bad_hex_finder.h
 * @class Bad_hex_finder
 */
class Bad_hex_finder {

private:

    /**
     * Value of scaled jacobian below that a hex is considered invalid
     */
    float scaled_jacobian_threshold = 0;


public:

    /**
     * @brief Setter for scaled jacobian value.
     *
     * @param scaledJacobianThreshold Value of scaled jacobian below that a hex is considered invalid.
     */
    void setScaledJacobianThreshold(float scaledJacobianThreshold);

    /**
     * @brief Check if a provided hexahedron is not of the desired quality based on scaled jacobian.
     *
     * @param aHex hexahedron to be checked.
     * @return true if the provided hexahedron not fulfill the quality requirment.
     */
    bool is_hex_bad(const Dart_handle& aHex, LCC_3& lcc);


    /**
     * @brief Find on provided lcc only the malformed hexahedra and fill the bad_hexes vector passed with the malformed hexahedra found.
     *
     * @param lcc linear cell complex where find bad hexahedra on.
     * @param bad_hexes vector of bad hexahedra to fill.
     */
    void find_bad_hexes(LCC_3 &lcc, std::vector<Dart_handle> &bad_hexes);
};


#endif //INC_3DMESHER_BAD_HEX_FINDER_H
