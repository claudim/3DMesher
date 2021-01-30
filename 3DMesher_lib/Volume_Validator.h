// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Validate the volume of the mesh blocks using Verdict Library.
//******************************************************************************


#ifndef INC_3DMESHER_VOLUME_VALIDATOR_H
#define INC_3DMESHER_VOLUME_VALIDATOR_H

#include "MyLCC.h"
#include <verdict.h>

/**
 * @brief Validate the volume of the mesh blocks using Verdict Library.
 *
 * @file Volume_Validator.h
 * @class Volume_Validator
 */
class Volume_Validator {
public:

    /**
     * @brief Remove/Delete all the hexahedral mesh blocks with a volume <= 0.
     *
     * @param hex_mesh The hexahedral mesh.
     */
    void delete_blocks_with_less_than_or_equal_to_zero(LCC_3& hex_mesh){
        if(!hex_mesh.is_empty()) {
            for (LCC_3::One_dart_per_cell_range<3, 3>::iterator cell_it = hex_mesh.one_dart_per_cell<3, 3>().begin(),
                         cell_it_end = hex_mesh.one_dart_per_cell<3, 3>().end(); cell_it != cell_it_end; ++cell_it) {
                if (this->is_block_to_remove(hex_mesh, cell_it)) {
                    this->remove_block(hex_mesh, cell_it);
                }
            }
        }
    }

    /**
     * @brief Remove the block from the hexahedral mesh.
     *
     * @param hex_mesh The hexahedral mesh from which to remove the block.
     * @param blockToRemove The block to delete.
     */
    void remove_block(LCC_3& hex_mesh, Dart_handle& blockToRemove) {
        if(!hex_mesh.is_empty()) {
            hex_mesh.remove_cell<3>(blockToRemove);
        }
    }

    /**
     * @brief Check if the mesh block is to remove/delete so check if the mesh block has a volume <= 0.
     *
     * @param hex_mesh The hexahedral mesh to which the block belongs.
     * @param blockToCheck The mesh block to check if it has volume <= 0.
     * @return true if the block has volume <= 0 and therefore it is to remove, false otherwise.
     */
    bool is_block_to_remove(LCC_3& hex_mesh, Dart_handle& blockToCheck) {
        bool toRemove = false;
        if(!hex_mesh.is_empty()) {
            double block_volume = this->get_block_volume(hex_mesh, blockToCheck);
            if (block_volume <= 0) {
                toRemove = true;
            }
        }
        return toRemove;
    }

    /**
     * @brief Get the block volume using the Verdict Library.
     *
     * @param hex_mesh The hexahedral mesh to which the block belongs.
     * @param block The block of which it is calculated the volume.
     * @return
     */
    double get_block_volume(LCC_3& hex_mesh, Dart_handle& block){
        std::vector<std::array<double, 3> > vertices;
        std::array<double, 3> point{};
        if(!hex_mesh.is_empty()) {
            for (LCC_3::One_dart_per_incident_cell_range<0, 3>::iterator vertex_it = hex_mesh.one_dart_per_incident_cell<0, 3>(
                    block).begin(), vertex_it_end = hex_mesh.one_dart_per_incident_cell<0, 3>(block).end();
                 vertex_it != vertex_it_end; ++vertex_it) {
                point[0] = hex_mesh.point(vertex_it).x();
                point[1] = hex_mesh.point(vertex_it).y();
                point[2] = hex_mesh.point(vertex_it).z();
                vertices.emplace_back(point);
            }
        }
        HexMetricVals vals{};
        std::array<double, 3> *pArray = vertices.data();
        v_hex_quality(vertices.size(), reinterpret_cast<const double (*)[3]>(pArray), V_HEX_VOLUME, &vals);
        return vals.volume;
    }
};


#endif //INC_3DMESHER_VOLUME_VALIDATOR_H
