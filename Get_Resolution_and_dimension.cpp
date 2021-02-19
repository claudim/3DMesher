#include <iostream>
#include "MyLCC.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include "STL_reader.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_with_features_3<K> Mesh_Domain;
//typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron,K> Mesh_Domain;
typedef CGAL::Mesh_triangulation_3<Mesh_Domain, CGAL::Default>::type Tr;

using namespace CGAL::parameters;

int main(int argc, char* argv[]) {
    try {
        if (argc == 3) {
            std::string inputPathFileName = argv[1]; // filename is path to filename with extension
            double frequency_in_GHz = std::stod(argv[2]);
            double light_speed = 0.30; // sarebbe 3e8 così posso dividerlo con la frequenza
            double lambda = light_speed/frequency_in_GHz;

            double grid_dimension1 = lambda/20;
            double grid_dimension2 = lambda/30;
            double grid_dimension3 = lambda/40;
            double grid_dimension4 = lambda/50;

            std::cout << "lambda su 20: " << grid_dimension1<<std::endl;
            std::cout << "lambda su 30: " << grid_dimension2<<std::endl;
            std::cout << "lambda su 40: " << grid_dimension3<<std::endl;
            std::cout << "lambda su 50: " << grid_dimension4<<std::endl;

            size_t startIndex = inputPathFileName.find_last_of(".");
            std::string fileName_extension = inputPathFileName.substr((startIndex + 1), (inputPathFileName.size()));

            // read input from file
            Polyhedron polyhedron;
            if (fileName_extension == "stl") {
                std::ofstream resolution_and_dimesion_file;

                std::cout << "file " << inputPathFileName << std::endl;
                STL_reader reader;
                polyhedron = reader.read(inputPathFileName);

                typedef CGAL::Bbox_3 Bbox;
                Bbox grid_box;

                const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);

                double delta_x = polyhedron_bbox3.xmax() - polyhedron_bbox3.xmin();
                double delta_y = polyhedron_bbox3.ymax() - polyhedron_bbox3.ymin();
                double delta_z = polyhedron_bbox3.zmax() - polyhedron_bbox3.zmin();
                std::cout<<delta_x<<std::endl;
                //moltiplico per mille perchè lamba è metro/secondo e  delta è in mm
                double resolution1 = 1000 * std::min(std::min(delta_y, delta_z), delta_x) / grid_dimension1;
                double resolution2 = 1000 * std::min(std::min(delta_y, delta_z), delta_x) / grid_dimension2;
                double resolution3 = 1000 * std::min(std::min(delta_y, delta_z), delta_x) / grid_dimension3;
                double resolution4 = 1000 * std::min(std::min(delta_y, delta_z), delta_x) / grid_dimension4;

                // path/file.ext
                std::size_t lastSlashPosition = inputPathFileName.find_last_of("/");
                std::string filenameWithExtension = inputPathFileName;
                if(lastSlashPosition != std::string::npos)
                    filenameWithExtension = inputPathFileName.substr(lastSlashPosition + 1);
                //file.ext
                std::size_t dotPosition = inputPathFileName.find_last_of(".");
                std::string filename = filenameWithExtension.substr(0, dotPosition);
                //file
                resolution_and_dimesion_file.open(filename + "_resolutions.txt");
                resolution_and_dimesion_file << "Frequency " + std::to_string(frequency_in_GHz) + "\n";
                resolution_and_dimesion_file << "Resolution L/20: " + std::to_string(resolution1) +  "\n";
                resolution_and_dimesion_file << "Resolution L/30: " + std::to_string(resolution2) +  "\n";
                resolution_and_dimesion_file << "Resolution L/40: " + std::to_string(resolution3) +  "\n";
                resolution_and_dimesion_file << "Resolution L/50: " + std::to_string(resolution4) +  "\n";
                resolution_and_dimesion_file.close();

            }
        }
    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
