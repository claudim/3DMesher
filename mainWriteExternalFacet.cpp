#include <iostream>
#include <array>
#include <Block_maker.h>
#include <External_facet_finder.h>
#include "VTK_manager.h"
#include "MyLCC.h"

int main(int argc, char* argv[]) {

    if (argc == 3)
    {
        std::string inputPathToVTKFileName = argv[1];

        std::cout << "Loading: " << inputPathToVTKFileName << std::endl;
        VTK_manager vtk_manager;
        std::map<int, int> statistics;

            std::string outputFolderPath = argv[2];

            LCC_3 hex_mesh;
            vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = vtk_manager.readUnstructuredGrid(inputPathToVTKFileName);
            for (vtkIdType i = 0; i < unstructuredGrid->GetNumberOfCells(); i++)
            {
                if(unstructuredGrid->GetCellType(i) == VTK_VOXEL || unstructuredGrid->GetCellType(i) == VTK_HEXAHEDRON) {
                    std::vector<Point> hex_vertices;
                    std::array<double, 3> point{};
                    vtkPoints *vtk_points = unstructuredGrid->GetCell(i)->GetPoints();
                        double point_coordinates[3];
                        vtk_points->GetPoint(0, point_coordinates);
                        Point p0 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(1, point_coordinates);
                        Point p1 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(2, point_coordinates);
                        Point p2 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(3, point_coordinates);
                        Point p3 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(4, point_coordinates);
                        Point p4 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(5, point_coordinates);
                        Point p5 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(6, point_coordinates);
                        Point p6 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);
                        vtk_points->GetPoint(7, point_coordinates);
                        Point p7 = Point(point_coordinates[0], point_coordinates[1], point_coordinates[2]);

                        hex_vertices.emplace_back(p0);
                        hex_vertices.emplace_back(p1);
                        hex_vertices.emplace_back(p2);
                        hex_vertices.emplace_back(p3);
                        hex_vertices.emplace_back(p7);
                        hex_vertices.emplace_back(p4);
                        hex_vertices.emplace_back(p5);
                        hex_vertices.emplace_back(p6);
                        Block_maker block_maker;
                        block_maker.make_block(hex_mesh, hex_vertices);
                }
            }
            //sew all the created hexahedra
            hex_mesh.sew3_same_facets();

            External_facet_finder externalFacetFinder;
            const std::vector<Dart_handle>  external_facets = externalFacetFinder.findFacets(hex_mesh);
            unsigned long numberOfExternalFacets = external_facets.size();
           // std::cout<< "facce esterne : "<< numberOfExternalFacets <<std::endl;
        std::string fileName_without_extension = "";
        if (inputPathToVTKFileName.find_last_of("/") != std::string::npos) {
            fileName_without_extension = inputPathToVTKFileName.substr((inputPathToVTKFileName.find_last_of("/")+1));
            fileName_without_extension.replace(fileName_without_extension.size()-4, 4,"" );
        }
        std::ofstream externalFacetsFile;
        std::string statistics_file_name = outputFolderPath +  fileName_without_extension + "_externalFacet.txt";
        externalFacetsFile.open(statistics_file_name, std::ios::out);
        externalFacetsFile << "This is the external facets file of the mesh stored in " << inputPathToVTKFileName << ".\n";
        externalFacetsFile << "External facets: " << numberOfExternalFacets << "\n";
        externalFacetsFile.close();
    }
    return EXIT_SUCCESS;
}
