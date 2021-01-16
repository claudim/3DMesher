
#include "../Include/catch.hpp"
#include "test_config.h"
#include "Writer.h"
#include <Block_maker.h>


TEST_CASE("must write a .vtk file", "[output_to_legacy_vtk_ascii_unstructured][Writer]") {

    LCC_3 hex_mesh;
    Block_maker blockMaker;
    FT lg = 1;
    blockMaker.make_cube(hex_mesh, Point(0,0,0), lg);

    std::string name = "unit_cube";
    const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/TestOutput/";
    std::string outputFileName = out_data_path + "/" + name + ".vtk";

    std::ofstream vtk_file(outputFileName);
    Writer writer;
    writer.output_to_legacy_vtk_ascii_unstructured(vtk_file, hex_mesh);
    vtk_file.close();

}