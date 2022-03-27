// Copyright (c) 2020-2021 Univaq (Italy)
// All rights reserved.
//
// Author(s): Claudia Di Marco <dimarco.claud@gmail.com>, Riccardo Mantini <mantini.riccardo@gmail.com>
//
//******************************************************************************
// File Description :
// Write the hex mesh on a file.
//******************************************************************************

#ifndef INC_3DMESHER_WRITER_H
#define INC_3DMESHER_WRITER_H

#include "MyLCC.h"
#include <ostream>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include "vtk-9.0/vtkVersion.h"
#include "vtk-9.1/vtkSmartPointer.h"
#include "vtk-9.1/vtkPoints.h"
#include "vtk-9.1/vtkHexahedron.h"
#include "vtk-9.1/vtkUnstructuredGrid.h"
#include "vtk-9.1/vtkUnstructuredGridWriter.h"

typedef CGAL::Bbox_3 Bbox;

/**
 * @brief Class responsible to write the hex mesh on a file.
 *
 * @file Writer.h
 * @class Writer
 */
class Writer {

public:
    /**
     * @brief Write the hex_mesh in a .mesh file.
     *
     * @param os Where store the output.
     * @param lcc The mesh.
     */
    void output_to_medit(std::ostream& os, const LCC_3& lcc);

    /**
     * @brief Write the hex_mesh in a .vtk file without using the vtk library.
     *
     * @param os Where store the output.
     * @param hex_mesh The hexahedral mesh to write in the vtk file format.
     */
    void output_to_legacy_vtk_ascii_unstructured(std::ostream& os, const LCC_3& hex_mesh);

    /**
    * @brief Write the hex_mesh in a .vtk file using the vtk library.
    *
    * @param outputFileName The path file name where store the output.
    * @param hex_mesh The hexahedral mesh to write in the vtk file format.
    */
    void output_to_legacy_vtk_ascii_unstructured(const std::string outputFileName, const LCC_3& hex_mesh);

    int get();

    LCC_3::size_type number_of_facets_in_lcc(const LCC_3 &lcc);

    LCC_3::size_type number_of_cells_in_lcc(const LCC_3 &lcc);

};


#endif //INC_3DMESHER_WRITER_H
