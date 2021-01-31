
#include "../Include/catch.hpp"
#include "test_config.h"
#include "VTK_manager.h"


//TEST_CASE("must find 1 hexahedron", "[][VTK_manager]") {
//
//    //const std::string filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/hexahedron.vtk";
//    const std::string filename_to_read = "/home/claudia/CLionProjects/3DMesher/Catch_tests/Data/hexahedron.vtk";
//    VTK_manager vtkManager;
//    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
//    std::map<std::string, int> statistics;
//    vtkManager.get_statistics_from_vtk_file(filename_to_read, statistics, true);
//    REQUIRE(statistics["3D_CELLS_NUMBER"] == 1);
//    REQUIRE(statistics["HEXES_NUMBER"] == 1);
//    REQUIRE(statistics["TETRA_NUMBER"] == 0);
//    REQUIRE(statistics["PYRAMIDS_NUMBER"] == 0);
//    REQUIRE(statistics["WEDGES_NUMBER"] == 0);
//    REQUIRE(statistics["OTHER_3D_CELLS_NUMBER"] == 0);
//
//}

