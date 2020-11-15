

#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/helpers.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/make_mesh_3.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_with_features_3<K> Mesh_Domain;
//typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron,K> Mesh_Domain;
typedef CGAL::Mesh_triangulation_3<Mesh_Domain, CGAL::Default>::type Tr;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;
typedef CGAL::Mesh_criteria_3<Tr> Mesh_Criteria;

using namespace CGAL::parameters;

int main(int argc, char* argv[]) {
    try {

        const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
        //std::string fileName = data_path + "/cubeTest.stl";
        //const char* fname = (argc>1)?argv[1]:"sfera.off";
        //std::string fileName = data_path + "/sphere.off";
        std::string name = "cube100x100axisAligned";
        std::string fileName = data_path + "/" + name + ".stl";

        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        const Polyhedron polyhedron = reader.read(fileName);

        //Create domain
        Mesh_Domain domain(polyhedron);

        //Get sharp features
        domain.detect_features();

        //Cube Pyramide Mesh Criteria
        //es1
        Mesh_Criteria criteria(facet_angle = 30, cell_radius_edge_ratio = 2);
        //Mesh_Criteria criteria(facet_angle=30, cell_radius_edge_ratio=2, facet_size=0.1);

        //Mesh generation
        C3t3 c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());
//        std::cout << "numero di celle: " << c3t3.number_of_cells() << std::endl;
//        std::cout << "numero di vertici: " << c3t3.number_of_vertices_in_complex() << std::endl;
//        std::cout << "numero di corners: " << c3t3.number_of_corners() << std::endl;
//        std::cout << "numero di edges: " << c3t3.number_of_edges() << std::endl;
//        std::cout << "numero di facets: " << c3t3.number_of_facets() << std::endl;
//        std::cout << "numero di facets in complex: " << c3t3.number_of_facets_in_complex() << std::endl;

        //Output
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/DelaunayTetMeshOutput";
        std::string outputFileName = out_data_path + "/" + name + ".mesh";
        std::ofstream medit_file(outputFileName);
        c3t3.output_to_medit(medit_file);
        medit_file.close();


    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
