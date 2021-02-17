
#include <Block_maker.h>
#include <Writer.h>
#include "../Include/catch.hpp"
#include "test_config.h"
#include "VTK_manager.h"
#include "MyLCC.h"


TEST_CASE("must find statistics from a vtk or vtu file", "[get_statistics_from_vtk_file][VTK_manager]") {

    const std::string filename_to_read =  "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/ugridex.vtk";
    //const std::string filename_to_read = "/home/claudia/CLionProjects/3DMesher/Catch_tests/Data/ugridex.vtk";

    VTK_manager vtkManager;
    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
    std::map<int, int> statistics;
    vtkManager.get_statistics_from_vtk_file(filename_to_read, statistics, true);
    REQUIRE(statistics[12] == 2);
    REQUIRE(statistics[10] == 2);
    REQUIRE(statistics[7] == 1);
    REQUIRE(statistics[6] == 1);
    REQUIRE(statistics[9] == 1);
    REQUIRE(statistics[5] == 2);
    REQUIRE(statistics[3] == 2);
    REQUIRE(statistics[1] == 1);

}

TEST_CASE("must read a vtk or vtu file", "[readUnstructuredGrid][VTK_manager]"){
    VTK_manager vtkManager;

    std::string filename_to_read;

    SECTION("must read from a vtk file version 1.0 and find 12 elements"){
        filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/ugridex.vtk";
        vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
        REQUIRE(12  == unstructuredGrid->GetNumberOfCells());
        REQUIRE(27 == unstructuredGrid->GetNumberOfPoints());
    }

    SECTION("must read from a vtk file version 2.0 and find 4456 elements"){
        filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/bolt_gmsh.vtk";
        vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
        REQUIRE(4456  == unstructuredGrid->GetNumberOfCells());
        REQUIRE(3630 == unstructuredGrid->GetNumberOfPoints());
    }

    SECTION("must read from a vtk file version 2.0 and find 6688 elements"){
        filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/sphere_snappy.vtk";
        vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
        REQUIRE(6688  == unstructuredGrid->GetNumberOfCells()); // cells
        REQUIRE(3477 == unstructuredGrid->GetNumberOfPoints()); // points
    }

    SECTION("must read vtu file and find "){
        filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/sfera_salome.vtu";
        vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtkManager.readUnstructuredGrid(filename_to_read);
        REQUIRE(278984  == unstructuredGrid->GetNumberOfCells());
        REQUIRE(297081 == unstructuredGrid->GetNumberOfPoints());

    }
}

TEST_CASE("scaled jacobian must be one for a voxel ", "[getQuality][VTK_manager]"){
    const std::string filename_to_read = "/Users/claudia/CLionProjects/3DMesher/Catch_tests/Data/one_folded_hex.vtk";
    VTK_manager vtkManager;

//    Point basepoint = Point(2, 2, 2);
//
//    FT blockLg = 1;
//    LCC_3 lcc;
//    Block_maker blockMaker = Block_maker();
//    const Dart_handle cube = blockMaker.make_cube(lcc, basepoint, blockLg);
//    std::string outputPathFileName = filename_to_read;
//    size_t startIndex = outputPathFileName.find_last_of(".");
//    Writer writer;
//    std::string output_file_extension = outputPathFileName.substr(startIndex + 1,
//                                                                  outputPathFileName.size());
//    std::ofstream vtk_file(outputPathFileName);
//    writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, lcc);


    REQUIRE(1 == vtkManager.getQuality(filename_to_read));
}
