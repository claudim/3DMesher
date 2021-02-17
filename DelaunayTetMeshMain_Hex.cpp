
#include <iostream>

#include "MyLCC.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/boost/graph/helpers.h>
#include <CGAL/Polyhedral_mesh_domain_with_features_3.h>
#include <CGAL/make_mesh_3.h>
#include "STL_reader.h"
#include "Writer.h"



typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::Mesh_polyhedron_3<K>::type Polyhedron;
typedef CGAL::Polyhedral_mesh_domain_with_features_3<K> Mesh_Domain;
//typedef CGAL::Polyhedral_mesh_domain_3<Polyhedron,K> Mesh_Domain;
typedef CGAL::Mesh_triangulation_3<Mesh_Domain, CGAL::Default>::type Tr;
//typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;
typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;
typedef CGAL::Mesh_criteria_3<Tr> Mesh_Criteria;

using namespace CGAL::parameters;

int main(int argc, char* argv[]) {
    try {

        const std::string data_path = "/Users/claudia/CLionProjects/3DMesher/DataInput";
        //std::string fileName = data_path + "/cubeTest.stl";
        //const char* fname = (argc>1)?argv[1]:"sfera.off";
        //std::string fileName = data_path + "/sphere.off";
        //std::string name = "cube100x100axisAligned";
        //std::string name = "bone";
        std::string name = "bolt";
        std::string fileName = data_path + "/" + name + ".stl";

        // read input from file
        //OFF_Reader reader;
        STL_reader reader;
        const Polyhedron polyhedron = reader.read(fileName);

        //Create domain
        Mesh_Domain domain(polyhedron);

        //Get sharp features
        domain.detect_features();

        //bolt criteria
        Mesh_Criteria criteria(facet_angle = 30, cell_radius_edge_ratio = 2);
        //bone criteria
        //Mesh_Criteria criteria(facet_angle=30, facet_size=0.1, facet_distance=0.025,cell_radius_edge_ratio=2, cell_size=0.1);
        //Mesh_Criteria criteria(facet_angle=30, cell_radius_edge_ratio=2, facet_size=0.1);

        //Mesh generation
        C3t3 c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria, no_perturb(), no_exude());
//        std::cout << "numero di celle: " << c3t3.number_of_cells() << std::endl;
//        std::cout << "numero di vertici: " << c3t3.number_of_vertices_in_complex() << std::endl;
//        std::cout << "numero di corners: " << c3t3.number_of_corners() << std::endl;
//        std::cout << "numero di edges: " << c3t3.number_of_edges() << std::endl;
//        std::cout << "numero di facets: " << c3t3.number_of_facets() << std::endl;
//        std::cout << "numero di facets in complex: " << c3t3.number_of_facets_in_complex() << std::endl;


        LCC_3 hex_mesh;
        //per ogni tetraedro
        for( C3t3::Cells_in_complex_iterator cell_it =  c3t3.cells_in_complex_begin();
             cell_it !=  c3t3.cells_in_complex_end();
             ++cell_it) {
            //tet vertices
            Point p0 = Point(cell_it->vertex(0)->point().x(), cell_it->vertex(0)->point().y(),cell_it->vertex(0)->point().z());
            Point p1 = Point(cell_it->vertex(1)->point().x(), cell_it->vertex(1)->point().y(),cell_it->vertex(1)->point().z());
            Point p2 = Point(cell_it->vertex(2)->point().x(), cell_it->vertex(2)->point().y(), cell_it->vertex(2)->point().z());
            Point p3 = Point(cell_it->vertex(3)->point().x(), cell_it->vertex(3)->point().y(),cell_it->vertex(3)->point().z());

            //tet centroid
            Point tet_centroid = CGAL::centroid(p0,p1,p2,p3);

            // edge midpoints
            Point midPoint_p0p1 = CGAL::midpoint(p0,p1);
            Point midPoint_p0p2 = CGAL::midpoint(p0,p2);
            Point midPoint_p0p3 = CGAL::midpoint(p0,p3);
            Point midPoint_p1p2 = CGAL::midpoint(p1,p2);
            Point midPoint_p1p3 = CGAL::midpoint(p1,p3);
            Point midPoint_p2p3 = CGAL::midpoint(p2,p3);

            //facet midpoints
            Point centroid_p0p1p2 = CGAL::centroid(p0,p1,p2);
            Point centroid_p0p1p3 = CGAL::centroid(p0,p1,p3);
            Point centroid_p0p2p3 = CGAL::centroid(p0,p2,p3);
            Point centroid_p1p2p3 = CGAL::centroid(p1,p2,p3);

            hex_mesh.make_hexahedron(p0, midPoint_p0p1,centroid_p0p1p2, midPoint_p0p2,centroid_p0p2p3,midPoint_p0p3, centroid_p0p1p3, tet_centroid);
            hex_mesh.make_hexahedron(p1, midPoint_p1p2,centroid_p0p1p2, midPoint_p0p1,centroid_p0p1p3,midPoint_p1p3, centroid_p1p2p3, tet_centroid);
            hex_mesh.make_hexahedron(p2, midPoint_p0p2,centroid_p0p1p2, midPoint_p1p2,centroid_p1p2p3,midPoint_p2p3, centroid_p0p2p3, tet_centroid);
            hex_mesh.make_hexahedron(p3, midPoint_p0p3,centroid_p0p2p3, midPoint_p2p3,centroid_p1p2p3,midPoint_p1p3, centroid_p0p1p3, tet_centroid);

        }
        //sew all the created hexahedra
        hex_mesh.sew3_same_facets();

        //Output
        const std::string out_data_path = "/Users/claudia/CLionProjects/3DMesher/MeshOutput/DelaunayTetMeshOutput";
        std::string outputFileName = out_data_path + "/" + name + ".mesh";
        std::ofstream medit_file(outputFileName);
        c3t3.output_to_medit(medit_file);
        medit_file.close();

        Writer hex_writer;
        std::string outputFileName2 = out_data_path + "/" + name + "split_from_tet.mesh";
        std::ofstream medit_file2(outputFileName2);
        hex_writer.output_to_medit(medit_file2, hex_mesh);
        medit_file2.close();

    }
    catch (std::ios_base::failure e) {
        std::cerr << "Exception opening/reading/closing file\n";
    }
    return EXIT_SUCCESS;
}
