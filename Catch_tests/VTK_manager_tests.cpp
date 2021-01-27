
#include "../Include/catch.hpp"
#include "test_config.h"
#include "VTK_manager.h"


TEST_CASE("must find 1 hexahedron", "[][VTK_manager]") {

    const std::string filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/ugridex.vtk";
    VTK_manager vtkManager;
    //vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
    vtkManager.get_statistics_from_vtk_file(filename_to_read);
}

