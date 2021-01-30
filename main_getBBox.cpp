

#include <string>
#include "STL_reader.h"
#include "CGAL/Polygon_mesh_processing/bbox.h"
#include "MyLCC.h"

int main(int argc, char* argv[]) {
    const std::string data_path = "/home/claudia/CLionProjects/3DMesher/DataInput";
    std::string name = "bolt";
    std::string fileName = data_path + "/" + name + ".stl";
    try {
        // Get starting timepoint
        auto start_reading = std::chrono::high_resolution_clock::now();

        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        const Polyhedron polyhedron = reader.read(fileName);

        // Get ending timepoint
        auto stop_reading = std::chrono::high_resolution_clock::now();

        // Get duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop_reading - start_reading);

        std::cout << "Time taken by read function is : "
                  << duration.count() << " microseconds" << std::endl;

        int resolution = 8;
        //int resolution = 24;

        double grid_dimension;

        typedef CGAL::Bbox_3 Bbox;
        Bbox grid_box;

        const CGAL::Bbox_3 &polyhedron_bbox3 = CGAL::Polygon_mesh_processing::bbox(polyhedron);

        double delta_x = polyhedron_bbox3.xmax() - polyhedron_bbox3.xmin();
        double delta_y = polyhedron_bbox3.ymax() - polyhedron_bbox3.ymin();
        double delta_z = polyhedron_bbox3.zmax() - polyhedron_bbox3.zmin();

        grid_dimension = std::min(std::min(delta_y, delta_z), delta_x) / resolution;


        grid_box = CGAL::Bbox_3(polyhedron_bbox3.xmin() - grid_dimension,
                                polyhedron_bbox3.ymin() - grid_dimension,
                                polyhedron_bbox3.zmin() - grid_dimension,
                                polyhedron_bbox3.xmax() + grid_dimension,
                                polyhedron_bbox3.ymax() + grid_dimension,
                                polyhedron_bbox3.zmax() + grid_dimension);
        double delta_x_grid = grid_box.xmax() - grid_box.xmin();
        double delta_y_grid = grid_box.ymax() - grid_box.ymin();
        double delta_z_grid = grid_box.zmax() - grid_box.zmin();

        double x_dimension = delta_x_grid;
        double y_dimension = delta_y_grid;
        double z_dimension = delta_z_grid;

        Point centroid = Point(grid_box.xmin() + x_dimension / 2,
                              grid_box.ymin() + y_dimension / 2,
                              grid_box.zmin() + z_dimension / 2);

        double number_of_x_nodes = round(x_dimension / grid_dimension);
        double number_of_y_nodes = round(y_dimension / grid_dimension);
        double number_of_z_nodes = round(z_dimension / grid_dimension);

        std::cout << "x_min is : " << polyhedron_bbox3.xmin() << std::endl;
        std::cout << "y_min is : " << polyhedron_bbox3.ymin() << std::endl;
        std::cout << "z_min is : " << polyhedron_bbox3.zmin() << std::endl;
        std::cout << "x_max is : " << polyhedron_bbox3.xmax() << std::endl;
        std::cout << "y_max is : " << polyhedron_bbox3.ymax() << std::endl;
        std::cout << "z_max is : " << polyhedron_bbox3.zmax() << std::endl;
        std::cout << "Centroid is : " << centroid << std::endl;
        std::cout << "numberod cell in x is : " << number_of_x_nodes << std::endl;
        std::cout << "numberod cell in y is : " << number_of_y_nodes << std::endl;
        std::cout << "numberod cell in z is : " << number_of_z_nodes << std::endl;

    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }

    return EXIT_SUCCESS;
}

