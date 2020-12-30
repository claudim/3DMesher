#ifndef INC_3DMESHER_VOLUME_VALIDATOR_H
#define INC_3DMESHER_VOLUME_VALIDATOR_H

#include "MyLCC.h"
#include <verdict.h>

class Volume_Validator {
public:

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

    void remove_block(LCC_3& hex_mesh, Dart_handle& blockToRemove) {
        if(!hex_mesh.is_empty()) {
            hex_mesh.remove_cell<3>(blockToRemove);
        }
    }

    bool is_block_to_remove(LCC_3& lcc, Dart_handle& aHex) {
        bool toRemove = false;
        if(!lcc.is_empty()) {
            double block_volume = this->get_block_volume(lcc, aHex);
            //std::cout<<"il volume è "<< block_volume <<std::endl;
            if (block_volume <= 0) {
                toRemove = true;
            }
        }
        return toRemove;
    }

    double get_block_volume(LCC_3& lcc, Dart_handle& aHex){
        std::vector<std::array<double, 3> > vertices;
        std::array<double, 3> point{};
        if(!lcc.is_empty()) {
            for (LCC_3::One_dart_per_incident_cell_range<0, 3>::iterator vertex_it = lcc.one_dart_per_incident_cell<0, 3>(
                    aHex).begin(), vertex_it_end = lcc.one_dart_per_incident_cell<0, 3>(aHex).end();
                 vertex_it != vertex_it_end; ++vertex_it) {
                point[0] = lcc.point(vertex_it).x();
                point[1] = lcc.point(vertex_it).y();
                point[2] = lcc.point(vertex_it).z();
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
