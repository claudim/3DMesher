#include "3D_hex_mesh_algorithms/hex_dom_gmsh_mesh.h"

int main(int argc, char* argv[]) {
    const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
    std::string name = "sfera";
    std::string fileName = data_path + "/" + name + ".stl";


    hex_dom_gmsh_mesh hexDomGmshMesh;
    hexDomGmshMesh.run();

    return EXIT_SUCCESS;
}

