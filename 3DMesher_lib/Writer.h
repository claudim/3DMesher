#ifndef INC_3DMESHER_WRITER_H
#define INC_3DMESHER_WRITER_H

#include "MyLCC.h"
#include <ostream>
#include <CGAL/Linear_cell_complex_for_combinatorial_map.h>
#include <CGAL/Linear_cell_complex_constructors.h>
#include <CGAL/Linear_cell_complex_operations.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include "vtk-9.0/vtkVersion.h"
#include "vtk-9.0/vtkSmartPointer.h"
#include "vtk-9.0/vtkPoints.h"
//#include <vtk-9.0/vtkCellArray.h>
//#include <vtk-9.0/vtkType.h>
//#include <vtk-9.0/vtkPointData.h>
#include "vtk-9.0/vtkHexahedron.h"
//#include <vtk-9.0/vtkIdList.h>
#include "vtk-9.0/vtkUnstructuredGrid.h"
#include "vtk-9.0/vtkUnstructuredGridWriter.h"
//#include <vtk-9.0/vtkDataSetMapper.h>
//#include <vtk-9.0/vtkPolyDataWriter.h>

//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Linear_cell_complex_for_combinatorial_map<3> LCC_3;
//typedef LCC_3::Dart_handle Dart_handle;
//typedef LCC_3::Point Point;
typedef CGAL::Bbox_3 Bbox;
//typedef LCC_3::Traits Traits;
//typedef LCC_3::FT FT;


class Writer {

public:
    void output_to_medit(std::ostream& os, const LCC_3& lcc);

    /**
     * \brief Write the hex_mesh in a .vtk file without using the vtk library.
     *
     * @param hex_mesh The hexahedral mesh to write in the vtk file format.
     */
    void output_to_legacy_vtk_ascii_unstructured(std::ostream& os, const LCC_3& hex_mesh);

    /**
    * \brief Write the hex_mesh in a .vtk file using the vtk library.
    *
    * @param hex_mesh The hexahedral mesh to write in the vtk file format.
    */
    void output_to_legacy_vtk_ascii_unstructured(const std::string outputFileName, const LCC_3& hex_mesh);

    int get();

    LCC_3::size_type number_of_facets_in_lcc(const LCC_3 &lcc);

    LCC_3::size_type number_of_cells_in_lcc(const LCC_3 &lcc);

};


#endif //INC_3DMESHER_WRITER_H
