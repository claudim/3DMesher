// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Find the mesh blocks more external.
// In other words if a mesh block is not internal in the mesh, it is detect and added in a vector to return.
//Note:These blocks found could be external or not to the polyhedron boundary.
//******************************************************************************

#ifndef INC_3DMESHER_MORE_EXTERNAL_BLOCK_FINDER_H
#define INC_3DMESHER_MORE_EXTERNAL_BLOCK_FINDER_H

#include "External_facet_finder.h"

class More_external_block_finder {

public:

    /**
     * \brief Find the mesh blocks more external. These blocks found could be external or not to a polyhedron boundary.
     *
     * @param lcc The hexahedral mesh.
     * @return vector of the mesh block more external.
     */
    std::vector<Dart_handle> find(LCC_3 &lcc) {
        std::vector<Dart_handle> more_external_mesh_block;
        if(!lcc.is_empty()) {
            for(LCC_3::One_dart_per_cell_range<3,3>::iterator cell_it = lcc.one_dart_per_cell<3>().begin(),
                    cell_end_it = lcc.one_dart_per_cell<3>().end(); cell_it != cell_end_it; ++cell_it){
                for (LCC_3::One_dart_per_incident_cell_range<2,3,3>::iterator it=lcc.one_dart_per_incident_cell<2,3,3>(cell_it).begin(),
                             itend = lcc.one_dart_per_incident_cell<2,3,3>(cell_it).end(); it!=itend; ++it)
                {
                    if(lcc.beta<3>(it) == lcc.null_dart_handle)
                    {
                        more_external_mesh_block.emplace_back(cell_it);
                        break;
                    }
                }
            }
        }
        return more_external_mesh_block;
    }
};



#endif //INC_3DMESHER_MORE_EXTERNAL_BLOCK_FINDER_H
